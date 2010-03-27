#ifndef QPROJECT_H
#define QPROJECT_H

#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <fcntl.h>

#include "qprojectfile.h"
#include <QString>
#include <QHash>
#include <QList>

QT_BEGIN_NAMESPACE

class QProject: public QObject
{
public:
	QProject();
	static QProject* LoadProjectFromFile(QString);
	static QProject* LoadProjectFromText(QString);
	enum ProjectType{LocalProject, RDSProject, FTPProject, SFTPProject};
	virtual char getDirSeparator() = 0;
	virtual QList<QProjectFile> getFolderItems(QString) = 0;
	virtual QByteArray ReadFile(QString) = 0;
	virtual void WriteFile(QString, QByteArray) = 0;
	virtual void DeleteFile(QString) = 0;
	virtual void RenameFile(QString, QString) = 0;
	virtual void CreateDir(QString) = 0;
	virtual void DeleteDir(QString, bool) = 0;
	virtual void RenameDir(QString, QString) = 0;
	QString getUrl();
protected:
	QString m_Url;
	QString m_Path;
private:
	ProjectType m_Type;
	QHash<QString, QString> m_Arguments;
	QString m_SavedAt;
	bool m_Modified;
};

QT_END_NAMESPACE

#endif // QPROJECT_H
