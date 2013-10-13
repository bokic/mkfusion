#include "qcfworkersmanager.h"
#include "qcfworkerthread.h"
#include "qcfserver.h"
#include "qcflog.h"

#include <QLocalServer>
#include <QLocalSocket>


QCFWorkersManager::QCFWorkersManager()
{
}

QString QCFWorkersManager::compile(const QString &file, bool checkForNewer)
{
    return "";
}

void QCFWorkersManager::on_newConnection()
{
    QCFLOG(CFLOG_WORKER, QCFLOG_INFO, "Worker has started.");

    while(((QLocalServer *)sender())->hasPendingConnections())
    {
        QLocalSocket *localSocket = ((QLocalServer *)sender())->nextPendingConnection();

        if (localSocket == nullptr)
        {
            QCFLOG(CFLOG_WORKER, QCFLOG_ERROR, "Got nullptr local connection.");

            continue;
        }

        if (localSocket->waitForConnected(1000) == false)
        {
            QCFLOG(CFLOG_WORKER, QCFLOG_ERROR, "Failed to connect with local socket.");

            delete localSocket;

            continue;
        }

        //if (m_RunnuingTemplatesByThreadId.count() >= m_MaxSimulRunningTemplates)
        //{
        //    l_LocalSocket->write("\x04\x00\x00\x00", 4);
        //    l_LocalSocket->write("Maximum running templates.");
        //    l_LocalSocket->waitForBytesWritten();
        //    l_LocalSocket->disconnectFromServer();
        //    l_LocalSocket->waitForDisconnected();
        //    l_LocalSocket->deleteLater();

        //    return;
        //}

        QCFWorkerThread *worker = new QCFWorkerThread(localSocket, this);
        connect(worker, &QThread::finished, this, &QCFWorkersManager::on_workerTerminated);

        {
            QMutexLocker lock(&m_mutex);

            m_workers.push_back(worker);
        }

        worker->start();
    }

    QCFLOG(CFLOG_WORKER, QCFLOG_INFO, "Worker has ended.");
}

void QCFWorkersManager::on_workerTerminated()
{
    QCFWorkerThread *l_sender = (QCFWorkerThread *)sender();

    {
        QMutexLocker lock(&m_mutex);

        if (m_workers.contains(l_sender))
        {
            m_workers.removeAll(l_sender);
        }
        else
        {
            QCFLOG(QCFLOG_DAEMON, QCFLOG_CRITICAL, "Worker object not found in list.");
        }
    }

    l_sender->deleteLater();

    //qApp->quit();
}
