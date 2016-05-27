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
    QSFTPProject(const QHash<QString, QString> &);
    virtual ~QSFTPProject();
    virtual char getDirSeparator();
    virtual QByteArray ReadFile(const QString &);
    virtual void WriteFile(const QString &, const QByteArray &);
    virtual void DeleteFile(const QString &);
    virtual void RenameFile(const QString &, const QString &);
    virtual QList<QProjectFile> getFolderItems(const QString &);
    virtual void CreateDir(const QString &);
    virtual void DeleteDir(const QString &, bool);
    virtual void RenameDir(const QString &, const QString &);
    QString getHostName();
    quint16 getPort();
    QString getUsername();
    QString getPassword();
protected:
    QString m_HostName;
    quint16 m_Port;
    QString m_Username;
    QString m_Password;
private:
    ssh_session m_SSHSession;
    sftp_session m_SFTPSession;
};

QT_END_NAMESPACE

#endif // QSFTPPROJECT_H
