#include "qrdsserver.h"
#include <QVector>
#include <QMap>

QRDSServer::QRDSServer()
{
}

QString QRDSServer::description() const
{
    return m_Description;
}

void QRDSServer::setDescription(const QString &description)
{
    m_Description = description;
}

QString QRDSServer::hostname() const
{
    return m_HostName;
}

void QRDSServer::setHostname(const QString &hostname)
{
    m_HostName = hostname;
}

quint16 QRDSServer::port() const
{
    return m_Port;
}

void QRDSServer::setPort(quint16 port)
{
    m_Port = port;
}

QString QRDSServer::contextRoot() const
{
    return m_ContextRoot;
}

void QRDSServer::setContextRoot(const QString &ContextRoot)
{
    m_ContextRoot = ContextRoot;
}

QString QRDSServer::username() const
{
    return m_UserName;
}

void QRDSServer::setUsername(const QString &username)
{
    m_UserName = username;
}

QString QRDSServer::password() const
{
    return m_Password;
}

void QRDSServer::setPassword(const QString &password)
{
    m_Password = password;
}

bool QRDSServer::authenticated() const
{
    return m_Authenticated;
}

void QRDSServer::setAuthenticated(bool Authenticated)
{
    m_Authenticated = Authenticated;
}

bool QRDSServer::promptForPassword() const
{
    return m_PromptForPassword;
}

void QRDSServer::setPromptForPassword(bool PromptForPassword)
{
    m_PromptForPassword = PromptForPassword;
}

QByteArray QRDSServer::promptedPassword() const
{
    return m_PromptedPassword;
}

void QRDSServer::setPromptedPassword(const QByteArray &PromptedPassword)
{
    m_PromptedPassword = PromptedPassword;
}

QVector<QMap<QString, QString>> QRDSServer::mapping() const
{
    return m_Mappings;
}

void QRDSServer::updateMapping(quint32 i, const QMap<QString, QString> &item)
{
    m_Mappings.replace(i, item);
}

void QRDSServer::addMapping(const QMap<QString, QString> &item)
{
    m_Mappings.append(item);
}

void QRDSServer::clearMappings()
{
    m_Mappings.clear();
}

int QRDSServer::mappingCount() const
{
    return m_Mappings.size();
}

bool QRDSServer::validateMap(const QMap<QString, QString> &map) const
{
    if ((!map.contains(QStringLiteral("CLIENT_VIEW")))||(!map.contains(QStringLiteral("SERVER_VIEW"))))
    {
        return false;
    }

    return true;
}
