#include "qcfapplicationmanager.h"
#include "qcfserver.h"

#include <QWriteLocker>


QCFApplicationManager::QCFApplicationManager()
    : m_lock(new QReadWriteLock)
{
}

QCFApplicationManager::~QCFApplicationManager()
{
    delete m_lock;
    m_lock = nullptr;
}

void QCFApplicationManager::updateApplication(QCFWorkerThread *worker, const QString &name, bool sessionManagement, bool setClientCookies)
{
    QWriteLocker locker(m_lock);

    QString l_name = name.toUpper();

    if(!m_applications.contains(l_name))
    {
        m_applications.insert(l_name, QCFApplication());
    }

    m_applications[l_name].m_sessionManagement = sessionManagement;
    m_applications[l_name].m_setClientCookies = setClientCookies;

    worker->m_APPLICATION = &m_applications[l_name].m_data;

    if (sessionManagement)
    {
        worker->m_SESSION = QCFServer::instance()->m_Sessions.getSession(worker, name, sessionManagement, setClientCookies);

    }
}

void QCFApplicationManager::stopAndRemoveTimeoutApplication()
{
    QWriteLocker locker(m_lock);

}


QReadWriteLock * QCFApplicationManager::lock()
{
    return m_lock;
}
