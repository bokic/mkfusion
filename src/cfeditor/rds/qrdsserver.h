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
	void setDescription(QString);
    QString hostname() const;
    void setHostname(QString);
    quint16 port() const;
	void setPort(quint16);
    QString contextRoot() const;
	void setContextRoot(QString);
    QString username() const;
    void setUsername(QString);
    QString password() const;
	void setPassword(QString);
    bool authenticated() const;
	void setAuthenticated(bool);
    bool promptForPassword() const;
	void setPromptForPassword(bool);
    QByteArray promptedPassword() const;
	void setPromptedPassword(QByteArray);
    QVector<QMap<QString, QString>> mapping() const;
	void updateMapping(quint32, QMap<QString, QString>);
	void addMapping(QMap<QString, QString>);
	void clearMappings();
    int getMappingCount() const;
	//static const QString CLIENT_DIR_VIEW;
	//static const QString SERVER_DIR_VIEW;
protected:
    bool validateMap(QMap<QString, QString>) const;
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
