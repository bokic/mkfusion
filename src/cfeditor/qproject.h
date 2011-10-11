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
	static QProject* LoadProjectFromFile(const QString&);
	static QProject* LoadProjectFromText(const QString&);
    enum QProjectType{BlankProject, LocalProject, RDSProject, FTPProject, SFTPProject};
    QProjectType getType();
	virtual char getDirSeparator() = 0;
	virtual QList<QProjectFile> getFolderItems(const QString&) = 0;
	virtual QByteArray ReadFile(const QString&) = 0;
	virtual void WriteFile(const QString&, const QByteArray&) = 0;
	virtual void DeleteFile(const QString&) = 0;
	virtual void RenameFile(const QString&, const QString&) = 0;
	virtual void CreateDir(const QString&) = 0;
	virtual void DeleteDir(const QString&, bool) = 0;
	virtual void RenameDir(const QString&, const QString&) = 0;
	const QString& getUrl();
    const QString& getPath();
protected:
	QString m_Url;
	QString m_Path;
    QProjectType m_Type;
private:
	QHash<QString, QString> m_Arguments;
	QString m_ProjectFile;
	bool m_ProjectFileSaved;
};

QT_END_NAMESPACE

#endif // QPROJECT_H
