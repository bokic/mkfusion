#ifndef QDATABASESERVICE_H
#define QDATABASESERVICE_H

#include "qabstractrdsservice.h"
#include <QObject>
#include <QString>
#include <QVector>
#include <QList>
#include <QMap>

class QDatabaseService : public QAbstractRDSService
{
public:
        QDatabaseService();
    enum Command {
        GetDataSource,
        GetTablesForDS,
        GetColumnsForTable,
        GetPrimaryKeysForTable,
        ExecuteSQLStatement,
        GetSQLMetadata,
        GetSQLSupportedCommands
	};
	QByteArray ExecuteRDSCommand(QRDSServer, quint8, QMap<QString, QString>);
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

#endif // QDATABASESERVICE_H