#ifndef QRDSSERVER_H
#define QRDSSERVER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QHash>
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
    QString m_Description;
    QString m_HostName;
    quint16 m_Port;
    QString m_ContextRoot;
    QString m_UserName;
    QString m_Password;
    bool m_PromptForPassword;
    QByteArray m_PromptedPassword;
    bool m_Authenticated;
    QVector<QMap<QString, QString>> m_Mappings;
};

#endif // QRDSSERVER_H
