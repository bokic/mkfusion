#include "qfileioservice.h"
#include <QByteArray>
#include <QVector>
#include <QString>
#include <QMap>

#define FILE_CONTENTS QStringLiteral("FILE_CONTENTS")
#define EMPTY_STR QStringLiteral("")
#define BROWSEDIR QStringLiteral("BROWSEDIR")
#define NEW_NAME QStringLiteral("NEW_NAME")
#define EXISTENCE QStringLiteral("EXISTENCE")
#define CF_DIRECTORY QStringLiteral("CF_DIRECTORY")
#define FILEIO QStringLiteral("FILEIO")
#define RENAME QStringLiteral("RENAME")
#define REMOVE QStringLiteral("REMOVE")
#define CREATE QStringLiteral("CREATE")
#define WRITE QStringLiteral("WRITE")
#define NAME QStringLiteral("NAME")
#define MASK QStringLiteral("MASK")
#define READ QStringLiteral("READ")
#define F QStringLiteral("F")
#define D QStringLiteral("D")

QFileIOService::QFileIOService()
    : QAbstractRDSService()
{

}

QFileIOService::~QFileIOService()
{

}

QByteArray QFileIOService::ExecuteRDSCommand(const QRDSServer &rdsserver, quint8 command, const QMap<QString, QString> &map)
{
    QByteArray ret;

    switch (command)
    {
    case QBrowseDirCommand:
        return BrowseDir(rdsserver, map);
        break;
    case QFileReadCommand:
        return FileRead(rdsserver, map);
        break;
    case QFileWriteCommand:
        return FileWrite(rdsserver, map);
        break;
    case QFileRenameCommand:
        return FileRename(rdsserver, map);
        break;
    case QFileRemoveFileCommand:
        return FileRemove(rdsserver, map, true);
        break;
    case QFileRemoveDirectoryCommand:
        return FileRemove(rdsserver, map, false);
        break;
    case QFileExistCommand:
        return Existence(rdsserver, map);
        break;
    case QFileCreateDirCommand:
        return CreateDir(rdsserver, map);
        break;
    case QFileGetRootDirCommand:
        return GetRootDir(rdsserver);
        break;
    }

    return ret;
}

QByteArray QFileIOService::BrowseDir(const QRDSServer &rdsserver, const QMap<QString, QString> &map)
{
    QVector<QString> vector;

    vector.append(map[NAME]);
    if (!map[MASK].isEmpty())
        vector.append(map[MASK]);

    return executeRDSCommandForByteArray(BROWSEDIR, rdsserver, vector);
}

QByteArray QFileIOService::FileRead(const QRDSServer &rdsserver, const QMap<QString, QString> &map)
{
    QVector<QString> vector;
    vector.append(map[NAME]);
    vector.append(READ);
    vector.append(EMPTY_STR);
    return executeRDSCommandForByteArray(FILEIO, rdsserver, vector);
}

QByteArray QFileIOService::FileWrite(const QRDSServer &rdsserver, const QMap<QString, QString> &map)
{
    QVector<QString> vector;
    vector.append(map[NAME]);
    vector.append(WRITE);
    vector.append(EMPTY_STR);
    vector.append(map[FILE_CONTENTS]);
    return executeRDSCommandForByteArray(FILEIO, rdsserver, vector);
}

QByteArray QFileIOService::FileRename(const QRDSServer &rdsserver, const QMap<QString, QString> &map)
{
    QVector<QString> vector;
    vector.append(map[NAME]);
    vector.append(RENAME);
    vector.append(EMPTY_STR);
    vector.append(map[NEW_NAME]);

    return executeRDSCommandForByteArray(FILEIO, rdsserver, vector);
}

QByteArray QFileIOService::FileRemove(const QRDSServer &rdsserver, const QMap<QString, QString> &map, bool isFile)
{
    QVector<QString> vector;

    vector.append(map[NAME]);
    vector.append(REMOVE);
    vector.append(EMPTY_STR);
    if (isFile)
        vector.append(F);
    else
        vector.append(D);

    return executeRDSCommandForByteArray(FILEIO, rdsserver, vector);
}

QByteArray QFileIOService::Existence(const QRDSServer &rdsserver, const QMap<QString, QString> &map)
{
    QVector<QString> vector;

    vector.append(map[NAME]);
    vector.append(EXISTENCE);
    vector.append(EMPTY_STR);
    vector.append(EMPTY_STR);

    return executeRDSCommandForByteArray(FILEIO, rdsserver, vector);
}

QByteArray QFileIOService::CreateDir(const QRDSServer &rdsserver, const QMap<QString, QString> &map)
{
    QVector<QString> vector;

    vector.append(map[NAME]);
    vector.append(CREATE);
    vector.append(EMPTY_STR);
    vector.append(EMPTY_STR);

    return executeRDSCommandForByteArray(FILEIO, rdsserver, vector);
}

QByteArray QFileIOService::GetRootDir(const QRDSServer &rdsserver)
{
    QVector<QString> vector;

    vector.append(EMPTY_STR);
    vector.append(CF_DIRECTORY);

    return executeRDSCommandForByteArray(FILEIO, rdsserver, vector);
}
