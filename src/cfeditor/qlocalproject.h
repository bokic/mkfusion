#ifndef QLOCALPROJECT_H
#define QLOCALPROJECT_H

#include "qproject.h"
#include <QString>
#include <QHash>
#include <QList>

class QLocalProject: public QProject
{
public:
	QLocalProject(QHash<QString, QString>);
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

#endif // QLOCALPROJECT_H
