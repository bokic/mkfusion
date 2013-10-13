#include "qcfdatabaseconnection.h"

QCFDatabaseConnection::QCFDatabaseConnection()
{
}

QCFDatabaseConnection::QCFDatabaseConnection(const QString &name, const QString &driver, const QString &str)
{
    m_connectionName = name;
    m_connectionDriver = driver;
    m_connectionString = str;
}

QSqlDatabase QCFDatabaseConnection::createConnection()
{
    return QSqlDatabase::database(m_connectionName);
}
