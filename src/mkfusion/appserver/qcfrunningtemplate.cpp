#include "qmkfusionexception.h"
#include "qcfrunningtemplate.h"
#include "cffunctions.h"
#include "qcfserver.h"
#include "common.h"

#include <QDataStream>
#include <QLibrary>
#include <QDir>
#include <QUrl>

QCFRunningTemplate::QCFRunningTemplate()
{
	m_Socket = NULL;
	m_CFServer = NULL;
	m_ContentType = "text/html; charset=utf-8";
	m_Status = 200;
	m_HeadersSent = false;
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

		l_ds >> tempstr;
		if (tempstr)
		{
			m_Request.m_Filename = QDir::toNativeSeparators(QString::fromUtf8(tempstr));
			delete[] tempstr;
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
		QCFTemplate* l_page = NULL;
		createCFMTemplateDef createCFMTemplate = NULL;

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

			if (createCFMTemplate != NULL)
			{
				l_page = createCFMTemplate();
				if (l_page != NULL)
				{
					m_APPLICATION.m_Type = QWDDX::Error;
					m_SESSION.m_Type = QWDDX::Error;
					m_SERVER.m_Type = QWDDX::Struct;
					m_CGI.m_Type = QWDDX::Struct;
					m_FORM.m_Type = QWDDX::Struct;
					m_VARIABLES.m_Type = QWDDX::Struct;

					// Run compiled template(dll/so).
					m_SERVER.wr(true)["COLDFUSION"] = QWDDX(QWDDX::Struct);
					m_SERVER.wr(true)["COLDFUSION"]["APPSERVER"] = "mkfusion";
					m_SERVER.wr(true)["COLDFUSION"]["EXPIRATION"] = QDateTime::currentDateTime();
#ifdef Q_WS_WIN
					m_SERVER.wr(true)["COLDFUSION"]["INSTALLKIT"] = "Windows";
#elif defined Q_WS_X11
					m_SERVER.wr(true)["COLDFUSION"]["INSTALLKIT"] = "Linux";
#else
#error Windows and Linux OSs are currently supported.
#endif
					m_SERVER.wr(true)["COLDFUSION"]["PRODUCTLEVEL"] = "Free";
					m_SERVER.wr(true)["COLDFUSION"]["PRODUCTNAME"] = "MKFusion Server";
					m_SERVER.wr(true)["COLDFUSION"]["PRODUCTVERSION"] = "0.4.1";
					m_SERVER.wr(true)["COLDFUSION"]["ROOTDIR"] = ((QCFServer*)m_CFServer)->m_MKFusionPath.left(-1);
					m_SERVER.wr(true)["COLDFUSION"]["SUPPORTEDLOCALES"] = "English (US),en,en_US";
					m_SERVER.wr(true)["OS"] = QWDDX(QWDDX::Struct);
#ifdef Q_WS_WIN
					m_SERVER.wr(true)["OS"]["ADDITIONALINFORMATION"] = "Windows";
					m_SERVER.wr(true)["OS"]["ARCH"] = "i386";
					m_SERVER.wr(true)["OS"]["BUILDNUMBER"] = "";
					m_SERVER.wr(true)["OS"]["NAME"] = "WINDOWS";
					m_SERVER.wr(true)["OS"]["VERSION"] = "XP";
#elif defined Q_WS_X11
					m_SERVER.wr(true)["OS"]["ADDITIONALINFORMATION"] = "Linux";
					m_SERVER.wr(true)["OS"]["ARCH"] = "i386";
					m_SERVER.wr(true)["OS"]["BUILDNUMBER"] = "";
					m_SERVER.wr(true)["OS"]["NAME"] = "Linux";
					m_SERVER.wr(true)["OS"]["VERSION"] = "(unknown distribution)";
#else
#error Windows and Linux OSs are currently supported.
#endif

					m_CGI.wr(true)["AUTH_PASSWORD"] = "";
					m_CGI.wr(true)["AUTH_TYPE"] = m_Request.m_AuthType;
					m_CGI.wr(true)["AUTH_USER"] = m_Request.m_User;
					m_CGI.wr(true)["CERT_COOKIE"] = "";
					m_CGI.wr(true)["CERT_FLAGS"] = "";
					m_CGI.wr(true)["CERT_ISSUER"] = "";
					m_CGI.wr(true)["CERT_KEYSIZE"] = "";
					m_CGI.wr(true)["CERT_SECRETKEYSIZE"] = "";
					m_CGI.wr(true)["CERT_SERIALNUMBER"] = "";
					m_CGI.wr(true)["CERT_SERVER_ISSUER"] = "";
					m_CGI.wr(true)["CERT_SERVER_SUBJECT"] = "";
					m_CGI.wr(true)["CERT_SUBJECT"] = "";
					m_CGI.wr(true)["CF_TEMPLATE_PATH"] = m_Request.m_Filename;
					m_CGI.wr(true)["CONTENT_LENGTH"] = "";
					m_CGI.wr(true)["CONTENT_TYPE"] = "";
					m_CGI.wr(true)["CONTEXT_PATH"] = "";
					m_CGI.wr(true)["GATEWAY_INTERFACE"] = "CGI/1.1"; // TODO: Hardcoded.
					m_CGI.wr(true)["HTTPS"] = "";
					m_CGI.wr(true)["HTTPS_KEYSIZE"] = "";
					m_CGI.wr(true)["HTTPS_SECRETKEYSIZE"] = "";
					m_CGI.wr(true)["HTTPS_SERVER_ISSUER"] = "";
					m_CGI.wr(true)["HTTPS_SERVER_SUBJECT"] = "";
					m_CGI.wr(true)["HTTP_ACCEPT"] = m_Request.m_Accept;
					m_CGI.wr(true)["HTTP_ACCEPT_ENCODING"] = m_Request.m_AcceptEncoding;
					m_CGI.wr(true)["HTTP_ACCEPT_LANGUAGE"] = m_Request.m_AcceptLanguage;
					m_CGI.wr(true)["HTTP_CONNECTION"] = m_Request.m_Connection;
					m_CGI.wr(true)["HTTP_COOKIE"] = "";
					m_CGI.wr(true)["HTTP_HOST"] = m_Request.m_Host;
					m_CGI.wr(true)["HTTP_REFERER"] = m_Request.m_Referer;
					m_CGI.wr(true)["HTTP_USER_AGENT"] = m_Request.m_UserAgent;
					m_CGI.wr(true)["PATH_INFO"] = "";
					m_CGI.wr(true)["PATH_TRANSLATED"] = m_Request.m_Filename;
					m_CGI.wr(true)["QUERY_STRING"] = m_Request.m_Args;
					m_CGI.wr(true)["REMOTE_ADDR"] = m_Request.m_RemoteHost; // TODO: please check me.
					m_CGI.wr(true)["REMOTE_HOST"] = m_Request.m_RemoteHost;
					m_CGI.wr(true)["REMOTE_USER"] = "";
					m_CGI.wr(true)["REQUEST_METHOD"] = m_Request.m_Method;
					m_CGI.wr(true)["SCRIPT_NAME"] = m_Request.m_URI;
					m_CGI.wr(true)["SERVER_NAME"] = m_Request.m_Host;
					m_CGI.wr(true)["SERVER_PORT"] = QString::number(80); // TODO: Hardcoded.
					m_CGI.wr(true)["SERVER_PORT_SECURE"] = "0";
					m_CGI.wr(true)["SERVER_PROTOCOL"] = m_Request.m_Protocol;
					m_CGI.wr(true)["SERVER_SOFTWARE"] = "Todo";
					m_CGI.wr(true)["WEB_SERVER_API"] = "";
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

					QList<QPair<QString, QString> > l_Arguments = l_url.queryItems();
					QPair<QString, QString> l_Argument;

					foreach(l_Argument, l_Arguments)
					{
						QString key = l_Argument.first;
						QString value = l_Argument.second;
						m_URL.wr(true)[key] = value;
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
		catch (QMKFusionCFAbortException&)
		{
		}
		catch (QMKFusionTemplateException& ex)
		{
			m_Status = 500;
			((QCFServer*)m_CFServer)->m_runningTemplatesLock.unlock();
			m_Output += WriteException(ex, this->m_Request);
		}
		catch (QMKFusionException& ex)
		{
			m_Status = 500;
			m_Output += WriteException(ex, this->m_Request);
		}

		delete l_page;
		createCFMTemplate = NULL;

		if (l_TemplateLib.isLoaded())
		{
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
			foreach(QString l_key, m_Header)
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
	m_Socket->deleteLater();
	deleteLater();

	emit finished();
}
