#ifndef QCFAPPLICATIONMANAGER_H
#define QCFAPPLICATIONMANAGER_H

#include "qcfworkerthread.h"
#include "qcfapplication.h"

#include <QReadWriteLock>
#include <QHash>


class QCFApplicationManager
{
public:
    QCFApplicationManager();

    void updateApplication(QCFWorkerThread *worker, const QString &name, bool sessionManagement, bool setClientCookies);
    void stopAndRemoveTimeoutApplication();
    QReadWriteLock *lock();

private:
    QHash<QString, QCFApplication> m_applications;
    QReadWriteLock m_lock;
};

#endif // QCFAPPLICATIONMANAGER_H
