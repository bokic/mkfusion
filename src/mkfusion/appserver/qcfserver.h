#pragma once

#include "qcfapplicationmanager.h"
#include "qcfsessionmanager.h"
#include "qcfdatabasepoolmanager.h"
#include "qcftemplatesmanager.h"
#include "qcfsettingsmanager.h"
#include "qcfschedulerthread.h"
#include "qcfworkersmanager.h"

#include <QLocalServer>
#include <QObject>


class QCFServer : public QObject
{
public:
    QCFServer();
    virtual ~QCFServer();

    void start();
    void stop();
    QString MKFusionPath() const;
    static QCFServer * instance();
    QString osName() const;
    QString osVersion() const;

    QCFApplicationManager m_Applications;
    QCFSessionManager m_Sessions;
    QCFDatabasePoolManager m_DatabasePool;
    QCFWorkersManager m_Workers;
    QCFTemplatesManager m_Templates;
    QLocalServer m_LocalServer;
    QCFSettingsManager m_Settings;
    QCFSchedulerThread m_Scheduler;

public slots:
    void on_workerTerminated();

private:
    QString m_MKFusionPath;
    static QString getProcessExecutableFileName();
    static QCFServer *m_instance;
    QString m_osName;
    QString m_osVersion;
};
