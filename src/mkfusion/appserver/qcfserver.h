#ifndef QCFSERVER_H
#define QCFSERVER_H

#include "qcfrunningtemplate.h"
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
    QSqlDatabase getDBConnection(const QString &datasource);
    QString compileTemplate(const QString&, const QString&);
    QCFTemplate * getTemplateByThreadId(Qt::HANDLE threadId);

protected:
    virtual void timerEvent(QTimerEvent*);

private slots:
	void on_newConnection();
	void on_workerTerminated();

public:
    QHash<QString, QCFCompiledTemplateItem> m_CompiledTemplates;
    QHash<Qt::HANDLE, QCFTemplate *> m_TemplatesByThreadId;
    QLocalServer m_LocalServer;
    QReadWriteLock m_runningTemplatesLock;
    QString m_MKFusionPath;
    int m_mainTimer;
    int m_MaxSimulRunningTemplates;
};

#endif // QCFSERVER_H
