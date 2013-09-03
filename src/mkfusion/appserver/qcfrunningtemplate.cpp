#include "qcfrunningtemplate.h"
#include "qmkfusionexception.h"
#include "cffunctions.h"
#include "qcfserver.h"
#include "common.h"

#include <QDataStream>
#include <QReadLocker>
#include <QUrlQuery>
#include <QLibrary>
#include <QProcess>
#include <QDebug>
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
        m_Output = "Compiling error: " + err;
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

void QCFRunningTemplate::worker()
{
	QByteArray l_RecievedBuffer;
	bool l_FoundRecieveBufSize = false;
	qint32 l_RecieveBufSize = 0;
    QProcess process;

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
			l_RecievedBuffer += m_Socket->readAll();
			if ((l_FoundRecieveBufSize == false)&&(l_RecievedBuffer.size() >= 4))
			{
				QDataStream l_ds(&l_RecievedBuffer, QIODevice::ReadOnly);
				l_ds.setVersion(QDataStream::Qt_4_4);

				l_ds >> l_RecieveBufSize;
				if (l_RecieveBufSize > 8196)
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

		QDataStream l_ds(&l_RecievedBuffer, QIODevice::ReadOnly);
        QStringList cookies;
		char *tempstr;
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
            cookies = QString::fromUtf8(tempstr).split(';');
            delete[] tempstr;
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

		QCFTemplate *l_page = 0;
		createCFMTemplateDef createCFMTemplate = 0;

		try
		{
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
                    m_FORM.setType(QWDDX::Struct);
                    m_VARIABLES.setType(QWDDX::Struct);
                    m_URL.setType(QWDDX::Struct);

                    for(const QString &cookie : cookies)
                    {
                        int separator = cookie.indexOf('=');

                        if (separator > 0)
                        {
                            QString key = cookie.left(separator).trimmed().toUpper();
                            QString value = cookie.right(cookie.length() - separator - 1);
                            m_COOKIE[key] = value;
                        }
                        else
                        {
                            qDebug() << "Invalid cookie.";
                        }
                    }

					// Run compiled template(dll/so).
                    m_SERVER[QStringLiteral("COLDFUSION")] = QWDDX(QWDDX::Struct);
                    m_SERVER[QStringLiteral("COLDFUSION")][QStringLiteral("APPSERVER")] = QStringLiteral("mkfusion");
                    m_SERVER[QStringLiteral("COLDFUSION")][QStringLiteral("EXPIRATION")] = QDateTime::currentDateTime();
#ifdef Q_OS_WIN
                    m_SERVER[QStringLiteral("COLDFUSION")][QStringLiteral("INSTALLKIT")] = QStringLiteral("Windows");
#elif defined Q_OS_LINUX
                    m_SERVER[QStringLiteral("COLDFUSION")][QStringLiteral("INSTALLKIT")] = QStringLiteral("Linux");
#else
#error Windows and Linux OSs are currently supported.
#endif
                    m_SERVER[QStringLiteral("COLDFUSION")][QStringLiteral("PRODUCTLEVEL")] = QStringLiteral("Free");
                    m_SERVER[QStringLiteral("COLDFUSION")][QStringLiteral("PRODUCTNAME")] = QStringLiteral("MKFusion Server");
                    m_SERVER[QStringLiteral("COLDFUSION")][QStringLiteral("PRODUCTVERSION")] = QStringLiteral("0.4.5");
                    m_SERVER[QStringLiteral("COLDFUSION")][QStringLiteral("ROOTDIR")] = ((QCFServer*)m_CFServer)->m_MKFusionPath.left(-1);
                    m_SERVER[QStringLiteral("COLDFUSION")][QStringLiteral("SUPPORTEDLOCALES")] = QStringLiteral("English (US),en,en_US");
                    m_SERVER[QStringLiteral("OS")] = QWDDX(QWDDX::Struct);
#ifdef Q_OS_WIN
                    m_SERVER[QStringLiteral("OS")][QStringLiteral("ADDITIONALINFORMATION")] = QStringLiteral("Windows");
#ifdef _WIN64
                    m_SERVER[QStringLiteral("OS")][QStringLiteral("ARCH")] = QStringLiteral("amd64");
#else
                    m_SERVER[QStringLiteral("OS")][QStringLiteral("ARCH")] = QStringLiteral("i386");
#endif
                    m_SERVER[QStringLiteral("OS")][QStringLiteral("BUILDNUMBER")] = QStringLiteral("");
                    m_SERVER[QStringLiteral("OS")][QStringLiteral("NAME")] = QStringLiteral("WINDOWS");
                    m_SERVER[QStringLiteral("OS")][QStringLiteral("VERSION")] = QStringLiteral("XP");
#elif defined Q_OS_LINUX
                    m_SERVER[QStringLiteral("OS")][QStringLiteral("ADDITIONALINFORMATION")] = QStringLiteral("Linux");
#ifdef __amd64__
                    m_SERVER[QStringLiteral("OS")][QStringLiteral("ARCH")] = QStringLiteral("amd64");
#else
                    m_SERVER[QStringLiteral("OS")][QStringLiteral("ARCH")] = QStringLiteral("i386");
#endif
                    m_SERVER[QStringLiteral("OS")][QStringLiteral("BUILDNUMBER")] = QStringLiteral("unknown");

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
                    m_SERVER[QStringLiteral("OS")][QStringLiteral("NAME")] = osName;

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
                    m_SERVER[QStringLiteral("OS")][QStringLiteral("VERSION")] = osVersion;
#else
#error Windows and Linux OSs are currently supported.
#endif

                    m_CGI[QStringLiteral("AUTH_PASSWORD")] = QStringLiteral("");
                    m_CGI[QStringLiteral("AUTH_TYPE")] = m_Request.m_AuthType;
                    m_CGI[QStringLiteral("AUTH_USER")] = m_Request.m_User;
                    m_CGI[QStringLiteral("CERT_COOKIE")] = QStringLiteral("");
                    m_CGI[QStringLiteral("CERT_FLAGS")] = QStringLiteral("");
                    m_CGI[QStringLiteral("CERT_ISSUER")] = QStringLiteral("");
                    m_CGI[QStringLiteral("CERT_KEYSIZE")] = QStringLiteral("");
                    m_CGI[QStringLiteral("CERT_SECRETKEYSIZE")] = QStringLiteral("");
                    m_CGI[QStringLiteral("CERT_SERIALNUMBER")] = QStringLiteral("");
                    m_CGI[QStringLiteral("CERT_SERVER_ISSUER")] = QStringLiteral("");
                    m_CGI[QStringLiteral("CERT_SERVER_SUBJECT")] = QStringLiteral("");
                    m_CGI[QStringLiteral("CERT_SUBJECT")] = QStringLiteral("");
                    m_CGI[QStringLiteral("CF_TEMPLATE_PATH")] = m_Request.m_Filename;
                    m_CGI[QStringLiteral("CONTENT_LENGTH")] = QStringLiteral("");
                    m_CGI[QStringLiteral("CONTENT_TYPE")] = QStringLiteral("");
                    m_CGI[QStringLiteral("CONTEXT_PATH")] = QStringLiteral("");
                    m_CGI[QStringLiteral("GATEWAY_INTERFACE")] = QStringLiteral("CGI/1.1"); // TODO: Hardcoded.
                    m_CGI[QStringLiteral("HTTPS")] = QStringLiteral("");
                    m_CGI[QStringLiteral("HTTPS_KEYSIZE")] = QStringLiteral("");
                    m_CGI[QStringLiteral("HTTPS_SECRETKEYSIZE")] = QStringLiteral("");
                    m_CGI[QStringLiteral("HTTPS_SERVER_ISSUER")] = QStringLiteral("");
                    m_CGI[QStringLiteral("HTTPS_SERVER_SUBJECT")] = QStringLiteral("");
                    m_CGI[QStringLiteral("HTTP_ACCEPT")] = m_Request.m_Accept;
                    m_CGI[QStringLiteral("HTTP_ACCEPT_ENCODING")] = m_Request.m_AcceptEncoding;
                    m_CGI[QStringLiteral("HTTP_ACCEPT_LANGUAGE")] = m_Request.m_AcceptLanguage;
                    m_CGI[QStringLiteral("HTTP_CONNECTION")] = m_Request.m_Connection;
                    m_CGI[QStringLiteral("HTTP_COOKIE")] = QStringLiteral("");
                    m_CGI[QStringLiteral("HTTP_HOST")] = m_Request.m_Host;
                    m_CGI[QStringLiteral("HTTP_REFERER")] = m_Request.m_Referer;
                    m_CGI[QStringLiteral("HTTP_USER_AGENT")] = m_Request.m_UserAgent;
                    m_CGI[QStringLiteral("PATH_INFO")] = QStringLiteral("");
                    m_CGI[QStringLiteral("PATH_TRANSLATED")] = m_Request.m_Filename;
                    m_CGI[QStringLiteral("QUERY_STRING")] = m_Request.m_Args;
                    m_CGI[QStringLiteral("REMOTE_ADDR")] = m_Request.m_RemoteHost; // TODO: please check me.
                    m_CGI[QStringLiteral("REMOTE_HOST")] = m_Request.m_RemoteHost;
                    m_CGI[QStringLiteral("REMOTE_USER")] = QStringLiteral("");
                    m_CGI[QStringLiteral("REQUEST_METHOD")] = m_Request.m_Method;
                    m_CGI[QStringLiteral("SCRIPT_NAME")] = m_Request.m_URI;
                    m_CGI[QStringLiteral("SERVER_NAME")] = m_Request.m_Host;
                    m_CGI[QStringLiteral("SERVER_PORT")] = QString::number(80); // TODO: Hardcoded.
                    m_CGI[QStringLiteral("SERVER_PORT_SECURE")] = QStringLiteral("0");
                    m_CGI[QStringLiteral("SERVER_PROTOCOL")] = m_Request.m_Protocol;
                    m_CGI[QStringLiteral("SERVER_SOFTWARE")] = QStringLiteral("Todo");
                    m_CGI[QStringLiteral("WEB_SERVER_API")] = QStringLiteral("");
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
						m_URL[key.toUpper()] = value;
					}

                    runApplicationTemplate();

					l_page->run(this);
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

            if (m_COOKIE.m_Type == QWDDX::Struct)
            {
                for(const QString &key : m_COOKIE.m_Struct->keys())
                { // TODO: Unhardcode Max-Age.
                    m_Header.insert("Set-Cookie", key + "=" + m_COOKIE[key].toString()+  "; Max-Age=3600; Path=/; HttpOnly");
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
