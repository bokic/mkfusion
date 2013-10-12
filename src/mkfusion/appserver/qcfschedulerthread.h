#ifndef QCFSCHEDULERTHREAD_H
#define QCFSCHEDULERTHREAD_H

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

#endif // QCFSCHEDULERTHREAD_H
