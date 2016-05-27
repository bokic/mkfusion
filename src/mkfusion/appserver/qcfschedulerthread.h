#pragma once

#include <QThread>
#include <QObject>

class QCFSchedulerThread : public QThread
{
public:
    QCFSchedulerThread(QObject *parent = nullptr);
    ~QCFSchedulerThread();

protected:
    void run();

private slots:
    void task();
};
