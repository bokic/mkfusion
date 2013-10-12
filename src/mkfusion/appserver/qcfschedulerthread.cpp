#include "qcfschedulerthread.h"
#include "qcflog.h"

#include <QThread>
#include <QObject>
#include <QTimer>

QCFSchedulerThread::QCFSchedulerThread(QObject *parent)
    : QThread(parent)
{
}

QCFSchedulerThread::~QCFSchedulerThread()
{
}

void QCFSchedulerThread::run()
{
    QTimer timer;

    connect(&timer, &QTimer::timeout, this, &QCFSchedulerThread::task);

    timer.start(5000);

    exec();
}

void QCFSchedulerThread::task()
{
    QCFLOG(QCFLOG_SCHEDULER, QCFLOG_INFO, "Scheduler task begin.");



    QCFLOG(QCFLOG_SCHEDULER, QCFLOG_INFO, "Scheduler task end.");
}
