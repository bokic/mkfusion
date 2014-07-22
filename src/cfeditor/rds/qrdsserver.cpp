#include "qrdsserver.h"
#include <QVector>
#include <QMap>

QRDSServer::QRDSServer()
{
    m_Description = "localhost";
    m_HostName = "127.0.0.1";
    m_Port = 80;
    //m_ContextRoot = "";
    //m_UserName = "";
    //m_Password = "";
    //m_PromptedPassword.clear();
    //m_Authenticated = false;
    //m_PromptForPassword = false;
}

QString QRDSServer::getDescription()
{
    return m_Description;
}

void QRDSServer::setDescription(QString Desctription)
{
    m_Description = Desctription;
}

QString QRDSServer::getHostName()
{
    return m_HostName;
}

void QRDSServer::setHostName(QString HostName)
{
    m_HostName = HostName;
}

quint16 QRDSServer::getPort()
{
    return m_Port;
}

void QRDSServer::setPort(quint16 Port)
{
    m_Port = Port;
}

QString QRDSServer::getContextRoot()
{
    return m_ContextRoot;
}

void QRDSServer::setContextRoot(QString ContextRoot)
{
    m_ContextRoot = ContextRoot;
}

QString QRDSServer::getUserName()
{
    return m_UserName;
}

void QRDSServer::setUserName(QString UserName)
{
    m_UserName = UserName;
}

QString QRDSServer::getPassword()
{
    return m_Password;
}

void QRDSServer::setPassword(QString Password)
{
    m_Password = Password;
}

bool QRDSServer::getAuthenticated()
{
    return m_Authenticated;
}

void QRDSServer::setAuthenticated(bool Authenticated)
{
    m_Authenticated = Authenticated;
}

bool QRDSServer::getPromptForPassword()
{
    return m_PromptForPassword;
}

void QRDSServer::setPromptForPassword(bool PromptForPassword)
{
    m_PromptForPassword = PromptForPassword;
}

QByteArray QRDSServer::getPromptedPassword()
{
    return m_PromptedPassword;
}

void QRDSServer::setPromptedPassword(QByteArray PromptedPassword)
{
    m_PromptedPassword = PromptedPassword;
}

QVector<QMap<QString, QString> > QRDSServer::getMapping()
{
    return m_Mappings;
}

void QRDSServer::updateMapping(quint32 i, QMap<QString, QString> item)
{
    m_Mappings.replace(i, item);
}

void QRDSServer::addMapping(QMap<QString, QString> item)
{
    m_Mappings.append(item);
}

void QRDSServer::clearMappings()
{
    m_Mappings.clear();
}

int QRDSServer::getMappingCount()
{
    return m_Mappings.size();
}

bool QRDSServer::validateMap(QMap<QString, QString> Map)
{
    if ((!Map.contains("CLIENT_VIEW"))||(!Map.contains("SERVER_VIEW")))
        return false;

    return true;
}
