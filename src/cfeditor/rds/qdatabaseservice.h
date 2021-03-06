#pragma once

#include "qabstractrdsservice.h"
#include <QObject>
#include <QString>
#include <QVector>
#include <QList>
#include <QMap>

class QDatabaseService : public QAbstractRDSService
{
public:
    enum Command
    {
        GetDataSource,
        GetTablesForDS,
        GetColumnsForTable,
        GetPrimaryKeysForTable,
        ExecuteSQLStatement,
        GetSQLMetadata,
        GetSQLSupportedCommands
    };

    QDatabaseService();
    virtual ~QDatabaseService();
    virtual QByteArray ExecuteRDSCommand(QRDSServer &rdsserver, quint8 command, const QMap<QString, QString> &map);
protected:
private:
    QByteArray GetDSNs(QRDSServer);
    QByteArray GetTables(QRDSServer, QMap<QString, QString>);
    QByteArray GetColumns(QRDSServer, QMap<QString, QString>);
    QByteArray GetPrimaryKeys(QRDSServer, QMap<QString, QString>);
    QByteArray ExecuteStatement(QRDSServer, QMap<QString, QString>);
    QByteArray GetMetaData(QRDSServer, QMap<QString, QString>);
    QByteArray GetSupportedCommands(QRDSServer);
};
