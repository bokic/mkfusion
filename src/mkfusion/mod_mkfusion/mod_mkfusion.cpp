#include <qsimplifiedlocalsocket.h>
#include <QCoreApplication>
#include <QByteArray>
#include <QDataStream>
#include <QFile>
#include <QDir>

#include <httpd.h>
#include <http_config.h>
#include <http_log.h>
#include <http_protocol.h>
#include <ap_config.h>

const int TIMEOUT = 100;

static void writeError(request_rec *r, const char *error)
{
	r->status = 500;
	r->content_type = "text/html; charset=utf-8";
	ap_rputs(error, r);
}

#ifdef QT_DEBUG
int iterate_func(void *req, const char *key, const char *value)
{
#if AP_SERVER_MINORVERSION_NUMBER > 2
    ap_log_rerror(__FILE__, __LINE__, ap_default_loglevel, APLOG_NOTICE, 0, (request_rec *)req, "New Key/Value pair:[%s], [%s]", key, value);
#else
    ap_log_rerror(__FILE__, __LINE__, APLOG_NOTICE, 0, (request_rec *)req, "New Key/Value pair:[%s], [%s]", key, value);
#endif

	return 1;
}
#endif

static int mkfusion_handler(request_rec *r)
{
	if (strcmp(r->handler, "application/x-httpd-mkfusion"))
	{
		return DECLINED;
	}

#ifdef QT_DEBUG
    apr_table_do(iterate_func, r, r->headers_in, nullptr);

 #if AP_SERVER_MINORVERSION_NUMBER > 2
    ap_log_rerror(__FILE__, __LINE__, ap_default_loglevel, APLOG_NOTICE, 0, r, "Template: %s.", r->filename);
    ap_log_rerror(__FILE__, __LINE__, ap_default_loglevel, APLOG_NOTICE, 0, r, "mod_mkfusion: Before QCoreApplication app();.");
    ap_log_rerror(__FILE__, __LINE__, ap_default_loglevel, APLOG_NOTICE, 0, r, "mod_mkfusion: After QCoreApplication app();.");
 #else
    ap_log_rerror(__FILE__, __LINE__, APLOG_NOTICE, 0, r, "Template: %s.", r->filename);
    ap_log_rerror(__FILE__, __LINE__, APLOG_NOTICE, 0, r, "mod_mkfusion: Before QCoreApplication app();.");
    ap_log_rerror(__FILE__, __LINE__, APLOG_NOTICE, 0, r, "mod_mkfusion: After QCoreApplication app();.");
 #endif
#endif
	QSimplifiedLocalSocket l_localSocket;
#ifdef QT_DEBUG
 #if AP_SERVER_MINORVERSION_NUMBER > 2
    ap_log_rerror(__FILE__, __LINE__, ap_default_loglevel, APLOG_NOTICE, 0, r, "mod_mkfusion: Before l_localSocket.connectToServer(\"mkfusion\");.");
 #else
    ap_log_rerror(__FILE__, __LINE__, APLOG_NOTICE, 0, r, "mod_mkfusion: Before l_localSocket.connectToServer(\"mkfusion\");.");
 #endif
#endif
	l_localSocket.connectToServer("mkfusion", TIMEOUT);
#ifdef QT_DEBUG
 #if AP_SERVER_MINORVERSION_NUMBER > 2
    ap_log_rerror(__FILE__, __LINE__, ap_default_loglevel, APLOG_NOTICE, 0, r, "mod_mkfusion: After l_localSocket.connectToServer(\"mkfusion\");.");
 #else
    ap_log_rerror(__FILE__, __LINE__, APLOG_NOTICE, 0, r, "mod_mkfusion: After l_localSocket.connectToServer(\"mkfusion\");.");
 #endif
#endif

	if (l_localSocket.waitForConnected())
	{
#ifdef QT_DEBUG
 #if AP_SERVER_MINORVERSION_NUMBER > 2
        ap_log_rerror(__FILE__, __LINE__, ap_default_loglevel, APLOG_NOTICE, 0, r, "mod_mkfusion: WaitForConnected() == true.");
 #else
        ap_log_rerror(__FILE__, __LINE__, APLOG_NOTICE, 0, r, "mod_mkfusion: WaitForConnected() == true.");
 #endif
#endif
		QByteArray l_Send;
		QDataStream l_IOStream(&l_Send, QIODevice::WriteOnly);
		l_IOStream.setVersion(QDataStream::Qt_4_4);

		l_IOStream << (quint32)0;
		l_IOStream << r->ap_auth_type;
		l_IOStream << r->user;
        l_IOStream << QDir::toNativeSeparators(r->filename).toUtf8();
		l_IOStream << apr_table_get(r->headers_in, "Accept");
		l_IOStream << apr_table_get(r->headers_in, "Accept-Encoding");
		l_IOStream << apr_table_get(r->headers_in, "Accept-Language");
		//l_IOStream << apr_table_get(r->headers_in, "Accept-Charset"); // New ISO-8859-1,utf-8;q=0.7,*;q=0.3
		l_IOStream << apr_table_get(r->headers_in, "Connection");
        l_IOStream << apr_table_get(r->headers_in, "Content-Type");
		l_IOStream << apr_table_get(r->headers_in, "Host");
		l_IOStream << apr_table_get(r->headers_in, "Referer");
		l_IOStream << apr_table_get(r->headers_in, "User-Agent");
        l_IOStream << apr_table_get(r->headers_in, "Cookie");

        // Transfer POST data.
        ap_setup_client_block(r, REQUEST_CHUNKED_DECHUNK);
        if (ap_should_client_block(r))
        {
            QByteArray buf, chunk;
            chunk.resize(4096);

            while(1)
            {
                long len = ap_get_client_block(r, chunk.data(), 4096);

                if (len < 0)
                {
                    writeError(r, "Error fetching POST data.");
                    return OK;
                }
                else if (len == 0)
                {
                    break;
                }

                buf.append(chunk.left(len));
            }

            l_IOStream << (int)buf.length();
            l_IOStream << buf;
        }
        else
        {
            l_IOStream << (int)0;
        }

//        ap_setup_client_block(r, REQUEST_CHUNKED_DECHUNK);
//        writeError(r, QString("ap_should_client_block(r): %1.<br />").arg(ap_should_client_block(r)).toLatin1());
//        char buf[1024];
//        memset(buf, 0, sizeof(buf));
//        long len = ap_get_client_block(r, buf, sizeof(buf));
//        if( len > 0)
//        {
//            writeError(r, QString("POST: %1.<br />").arg(buf).toLatin1());
//        }
//        return OK;

		l_IOStream << r->args;
		l_IOStream << r->method;
		l_IOStream << r->protocol;
		l_IOStream << r->hostname;
		l_IOStream << r->uri;
		l_IOStream.device()->seek(0);
		l_IOStream << (quint32)l_Send.size();

		if (l_localSocket.write(l_Send) == -1)
		{
			writeError(r, "Can\'t write to mkfusion.<br />\nMake sure mkfusion server is running.");
			return OK;
		}

		bool l_HeadersWritten = false;
		qint32 l_HeaderSize = 0;
		QByteArray l_ReadBuf;

		while(l_localSocket.isValid())
		{
#ifndef Q_OS_WIN
			if (l_localSocket.waitForReadyRead())
#endif
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
#if AP_SERVER_MINORVERSION_NUMBER > 2
                                ap_log_rerror(__FILE__, __LINE__, ap_default_loglevel, APLOG_ERR, 0, r, "mod_mkfusion: Invalid header length.");
#else
                                ap_log_rerror(__FILE__, __LINE__, APLOG_ERR, 0, r, "mod_mkfusion: Invalid header length.");
#endif
								writeError(r, "Invalid header length.");
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
					char *l_content_type = (char *)apr_palloc(r->pool, l_tempByte.size() + 1);
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
#if AP_SERVER_MINORVERSION_NUMBER > 2
        ap_log_rerror(__FILE__, __LINE__, ap_default_loglevel, APLOG_ERR, 0, r, "mod_mkfusion: Can\'t connect to mkfusion. Make sure mkfusion server is running.");
#else
        ap_log_rerror(__FILE__, __LINE__, APLOG_ERR, 0, r, "mod_mkfusion: Can\'t connect to mkfusion. Make sure mkfusion server is running.");
#endif
		writeError(r, "Can\'t connect to mkfusion.<br />\nMake sure mkfusion server is running.");
	}

	return OK;
}

static void mkfusion_register_hooks(apr_pool_t *p)
{
#ifdef QT_DEBUG
    ap_log_perror(__FILE__, __LINE__, APLOG_NOTICE, 0, p, "mod_mkfusion: init.");
#endif

    ap_hook_handler(mkfusion_handler, nullptr, nullptr, APR_HOOK_MIDDLE);
#ifdef Q_OS_WIN
    ap_add_version_component(p, "MKFusion/0.4.5 (Win32)");
#elif defined Q_OS_LINUX
	ap_add_version_component(p, "MKFusion/0.4.5 (Linux)");
#else
#error Windows and Linux OSs are currently supported.
#endif
}

module AP_MODULE_DECLARE_DATA mkfusion_module = {
	STANDARD20_MODULE_STUFF,
    nullptr,                 /* create per-dir    config structures */
    nullptr,                 /* merge  per-dir    config structures */
    nullptr,                 /* create per-server config structures */
    nullptr,                 /* merge  per-server config structures */
    nullptr,                 /* table of config file commands       */
	mkfusion_register_hooks  /* register hooks                      */
};
