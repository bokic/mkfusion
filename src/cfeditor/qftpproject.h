#ifndef QFTPPROJECT_H
#define QFTPPROJECT_H

#include "qproject.h"
#include <QNetworkAccessManager>
#include <QString>
#include <QHash>
#include <QList>

class QFTPProject: public QProject
{
public:
	QFTPProject(const QHash<QString, QString>&);
	virtual char getDirSeparator();
	virtual QByteArray ReadFile(const QString&);
	virtual void WriteFile(const QString&, const QByteArray&);
	virtual void DeleteFile(const QString&);
	virtual void RenameFile(const QString&, const QString&);
	virtual QList<QProjectFile> getFolderItems(const QString&);
	virtual void CreateDir(const QString&);
	virtual void DeleteDir(const QString&, bool);
	virtual void RenameDir(const QString&, const QString&);
    const QString &getHostName();
    quint16 getPort();
    const QString &getUsername();
    const QString &getPassword();
protected:
    QString m_HostName;
    quint16 m_Port;
    QString m_Username;
    QString m_Password;
private:
    QNetworkAccessManager m_Network;
};

#endif // QFTPPROJECT_H
