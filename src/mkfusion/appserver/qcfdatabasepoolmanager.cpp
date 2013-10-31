#include "qcfdatabasepoolmanager.h"
#include "qcflog.h"

#include <QWriteLocker>
#include <QStringList>


QCFDatabasePoolManager::QCFDatabasePoolManager()
{
}

void QCFDatabasePoolManager::setConnectionDefinition(const QList<QCFDatabaseConnection> &db_connections)
{
    QWriteLocker locker(&m_lock);

    for(const QCFDatabaseConnection & connection : m_connectionDefinition)
    {
        QSqlDatabase::removeDatabase(connection.m_connectionName);
    }

    m_connectionDefinition = db_connections;

    for(const QCFDatabaseConnection & connection : m_connectionDefinition)
    {
        if (connection.m_connectionDriver == "QSQLITE")
        {
            QSqlDatabase db = QSqlDatabase::addDatabase(connection.m_connectionDriver, connection.m_connectionName.toUpper());

            db.setDatabaseName(connection.m_connectionString);
        }
        else if (connection.m_connectionDriver == "QODBC")
        {
            QSqlDatabase db = QSqlDatabase::addDatabase(connection.m_connectionDriver, connection.m_connectionName.toUpper());

            db.setDatabaseName(connection.m_connectionString);
        }
        else if (connection.m_connectionDriver == "QMYSQL")
        {
            QSqlDatabase db = QSqlDatabase::addDatabase(connection.m_connectionDriver, connection.m_connectionName.toUpper());

            for(const QString item : connection.m_connectionString.split(';'))
            {
                QStringList key_value = item.split(':');

                if (key_value.count() != 2)
                {
                    continue;
                }

                QString key = key_value.first();
                QString value = QByteArray::fromBase64(key_value.last().toLatin1());

                if (key.compare("hostname", Qt::CaseInsensitive) == 0)
                {
                    db.setHostName(value);
                }
                else if (key.compare("databasename", Qt::CaseInsensitive) == 0)
                {
                    db.setDatabaseName(value);
                }
                else if (key.compare("username", Qt::CaseInsensitive) == 0)
                {
                    db.setUserName(value);
                }
                else if (key.compare("password", Qt::CaseInsensitive) == 0)
                {
                    db.setPassword(value);
                }
                else if (key.compare("port", Qt::CaseInsensitive) == 0)
                {
                    db.setPort(value.toInt());
                }
            }
        }
        else
        {
            QCFLOG_QSTRING(QCFLOG_DAEMON, QCFLOG_ERROR, "Unsupported database connection(" + connection.m_connectionDriver + ")");
        }
    }
}

QSqlDatabase QCFDatabasePoolManager::getDatabaseConnection(const QString &name)
{
    QWriteLocker locker(&m_lock);

    return QSqlDatabase::database(name);
}

void QCFDatabasePoolManager::putBackDatabaseConnection(QSqlDatabase old_db_connection)
{
    QWriteLocker locker(&m_lock);

    old_db_connection.close();
}

QReadWriteLock * QCFDatabasePoolManager::lock()
{
    return &m_lock;
}
