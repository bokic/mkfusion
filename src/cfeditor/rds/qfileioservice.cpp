#include "qfileioservice.h"
#include <QByteArray>
#include <QVector>
#include <QString>
#include <QMap>

QByteArray QFileIOService::ExecuteRDSCommand(QRDSServer rdsserver, quint8 command, QMap<QString, QString> map)
{
    QByteArray ret;

    switch (command)
    {
    case 0:
        return BrowseDir(rdsserver, map);
        break;
    case 1:
        return FileRead(rdsserver, map);
        break;
    case 2:
        return FileWrite(rdsserver, map);
        break;
    case 3:
        return FileRename(rdsserver, map);
        break;
    case 4:
        return FileRemove(rdsserver, map, true);
        break;
    case 5:
        return FileRemove(rdsserver, map, false);
        break;
    case 6:
        return Existence(rdsserver, map);
        break;
    case 7:
        return CreateDir(rdsserver, map);
        break;
    case 8:
        return GetRootDir(rdsserver);
        break;
    }

    return ret;
}

QByteArray QFileIOService::BrowseDir(QRDSServer rdsserver, QMap<QString, QString> map)
{
    QVector<QString> vector;

    vector.append(map["NAME"]);
    if ((!map["MASK"].isNull())&&(map["MASK"]!=""))
        vector.append(map["MASK"]);

    return executeRDSCommandForByteArray("BROWSEDIR", rdsserver, vector);
}

QByteArray QFileIOService::FileRead(QRDSServer rdsserver, QMap<QString, QString> map)
{
    QVector<QString> vector;
    vector.append(map["NAME"]);
    vector.append("READ");
    vector.append("");
    return executeRDSCommandForByteArray("FILEIO", rdsserver, vector);
}

QByteArray QFileIOService::FileWrite(QRDSServer rdsserver, QMap<QString, QString> map)
{
    QVector<QString> vector;
    vector.append(map["NAME"]);
    vector.append("WRITE");
    vector.append("");
    vector.append(map["FILE_CONTENTS"]);
    return executeRDSCommandForByteArray("FILEIO", rdsserver, vector);
}

QByteArray QFileIOService::FileRename(QRDSServer rdsserver, QMap<QString, QString> map)
{
    QVector<QString> vector;
    vector.append(map["NAME"]);
    vector.append("RENAME");
    vector.append("");
    vector.append(map["NEW_NAME"]);

    return executeRDSCommandForByteArray("FILEIO", rdsserver, vector);
}

QByteArray QFileIOService::FileRemove(QRDSServer rdsserver, QMap<QString, QString> map, bool isFile = true)
{
    QVector<QString> vector;

    vector.append(map["NAME"]);
    vector.append("REMOVE");
    vector.append("");
    if (isFile)
        vector.append("F");
    else
        vector.append("D");

    return executeRDSCommandForByteArray("FILEIO", rdsserver, vector);
}

QByteArray QFileIOService::Existence(QRDSServer rdsserver, QMap<QString, QString> map)
{
    QVector<QString> vector;

    vector.append(map["NAME"]);
    vector.append("EXISTENCE");
    vector.append("");
    vector.append("");

    return executeRDSCommandForByteArray("FILEIO", rdsserver, vector);
}

QByteArray QFileIOService::CreateDir(QRDSServer rdsserver, QMap<QString, QString> map)
{
    QVector<QString> vector;

    vector.append(map["NAME"]);
    vector.append("CREATE");
    vector.append("");
    vector.append("");

    return executeRDSCommandForByteArray("FILEIO", rdsserver, vector);
}

QByteArray QFileIOService::GetRootDir(QRDSServer rdsserver)
{
    QVector<QString> vector;

    vector.append("");
    vector.append("CF_DIRECTORY");

    return executeRDSCommandForByteArray("FILEIO", rdsserver, vector);
}
