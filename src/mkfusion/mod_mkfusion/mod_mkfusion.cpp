#include <qsimplifiedlocalsocket.h>
#include <QCoreApplication>
#include <QDataStream>
#include <QByteArray>

#include <httpd.h>
#include <http_config.h>
#include <http_log.h>
#include <http_protocol.h>
#include <ap_config.h>

const int TIMEOUT = 100;

#ifdef QT_DEBUG
    #if AP_SERVER_MINORVERSION_NUMBER > 2
        #define AP_LOG_RERROR(TEXT...) ap_log_rerror(__FILE__, __LINE__, ap_default_loglevel, APLOG_NOTICE, 0, req, TEXT);
        #define AP_LOG_PERROR(TEXT...) ap_log_perror(__FILE__, __LINE__, ap_default_loglevel, APLOG_NOTICE, 0, p, TEXT);
    #else
        #define AP_LOG_RERROR(TEXT...) ap_log_rerror(__FILE__, __LINE__, APLOG_NOTICE, 0, req, TEXT);
        #define AP_LOG_PERROR(TEXT...) ap_log_perror(__FILE__, __LINE__, APLOG_NOTICE, 0, p, TEXT);
    #endif
#else
#define AP_LOG_RERROR(TEXT...)
#endif

#ifdef Q_OS_WIN
    #define OS_STR "Win32"
#elif defined Q_OS_LINUX
    #define OS_STR "Linux"
#else
    #define OS_STR "Unknown"
#endif


static void write_error(request_rec *req, const char *error)
{
    req->status = 500;
    req->content_type = "text/html; charset=utf-8";
    ap_rputs(error, req);
}

int iterate_func(void *r, const char *key, const char *value)
{
    request_rec *req = (request_rec *)r;

    AP_LOG_RERROR("New Key/Value pair:[%s], [%s]", key, value);

    return 1;
}

static int mkfusion_handler(request_rec *req)
{
    if (strcmp(req->handler, "application/x-httpd-mkfusion"))
    {
        return DECLINED;
    }

#ifdef QT_DEBUG
    apr_table_do(iterate_func, req, req->headers_in, nullptr);
#endif

    AP_LOG_RERROR("Template: %s.", req->filename);
    AP_LOG_RERROR("mod_mkfusion: Before QCoreApplication app();.");
    AP_LOG_RERROR("mod_mkfusion: After QCoreApplication app();.");

    QSimplifiedLocalSocket l_localSocket;

    AP_LOG_RERROR("mod_mkfusion: Before l_localSocket.connectToServer(\"mkfusion\");.");
    l_localSocket.connectToServer("mkfusion", TIMEOUT);
    AP_LOG_RERROR("mod_mkfusion: After l_localSocket.connectToServer(\"mkfusion\");.");

    if (l_localSocket.waitForConnected())
    {
        AP_LOG_RERROR("mod_mkfusion: WaitForConnected() == true.");

        QByteArray l_Send;
        QDataStream stream(&l_Send, QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_5_0);

        stream << req->filename;

        qint64 chunk_pos = stream.device()->pos();

        stream << (qint64)0;
        stream << req->ap_auth_type;
        stream << req->user;
        stream << apr_table_get(req->headers_in, "Accept");
        stream << apr_table_get(req->headers_in, "Accept-Encoding");
        stream << apr_table_get(req->headers_in, "Accept-Language");
        //stream << apr_table_get(r->headers_in, "Accept-Charset"); // New ISO-8859-1,utf-8;q=0.7,*;q=0.3
        stream << apr_table_get(req->headers_in, "Connection");
        stream << apr_table_get(req->headers_in, "Content-Type");
        stream << apr_table_get(req->headers_in, "Host");
        stream << apr_table_get(req->headers_in, "Referer");
        stream << apr_table_get(req->headers_in, "User-Agent");
        stream << apr_table_get(req->headers_in, "Cookie");

        // Transfer POST data.
        ap_setup_client_block(req, REQUEST_CHUNKED_DECHUNK);
        if (ap_should_client_block(req))
        {
            QByteArray buf, chunk;
            chunk.resize(4096);

            while(1)
            {
                long len = ap_get_client_block(req, chunk.data(), 4096);

                if (len < 0)
                {
                    write_error(req, "Error fetching POST data.");
                    return OK;
                }
                else if (len == 0)
                {
                    break;
                }

                buf.append(chunk.left(len));
            }

            stream << (int)buf.length();
            stream << buf;
        }
        else
        {
            stream << 0;
        }

        stream << req->args;
        stream << req->method;
        stream << req->protocol;
        stream << req->hostname;
        stream << req->uri;
        stream.device()->seek(chunk_pos);
        stream << (qint64)l_Send.size() - chunk_pos;

        if (l_localSocket.write(l_Send) == -1)
        {
            write_error(req, "Can\'t write to mkfusion.<br />\nMake sure mkfusion server is running.");
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
                            l_HeadersDataStream.setVersion(QDataStream::Qt_5_0);
                            l_HeadersDataStream >> l_HeaderSize;
                            if ((l_HeaderSize <= 0)||(l_HeaderSize > 0x01000000))
                            {
                                AP_LOG_RERROR("mod_mkfusion: Invalid header length.");
                                write_error(req, "Invalid header length.");
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
                    l_HeadersDataStream.setVersion(QDataStream::Qt_5_0);
                    l_HeadersDataStream >> l_HeaderSize;

                    QString l_tempStr;
                    l_HeadersDataStream >> l_tempStr;
                    QByteArray l_tempByte = l_tempStr.toUtf8();
                    char *l_content_type = (char *)apr_palloc(req->pool, l_tempByte.size() + 1);
                    memcpy(l_content_type, l_tempByte.constData(), l_tempByte.size() + 1);
                    req->content_type = l_content_type;

                    l_HeadersDataStream >> req->status;

                    qint32 l_HeaderLen;
                    l_HeadersDataStream >> l_HeaderLen;
                    for (qint32 c = 0; c < l_HeaderLen; c++)
                    {
                        QString key, val;

                        l_HeadersDataStream >> key;
                        l_HeadersDataStream >> val;

                        apr_table_add(req->headers_out, key.toUtf8().constData(), val.toUtf8().constData());
                    }
                    l_HeadersWritten = true;
                }

                if (l_ReadBuf.size() > 0)
                {
                    ap_rwrite(l_ReadBuf.constData(), l_ReadBuf.size(), req);
                }

                l_ReadBuf.clear();
            }
        }
    }
    else
    {
        AP_LOG_RERROR("mod_mkfusion: Can\'t connect to mkfusion. Make sure mkfusion server is running.");
        write_error(req, "Can\'t connect to mkfusion.<br />\nMake sure mkfusion server is running.");
    }

    return OK;
}

static void mkfusion_register_hooks(apr_pool_t *p)
{
    AP_LOG_PERROR("mod_mkfusion: init.");

    ap_hook_handler(mkfusion_handler, nullptr, nullptr, APR_HOOK_MIDDLE);
    ap_add_version_component(p, "MKFusion/0.5.0 (" OS_STR ")");
}

module AP_MODULE_DECLARE_DATA mkfusion_module =
{
    STANDARD20_MODULE_STUFF,
    nullptr,                 /* create per-dir    config structures */
    nullptr,                 /* merge  per-dir    config structures */
    nullptr,                 /* create per-server config structures */
    nullptr,                 /* merge  per-server config structures */
    nullptr,                 /* table of config file commands       */
    mkfusion_register_hooks  /* register hooks                      */
};
