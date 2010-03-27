#ifndef QFTPPROJECT_H
#define QFTPPROJECT_H

#include "qproject.h"
#include <QString>
#include <QHash>
#include <QList>

class QFTPProject: public QProject
{
public:
	QFTPProject(QHash<QString, QString>);
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
};

#endif // QFTPPROJECT_H
