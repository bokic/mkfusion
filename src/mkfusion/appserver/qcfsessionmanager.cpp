#include "qcfsessionmanager.h"

#include <QWriteLocker>
#include <QMutexLocker>
#include <QMutex>

QCFSessionManager::QCFSessionManager()
{
}

void QCFSessionManager::createSessonStrings(QString &cfid, QString &cftoken)
{
    static QMutex global_cfid_lock;
    static int global_cfid = 1000;

    int local_cfid;

    {
        QMutexLocker lock(&global_cfid_lock);
        local_cfid = ++global_cfid;
    }

    cfid = QString::number(local_cfid);
    cftoken.clear();

    for(int c = 0; c < 24; c++)
    {
        QString byte = QString::number(rand() % 256, 16);
        while(byte.length() < 2)
        {
            byte.prepend('0');
        }

        if (c >= 8)
        {
            byte = byte.toUpper();
        }

        if ((c == 8)||(c == 12)||(c == 14)||(c == 16))
        {
            cftoken.append('-');
        }

        cftoken.append(byte);
    }
}

QReadWriteLock * QCFSessionManager::lock()
{
    return &m_lock;
}
