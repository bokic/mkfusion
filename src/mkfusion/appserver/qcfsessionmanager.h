#ifndef QCFSESSIONMANAGER_H
#define QCFSESSIONMANAGER_H

#include "qcfsession.h"

#include <QReadWriteLock>
#include <QHash>


class QCFSessionManager
{
public:
    QCFSessionManager();
    void createSessonStrings(QString &cfid, QString &cftoken);
    QReadWriteLock * lock();

private:
    QHash<QString, QCFSession> m_applications;
    QReadWriteLock m_lock;
};

#endif // QCFSESSIONMANAGER_H
