#include "qcfrunningtemplate.h"
#include "qmkfusionexception.h"
#include "cffunctions.h"
#include "qhttpcodec.h"
#include "qcfserver.h"
#include "common.h"

#include <QTemporaryFile>
#include <QDataStream>
#include <QReadLocker>
#include <QUrlQuery>
#include <QLibrary>
#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QUrl>


QCFRunningTemplate::QCFRunningTemplate()
	: QObject()
    , m_APPLICATION(nullptr)
    , m_SESSION(nullptr)
	, m_CFOutput(0)
	, m_ContentType("text/html; charset=utf-8")
    , m_StatusCode(200)
	, m_HeadersSent(false)
    , m_Socket(nullptr)
    , m_CFServer(nullptr)
    , m_OutputType(OutputTypeContent)
{
}

QCFRunningTemplate::~QCFRunningTemplate()
{
    m_CustomFunctions.clear();

    while(!m_LoadedTemplates.isEmpty())
    {
        QLibrary *lib = m_LoadedTemplates.take(m_LoadedTemplates.keys().first());

        if (lib == nullptr)
        {
            qDebug() << "lib == nullptr";
            continue;
        }

        lib->unload();
        delete lib;
    }
}

void QCFRunningTemplate::cf_WriteOutput(const QString &string)
{
    m_Output.append(string);
}

void * QCFRunningTemplate::compileAndLoadTemplate(const QString &filename, const QString &uri)
{
    if(m_LoadedTemplates.contains(filename))
    {
        if (m_LoadedTemplates[filename]->isLoaded() == false)
        {
            m_StatusCode = 500;
            m_Output = "template library was not loaded.";

            return nullptr;
        }

        return (void *)m_LoadedTemplates[filename]->resolve("createCFMTemplate");
    }

    QReadLocker lock(&((QCFServer*)m_CFServer)->m_runningTemplatesLock);

    QString err = ((QCFServer*)m_CFServer)->compileTemplate(filename, uri);
    if (err.isEmpty())
    {
        QLibrary *templateLib = new QLibrary();

        templateLib->setFileName(((QCFServer*)m_CFServer)->m_MKFusionPath + "templates/" + ((QCFServer*)m_CFServer)->m_CompiledTemplates[filename].m_CompiledFileName);
        if (templateLib->load() != false)
        {
            m_LoadedTemplates.insert(filename, templateLib);

            return (void *)templateLib->resolve("createCFMTemplate");
        }
        else
        {
            delete templateLib;

            m_StatusCode = 500;
            m_Output = "Can\'t load template library.";
        }
    }
    else
    {
        m_StatusCode = 500;
        m_Output = "<div><code>" + err.toHtmlEscaped() + "</code></div><br /><br />";
    }

    return nullptr;
}

void QCFRunningTemplate::runApplicationTemplate()
{
    QDir dir(QFileInfo(m_Request.m_Filename).absoluteDir());

    if (!dir.exists())
    {
        qDebug() << "Bad path!! Check code.";
        return;
    }

    do
    {
        QFile app_file(dir.absoluteFilePath("Application.cfm"));

#ifndef Q_OS_WIN // Play nice with case sensitive OSs
        if (!app_file.exists())
        {
            app_file.setFileName(dir.absoluteFilePath("application.cfm"));
        }
#endif

        if (app_file.exists())
        {
            createCFMTemplateDef createCFMTemplate = 0;

            createCFMTemplate = (createCFMTemplateDef)compileAndLoadTemplate(app_file.fileName(), m_Request.m_URI);

            if (createCFMTemplate)
            {
                QCFTemplate *l_page = createCFMTemplate();
                l_page->run(this);
                delete l_page;
                l_page = 0;
            }

            break;
        }

    } while (dir.cdUp());
}

void QCFRunningTemplate::processPostData(QByteArray post)
{
    m_FORM.setType(QWDDX::Struct);

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

void QCFRunningTemplate::worker()
{
    createCFMTemplateDef createCFMTemplate = 0;
    bool l_FoundRecieveBufSize = false;
	QByteArray l_RecievedBuffer;
	qint32 l_RecieveBufSize = 0;
    QCFTemplate *l_page = 0;

#ifdef Q_OS_LINUX
    QProcess process;
#endif

	if ((!m_Socket)||(!m_CFServer))
	{
		return;
	}

	forever
	{
		forever
		{
			if (m_Socket->bytesAvailable() == 0)
			{
				m_Socket->waitForReadyRead(100);
			}

            if(!m_Socket->isOpen())
            {
                break;
            }

			l_RecievedBuffer += m_Socket->readAll();
			if ((l_FoundRecieveBufSize == false)&&(l_RecievedBuffer.size() >= 4))
			{
				QDataStream l_ds(&l_RecievedBuffer, QIODevice::ReadOnly);
				l_ds.setVersion(QDataStream::Qt_4_4);

				l_ds >> l_RecieveBufSize;
				if (l_RecieveBufSize > 10485760) // 10MB
				{
					break;
				}
				l_FoundRecieveBufSize = true;
			}

			if ((l_FoundRecieveBufSize == true)&&(l_RecievedBuffer.size() >= l_RecieveBufSize))
			{
				break;
			}
		}

		if (l_FoundRecieveBufSize == false)
		{
			break;
		}

        try
        {
            QDataStream l_ds(&l_RecievedBuffer, QIODevice::ReadOnly);
            QStringList cookies;
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
                cookies = m_Request.m_Cookie.split(';');
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

            createCFMTemplate = (createCFMTemplateDef)compileAndLoadTemplate(m_Request.m_Filename, m_Request.m_URI);

            if (createCFMTemplate)
			{
				l_page = createCFMTemplate();
                if (l_page)
				{
                    ((QCFServer*)m_CFServer)->m_RunnuingTemplatesByThreadId.insert(QThread::currentThreadId(), this);

                    m_SERVER.setType(QWDDX::Struct);
                    m_COOKIE.setType(QWDDX::Struct);
                    m_CGI.setType(QWDDX::Struct);
                    m_VARIABLES.setType(QWDDX::Struct);
                    m_URL.setType(QWDDX::Struct);
                    m_SetCookies.setType(QWDDX::Struct);

                    if (m_Request.m_Method == "GET")
                    {
                        m_FORM.setType(QWDDX::Error);
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
                    cf_StructUpdate(m_SERVER, QStringLiteral("COLDFUSION"), QWDDX(QWDDX::Struct));
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
                    cf_StructUpdate(m_SERVER[QStringLiteral("COLDFUSION")], QStringLiteral("PRODUCTVERSION"), QStringLiteral("0.4.5"));
                    cf_StructUpdate(m_SERVER[QStringLiteral("COLDFUSION")], QStringLiteral("ROOTDIR"), ((QCFServer*)m_CFServer)->m_MKFusionPath.left(-1));
                    cf_StructUpdate(m_SERVER[QStringLiteral("COLDFUSION")], QStringLiteral("SUPPORTEDLOCALES"), QStringLiteral("English (US),en,en_US"));
                    cf_StructUpdate(m_SERVER, QStringLiteral("OS"), QWDDX(QWDDX::Struct));
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

                    static QString osName;
                    if (osName.isEmpty())
                    {
#ifdef Q_OS_WIN
                        osName = QStringLiteral("Windows");
#elif defined Q_OS_LINUX
                        process.start("lsb_release", QStringList() << "-d");

                        process.waitForFinished();

                        osName = QString::fromUtf8(process.readAllStandardOutput());

                        if(osName.indexOf(":") > -1)
                        {
                            osName = osName.right(osName.length() - osName.lastIndexOf(":") - 1).trimmed();
                        }
#else
                        osName = QStringLiteral("Other");
#endif
                    }
                    cf_StructUpdate(m_SERVER[QStringLiteral("OS")], QStringLiteral("NAME"), osName);

                    static QString osVersion;
                    if(osVersion.isEmpty())
                    {
#ifdef Q_OS_WIN
                        osVersion = QStringLiteral("unknown");
#elif defined Q_OS_LINUX
                        process.start("lsb_release", QStringList() << "-c");

                        process.waitForFinished();

                        osVersion = QString::fromUtf8(process.readAllStandardOutput());

                        if(osVersion.indexOf(":") > -1)
                        {
                        osVersion = osVersion.right(osVersion.length() - osVersion.lastIndexOf(":") - 1).trimmed();
                        }
#else
                        osVersion = QStringLiteral("unknown");
#endif
                    }
                    cf_StructUpdate(m_SERVER[QStringLiteral("OS")], QStringLiteral("VERSION"), osVersion);
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

                    runApplicationTemplate();

                    if (m_StatusCode == 200)
                    {
                        l_page->run(this);
                    }
				}
				else
				{
                    m_StatusCode = 500;
                    m_Output = "QCFTemplate == nullptr";
				}
			}
			else
			{
                if (m_StatusCode == 200)
				{
                    m_StatusCode = 500;
                    m_Output = "createCFMTemplate() == nullptr";
				}
			}
		}
		catch (const QMKFusionCFAbortException &ex)
		{
		}
		catch (const QMKFusionTemplateException &ex)
		{
            m_StatusCode = 500;
			m_Output += WriteException(ex, this->m_Request);
		}
		catch (const QMKFusionException &ex)
		{
            m_StatusCode = 500;
			m_Output += WriteException(ex, this->m_Request);
		}
#ifndef QT_DEBUG
        catch(...)
        {
            m_StatusCode = 500;
            m_Output += WriteException(QMKFusionException("Internal error."), this->m_Request);
        }
#endif

        if (((QCFServer*)m_CFServer)->m_RunnuingTemplatesByThreadId.contains(QThread::currentThreadId()))
        {
            ((QCFServer*)m_CFServer)->m_RunnuingTemplatesByThreadId.remove(QThread::currentThreadId());
        }

		delete l_page;
        l_page = 0;

        createCFMTemplate = nullptr;

/*		if (l_TemplateLib.isLoaded())
		{
#ifdef Q_OS_WIN
            m_VARIABLES.m_Struct->clear(); // TODO: If this line is not here the app will crash. Check it when possible.
#endif

            l_TemplateLib.unload();
        }*/

		if (m_HeadersSent == false)
		{
			QByteArray l_header;
			QDataStream l_headerDataStream(&l_header, QIODevice::WriteOnly);
			l_headerDataStream.setVersion(QDataStream::Qt_4_4);

			l_headerDataStream << (qint32) 0;
			l_headerDataStream << m_ContentType;

            l_headerDataStream << m_StatusCode;

            if (m_SetCookies.m_Type == QWDDX::Struct)
            {
                for(const QString &key : m_SetCookies.m_Struct->keys())
                {
                    if (m_COOKIE.m_Struct->contains(key))
                    {
                        m_COOKIE.m_Struct->remove(key);
                    }

                    const QWDDX cookieData = m_SetCookies.m_Struct->value(key);

                    if (cookieData.m_Struct->value("expires").m_Type == QWDDX::Number)
                    {
                        m_Header.insert("Set-Cookie", QUrl::toPercentEncoding(key) + "=" + QUrl::toPercentEncoding(cookieData.m_Struct->value("value").toString()) +  ";Max-Age=" + cookieData.m_Struct->value("expires").toString() + ";path=/");
                    }
                    else
                    {
                        m_Header.insert("Set-Cookie", QUrl::toPercentEncoding(key) + "=" + QUrl::toPercentEncoding(cookieData.m_Struct->value("value").toString()) +  ";expires=" + cookieData.m_Struct->value("expires").toString() + ";path=/");
                    }
                }
            }

            if (m_COOKIE.m_Type == QWDDX::Struct)
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

			if (m_Socket->write(l_header) == -1)
			{
				break;
			}

			m_Socket->waitForBytesWritten(-1);
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

		break;
	}

	m_Socket->close();

	QThread::currentThread()->setPriority(QThread::IdlePriority);
	m_Socket->deleteLater();
	deleteLater();

	emit finished();
}
