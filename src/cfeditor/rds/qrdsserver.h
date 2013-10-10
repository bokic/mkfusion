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
	QString getDescription();
	void setDescription(QString);
	QString getHostName();
	void setHostName(QString);
	quint16 getPort();
	void setPort(quint16);
	QString getContextRoot();
	void setContextRoot(QString);
	QString getUserName();
	void setUserName(QString);
	QString getPassword();
	void setPassword(QString);
	bool getAuthenticated();
	void setAuthenticated(bool);
	bool getPromptForPassword();
	void setPromptForPassword(bool);
	QByteArray getPromptedPassword();
	void setPromptedPassword(QByteArray);
    QVector<QMap<QString, QString>> getMapping();
	void updateMapping(quint32, QMap<QString, QString>);
	void addMapping(QMap<QString, QString>);
	void clearMappings();
	int getMappingCount();
	//QRDSServer duplicate();
	//static const QString CLIENT_DIR_VIEW;
	//static const QString SERVER_DIR_VIEW;
protected:
	bool validateMap(QMap<QString, QString>);
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
