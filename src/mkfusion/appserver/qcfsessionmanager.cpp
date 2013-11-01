#include "qcfsessionmanager.h"
#include "qcfworkerthread.h"

#include <QWriteLocker>
#include <QMutexLocker>
#include <QMutex>


QCFSessionManager::QCFSessionManager()
{
}

QCFVariant * QCFSessionManager::getSession(QCFWorkerThread *worker, const QString &name, bool sessionManagement, bool setClientCookies)
{
    /*
        worker->updateVariable(*worker->m_SESSION, L"CFID", CFID);
        worker->updateVariable(*worker->m_SESSION, L"CFTOKEN", CFTOKEN);
        worker->updateVariable(*worker->m_SESSION, L"SESSIONID", l_name + "_" + CFID + "_" + CFTOKEN);
        worker->updateVariable(*worker->m_SESSION, L"URLTOKEN", "CFID=" + CFID + "&CFTOKEN=" + CFTOKEN);
    */

    return nullptr;
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
