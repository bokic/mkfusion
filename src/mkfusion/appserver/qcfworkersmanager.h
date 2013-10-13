#ifndef QCFWORKERSMANAGER_H
#define QCFWORKERSMANAGER_H

#include "qcfworkerthread.h"

#include <QString>
#include <QObject>
#include <QMutex>
#include <QList>


class QCFWorkersManager : public QObject
{
public:
    QCFWorkersManager();
    QString compile(const QString &file, bool checkForNewer = true);

public slots:
    void on_newConnection();

private slots:
    void on_workerTerminated();

private:
    QList<QCFWorkerThread *> m_workers;
    QMutex m_mutex;
};

#endif // QCFWORKERSMANAGER_H
