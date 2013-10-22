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
    , m_Socket(nullptr)
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
    m_Socket->setParent(this);
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

        l_RecievedBuffer += m_Socket->readAll();
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

    if (l_FoundRecieveBufSize)
    {
        return false;
    }

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

    l_ds >> tempba;
    if (!tempba.isEmpty())
    {
        m_Request.m_Filename = QString::fromUtf8(tempba.constData());
        tempba.clear();
    }

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

    QList<QPair<QString, QString> > l_Arguments = QUrlQuery(l_url).queryItems();

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

void QCFWorkerThread::f_WriteOutput(const QString &value)
{
    m_Output.append(value);
}
