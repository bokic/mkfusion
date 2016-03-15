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
    enum QFileIOCommand
    {
        QBrowseDirCommand,
        QFileReadCommand,
        QFileWriteCommand,
        QFileRenameCommand,
        QFileRemoveFileCommand,
        QFileRemoveDirectoryCommand,
        QFileExistCommand,
        QFileCreateDirCommand,
        QFileGetRootDirCommand
    };

    QFileIOService();
    virtual ~QFileIOService();

    virtual QByteArray ExecuteRDSCommand(QRDSServer &rdsserver, quint8 command, const QMap<QString, QString> &map) override;
private:
    QByteArray BrowseDir(const QRDSServer &rdsserver, const QMap<QString, QString> &map);
    QByteArray FileRead(const QRDSServer &rdsserver, const QMap<QString, QString> &map);
    QByteArray FileWrite(const QRDSServer &rdsserver, const QMap<QString, QString> &map);
    QByteArray FileRename(const QRDSServer &rdsserver, const QMap<QString, QString> &map);
    QByteArray FileRemove(const QRDSServer &rdsserver, const QMap<QString, QString> &map, bool isFile = true);
    QByteArray Existence(const QRDSServer &rdsserver, const QMap<QString, QString> &map);
    QByteArray CreateDir(const QRDSServer &rdsserver, const QMap<QString, QString> &map);
    QByteArray GetRootDir(const QRDSServer &rdsserver);
};

#endif // QFILEIOSERVICE_H
