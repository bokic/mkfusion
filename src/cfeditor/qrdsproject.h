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
	QRDSProject(const QHash<QString, QString>&);
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
	QRDSServer m_Server;
	char m_DirSeparator;
};

#endif // QRDSPROJECT_H
