#ifndef QFILEIOSERVICE_H
#define QFILEIOSERVICE_H

#include "qabstractrdsservice.h"
#include <QObject>
#include <QString>
#include <QVector>
#include <QList>
#include <QMap>

class QFileIOService : public QAbstractRDSService
{
public:
    enum Command
    {
        BrowseDirCommand,
        FileReadCommand,
        FileWriteCommand,
        FileRenameCommand,
        FileRemoveFileCommand,
        FileRemoveDirectoryCommand,
        FileExistCommand,
        FileCreateDirCommand,
        FileGetRootDirCommand
    };

    QFileIOService() : QAbstractRDSService() {}
    virtual ~QFileIOService() {}

    virtual QByteArray ExecuteRDSCommand(QRDSServer, quint8, QMap<QString, QString>);
protected:
private:
    QByteArray BrowseDir(QRDSServer, QMap<QString, QString>);
    QByteArray FileRead(QRDSServer, QMap<QString, QString>);
    QByteArray FileWrite(QRDSServer, QMap<QString, QString>);
    QByteArray FileRename(QRDSServer, QMap<QString, QString>);
    QByteArray FileRemove(QRDSServer, QMap<QString, QString>, bool);
    QByteArray Existence(QRDSServer, QMap<QString, QString>);
    QByteArray CreateDir(QRDSServer, QMap<QString, QString>);
    QByteArray GetRootDir(QRDSServer rdsserver);
};

#endif // QFILEIOSERVICE_H
