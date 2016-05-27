#pragma once

#include <QByteArray>
#include <QString>
#include <QHash>


struct QHttpCodecParameter
{
    QString paramName;
    QString paramValue;
};

struct QHttpCodecValue
{
    QHttpCodecValue()
    {
    }

    QHttpCodecValue(const QString &value)
    {
        this->value = value;
    }

    bool hasParameter(const QString &name) const
    {
        for(int c = 0; c < parameters.count(); c++)
        {
            if (parameters.at(c).paramName == name)
            {
                return true;
            }
        }

        return false;
    }

    QString getParameterValue(const QString &name) const
    {
        for(int c = 0; c < parameters.count(); c++)
        {
            if (parameters.at(c).paramName == name)
            {
                return parameters.at(c).paramValue;
            }
        }

        return "";
    }

    QString value;
    QList<QHttpCodecParameter> parameters;
};

struct QHttpCodecKey
{
    QHttpCodecValue getValue(const QString &name) const
    {
        for(int c = 0; c < values.count(); c++)
        {
            if (values.at(c).value == name)
            {
                return values.at(c);
            }
        }

        return QHttpCodecValue();
    }

    QList<QHttpCodecValue> values;
};


class QHttpCodec
{
public:
    QHttpCodec();
    static QHttpCodec decodeFromByteArray(const QByteArray &source);
    bool contansHeaderKey(const QString &keyName);
    QHttpCodecKey getHeaderKey(const QString &keyName);
    bool isValid();
    QByteArray getBody();

private:
    QHash<QString, QHttpCodecKey> m_HeaderKeys;
    QString m_Error;
    QByteArray m_Body;
    bool m_Valid;
};
