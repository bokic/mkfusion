#include "qcfapplicationmanager.h"

QCFApplicationManager::QCFApplicationManager()
{
}

void QCFApplicationManager::stopAndRemoveTimeoutApplication()
{

}


QReadWriteLock * QCFApplicationManager::lock()
{
    return &m_lock;
}
