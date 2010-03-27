#ifndef QSFTPPROJECT_H
#define QSFTPPROJECT_H

#include "qprojectfile.h"
#include "qproject.h"
#include <QString>
#include <QHash>
#include <QList>

#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <fcntl.h>

QT_BEGIN_NAMESPACE

class QSFTPProject: public QProject
{
public:
	QSFTPProject(QHash<QString, QString>);
	~QSFTPProject();
	virtual char getDirSeparator();
	virtual QByteArray ReadFile(QString);
	virtual void WriteFile(QString, QByteArray);
	virtual void DeleteFile(QString);
	virtual void RenameFile(QString, QString);
	virtual QList<QProjectFile> getFolderItems(QString);
	virtual void CreateDir(QString);
	virtual void DeleteDir(QString, bool);
	virtual void RenameDir(QString, QString);
protected:
private:
	ssh_session m_SSHSession;
	sftp_session m_SFTPSession;
};

QT_END_NAMESPACE

#endif // QSFTPPROJECT_H
