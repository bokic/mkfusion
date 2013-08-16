#include "qcfrunningtemplate.h"
#include "qmkfusionexception.h"
#include "cffunctions.h"
#include "qcfserver.h"
#include "common.h"

#include <QDataStream>
#include <QUrlQuery>
#include <QLibrary>
#include <QDir>
#include <QUrl>

QCFRunningTemplate::QCFRunningTemplate()
	: QObject()
	, m_CFOutput(0)
	, m_ContentType("text/html; charset=utf-8")
	, m_Status(200)
	, m_HeadersSent(false)
	, m_Socket(NULL)
	, m_CFServer(NULL)
{
}

void QCFRunningTemplate::worker()
{
	QByteArray l_RecievedBuffer;
	bool l_FoundRecieveBufSize = false;
	qint32 l_RecieveBufSize = 0;

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

		QLibrary l_TemplateLib;
		QCFTemplate *l_page = 0;
		createCFMTemplateDef createCFMTemplate = 0;

		try
		{
			((QCFServer*)m_CFServer)->m_runningTemplatesLock.lockForRead();

			QString err = ((QCFServer*)m_CFServer)->compileTemplate(m_Request.m_Filename, m_Request.m_URI);
			if (err.isEmpty())
			{
				l_TemplateLib.setFileName(((QCFServer*)m_CFServer)->m_MKFusionPath + "templates/" + ((QCFServer*)m_CFServer)->m_CompiledTemplates[m_Request.m_Filename].m_CompiledFileName);
				if (l_TemplateLib.load() != false)
				{
					createCFMTemplate = (createCFMTemplateDef) l_TemplateLib.resolve("createCFMTemplate");
				}
				else
				{
					m_Status = 500;
					m_Output = "Can\'t load template library.";
				}
			}
			else
			{
				m_Status = 500;
				m_Output = "Compiling error: " + err;
			}

			((QCFServer*)m_CFServer)->m_runningTemplatesLock.unlock();

            if (createCFMTemplate)
			{
				l_page = createCFMTemplate();
                if (l_page)
				{
                    m_APPLICATION.setType(QWDDX::Error);
                    m_SESSION.setType(QWDDX::Error);
                    m_SERVER.setType(QWDDX::Struct);
                    m_CGI.setType(QWDDX::Struct);
                    m_FORM.setType(QWDDX::Struct);
                    m_VARIABLES.setType(QWDDX::Struct);
                    m_URL.setType(QWDDX::Struct);

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
                    m_SERVER[QStringLiteral("COLDFUSION")][QStringLiteral("PRODUCTVERSION")] = QStringLiteral("0.4.2");
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
                    m_SERVER[QStringLiteral("OS")][QStringLiteral("BUILDNUMBER")] = QStringLiteral("");
                    m_SERVER[QStringLiteral("OS")][QStringLiteral("NAME")] = QStringLiteral("Linux");
                    m_SERVER[QStringLiteral("OS")][QStringLiteral("VERSION")] = QStringLiteral("(unknown distribution)"); // TODO: Use: lsb_release -d
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

					l_page->run(this);
				}
				else
				{
					m_Status = 500;
					m_Output = "QCFTemplate == NULL";
				}
			}
			else
			{
				if (m_Status == 200)
				{
					m_Status = 500;
					m_Output = "createCFMTemplate() == NULL";
				}
			}
		}
		catch (const QMKFusionCFAbortException &ex)
		{
		}
		catch (const QMKFusionTemplateException &ex)
		{
			m_Status = 500;
			((QCFServer*)m_CFServer)->m_runningTemplatesLock.unlock();
			m_Output += WriteException(ex, this->m_Request);
		}
		catch (const QMKFusionException &ex)
		{
			m_Status = 500;
			m_Output += WriteException(ex, this->m_Request);
		}

		delete l_page;
        l_page = 0;

		createCFMTemplate = NULL;

		if (l_TemplateLib.isLoaded())
		{
#ifdef Q_OS_WIN
            m_VARIABLES.m_Struct->clear(); // TODO: If this line is not here the app will crash. Check it when possible.
#endif

            l_TemplateLib.unload();
		}

		if (m_HeadersSent == false)
		{
			QByteArray l_header;
			QDataStream l_headerDataStream(&l_header, QIODevice::WriteOnly);
			l_headerDataStream.setVersion(QDataStream::Qt_4_4);

			l_headerDataStream << (qint32) 0;
			l_headerDataStream << m_ContentType;

			l_headerDataStream << m_Status;

			l_headerDataStream << (qint32) m_Header.size();
            for(const QString &l_key: m_Header)
			{
				l_headerDataStream << l_key;
				l_headerDataStream << m_Header[l_key];
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
