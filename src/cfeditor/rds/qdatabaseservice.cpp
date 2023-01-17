#include "qdatabaseservice.h"
#include <QByteArray>
#include <QVector>
#include <QString>
#include <QMap>

QDatabaseService::QDatabaseService(): QAbstractRDSService()
{
}

QDatabaseService::~QDatabaseService()
{
}

QByteArray QDatabaseService::ExecuteRDSCommand(QRDSServer &rdsserver, quint8 command, const QMap<QString, QString> &map)
{
    QByteArray ret;

    switch (command)
    {
    case 0:
        return GetDSNs(rdsserver);
    case 1:
        return GetTables(rdsserver, map);
    case 2:
        return GetColumns(rdsserver, map);
    case 3:
        return GetPrimaryKeys(rdsserver, map);
    case 4:
        return ExecuteStatement(rdsserver, map);
    case 5:
        return GetMetaData(rdsserver, map);
    case 6:
        return GetSupportedCommands(rdsserver);
    default:
        return ret;
    }
}

QByteArray QDatabaseService::GetDSNs(QRDSServer rdsserver)
{
    QVector<QString> vector;

    vector.append(QStringLiteral("X"));
    vector.append(QStringLiteral("DSNINFO"));
    vector.append(QStringLiteral("X"));
    vector.append(QStringLiteral("X"));

    return executeRDSCommandForByteArray(QStringLiteral("DBFUNCS"), rdsserver, vector);
}

QByteArray QDatabaseService::GetTables(QRDSServer rdsserver, QMap<QString, QString> map)
{
    QVector<QString> vector;

    vector.append(map[QStringLiteral("DATASOURCE_NAME")] + QStringLiteral(";;;"));
    vector.append(QStringLiteral("TABLEINFO"));
    vector.append("");
    vector.append("");

    return executeRDSCommandForByteArray(QStringLiteral("DBFUNCS"), rdsserver, vector);
}

QByteArray QDatabaseService::GetColumns(QRDSServer rdsserver, QMap<QString, QString> map)
{
    QVector<QString> vector;

    vector.append(map[QStringLiteral("DATASOURCE_NAME")] + QStringLiteral(";;;"));
    vector.append(QStringLiteral("COLUMNINFO"));
    vector.append(map[QStringLiteral("TABLE_NAME")]);
    vector.append("");

    return executeRDSCommandForByteArray(QStringLiteral("DBFUNCS"), rdsserver, vector);
}

QByteArray QDatabaseService::GetPrimaryKeys(QRDSServer rdsserver, QMap<QString, QString> map)
{
    QVector<QString> vector;

    vector.append(map[QStringLiteral("DATASOURCE_NAME")] + QStringLiteral(";;;"));
    vector.append(QStringLiteral("PRIMARYKEYS"));
    vector.append(map[QStringLiteral("TABLE_NAME")]);
    vector.append("");

    return executeRDSCommandForByteArray(QStringLiteral("DBFUNCS"), rdsserver, vector);
}

QByteArray QDatabaseService::ExecuteStatement(QRDSServer rdsserver, QMap<QString, QString> map)
{
    QVector<QString> vector;

    vector.append(map[QStringLiteral("DATASOURCE_NAME")] + QStringLiteral(";;;"));
    vector.append(QStringLiteral("SQLSTMNT"));
    vector.append(map[QStringLiteral("SQL_STATEMENT")]);
    vector.append(QStringLiteral("SELECT"));

    return executeRDSCommandForByteArray(QStringLiteral("DBFUNCS"), rdsserver, vector);
}

QByteArray QDatabaseService::GetMetaData(QRDSServer rdsserver, QMap<QString, QString> map)
{
    QVector<QString> vector;

    vector.append(map[QStringLiteral("DATASOURCE_NAME")] + QStringLiteral(";;;"));
    vector.append(QStringLiteral("SQLMETADATA"));
    vector.append(map[QStringLiteral("SQL_STATEMENT")]);
    vector.append(QStringLiteral("SELECT"));

    return executeRDSCommandForByteArray(QStringLiteral("DBFUNCS"), rdsserver, vector);
}

QByteArray QDatabaseService::GetSupportedCommands(QRDSServer rdsserver)
{
    QVector<QString> vector;

    vector.append(QStringLiteral("X"));
    vector.append(QStringLiteral("SUPPORTEDCOMMANDS"));
    vector.append(QStringLiteral("X"));
    vector.append(QStringLiteral("X"));

    return executeRDSCommandForByteArray(QStringLiteral("DBFUNCS"), rdsserver, vector);
}
