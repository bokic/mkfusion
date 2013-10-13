#ifndef QCFDATABASEPOOLMANAGER_H
#define QCFDATABASEPOOLMANAGER_H

#include "qcfdatabaseconnection.h"

#include <QReadWriteLock>
#include <QSqlDatabase>
#include <QHash>
#include <QList>


class QCFDatabasePoolManager
{
public:
    QCFDatabasePoolManager();
    void setConnectionDefinition(const QList<QCFDatabaseConnection> &db_connections);
    QSqlDatabase *getDatabaseConnection(const QString &name);
    void putBackDatabaseConnection(QSqlDatabase *old_db_connection);
    QReadWriteLock *lock();

private:
    QHash<QString, QSqlDatabase *> m_connections;
    QList<QCFDatabaseConnection> m_connectionDefinition;
    QReadWriteLock m_lock;
};

#endif // QCFDATABASEPOOLMANAGER_H
