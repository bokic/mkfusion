#pragma once

//#include "qrdsserver.h"
#include "qprojectfile.h"
#include "qproject.h"
#include <QString>
#include <QList>

class QRDSProject: public QProject
{
public:
    explicit QRDSProject(const QHash<QString, QString> &);
    virtual ~QRDSProject();
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
    //QRDSServer m_Server;
    char m_DirSeparator;
};
