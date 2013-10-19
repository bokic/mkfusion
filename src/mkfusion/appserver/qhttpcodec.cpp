#include "qhttpcodec.h"
#include <QStringList>
#include <QByteArray>


QHttpCodec::QHttpCodec()
    : m_Valid(false)
{
}

QHttpCodec QHttpCodec::decodeFromByteArray(const QByteArray &source)
{
    QHttpCodec ret;

    int sep1, sep2;

    sep1 = source.indexOf("\r\n\r\n");

    if (sep1 < 0)
    {
        ret.m_Error = "Didn\'t found separator.";

        return ret;
    }

    QString header = QString::fromUtf8(source.left(sep1));
    ret.m_Body = source.right(source.length() - sep1 - 4);

    for(QString line : header.split("\r\n"))
    {
        sep1 = line.indexOf(':');

        if (sep1 <= 0)
        {
            ret.m_Error = "Invalid key name.";

            return ret;
        }

        QString key = line.left(sep1);

        line = line.right(line.length() - sep1 - 1).trimmed();

        while(!line.isEmpty())
        {
            QHttpCodecKey codecKey;

            sep1 = line.indexOf(';');
            sep2 = line.indexOf(',');

            if ((sep1 == -1)&&(sep2 == -1))
            {
                codecKey.values.push_front(QHttpCodecValue(line));
                ret.m_HeaderKeys.insert(key, codecKey);
                line.clear();

                continue;
            }
            else if ((sep1 > -1)&&(sep2 == -1))
            {
                QHttpCodecValue codecValue;

                codecValue = QHttpCodecValue(line.left(sep1));

                do
                {
                    line = line.right(line.length() - sep1 - 1).trimmed();

                    sep1 = line.indexOf('=');
                    if(sep1 < 1)
                    {
                        ret.m_Error = "No [=] separator.";

                        return ret;
                    }

                    QHttpCodecParameter param;

                    param.paramName = line.left(sep1);

                    line = line.right(line.length() - sep1 - 1).trimmed();

                    if(line.isEmpty())
                    {
                        ret.m_Error = "No parameter value.";

                        return ret;
                    }

                    if (line.at(0) =='\"')
                    {
                        sep1 = line.indexOf('\"', 1);

                        if (sep1 == -1)
                        {
                            ret.m_Error = "No parameter value.";

                            return ret;
                        }

                        param.paramValue = line.mid(1, sep1 - 1);

                        line = line.right(line.length() - sep1 - 1).trimmed();
                    }
                    else
                    {
                        ret.m_Error = "Unimplemented parameter value.";

                        return ret;
                    }

                    codecValue.parameters.push_back(param);

                    sep1 = line.indexOf(';');

                } while(!line.isEmpty());

                codecKey.values.push_front(codecValue);
                ret.m_HeaderKeys.insert(key, codecKey);
                line.clear();

                continue;
            }
            else
            {
                ret.m_Error = "Unimplemented.";

                return ret;
            }
        }
    }

    ret.m_Valid = true;

    return ret;
}

bool QHttpCodec::contansHeaderKey(const QString &keyName)
{
    return m_HeaderKeys.contains(keyName);
}

const QHttpCodecKey * QHttpCodec::getHeaderKey(const QString &keyName)
{
    return &m_HeaderKeys[keyName];
}

bool QHttpCodec::isValid()
{
    return m_Valid;
}

QByteArray QHttpCodec::getBody()
{
    return m_Body;
}
