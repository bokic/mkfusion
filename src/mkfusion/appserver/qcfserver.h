#ifndef QCFSERVER_H
#define QCFSERVER_H

#include "qcfrunningtemplate.h"
#include "qcfapplication.h"
#include "qcftemplate.h"

#include <QReadWriteLock>
#include <QLocalServer>
#include <QSqlDatabase>
#include <QThread>
#include <QObject>
#include <QList>
#include <QHash>

struct QCFCompiledTemplateItem
{
    QString m_CompiledFileName;
    QIsTemplateModified m_ModifiedInfo;
};

class QCFServer : public QObject
{
    Q_OBJECT
public:
    QCFServer();
    virtual ~QCFServer();
    void start();
    void stop();
    void readConfig();
    QSqlDatabase *getDBConnection(const QString &datasource);
    QString compileTemplate(const QString&, const QString&);
    QCFRunningTemplate *getRunningTemplateByThreadId(Qt::HANDLE threadId);
    void createSessonStrings(QString &cfid, QString &cftoken);

protected:
    virtual void timerEvent(QTimerEvent*);

private slots:
    void on_newConnection();
    void on_workerTerminated();

public:
    QHash<QString, QCFCompiledTemplateItem> m_CompiledTemplates;
    QHash<Qt::HANDLE, QCFRunningTemplate *> m_RunnuingTemplatesByThreadId;
    QHash<QString, QCFApplication> m_Applications;
    QHash<QString, QWDDX> m_Sessions;
    QHash<QString, QSqlDatabase> m_DatabasePool;
    QLocalServer m_LocalServer;
    QReadWriteLock m_runningTemplatesLock;
    QString m_LeaveGeneratedFilesPath;
    QString m_CustomTagsPath;
    QString m_MKFusionPath;
    QString m_TemplatesPath;
    int m_mainTimer;
    int m_MaxSimulRunningTemplates;
};

#endif // QCFSERVER_H
