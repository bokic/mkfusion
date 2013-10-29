#include "qcfworkerthread.h"
#include "qmkfusionexception.h"
#include "cffunctions.h"
#include "qhttpcodec.h"
#include "qcfserver.h"
#include "qcflog.h"

#include <QDataStream>
#include <QStringList>
#include <QUrlQuery>
#include <QPair>
#include <QDir>


QCFWorkerThread::QCFWorkerThread(QObject *parent)
    : QThread(parent)
    , m_APPLICATION(nullptr)
    , m_SESSION(nullptr)
    , m_StatusCode(200)
    , m_HeadersSent(false)
    , m_Socket(nullptr)
    , m_CFDump(false)
{
}

QCFWorkerThread::~QCFWorkerThread()
{
    m_APPLICATION = nullptr;
    m_SESSION = nullptr;

    if (m_Socket)
    {
        m_Socket->deleteLater();
        m_Socket = nullptr;
    }
}

void QCFWorkerThread::setSocket(QLocalSocket *socket)
{
    if (m_Socket)
    {
        QCFLOG(CFLOG_WORKER, QCFLOG_ERROR, "m_Socket NOT null at QCFWorkerThread::setSocket. Memory might leak.");
    }

    m_Socket = socket;
    m_Socket->setParent(nullptr);
    m_Socket->moveToThread(this);
    //m_Socket->setParent(this);
}

void QCFWorkerThread::run()
{
    QCFLOG(CFLOG_WORKER, QCFLOG_INFO_PERF, "Worker thread started.");

    try
    {
        if (!readRequest())
        {
            QCFLOG(CFLOG_WORKER, QCFLOG_ERROR, "Reading worker request failed.");

            throw QMKFusionException("Read request failed.");
        }

        updateVariables();

        runApplicationTemplate();

        if (m_StatusCode == 200)
        {
            executePage();
        }
    }
    catch (const QMKFusionCFAbortException &ex)
    {
        Q_UNUSED(ex);
    }
    catch (const QMKFusionTemplateException &ex)
    {
        m_StatusCode = 500;

        writeException(ex);
    }
    catch (const QMKFusionException &ex)
    {
        m_StatusCode = 500;

        writeException(ex);
    }
#ifndef QT_DEBUG
    catch(...)
    {
        m_StatusCode = 500;

        writeException(QMKFusionException("Internal error."));
    }
#endif

    writeResponse();

    m_Socket->close();

    setPriority(QThread::LowPriority);

    QCFLOG(CFLOG_WORKER, QCFLOG_INFO_PERF, "Worker thread ended.");
}

void QCFWorkerThread::executePage()
{
    QCFLOG(CFLOG_WORKER, QCFLOG_WARNING, "Empty QCFWorkerThread::executePage() has been executed.");
}

void QCFWorkerThread::processPostData(QByteArray post)
{
    m_FORM.setType(QCFVariant::Struct);

    if (!m_Request.m_ContentType.isEmpty())
    {
        if (m_Request.m_ContentType.startsWith("application/x-www-form-urlencoded"))
        {
            for(const QByteArray &item : post.split('&'))
            {
                if (item.isEmpty())
                {
                    continue;
                }

                QList<QPair<QString, QString>> pairs = QUrlQuery(item).queryItems();

                if (pairs.length() != 1)
                {
                    throw QMKFusionException("Invalid application/x-www-form-urlencoded POST item.");
                }

                QPair<QString, QString> pair = pairs.takeFirst();

                QString key = pair.first;
                QString value = pair.second;

                if (pair.first.isEmpty())
                {
                    throw QMKFusionException("Invalid application/x-www-form-urlencoded POST item name.");
                }

                updateVariableQStr(m_FORM, key, value);
            }
        }
        else if (m_Request.m_ContentType.startsWith("multipart/form-data"))
        {
            int tmp1 = post.indexOf("\r\n");

            if (tmp1 <= 0)
            {
                throw QMKFusionException("Invalid boundary line in POST method.");
            }

            QByteArray boundary = post.left(tmp1);
            QByteArray stWith = post.left(tmp1 + 2);
            QByteArray separator = "\r\n" + post.left(tmp1 + 2);
            QByteArray enWith = "\r\n" + post.right(tmp1 + 4);

            if ((!post.startsWith(stWith))||(!post.endsWith(enWith))||(stWith != boundary + "\r\n")||(enWith != "\r\n" + boundary + "--\r\n"))
            {
                throw QMKFusionException("Corrupted POST method.");
            }

            post = post.mid(stWith.length(), post.length() - stWith.length() - enWith.length());

            QList<QByteArray> formFields;

            int index;

            while ((index = post.indexOf(separator)) >= 0)
            {
                formFields.push_back(post.left(index));
                post.remove(0, index + separator.length());
            }

            formFields.push_back(post);

            for(QByteArray formField : formFields)
            {
                QHttpCodec codec = QHttpCodec::decodeFromByteArray(formField);

                if (!codec.isValid())
                {
                    throw QMKFusionException("Corrupted POST method(Form field NOT valid).");
                }

                if (!codec.contansHeaderKey("Content-Disposition"))
                {
                    throw QMKFusionException("Corrupted POST method(Content-Disposition is missing).");
                }

                const QHttpCodecValue *headerKeyValue = codec.getHeaderKey("Content-Disposition")->getValue("form-data");

                if (codec.contansHeaderKey("Content-Type"))
                {
                    // file upload.
                    QString key = headerKeyValue->getParameterValue("name").toUpper();

                    if (!headerKeyValue->getParameterValue("filename").isEmpty())
                    {
                        m_FileUpload[key] = QCFFileUpload();
                        QCFFileUpload *item = &m_FileUpload[key];

                        item->createTmpFile();

                        if (item->m_File->open() == false)
                        {
                            throw QMKFusionException("Can\'t create temponary file.");
                        }

                        if (item->m_File->write(codec.getBody()) != codec.getBody().length())
                        {
                            throw QMKFusionException("Temponary file didn\'t write all data.");
                        }

                        item->m_File->close();

                        item->m_ContentType = codec.getHeaderKey("Content-Type")->values.at(0).value;
                        item->m_Filename = headerKeyValue->getParameterValue("filename");

                        m_FORM.m_Struct->insert(key, QDir::toNativeSeparators(item->m_File->fileName()));
                    }
                    else
                    {
                        m_FORM.m_Struct->insert(key, L"");
                    }
                }
                else
                {
                    QString key = headerKeyValue->getParameterValue("name").toUpper();
                    QString value = QString::fromUtf8(codec.getBody());

                    m_FORM.m_Struct->insert(key, value);
                }
            }
        }
        else
        {
            throw QMKFusionException("Unsupported Content-Type in POST method.");
        }
    }
}

bool QCFWorkerThread::readRequest()
{
    bool l_FoundRecieveBufSize = false;
    QByteArray l_RecievedBuffer;
    qint64 l_RecieveBufSize = 0;

    forever
    {
        if (m_Socket->bytesAvailable() == 0)
        {
            m_Socket->waitForReadyRead(100);
        }

        if(!m_Socket->isOpen())
        {
            return false;
        }

        l_RecievedBuffer.append(m_Socket->readAll());
        if ((l_FoundRecieveBufSize == false)&&(l_RecievedBuffer.size() >= (int)sizeof(qint64)))
        {
            QDataStream l_ds(&l_RecievedBuffer, QIODevice::ReadOnly);
            l_ds.setVersion(QDataStream::Qt_5_0);

            l_ds >> l_RecieveBufSize;

            if (l_RecieveBufSize < 0)
            {
                return false;
            }

            if (l_RecieveBufSize > 10485760) // 10MB
            {
                return false;
            }

            l_FoundRecieveBufSize = true;
        }

        if ((l_FoundRecieveBufSize == true)&&(l_RecievedBuffer.size() >= l_RecieveBufSize))
        {
            break;
        }
    }

    //if (l_FoundRecieveBufSize)
    //{
    //    return false;
    //}

    QDataStream l_ds(&l_RecievedBuffer, QIODevice::ReadOnly);
    l_ds.setVersion(QDataStream::Qt_5_0);

    char *tempstr;
    int tempint;
    QByteArray tempba;

    l_ds >> l_RecieveBufSize;

    l_ds >> tempstr;
    if (tempstr)
    {
        m_Request.m_AuthType = QString::fromUtf8(tempstr);
        delete[] tempstr;
    }

    l_ds >> tempstr;
    if (tempstr)
    {
        m_Request.m_User = QString::fromUtf8(tempstr);
        delete[] tempstr;
    }

    //l_ds >> tempba;
    //if (!tempba.isEmpty())
    //{
    //    m_Request.m_Filename = QString::fromUtf8(tempba.constData());
    //    tempba.clear();
    //}

    l_ds >> tempstr;
    if (tempstr)
    {
        m_Request.m_Accept = QString::fromUtf8(tempstr);
        delete[] tempstr;
    }

    l_ds >> tempstr;
    if (tempstr)
    {
        m_Request.m_AcceptEncoding = QString::fromUtf8(tempstr);
        delete[] tempstr;
    }

    l_ds >> tempstr;
    if (tempstr)
    {
        m_Request.m_AcceptLanguage = QString::fromUtf8(tempstr);
        delete[] tempstr;
    }

    l_ds >> tempstr;
    if (tempstr)
    {
        m_Request.m_Connection = QString::fromUtf8(tempstr);
        delete[] tempstr;
    }

    l_ds >> tempstr;
    if (tempstr)
    {
        m_Request.m_ContentType = QString::fromUtf8(tempstr);
        delete[] tempstr;
    }

    l_ds >> tempstr;
    if (tempstr)
    {
        m_Request.m_RemoteHost = QString::fromUtf8(tempstr);
        delete[] tempstr;
    }

    l_ds >> tempstr;
    if (tempstr)
    {
        m_Request.m_Referer = QString::fromUtf8(tempstr);
        delete[] tempstr;
    }

    l_ds >> tempstr;
    if (tempstr)
    {
        m_Request.m_UserAgent = QString::fromUtf8(tempstr);
        delete[] tempstr;
    }

    l_ds >> tempstr;
    if (tempstr)
    {
        m_Request.m_Cookie = QString::fromUtf8(tempstr);
        delete[] tempstr;
    }

    l_ds >> tempint;
    if (tempint > 0)
    {
        QByteArray postData;
        l_ds >> postData;

        processPostData(postData);
    }
    else if (tempint < 0)
    {
        throw QMKFusionException("Invalid POST data size.");
    }

    l_ds >> tempstr;
    if (tempstr)
    {
        m_Request.m_Args = QString::fromUtf8(tempstr);
        delete[] tempstr;
    }

    l_ds >> tempstr;
    if (tempstr)
    {
        m_Request.m_Method = QString::fromUtf8(tempstr);
        delete[] tempstr;
    }

    l_ds >> tempstr;
    if (tempstr)
    {
        m_Request.m_Protocol = QString::fromUtf8(tempstr);
        delete[] tempstr;
    }

    l_ds >> tempstr;
    if (tempstr)
    {
        m_Request.m_Host = QString::fromUtf8(tempstr);
        delete[] tempstr;
    }

    l_ds >> tempstr;
    if (tempstr)
    {
        m_Request.m_URI = QString::fromUtf8(tempstr);
        delete[] tempstr;
    }

    l_RecievedBuffer.clear();
    l_RecieveBufSize = 0;

    return true;
}

bool QCFWorkerThread::writeResponse()
{
    if (!m_HeadersSent)
    {
        QByteArray l_header;
        QDataStream l_headerDataStream(&l_header, QIODevice::WriteOnly);
        l_headerDataStream.setVersion(QDataStream::Qt_5_0);

        l_headerDataStream << (qint32) 0;
        l_headerDataStream << m_ContentType;

        l_headerDataStream << m_StatusCode;

        if (m_SetCookies.m_Type == QCFVariant::Struct)
        {
            for(const QString &key : m_SetCookies.m_Struct->keys())
            {
                if (m_COOKIE.m_Struct->contains(key))
                {
                    m_COOKIE.m_Struct->remove(key);
                }

                const QCFVariant cookieData = m_SetCookies.m_Struct->value(key);

                if (cookieData.m_Struct->value("expires").m_Type == QCFVariant::Number)
                {
                    m_Header.insert("Set-Cookie", QUrl::toPercentEncoding(key) + "=" + QUrl::toPercentEncoding(cookieData.m_Struct->value("value").toString()) +  ";Max-Age=" + cookieData.m_Struct->value("expires").toString() + ";path=/");
                }
                else
                {
                    m_Header.insert("Set-Cookie", QUrl::toPercentEncoding(key) + "=" + QUrl::toPercentEncoding(cookieData.m_Struct->value("value").toString()) +  ";expires=" + cookieData.m_Struct->value("expires").toString() + ";path=/");
                }
            }
        }

        if (m_COOKIE.m_Type == QCFVariant::Struct)
        {
            for(const QString &key : m_COOKIE.m_Struct->keys())
            { // TODO: Unhardcode Max-Age.
                m_Header.insert("Set-Cookie", QUrl::toPercentEncoding(key) + "=" + QUrl::toPercentEncoding(m_COOKIE[key].toString()) + "; Max-Age=3600; Path=/; HttpOnly");
            }
        }

        l_headerDataStream << (qint32) m_Header.size();
        for(int c = 0; c < m_Header.count(); c++)
        {
            l_headerDataStream << m_Header.keys().at(c);
            l_headerDataStream << m_Header.values().at(c);
        }

        l_headerDataStream.device()->seek(0);
        l_headerDataStream << (qint32) l_header.size();

        m_Socket->write(l_header);

        m_Socket->waitForBytesWritten(-1);

        m_HeadersSent = true;
    }

    QByteArray l_SendBuf = m_Output.toUtf8(); // TODO: utf-8 output hardcoded
    int l_SendBufPos = 0;

    while(l_SendBuf.size() > l_SendBufPos)
    {
        if (m_Socket->write(l_SendBuf.mid(l_SendBufPos, 1024)) == -1)
        {
            break;
        }
        m_Socket->waitForBytesWritten(-1);

        l_SendBufPos += 1024;
    }

    return true;
}

void QCFWorkerThread::writeException(const QMKFusionException &ex)
{
    m_Output.append("<font style=\"COLOR: black; FONT: 16pt/18pt verdana\">The web site you are accessing has experienced an unexpected error.<br>Please contact the website administrator.</font>\n");
    m_Output.append("<br>\n");
    m_Output.append("<br>\n");
    m_Output.append("<table border=\"1\" cellpadding=\"3\" bordercolor=\"#000808\" bgcolor=\"#e7e7e7\">\n");
    m_Output.append("\t<tr>\n");
    m_Output.append("\t\t<td bgcolor=\"#000066\">\n");
    m_Output.append("\t\t\t<font style=\"COLOR: white; FONT: 11pt/13pt verdana\" color=\"white\">The following information is meant for the website developer for debugging purposes.</font>\n");
    m_Output.append("\t\t</td>\n");
    m_Output.append("\t<tr>\n");
    m_Output.append("\t<tr>\n");
    m_Output.append("\t\t<td bgcolor=\"#4646EE\">\n");
    m_Output.append("\t\t\t<font style=\"COLOR: white; FONT: 11pt/13pt verdana\" color=\"white\">Error Occurred While Processing Request</font>\n");
    m_Output.append("\t\t</td>\n");
    m_Output.append("\t</tr>\n");
    m_Output.append("\t<tr>\n");
    m_Output.append("\t\t<td>\n");
    m_Output.append("\t\t\t<font style=\"COLOR: black; FONT: 8pt/11pt verdana\">\n");
    m_Output.append("\t\t\t\t<table width=\"500\" cellpadding=\"0\" cellspacing=\"0\" border=\"0\">\n");
    m_Output.append("\t\t\t\t\t<tr>\n");
    m_Output.append("\t\t\t\t\t\t<td id=\"tableProps2\" align=\"left\" valign=\"middle\" width=\"500\">\n");
    m_Output.append("\t\t\t\t\t\t\t<h1 id=\"textSection1\" style=\"COLOR: black; FONT: 13pt/15pt verdana\">" + ex.m_Message.toHtmlEscaped() + "</h1>\n");
    m_Output.append("\t\t\t\t\t\t\t" + ex.m_Detail.toHtmlEscaped() + "\n");
    m_Output.append("\t\t\t\t\t\t</td>\n");
    m_Output.append("\t\t\t\t\t</tr>\n");
    m_Output.append("\t\t\t\t\t<tr>\n");
    m_Output.append("\t\t\t\t\t\t<td id=\"tablePropsWidth\" width=\"400\" colspan=\"2\">\n");
    m_Output.append("\t\t\t\t\t\t\t<font style=\"COLOR: black; FONT: 8pt/11pt verdana\"></font>\n");
    m_Output.append("\t\t\t\t\t\t</td>\n");
    m_Output.append("\t\t\t\t\t</tr>\n");
    m_Output.append("\t\t\t\t\t<tr>\n");
    m_Output.append("\t\t\t\t\t\t<td height>&nbsp;</td>\n");
    m_Output.append("\t\t\t\t\t</tr>\n");
    m_Output.append("\t\t\t\t\t<tr>\n");
    m_Output.append("\t\t\t\t\t\t<td colspan=\"2\">\n");
    m_Output.append("\t\t\t\t\t\t\t<font style=\"COLOR: black; FONT: 8pt/11pt verdana\">\n");
    m_Output.append("\t\t\t\t\t\t\t\tResources:\n");
    m_Output.append("\t\t\t\t\t\t\t\t<ul>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<li>Enable Robust Exception Information to provide greater detail about the source of errors.  In the Administrator, click Debugging & Logging > Debug Output Settings, and select the Robust Exception Information option.</li>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<li>Check the <a href='http://www.bokicsoft.com/mkfusion/docs/' target=\"new\">ColdFusion documentation</a> to verify that you are using the correct syntax.</li>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<li>Search the <a href='http://www.bokicsoft.com/mkfusion/kb/' target=\"new\">Knowledge Base</a> to find a solution to your problem.</li>\n");
    m_Output.append("\t\t\t\t\t\t\t\t</ul>\n");
    m_Output.append("\t\t\t\t\t\t\t</font>\n");
    m_Output.append("\t\t\t\t\t\t</td>\n");
    m_Output.append("\t\t\t\t\t</tr>\n");
    m_Output.append("\t\t\t\t\t<tr>\n");
    m_Output.append("\t\t\t\t\t\t<td colspan=\"2\">\n");
    m_Output.append("\t\t\t\t\t\t\t<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\">\n");
    m_Output.append("\t\t\t\t\t\t\t\t<tr>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">Browser&nbsp;&nbsp;</td>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">" + m_Request.m_UserAgent.toHtmlEscaped() + "</td>\n");
    m_Output.append("\t\t\t\t\t\t\t\t</tr>\n");
    m_Output.append("\t\t\t\t\t\t\t\t<tr>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">Remote Address&nbsp;&nbsp;</td>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">" + m_Request.m_Host.toHtmlEscaped() + "</td>\n");
    m_Output.append("\t\t\t\t\t\t\t\t</tr>\n");
    m_Output.append("\t\t\t\t\t\t\t\t<tr>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">Referrer&nbsp;&nbsp;</td>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">" + m_Request.m_Referer.toHtmlEscaped() + "</td>\n");
    m_Output.append("\t\t\t\t\t\t\t\t</tr>\n");
    m_Output.append("\t\t\t\t\t\t\t\t<tr>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">Date/Time&nbsp;&nbsp;</td>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">" + QDateTime::currentDateTime().toString("dd-MMM-yy hh:mm AP").toHtmlEscaped() + "</td>\n");
    m_Output.append("\t\t\t\t\t\t\t\t</tr>\n");
    m_Output.append("\t\t\t\t\t\t\t</table>\n");
    m_Output.append("\t\t\t\t\t\t</td>\n");
    m_Output.append("\t\t\t\t\t</tr>\n");
    m_Output.append("\t\t\t\t</table>\n");
    m_Output.append("\t\t\t</font>\n");
    m_Output.append("\t\t</td>\n");
    m_Output.append("\t</tr>\n");
    m_Output.append("</table>\n");
}

void QCFWorkerThread::runApplicationTemplate()
{
    //executePage();
}

void QCFWorkerThread::updateVariables()
{
    m_SERVER.setType(QCFVariant::Struct);
    m_COOKIE.setType(QCFVariant::Struct);
    m_CGI.setType(QCFVariant::Struct);
    m_VARIABLES.setType(QCFVariant::Struct);
    m_URL.setType(QCFVariant::Struct);
    m_SetCookies.setType(QCFVariant::Struct);

    if (m_Request.m_Method == "GET")
    {
        m_FORM.setType(QCFVariant::Error);
        m_VARIABLES.m_HiddenScopeLast1 = &m_URL;
        m_VARIABLES.m_HiddenScopeLast2 = &m_COOKIE;

    }
    else if (m_Request.m_Method == "POST")
    {
        m_VARIABLES.m_HiddenScopeLast1 = &m_FORM;
        m_VARIABLES.m_HiddenScopeLast2 = &m_COOKIE;
    }
    else
    {
        throw QMKFusionException("Unknown HTTP Method.");
    }

    if (!m_Request.m_Cookie.isEmpty())
    {
        QStringList cookies = m_Request.m_Cookie.split(';');
        for(const QString &cookie : cookies)
        {
            int separator = cookie.indexOf('=');

            if (separator > 0)
            {
                QString key = QUrl::fromPercentEncoding(cookie.left(separator).trimmed().toLatin1()).toUpper();
                QString value = QUrl::fromPercentEncoding(cookie.right(cookie.length() - separator - 1).toLatin1());
                updateVariable(m_COOKIE, key, value);
            }
            else
            {
                qDebug() << "Invalid cookie.";
            }
        }
    }

    // Run compiled template(dll/so).
    cf_StructUpdate(m_SERVER, QStringLiteral("COLDFUSION"), QCFVariant(QCFVariant::Struct));
    cf_StructUpdate(m_SERVER[QStringLiteral("COLDFUSION")], QStringLiteral("APPSERVER"), QStringLiteral("mkfusion"));
    cf_StructUpdate(m_SERVER[QStringLiteral("COLDFUSION")], QStringLiteral("EXPIRATION"), QDateTime::currentDateTime());
#ifdef Q_OS_WIN
    cf_StructUpdate(m_SERVER[QStringLiteral("COLDFUSION")], QStringLiteral("INSTALLKIT"), QStringLiteral("Windows"));
#elif defined Q_OS_LINUX
    cf_StructUpdate(m_SERVER[QStringLiteral("COLDFUSION")], QStringLiteral("INSTALLKIT"), QStringLiteral("Linux"));
#else
#error Windows and Linux OSs are currently supported.
#endif
    cf_StructUpdate(m_SERVER[QStringLiteral("COLDFUSION")], QStringLiteral("PRODUCTLEVEL"), QStringLiteral("Free"));
    cf_StructUpdate(m_SERVER[QStringLiteral("COLDFUSION")], QStringLiteral("PRODUCTNAME"), QStringLiteral("MKFusion Server"));
    cf_StructUpdate(m_SERVER[QStringLiteral("COLDFUSION")], QStringLiteral("PRODUCTVERSION"), QStringLiteral("0.5.0"));
    cf_StructUpdate(m_SERVER[QStringLiteral("COLDFUSION")], QStringLiteral("ROOTDIR"), QCFServer::instance()->MKFusionPath().left(-1));
    cf_StructUpdate(m_SERVER[QStringLiteral("COLDFUSION")], QStringLiteral("SUPPORTEDLOCALES"), QStringLiteral("English (US),en,en_US"));
    cf_StructUpdate(m_SERVER, QStringLiteral("OS"), QCFVariant(QCFVariant::Struct));
#ifdef Q_OS_WIN
    cf_StructUpdate(m_SERVER[QStringLiteral("OS")], QStringLiteral("ADDITIONALINFORMATION"), QStringLiteral("Windows"));
#ifdef _WIN64
    cf_StructUpdate(m_SERVER[QStringLiteral("OS")], QStringLiteral("ARCH"), QStringLiteral("amd64"));
#else
    cf_StructUpdate(m_SERVER[QStringLiteral("OS")], QStringLiteral("ARCH"), QStringLiteral("i386"));
#endif
    cf_StructUpdate(m_SERVER[QStringLiteral("OS")], QStringLiteral("BUILDNUMBER"), QStringLiteral(""));
    cf_StructUpdate(m_SERVER[QStringLiteral("OS")], QStringLiteral("NAME"), QStringLiteral("WINDOWS"));
    cf_StructUpdate(m_SERVER[QStringLiteral("OS")], QStringLiteral("VERSION"), QStringLiteral("XP"));
#elif defined Q_OS_LINUX
    cf_StructUpdate(m_SERVER[QStringLiteral("OS")], QStringLiteral("ADDITIONALINFORMATION"), QStringLiteral("Linux"));
#ifdef __amd64__
    cf_StructUpdate(m_SERVER[QStringLiteral("OS")], QStringLiteral("ARCH"), QStringLiteral("amd64"));
#else
    cf_StructUpdate(m_SERVER[QStringLiteral("OS")], QStringLiteral("ARCH"), QStringLiteral("i386"));
#endif
    cf_StructUpdate(m_SERVER[QStringLiteral("OS")], QStringLiteral("BUILDNUMBER"), QStringLiteral("unknown"));

    cf_StructUpdate(m_SERVER[QStringLiteral("OS")], QStringLiteral("NAME"), QCFServer::instance()->osName());

    cf_StructUpdate(m_SERVER[QStringLiteral("OS")], QStringLiteral("VERSION"), QCFServer::instance()->osVersion());
#else
#error Windows and Linux OSs are currently supported.
#endif

    cf_StructUpdate(m_CGI, QStringLiteral("AUTH_PASSWORD"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("AUTH_TYPE"), m_Request.m_AuthType);
    cf_StructUpdate(m_CGI, QStringLiteral("AUTH_USER"), m_Request.m_User);
    cf_StructUpdate(m_CGI, QStringLiteral("CERT_COOKIE"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("CERT_FLAGS"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("CERT_ISSUER"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("CERT_KEYSIZE"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("CERT_SECRETKEYSIZE"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("CERT_SERIALNUMBER"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("CERT_SERVER_ISSUER"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("CERT_SERVER_SUBJECT"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("CERT_SUBJECT"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("CF_TEMPLATE_PATH"), m_Request.m_Filename);
    cf_StructUpdate(m_CGI, QStringLiteral("CONTENT_LENGTH"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("CONTENT_TYPE"), m_Request.m_ContentType);
    cf_StructUpdate(m_CGI, QStringLiteral("CONTEXT_PATH"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("GATEWAY_INTERFACE"), QStringLiteral("CGI/1.1")); // TODO: Hardcoded.
    cf_StructUpdate(m_CGI, QStringLiteral("HTTPS"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("HTTPS_KEYSIZE"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("HTTPS_SECRETKEYSIZE"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("HTTPS_SERVER_ISSUER"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("HTTPS_SERVER_SUBJECT"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("HTTP_ACCEPT"), m_Request.m_Accept);
    cf_StructUpdate(m_CGI, QStringLiteral("HTTP_ACCEPT_ENCODING"), m_Request.m_AcceptEncoding);
    cf_StructUpdate(m_CGI, QStringLiteral("HTTP_ACCEPT_LANGUAGE"), m_Request.m_AcceptLanguage);
    cf_StructUpdate(m_CGI, QStringLiteral("HTTP_CONNECTION"), m_Request.m_Connection);
    cf_StructUpdate(m_CGI, QStringLiteral("HTTP_COOKIE"), m_Request.m_Cookie);
    cf_StructUpdate(m_CGI, QStringLiteral("HTTP_HOST"), m_Request.m_Host);
    cf_StructUpdate(m_CGI, QStringLiteral("HTTP_REFERER"), m_Request.m_Referer);
    cf_StructUpdate(m_CGI, QStringLiteral("HTTP_USER_AGENT"), m_Request.m_UserAgent);
    cf_StructUpdate(m_CGI, QStringLiteral("PATH_INFO"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("PATH_TRANSLATED"), m_Request.m_Filename);
    cf_StructUpdate(m_CGI, QStringLiteral("QUERY_STRING"), m_Request.m_Args);
    cf_StructUpdate(m_CGI, QStringLiteral("REMOTE_ADDR"), m_Request.m_RemoteHost); // TODO: please check me.
    cf_StructUpdate(m_CGI, QStringLiteral("REMOTE_HOST"), m_Request.m_RemoteHost);
    cf_StructUpdate(m_CGI, QStringLiteral("REMOTE_USER"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("REQUEST_METHOD"), m_Request.m_Method);
    cf_StructUpdate(m_CGI, QStringLiteral("SCRIPT_NAME"), m_Request.m_URI);
    cf_StructUpdate(m_CGI, QStringLiteral("SERVER_NAME"), m_Request.m_Host);
    cf_StructUpdate(m_CGI, QStringLiteral("SERVER_PORT"), 80); // TODO: Hardcoded.
    cf_StructUpdate(m_CGI, QStringLiteral("SERVER_PORT_SECURE"), 0); // TODO: Hardcoded.
    cf_StructUpdate(m_CGI, QStringLiteral("SERVER_PROTOCOL"), m_Request.m_Protocol);
    cf_StructUpdate(m_CGI, QStringLiteral("SERVER_SOFTWARE"), QStringLiteral(""));
    cf_StructUpdate(m_CGI, QStringLiteral("WEB_SERVER_API"), QStringLiteral(""));
    /*

      public void fillKnownVariables()
      {
        this.knownVariables.add("VARIABLES");
        this.knownVariables.add("FORM");
        this.knownVariables.add("URL");
        this.knownVariables.add("ATTRIBUTES");
        this.knownVariables.add("CALLER");
        this.knownVariables.add("REQUEST");
        this.knownVariables.add("CGI");
        this.knownVariables.add("COOKIE");
        this.knownVariables.add("CLIENT");
        this.knownVariables.add("SESSION");
        this.knownVariables.add("APPLICATION");
        this.knownVariables.add("SERVER");
        this.knownVariables.add("THISTAG");
      }
    */
    QUrl l_url = QUrl::fromEncoded(QByteArray("?") + m_Request.m_Args.toUtf8(), QUrl::StrictMode);

    QList<QPair<QString, QString>> l_Arguments = QUrlQuery(l_url).queryItems();

    for(const QPair<QString, QString> &l_Argument: l_Arguments)
    {
        QString key = l_Argument.first;
        QString value = l_Argument.second;
        cf_StructUpdate(m_URL, key.toUpper(), value);
    }
}

void QCFWorkerThread::updateVariableInt(QCFVariant &dest, int key, const QCFVariant &value)
{
    int index;

    switch(dest.m_Type)
    {
    case QCFVariant::Array:
        index = key;

        if (index < 1)
        {
            throw QMKFusionException("Key index must be more than 0.");
        }

        if (index > dest.m_Array->size())
        {
            dest.m_Array->resize(index);
        }

        (*dest.m_Array)[index - 1] = value;
        break;
    default:
        throw QMKFusionException("Destination variable is not Struct nor Array.");
    }
}

void QCFWorkerThread::updateVariableStr(QCFVariant &dest, const wchar_t *key, const QCFVariant &value)
{
    int index;
    bool ok;

    switch(dest.m_Type)
    {
    case QCFVariant::Struct:
        (*dest.m_Struct)[QString::fromWCharArray(key).toUpper()] = value;
        break;
    case QCFVariant::Array:
        index = QString::fromWCharArray(key).toInt(&ok);

        if (!ok)
        {
            throw QMKFusionException("index is not number.");
        }

        if (index < 1)
        {
            throw QMKFusionException("Key index must be more than 0.");
        }

        if (index > dest.m_Array->size())
        {
            dest.m_Array->resize(index);
        }

        (*dest.m_Array)[index - 1] = value;
        break;
    default:
        throw QMKFusionException("Destination variable is not Struct nor Array.");
    }
}

void QCFWorkerThread::updateVariableQStr(QCFVariant &dest, const QString &key, const QCFVariant &value)
{
    int index;
    bool ok;

    switch(dest.m_Type)
    {
    case QCFVariant::Struct:
        (*dest.m_Struct)[key.toUpper()] = value;
        break;
    case QCFVariant::Array:
        index = key.toInt(&ok);

        if (!ok)
        {
            throw QMKFusionException("index is not number.");
        }

        if (index < 1)
        {
            throw QMKFusionException("Key index must be more than 0.");
        }

        if (index > dest.m_Array->size())
        {
            dest.m_Array->resize(index);
        }

        (*dest.m_Array)[index - 1] = value;
        break;
    default:
        throw QMKFusionException("Destination variable is not Struct nor Array.");
    }
}

void QCFWorkerThread::updateVariable(QCFVariant &dest, const QCFVariant &key, const QCFVariant &value)
{
    int index;
    bool ok;

    if (&dest == nullptr)
    {
        throw QMKFusionException("Variable is null.");
    }

    switch(dest.m_Type)
    {
    case QCFVariant::Struct:
        (*dest.m_Struct)[key.toString().toUpper()] = value;
        break;
    case QCFVariant::Array:
        index = key.toString().toInt(&ok);

        if (!ok)
        {
            throw QMKFusionException("index is not number.");
        }

        if (index < 1)
        {
            throw QMKFusionException("Key index must be more than 0.");
        }

        if (index > dest.m_Array->size())
        {
            dest.m_Array->resize(index);
        }

        (*dest.m_Array)[index - 1] = value;
        break;
    default:
        throw QMKFusionException("Destination variable is not Struct nor Array.");
    }
}

void QCFWorkerThread::f_WriteOutput(const QCFVariant &value)
{
    m_Output.append(value.toString());
}

void QCFWorkerThread::f_WriteOutput(const QString &value)
{
    m_Output.append(value);
}

void QCFWorkerThread::f_Location(const QString &p_URL, int p_StatusCode)
{
    if ((p_StatusCode < 300)||(p_StatusCode > 307))
    {
        throw QMKFusionInvalidArgumentException("f_Location", 2, p_StatusCode, 300, 307);
    }

    m_StatusCode = p_StatusCode;

    m_Header.insert("location", p_URL);

    m_Output.clear();

    // TODO: Add url redirect
    throw QMKFusionCFAbortException();
}

void QCFWorkerThread::f_Location(const QString &p_URL, bool p_AddToken, int p_StatusCode)
{
    Q_UNUSED(p_URL);
    Q_UNUSED(p_AddToken);
    Q_UNUSED(p_StatusCode);
}

void QCFWorkerThread::f_Include(const QString &p_template)
{
    // TODO: Implement void QCFWorkerThread::f_Include(const QString &p_template)
}

void QCFWorkerThread::f_Param(const QString &name)
{
    if(name.length() == 0)
    {
        throw QMKFusionException(
                    tr("Attribute validation error for CFPARAM."),
                    tr("The value of the NAME attribute is invalid."
                       "The length of the string, 0 character(s), must be greater than or equal to 1 character(s).")
                    );
    }

    if (!cf_IsDefined(this, name))
    {
        throw QMKFusionException(
                    tr("The required parameter '%1' was not provided.").arg(name.toUpper()),
                    tr("This page uses the cfparam tag to declare the parameter '%1' as required for this template."
                       "The parameter is not available. Ensure that you have passed or initialized the parameter correctly."
                       "To set a default value for the parameter, use the default attribute of the cfparam tag.").arg(name.toUpper())
                    );
    }
}

void QCFWorkerThread::f_Param(const QString &name, const QCFVariant &p_default)
{
    QStringList parts;

    if(name.length() == 0)
    {
        throw QMKFusionException(
                    tr("Attribute validation error for CFPARAM."),
                    tr("The value of the NAME attribute is invalid."
                       "The length of the string, 0 character(s), must be greater than or equal to 1 character(s).")
                    );
    }


    parts = name.toUpper().split(".");

    if (parts.count() == 1)
    {
        if(!m_VARIABLES.m_Struct->contains(parts.at(0)))
        {
            if (m_VARIABLES.m_HiddenScopeLast1)
            {
                if (m_VARIABLES.m_HiddenScopeLast1->m_Struct->contains(parts.at(0)))
                {
                    return;
                }
            }
            m_VARIABLES.m_Struct->insert(parts.at(0), p_default);
        }

        return;
    }

    if ((parts.first() != "CGI")&&(parts.first() != "SERVER")&&(parts.first() != "APPLICATION")&&(parts.first() != "SESSION")&&(parts.first() != "URL")&&(parts.first() != "FORM")&&(parts.first() != "VARIABLES"))
    {
        parts.prepend("VARIABLES");
    }

    const QString &first = parts.takeFirst();

    QCFVariant *var = &m_VARIABLES;

    if (first == "CGI")
    {
        var = &m_CGI;
    }
    else if (first == "SERVER")
    {
        var = &m_SERVER;
    }
    else if (first == "APPLICATION")
    {
        if (m_APPLICATION == nullptr)
        {
            throw QMKFusionException(tr("Appication scope not enabled."));
        }

        var = m_APPLICATION;
    }
    else if (first == "SESSION")
    {
        if (m_SESSION == nullptr)
        {
            throw QMKFusionException(tr("Session scope not enabled."));
        }

        var = m_SESSION;
    }
    else if (first == "URL")
    {
        var = &m_URL;
    }
    else if (first == "FORM")
    {
        var = &m_FORM;
    }
    else if (first == "VARIABLES")
    {
    }
    else
    {
        throw QMKFusionException(tr("Internal error."), tr("Unknown type(cf_IsDefined)."));
    }

    bool inserted = false;

    for(const QString &item : parts)
    {
        if ((var->m_Type != QCFVariant::Struct)&&(var->m_Type != QCFVariant::Null))
        {
            throw QMKFusionException(tr("Variable not object."));
        }

        if (var->m_Type == QCFVariant::Null)
        {
            var->setType(QCFVariant::Struct);
        }

        if (!var->m_Struct->contains(item))
        {
            if (var->m_HiddenScopeLast1)
            {
                var = var->m_HiddenScopeLast1;

                if (var->m_Struct->contains(item))
                {
                    var = &(*var)[item];

                    continue;
                }
            }

            var->m_Struct->insert(item, QCFVariant(QCFVariant::Null));

            inserted = true;
        }

        var = &(*var)[item];
    }

    if (inserted)
    {
        *var = p_default;
    }
}

bool QCFWorkerThread::f_FetchQueryRow(QCFVariant &destination, QCFVariant &query, int row)
{

}

void QCFWorkerThread::f_Application(QString name, bool sessionManagement, bool setClientCookies)
{

}

void QCFWorkerThread::f_FileUploadMove(const QString &destination, const QString &fileField, const QString &accept, const QString &attributes, const QString &mode, const QString &nameConflict, const QString &result)
{

}

void QCFWorkerThread::startQuery()
{

}

QCFVariant QCFWorkerThread::endQuery(const QString &p_DataSource)
{

}

void QCFWorkerThread::endQueryNoReturn(const QString &p_DataSource)
{

}

void QCFWorkerThread::addCustomFunction(const QString &functionName, std::function<QCFVariant (QCFWorkerThread *, const QList<QCFVariant> &)> function)
{
    if (m_CustomFunctions.contains(functionName))
    {
        throw QMKFusionException(tr("Function [%1] is already defined in other template.").arg(functionName));
    }

    m_CustomFunctions.insert(functionName, function);
}

void QCFWorkerThread::f_SetCookie(const QString &name, const QString &value, const QString &expires)
{
    QCFVariant val(QCFVariant::Struct);

    val.m_Struct->insert("value", value);

    if (expires.compare("never", Qt::CaseInsensitive) == 0)
    {
        val.m_Struct->insert("expires", QLocale("en").toString(QDateTime::currentDateTime().addYears(30), "ddd, dd-MMM-yyyy hh:mm:ss").append(" GMT"));
    }
    else if (expires.compare("now", Qt::CaseInsensitive) == 0)
    {
        val.m_Struct->insert("expires", 0);
    }
    else
    {
        val.m_Struct->insert("expires", expires);
    }

    m_COOKIE.m_Struct->insert(name.toUpper(), value);

    m_SetCookies.m_Struct->insert(name.toUpper(), val);
}

void QCFWorkerThread::startCustomTag(const QString &path, const QString &name, const QCFVariant &attributes, bool hasEndTag, QCustomTagType type)
{

}

bool QCFWorkerThread::endCustomTag(const QString &path, const QString &name, QCustomTagType type)
{
    return false;
}

void QCFWorkerThread::f_cfAssociate(const QString &baseTagName, const QString &keyName)
{
    for(QCFVariant &customTag : m_CustomTags)
    {
        const QString &name = QString("cf_") + customTag[L"Name"].toString();

        if (name.compare(baseTagName, Qt::CaseInsensitive) == 0)
        {
            if (!cf_StructKeyExists(customTag[L"ThisTag"], keyName.toUpper()))
            {
                updateVariableQStr(customTag[L"ThisTag"], keyName, QCFVariant(QCFVariant::Array));
            }

            cf_ArrayAppend(customTag[L"ThisTag"][keyName.toUpper()], m_VARIABLES[L"Attributes"]);

            return;
        }
    }

    throw QMKFusionException(QString("Not within [%1] custom tag.").arg(baseTagName));
}

QCFVariant QCFWorkerThread::f_CreateComponent(const QString &component_name)
{
    /*QString componentFileName = component_name;

    componentFileName = QFileInfo(m_isModified.m_Filename).absolutePath() + QDir::separator() + componentFileName.replace('.', QDir::separator()) + ".cfc";

    void * obj = this->m_TemplateInstance->compileAndLoadComponent(componentFileName, "");

    if (obj == nullptr)
    {
        throw QMKFusionCFAbortException();
    }*/

    return QCFVariant();
}

void QCFWorkerThread::f_cfdump(const QCFVariant &var)
{
    if (!m_CFDump)
    {
        m_Output += "<style type=\"text/css\">\n" \
            "	table.cfdump_wddx,\n" \
            "	table.cfdump_xml,\n" \
            "	table.cfdump_struct,\n" \
            "	table.cfdump_array,\n" \
            "	table.cfdump_query,\n" \
            "	table.cfdump_cfc,\n" \
            "	table.cfdump_object,\n" \
            "	table.cfdump_binary,\n" \
            "	table.cfdump_udf,\n" \
            "	table.cfdump_udfbody,\n" \
            "	table.cfdump_udfarguments {\n" \
            "		font-size: xx-small;\n" \
            "		font-family: verdana, arial, helvetica, sans-serif;\n" \
            "		cell-spacing: 2px;\n" \
            "	}\n" \
            "	table.cfdump_wddx th,\n" \
            "	table.cfdump_xml th,\n" \
            "	table.cfdump_struct th,\n" \
            "	table.cfdump_array th,\n" \
            "	table.cfdump_query th,\n" \
            "	table.cfdump_cfc th,\n" \
            "	table.cfdump_object th,\n" \
            "	table.cfdump_binary th,\n" \
            "	table.cfdump_udf th,\n" \
            "	table.cfdump_udfbody th,\n" \
            "	table.cfdump_udfarguments th {\n" \
            "		text-align: left;\n" \
            "		color: white;\n" \
            "		padding: 5px;\n" \
            "	} \n" \
            "	table.cfdump_wddx td,\n" \
            "	table.cfdump_xml td,\n" \
            "	table.cfdump_struct td,\n" \
            "	table.cfdump_array td,\n" \
            "	table.cfdump_query td,\n" \
            "	table.cfdump_cfc td,\n" \
            "	table.cfdump_object td,\n" \
            "	table.cfdump_binary td,\n" \
            "	table.cfdump_udf td,\n" \
            "	table.cfdump_udfbody td,\n" \
            "	table.cfdump_udfarguments td {\n" \
            "		padding: 3px;\n" \
            "		background-color: #ffffff;\n" \
            "		vertical-align : top;\n" \
            "	} \n" \
            "	table.cfdump_wddx {\n" \
            "		background-color: #000000;\n" \
            "	}\n" \
            "	table.cfdump_wddx th.wddx {\n" \
            "		background-color: #444444;\n" \
            "	}  \n" \
            "	table.cfdump_xml {\n" \
            "		background-color: #888888;\n" \
            "	}\n" \
            "	table.cfdump_xml th.xml {\n" \
            "		background-color: #aaaaaa;\n" \
            "	}\n" \
            "	table.cfdump_xml td.xml {\n" \
            "		background-color: #dddddd;\n" \
            "	} \n" \
            "	table.cfdump_struct {\n" \
            "		background-color: #0000cc ;\n" \
            "	}\n" \
            "	table.cfdump_struct th.struct {\n" \
            "		background-color: #4444cc ;\n" \
            "	}\n" \
            "	table.cfdump_struct td.struct {\n" \
            "		background-color: #ccddff;\n" \
            "	} \n" \
            "	table.cfdump_array {\n" \
            "		background-color: #006600 ;\n" \
            "	}\n" \
            "	table.cfdump_array th.array {\n" \
            "		background-color: #009900 ;\n" \
            "	}\n" \
            "	table.cfdump_array td.array {\n" \
            "		background-color: #ccffcc ;\n" \
            "	} \n" \
            "	table.cfdump_query {\n" \
            "		background-color: #884488 ;\n" \
            "	}\n" \
            "	table.cfdump_query th.query {\n" \
            "		background-color: #aa66aa ;\n" \
            "	}\n" \
            "	table.cfdump_query td.query {\n" \
            "		background-color: #ffddff ;\n" \
            "	}\n" \
            "	table.cfdump_cfc {\n" \
            "		background-color: #ff0000;\n" \
            "	}\n" \
            "	table.cfdump_cfc th.cfc{\n" \
            "		background-color: #ff4444;\n" \
            "	}\n" \
            "	table.cfdump_cfc td.cfc {\n" \
            "		background-color: #ffcccc;\n" \
            "	}\n" \
            "	table.cfdump_object {\n" \
            "		background-color : #ff0000;\n" \
            "	}\n" \
            "	table.cfdump_object th.object{\n" \
            "		background-color: #ff4444;\n" \
            "	}\n" \
            "	table.cfdump_binary {\n" \
            "		background-color : #eebb00;\n" \
            "	}\n" \
            "	table.cfdump_binary th.binary {\n" \
            "		background-color: #ffcc44;\n" \
            "	}\n" \
            "	table.cfdump_binary td {\n" \
            "		font-size: x-small;\n" \
            "	}\n" \
            "	table.cfdump_udf {\n" \
            "		background-color: #aa4400;\n" \
            "	}\n" \
            "	table.cfdump_udf th.udf {\n" \
            "		background-color: #cc6600;\n" \
            "	}\n" \
            "	table.cfdump_udfarguments {\n" \
            "		background-color: #dddddd;\n" \
            "		cell-spacing: 3;\n" \
            "	}\n" \
            "	table.cfdump_udfarguments th {\n" \
            "		background-color: #eeeeee;\n" \
            "		color: #000000;\n" \
            "	} \n" \
            "	</style>\n" \
            "	<script language=\"javascript\" type=\"text/javascript\">\n" \
            "		var expand = \"open\";\n" \
            "	\n" \
            "		dump = function( obj ) {\n" \
            "			var out = \"\" ;\n" \
            "			if ( typeof obj == \"object\" ) {\n" \
            "				for ( key in obj ) {\n" \
            "					if ( typeof obj[key] != \"function\" ) out += key + ': ' + obj[key] + '<br>' ;\n" \
            "				}\n" \
            "			}\n" \
            "		}\n" \
            "	\n" \
            "		cfdump_toggleRow = function(source) {\n" \
            "			//target is the right cell\n" \
            "			if(document.all) target = source.parentElement.cells[1];\n" \
            "			else {\n" \
            "				var element = null;\n" \
            "				var vLen = source.parentNode.childNodes.length;\n" \
            "				for(var i=vLen-1;i>0;i--){\n" \
            "					if(source.parentNode.childNodes[i].nodeType == 1){\n" \
            "						element = source.parentNode.childNodes[i];\n" \
            "						break;\n" \
            "					}\n" \
            "				}\n" \
            "				if(element == null)\n" \
            "					target = source.parentNode.lastChild;\n" \
            "				else\n" \
            "					target = element;\n" \
            "			}\n" \
            "			//target = source.parentNode.lastChild ;\n" \
            "			cfdump_toggleTarget( target, cfdump_toggleSource( source ) ) ;\n" \
            "		}\n" \
            "	\n" \
            "		cfdump_toggleXmlDoc = function(source) {\n" \
            "	\n" \
            "			var caption = source.innerHTML.split( ' [' ) ;\n" \
            "	\n" \
            "			if ( source.style.fontStyle == 'italic' ) {\n" \
            "				source.style.fontStyle = 'normal' ;\n" \
            "				source.innerHTML = caption[0] + ' [short version]' ;\n" \
            "				source.title = 'click to maximize' ;\n" \
            "				switchLongToState = 'closed' ;\n" \
            "				switchShortToState = 'open' ;\n" \
            "			} else if ( source.innerHTML.indexOf('[short version]') != -1 ) {\n" \
            "				source.innerHTML = caption[0] + ' [long version]' ;\n" \
            "				source.title = 'click to collapse' ;\n" \
            "				switchLongToState = 'open' ;\n" \
            "				switchShortToState = 'closed' ;\n" \
            "			} else {\n" \
            "				source.style.fontStyle = 'italic' ;\n" \
            "				source.title = 'click to expand' ;\n" \
            "				source.innerHTML = caption[0] ;\n" \
            "				switchLongToState = 'closed' ;\n" \
            "				switchShortToState = 'closed' ;\n" \
            "			}\n" \
            "	\n" \
            "			if(document.all) {\n" \
            "				var table = source.parentElement.parentElement ;\n" \
            "				for ( var i = 1; i < table.rows.length; i++ ) {\n" \
            "					target = table.rows[i] ;\n" \
            "					if ( i < 3 ) cfdump_toggleTarget( target, switchLongToState ) ;\n" \
            "					else cfdump_toggleTarget( target, switchShortToState ) ;\n" \
            "				}\n" \
            "			} else {\n" \
            "				var table = source.parentNode.parentNode ;\n" \
            "				var row = 1;\n" \
            "				for ( var i = 1; i < table.childNodes.length; i++ ) {\n" \
            "					target = table.childNodes[i] ;\n" \
            "					if( target.style ) {\n" \
            "						if ( row < 3 ) {\n" \
            "							cfdump_toggleTarget( target, switchLongToState ) ;\n" \
            "						} else {\n" \
            "							cfdump_toggleTarget( target, switchShortToState ) ;\n" \
            "						}\n" \
            "						row++;\n" \
            "					}\n" \
            "				}\n" \
            "			}\n" \
            "		}\n" \
            "	\n" \
            "		cfdump_toggleTable = function(source) {\n" \
            "	\n" \
            "			var switchToState = cfdump_toggleSource( source ) ;\n" \
            "			if(document.all) {\n" \
            "				var table = source.parentElement.parentElement ;\n" \
            "				for ( var i = 1; i < table.rows.length; i++ ) {\n" \
            "					target = table.rows[i] ;\n" \
            "					cfdump_toggleTarget( target, switchToState ) ;\n" \
            "				}\n" \
            "			}\n" \
            "			else {\n" \
            "				var table = source.parentNode.parentNode ;\n" \
            "				for ( var i = 1; i < table.childNodes.length; i++ ) {\n" \
            "					target = table.childNodes[i] ;\n" \
            "					if(target.style) {\n" \
            "						cfdump_toggleTarget( target, switchToState ) ;\n" \
            "					}\n" \
            "				}\n" \
            "			}\n" \
            "		}\n" \
            "	\n" \
            "		cfdump_toggleSource = function( source ) {\n" \
            "			if ( source.style.fontStyle == 'italic' || source.style.fontStyle == null) {\n" \
            "				source.style.fontStyle = 'normal' ;\n" \
            "				source.title = 'click to collapse' ;\n" \
            "				return 'open' ;\n" \
            "			} else {\n" \
            "				source.style.fontStyle = 'italic' ;\n" \
            "				source.title = 'click to expand' ;\n" \
            "				return 'closed' ;\n" \
            "			}\n" \
            "		}\n" \
            "	\n" \
            "		cfdump_toggleTarget = function( target, switchToState ) {\n" \
            "			if ( switchToState == 'open' )	target.style.display = '' ;\n" \
            "			else target.style.display = 'none' ;\n" \
            "		}\n" \
            "	\n" \
            "		cfdump_toggleRow_qry = function(source) {\n" \
            "			expand = (source.title == \"click to collapse\") ? \"closed\" : \"open\";\n" \
            "			if(document.all) {\n" \
            "				var nbrChildren = source.parentElement.cells.length;\n" \
            "				if(nbrChildren > 1){\n" \
            "					for(i=nbrChildren-1;i>0;i--){\n" \
            "						target = source.parentElement.cells[i];\n" \
            "						cfdump_toggleTarget( target,expand ) ;\n" \
            "						cfdump_toggleSource_qry(source);\n" \
            "					}\n" \
            "				}\n" \
            "				else {\n" \
            "					//target is the right cell\n" \
            "					target = source.parentElement.cells[1];\n" \
            "					cfdump_toggleTarget( target, cfdump_toggleSource( source ) ) ;\n" \
            "				}\n" \
            "			}\n" \
            "			else{\n" \
            "				var target = null;\n" \
            "				var vLen = source.parentNode.childNodes.length;\n" \
            "				for(var i=vLen-1;i>1;i--){\n" \
            "					if(source.parentNode.childNodes[i].nodeType == 1){\n" \
            "						target = source.parentNode.childNodes[i];\n" \
            "						cfdump_toggleTarget( target,expand );\n" \
            "						cfdump_toggleSource_qry(source);\n" \
            "					}\n" \
            "				}\n" \
            "				if(target == null){\n" \
            "					//target is the last cell\n" \
            "					target = source.parentNode.lastChild;\n" \
            "					cfdump_toggleTarget( target, cfdump_toggleSource( source ) ) ;\n" \
            "				}\n" \
            "			}\n" \
            "		}\n" \
            "	\n" \
            "		cfdump_toggleSource_qry = function(source) {\n" \
            "			if(expand == \"closed\"){\n" \
            "				source.title = \"click to expand\";\n" \
            "				source.style.fontStyle = \"italic\";\n" \
            "			}\n" \
            "			else{\n" \
            "				source.title = \"click to collapse\";\n" \
            "				source.style.fontStyle = \"normal\";\n" \
            "			}\n" \
            "		}\n" \
            "	 </script>\n";

        m_CFDump = true;
    }

    m_Output += f_cfdump_var(var);
}

QString QCFWorkerThread::f_cfdump_var(const QCFVariant &var)
{
    QString ret;

    int columns;

    QCFVariant l_temp = var;
    switch(l_temp.type())
    {
        case QCFVariant::Boolean:
        case QCFVariant::DateTime:
        case QCFVariant::Number:
            ret += l_temp.toString();
            break;
        case QCFVariant::String:
            if (!l_temp.m_String->isEmpty())
            {
                ret += *l_temp.m_String;
            }
            else
            {
                ret += "[empty string]";
            }
            break;
        case QCFVariant::Struct:
            ret += "<table class=\"cfdump_struct\"><tr><th class=\"struct\" colspan=\"2\" onClick=\"cfdump_toggleTable(this);\" onmousedown=\"return false;\" onselectstart=\"return false;\" style=\"cursor:pointer;\" title=\"click to collapse\">struct</th></tr>\n";

            for(const QString &l_key: l_temp.m_Struct->keys())
            {
                QString l_keyType;

                switch ((*l_temp.m_Struct)[l_key].m_Type) {
                case QCFVariant::Null:
                    ret += "<tr><td class=\"struct\" onClick=\"cfdump_toggleRow(this);\" onmousedown=\"return false;\" onselectstart=\"return false;\" style=\"cursor:pointer;\" title=\"click to collapse\">" + l_key + " [null]</td><td>null</td></tr>\n";
                    continue;
                case QCFVariant::Boolean:
                    l_keyType = "[boolean]";
                    break;
                case QCFVariant::Number:
                    l_keyType = "[number]";
                    break;
                case QCFVariant::String:
                    l_keyType = "[string]";
                    break;
                case QCFVariant::DateTime:
                    l_keyType = "[datetime]";
                    break;
                case QCFVariant::Array:
                    l_keyType = "[array]";
                    break;
                case QCFVariant::Struct:
                    l_keyType = "[object]";
                    break;
                case QCFVariant::Binary:
                    l_keyType = "[binary]";
                    break;
                case QCFVariant::Query:
                    l_keyType = "[query]";
                    break;
                case QCFVariant::NotImplemented:
                    l_keyType = "[not implemented]";
                    break;
                case QCFVariant::Error:
                    l_keyType = "[error]";
                    break;
                default:
                    l_keyType = "[unknown]";
                    break;
                }

                ret += "<tr><td class=\"struct\" onClick=\"cfdump_toggleRow(this);\" onmousedown=\"return false;\" onselectstart=\"return false;\" style=\"cursor:pointer;\" title=\"click to collapse\">" + l_key + " " + l_keyType + "</td><td>" + f_cfdump_var((*l_temp.m_Struct)[l_key]) + "</td></tr>\n";
            }

            ret += "</table>\n";
            break;
        case QCFVariant::Array:
            ret += "<table class=\"cfdump_array\"><tr><th class=\"array\" colspan=\"2\" onClick=\"cfdump_toggleTable(this);\" onmousedown=\"return false;\" onselectstart=\"return false;\" style=\"cursor:pointer;\" title=\"click to collapse\">array</th></tr>\n";

            for(int i = 0; i < var.m_Array->size(); i++)
            {
                QString l_keyType;

                switch (l_temp.m_Array->at(i).m_Type) {
                case QCFVariant::Null:
                    ret += "<tr><td class=\"array\" onClick=\"cfdump_toggleRow(this);\" onmousedown=\"return false;\" onselectstart=\"return false;\" style=\"cursor:pointer;\" title=\"click to collapse\">" + QString::number(i) + " [null]</td><td>null</td></tr>\n";
                    continue;
                case QCFVariant::Boolean:
                    l_keyType = "[boolean]";
                    break;
                case QCFVariant::Number:
                    l_keyType = "[number]";
                    break;
                case QCFVariant::String:
                    l_keyType = "[string]";
                    break;
                case QCFVariant::DateTime:
                    l_keyType = "[datetime]";
                    break;
                case QCFVariant::Array:
                    l_keyType = "[array]";
                    break;
                case QCFVariant::Struct:
                    l_keyType = "[object]";
                    break;
                case QCFVariant::Binary:
                    l_keyType = "[binary]";
                    break;
                case QCFVariant::Query:
                    l_keyType = "[query]";
                    break;
                case QCFVariant::NotImplemented:
                    l_keyType = "[not implemented]";
                    break;
                case QCFVariant::Error:
                    l_keyType = "[error]";
                    break;
                default:
                    l_keyType = "[unknown]";
                    break;
                }

                ret += "<tr><td class=\"array\" onClick=\"cfdump_toggleRow(this);\" onmousedown=\"return false;\" onselectstart=\"return false;\" style=\"cursor:pointer;\" title=\"click to collapse\">" + QString::number(i) + " " + l_keyType + "</td><td>" + f_cfdump_var(l_temp.m_Array->at(i)) + "</td></tr>\n";
            }

            ret += "</table>\n";
            break;
        case QCFVariant::Query:

            columns = var.m_Struct->value("RESULTSET").m_Struct->count();

            ret += "<table class=\"cfdump_query\"><tr><th class=\"array\" colspan=\"" + QString::number(columns) + "\" onClick=\"cfdump_toggleTable(this);\" onmousedown=\"return false;\" onselectstart=\"return false;\" style=\"cursor:pointer;\" title=\"click to collapse\">query</th></tr>\n";

            if (columns > 0)
            {
                ret += "<tr bgcolor=\"eeaaaa\">\n";

                ret += "<td class=\"query\" style=\"cursor: pointer; font-style: normal;\" title=\"click to collapse\" onclick=\"cfdump_toggleRow_qry(this);\">&nbsp;</td>\n";

                for(int c = 0; c < columns; c++)
                {
                    ret += "<td class=\"query\">" + var.m_Struct->value("RESULTSET").m_Struct->keys().at(c).toHtmlEscaped() + "</td>\n";
                }

                ret += "</tr>";

                int rows = var.m_Struct->value("RECORDCOUNT").toInt();

                for(int r = 0; r < rows; r++)
                {
                    ret += "<tr>\n";

                    ret += "<td class=\"query\" style=\"cursor: pointer; font-style: normal;\" title=\"click to collapse\" onclick=\"cfdump_toggleRow_qry(this);\">" + QString::number(r + 1) + "</td>\n";

                    for(int c = 0; c < columns; c++)
                    {
                        QString cell_text = var.m_Struct->value("RESULTSET").m_Struct->values().at(c).m_Array->at(r).toString();

                        if (cell_text.isEmpty())
                        {
                            cell_text = "[empty string]";
                        }

                        ret += "<td valign=\"top\">" + cell_text.toHtmlEscaped() + "</td>\n";
                    }

                    ret += "</tr>";
                }
            }

            ret += "</table>\n";
            break;
        default:
            break;
    }

    return ret;
}
