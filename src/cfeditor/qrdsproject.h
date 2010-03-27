#ifndef QRDSPROJECT_H
#define QRDSPROJECT_H

#include "qrdsserver.h"
#include "qprojectfile.h"
#include "qproject.h"
#include <QString>
#include <QList>

class QRDSProject: public QProject
{
public:
	QRDSProject(QHash<QString, QString>);
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
	QRDSServer m_Server;
	char m_DirSeparator;
};

#endif // QRDSPROJECT_H
