#pragma once

#include <QString>
#include <QVector>
#include <QMap>

class QRDSServer
{
public:
    QRDSServer();
    QString description() const;
    void setDescription(const QString &description);
    QString hostname() const;
    void setHostname(const QString &hostname);
    quint16 port() const;
    void setPort(quint16 port);
    QString contextRoot() const;
    void setContextRoot(const QString &ContextRoot);
    QString username() const;
    void setUsername(const QString &username);
    QString password() const;
    void setPassword(const QString &password);
    bool authenticated() const;
    void setAuthenticated(bool);
    bool promptForPassword() const;
    void setPromptForPassword(bool);
    QByteArray promptedPassword() const;
    void setPromptedPassword(const QByteArray &PromptedPassword);
    QVector<QMap<QString, QString>> mapping() const;
    void updateMapping(quint32, const QMap<QString, QString> &item);
    void addMapping(const QMap<QString, QString> &item);
    void clearMappings();
    int mappingCount() const;
protected:
    bool validateMap(const QMap<QString, QString> &map) const;
private:
    QString m_Description = QStringLiteral("localhost");
    QString m_HostName = QStringLiteral("127.0.0.1");
    quint16 m_Port = 80;
    QString m_ContextRoot;
    QString m_UserName;
    QString m_Password;
    bool m_PromptForPassword = false;
    QByteArray m_PromptedPassword;
    bool m_Authenticated = false;
    QVector<QMap<QString, QString>> m_Mappings;
};
