#include "qdatabaseservice.h"
#include <QByteArray>
#include <QVector>
#include <QString>
#include <QMap>

 QDatabaseService::QDatabaseService(): QAbstractRDSService()
 {
 }

QByteArray QDatabaseService::ExecuteRDSCommand(QRDSServer rdsserver, quint8 command, QMap<QString, QString> map)
{
	QByteArray ret;

	switch (command)
	{
	case 0:
		return GetDSNs(rdsserver);
		break;
	case 1:
		return GetTables(rdsserver, map);
		break;
	case 2:
		return GetColumns(rdsserver, map);
		break;
	case 3:
		return GetPrimaryKeys(rdsserver, map);
		break;
	case 4:
		return ExecuteStatement(rdsserver, map);
		break;
	case 5:
		return GetMetaData(rdsserver, map);
		break;
	case 6:
		return GetSupportedCommands(rdsserver);
		break;
	}
	
	return ret;
}

QByteArray QDatabaseService::GetDSNs(QRDSServer rdsserver)
{
	QVector<QString> vector;
	
	vector.append("X");
	vector.append("DSNINFO");
	vector.append("X");
	vector.append("X");
	
	return executeRDSCommandForByteArray("DBFUNCS", rdsserver, vector);
}

QByteArray QDatabaseService::GetTables(QRDSServer rdsserver, QMap<QString, QString> map)
{
	QVector<QString> vector;

	vector.append(map["DATASOURCE_NAME"] + ";;;");
	vector.append("TABLEINFO");
	vector.append("");
	vector.append("");

	return executeRDSCommandForByteArray("DBFUNCS", rdsserver, vector);
}

QByteArray QDatabaseService::GetColumns(QRDSServer rdsserver, QMap<QString, QString> map)
{
	QVector<QString> vector;

	vector.append(map["DATASOURCE_NAME"] + ";;;");
	vector.append("COLUMNINFO");
	vector.append(map["TABLE_NAME"]);
	vector.append("");

	return executeRDSCommandForByteArray("DBFUNCS", rdsserver, vector);
}

QByteArray QDatabaseService::GetPrimaryKeys(QRDSServer rdsserver, QMap<QString, QString> map)
{
	QVector<QString> vector;

	vector.append(map["DATASOURCE_NAME"] + ";;;");
	vector.append("PRIMARYKEYS");
	vector.append(map["TABLE_NAME"]);
	vector.append("");

	return executeRDSCommandForByteArray("DBFUNCS", rdsserver, vector);
}

QByteArray QDatabaseService::ExecuteStatement(QRDSServer rdsserver, QMap<QString, QString> map)
{
	QVector<QString> vector;

	vector.append(map["DATASOURCE_NAME"] + ";;;");
	vector.append("SQLSTMNT");
	vector.append(map["SQL_STATEMENT"]);
	vector.append("SELECT");

	return executeRDSCommandForByteArray("DBFUNCS", rdsserver, vector);
}

QByteArray QDatabaseService::GetMetaData(QRDSServer rdsserver, QMap<QString, QString> map)
{
	QVector<QString> vector;

	vector.append(map["DATASOURCE_NAME"] + ";;;");
	vector.append("SQLMETADATA");
	vector.append(map["SQL_STATEMENT"]);
	vector.append("SELECT");

	return executeRDSCommandForByteArray("DBFUNCS", rdsserver, vector);
}

QByteArray QDatabaseService::GetSupportedCommands(QRDSServer rdsserver)
{
	QVector<QString> vector;

	vector.append("X");
	vector.append("SUPPORTEDCOMMANDS");
	vector.append("X");
	vector.append("X");

	return executeRDSCommandForByteArray("DBFUNCS", rdsserver, vector);
}
