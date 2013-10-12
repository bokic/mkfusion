#ifndef QCFDATABASEPOOLMANAGER_H
#define QCFDATABASEPOOLMANAGER_H

#include <QReadWriteLock>
#include <QSqlDatabase>
#include <QHash>


class QCFDatabasePoolManager
{
public:
    QCFDatabasePoolManager();
    QReadWriteLock *lock();

private:
    QHash<QString, QSqlDatabase *> m_connections;
    QReadWriteLock m_lock;
};

#endif // QCFDATABASEPOOLMANAGER_H
