#include "qcfworkerthread.h"
#include "qmkfusionexception.h"

#include <qcflog.h>


QCFWorkerThread::QCFWorkerThread(QLocalSocket *socket, QObject *parent): QThread(parent)
{
    m_Socket = socket;
    m_Socket->setParent(nullptr);
    m_Socket->moveToThread(this);

    start();
}

QCFWorkerThread::~QCFWorkerThread()
{
    if (m_Socket)
    {
        delete m_Socket;
        m_Socket = nullptr;
    }
}

bool QCFWorkerThread::readRequest()
{
    return true;
}

bool QCFWorkerThread::writeResponse()
{
    return true;
}

void QCFWorkerThread::run()
{
    QCFLOG(CFLOG_WORKER, QCFLOG_INFO_PERF, "Worker thread started.");

    try
    {
        if (!readRequest())
        {
            QCFLOG(CFLOG_WORKER, QCFLOG_ERROR, "Reading worker request failed.");

            throw QMKFusionException("Unknown HTTP Method.");
        }

        // LoadCompiledFile
    }
    catch (const QMKFusionCFAbortException &ex)
    {
    }
    catch (const QMKFusionTemplateException &ex)
    {
        m_StatusCode = 500;
        //m_Output += WriteException(ex, this->m_Request);
    }
    catch (const QMKFusionException &ex)
    {
        m_StatusCode = 500;
        //m_Output += WriteException(ex, this->m_Request);
    }
#ifndef QT_DEBUG
    catch(...)
    {
        m_StatusCode = 500;
        m_Output += WriteException(QMKFusionException("Internal error."), this->m_Request);
    }
#endif

    writeResponse();

    m_Socket->close();

    QCFLOG(CFLOG_WORKER, QCFLOG_INFO_PERF, "Worker thread ended.");
}
