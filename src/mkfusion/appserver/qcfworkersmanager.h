#pragma once

#include "qcfworkerthread.h"

#include <QString>
#include <QObject>
#include <QMutex>
#include <QList>


class QCFWorkersManager : public QObject
{
public:
    QCFWorkersManager();
    void init();
    void waitForAllWorkersToFinish();

public slots:
    void on_newConnection();

private slots:
    void on_workerTerminated();

private:
    QList<QCFWorkerThread *> m_workers;
    QMutex m_mutex;
};
