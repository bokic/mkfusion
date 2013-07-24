#ifndef QLOCALPROJECT_H
#define QLOCALPROJECT_H

#include "qproject.h"
#include <QString>
#include <QHash>
#include <QList>

class QLocalProject: public QProject
{
public:
	explicit QLocalProject(const QHash<QString, QString>&);
	virtual ~QLocalProject();
	
	virtual char getDirSeparator();
	virtual QByteArray ReadFile(const QString&);
	virtual void WriteFile(const QString&, const QByteArray&);
	virtual void DeleteFile(const QString&);
	virtual void RenameFile(const QString&, const QString&);
	virtual QList<QProjectFile> getFolderItems(const QString&);
	virtual void CreateDir(const QString&);
	virtual void DeleteDir(const QString&, bool);
	virtual void RenameDir(const QString&, const QString&);
protected:
private:
};

#endif // QLOCALPROJECT_H
