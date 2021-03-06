#pragma once

#include <QSqlDatabase>
#include <QString>


class QCFDatabaseConnection
{
public:
    QCFDatabaseConnection();
    QCFDatabaseConnection(const QString &name, const QString &driver, const QString &str);
    QSqlDatabase createConnection();

    QString m_connectionName;
    QString m_connectionDriver;
    QString m_connectionString;
};
