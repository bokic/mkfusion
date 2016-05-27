#pragma once

#include "qcfsession.h"
#include "qcfworkerthread.h"

#include <QReadWriteLock>
#include <QHash>


class QCFSessionManager
{
public:
    QCFSessionManager();
    QCFVariant * getSession(QCFWorkerThread *worker, const QString &name, bool sessionManagement, bool setClientCookies);
    QReadWriteLock * lock();

private:
    void createSessonStrings(QString &cfid, QString &cftoken);
    QHash<QString, QCFSession> m_applications;
    QReadWriteLock m_lock;
};
