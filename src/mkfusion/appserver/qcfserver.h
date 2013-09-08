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

struct QCFCompiledTemplateItem {
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
    QSqlDatabase getDBConnection(const QString &datasource);
    QString compileTemplate(const QString&, const QString&);
    QCFRunningTemplate * getRunningTemplateByThreadId(Qt::HANDLE threadId);
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
    QLocalServer m_LocalServer;
    QReadWriteLock m_runningTemplatesLock;
    QString m_MKFusionPath;
    int m_mainTimer;
    int m_MaxSimulRunningTemplates;
};

#endif // QCFSERVER_H
