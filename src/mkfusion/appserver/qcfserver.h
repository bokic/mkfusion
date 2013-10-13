#ifndef QCFSERVER_H
#define QCFSERVER_H

#include "qcfapplicationmanager.h"
#include "qcfsessionmanager.h"
#include "qcfdatabasepoolmanager.h"
#include "qcfworkersmanager.h"
#include "qcfsettingsmanager.h"
#include "qcfschedulerthread.h"

#include <QLocalServer>
#include <QObject>


class QCFServer : public QObject
{
public:
    QCFServer();
    virtual ~QCFServer();

	void start();
	void stop();
    static QCFServer * instance();
    static QString osName();
    static QString osVersion();

    QCFApplicationManager m_Applications;
    QCFSessionManager m_Sessions;
    QCFDatabasePoolManager m_DatabasePool;
    QCFWorkersManager m_Workers;
    QLocalServer m_LocalServer;
    QCFSettingsManager m_Settings;
    QCFSchedulerThread m_Scheduler;

public slots:
    void on_workerTerminated();

private:
    QString m_MKFusionPath;
    static QString getProcessExecutableFileName();
    static QCFServer *m_instance;
    static QString m_osName;
    static QString m_osVersion;
};

#endif // QCFSERVER_H
