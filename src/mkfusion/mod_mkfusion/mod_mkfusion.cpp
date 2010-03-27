#include <QCoreApplication>
#include <QLocalSocket>
#include <QByteArray>
#include <QDataStream>
#include <QFile>
#include <QDir>

#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"

#define CONNECT_TIMEOUT 1000
#define READ_TIMEOUT 100

void log(const QString& p_Line)
{
#ifdef Q_WS_WIN
	QFile l_Log("c:\\mod_mkfusion.log");
#elif defined Q_WS_X11
	QFile l_Log("/opt/mkfusion/logs/mod_server.log");
#else
#error Windows and Linux OSs are currently supported.
#endif
	l_Log.open(QIODevice::WriteOnly	| QIODevice::Append);
	if (l_Log.size() == 0)
	{
		l_Log.write("\xEF\xBB\xBF"); // Add utf-8 BOM.
	}
#ifdef Q_WS_WIN
	l_Log.write(p_Line.toUtf8() + "\r\n");
#else
	l_Log.write(p_Line.toUtf8() + "\n");
#endif
	l_Log.close();
}

static void writeError(request_rec *r, char *error)
{
	r->status = 500;
	r->content_type = "text/html; charset=utf-8";
	ap_rputs(error, r);
}

static int mkfusion_handler(request_rec *r)
{
	if (strcmp(r->handler, "application/x-httpd-mkfusion"))
	{
		return DECLINED;
	}

	log("Before app().");
	QCoreApplication app();
	log("After app().");

	log("Before connect.");
	log(QDir::toNativeSeparators(r->filename));
	log("Before QIODevice().");
	//QIODevice de(NULL);
	log("After QIODevice().");
	QLocalSocket l_localSocket(NULL);
	log("Before connect sent.");
	l_localSocket.connectToServer("mkfusion");
	log("After connect sent.");

	if (l_localSocket.waitForConnected(CONNECT_TIMEOUT))
	{
		QByteArray l_Send;
		QDataStream l_IOStream(&l_Send, QIODevice::WriteOnly);
		l_IOStream.setVersion(QDataStream::Qt_4_4);

		l_IOStream << (quint32)0;
		l_IOStream << r->ap_auth_type;
		l_IOStream << r->user;
		l_IOStream << QDir::toNativeSeparators(r->filename).toLatin1();
		l_IOStream << apr_table_get(r->headers_in, "Accept");
		l_IOStream << apr_table_get(r->headers_in, "Accept-Encoding");
		l_IOStream << apr_table_get(r->headers_in, "Accept-Language");
		l_IOStream << apr_table_get(r->headers_in, "Connection");
		l_IOStream << apr_table_get(r->headers_in, "Host");
		l_IOStream << apr_table_get(r->headers_in, "Referer");
		l_IOStream << apr_table_get(r->headers_in, "User-Agent");
		l_IOStream << r->args;
		l_IOStream << r->method;
		l_IOStream << r->protocol;
		l_IOStream.device()->seek(0);
		l_IOStream << (quint32)l_Send.size();

		if (l_localSocket.write(l_Send) == -1)
		{
			writeError(r, (char*)"Can\'t write to mkfusion.<br />\nMake sure mkfusion server is running.");
			return OK;
		}

		if (!l_localSocket.waitForBytesWritten(30000))
		{
			writeError(r, (char*)"Can\'t write to mkfusion.<br />\nMake sure mkfusion server is running.");
			return OK;
		}

		bool l_HeadersWritten = false;
		qint32 l_HeaderSize = 0;
		QByteArray l_ReadBuf;

		while(l_localSocket.isValid())
		{
			if (l_localSocket.waitForReadyRead(READ_TIMEOUT))
			{
				l_ReadBuf = l_localSocket.readAll();

				if (l_HeadersWritten == false)
				{
					if (l_HeaderSize == 0)
					{
						if (l_ReadBuf.size() >= 4)
						{
							QDataStream l_HeadersDataStream(&l_ReadBuf, QIODevice::ReadOnly);
							l_HeadersDataStream.setVersion(QDataStream::Qt_4_4);
							l_HeadersDataStream >> l_HeaderSize;
							if ((l_HeaderSize <= 0)||(l_HeaderSize > 0x01000000))
							{
								writeError(r, (char*)"Invalid header length.");
								return OK;
							}
						}
					}

					if ((l_HeaderSize < 4)||(l_ReadBuf.size() < l_HeaderSize))
					{
						continue;
					}

					QByteArray l_Header = l_ReadBuf.left(l_HeaderSize);
					l_ReadBuf = l_ReadBuf.right(l_ReadBuf.size() - l_HeaderSize);

					QDataStream l_HeadersDataStream(&l_Header, QIODevice::ReadOnly);
					l_HeadersDataStream.setVersion(QDataStream::Qt_4_4);
					l_HeadersDataStream >> l_HeaderSize;

					QString l_tempStr;
					l_HeadersDataStream >> l_tempStr;
					QByteArray l_tempByte = l_tempStr.toUtf8();
					char* l_content_type = (char*)apr_palloc(r->pool, l_tempByte.size() + 1);
					memcpy(l_content_type, l_tempByte.constData(), l_tempByte.size() + 1);
					r->content_type = l_content_type;

					l_HeadersDataStream >> r->status;

					qint32 l_HeaderLen;
					l_HeadersDataStream >> l_HeaderLen;
					for (qint32 c = 0; c < l_HeaderLen; c++)
					{
						QString key, val;

						l_HeadersDataStream >> key;
						l_HeadersDataStream >> val;

						apr_table_add(r->headers_out, key.toUtf8().constData(), val.toUtf8().constData());
					}
					l_HeadersWritten = true;
				}

				if (l_ReadBuf.size() > 0)
				{
					ap_rwrite(l_ReadBuf.constData(), l_ReadBuf.size(), r);
				}

				l_ReadBuf.clear();
			}
		}
	}
	else
	{
		writeError(r, (char*)"Can\'t connect to mkfusion.<br />\nMake sure mkfusion server is running.");
	}

	return OK;
}

static void mkfusion_register_hooks(apr_pool_t *p)
{
	log("mod_mkfusion init.");
	ap_hook_handler(mkfusion_handler, NULL, NULL, APR_HOOK_MIDDLE);
#ifdef Q_WS_WIN
	ap_add_version_component(p, "MKFusion/0.4.1 (Win32)");
#elif defined Q_WS_X11
	ap_add_version_component(p, "MKFusion/0.4.1 (Linux)");
#else
#error Windows and Linux OSs are currently supported.
#endif
}

module AP_MODULE_DECLARE_DATA mkfusion_module = {
	STANDARD20_MODULE_STUFF,
	NULL,                    /* create per-dir    config structures */
	NULL,                    /* merge  per-dir    config structures */
	NULL,                    /* create per-server config structures */
	NULL,                    /* merge  per-server config structures */
	NULL,                    /* table of config file commands       */
	mkfusion_register_hooks  /* register hooks                      */
};