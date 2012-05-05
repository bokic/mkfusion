#ifndef QCFSERVER_H
#define QCFSERVER_H

#include "qcfrunningtemplate.h"
#include "qcftemplate.h"

#include <QReadWriteLock>
#include <QLocalServer>
#include <QThread>
#include <QObject>
#include <QList>
#include <QHash>

struct QCFCompiledTemplateItem {
	QString m_CompiledFileName;
	QIsTemplateModified m_ModifiedInfo;
};

extern QString getCurrentExecutableFileName();

class QCFServer : public QObject
{
	Q_OBJECT
public:
	QCFServer();
	void start();
	void stop();
protected:
	void timerEvent(QTimerEvent*);
public:
	QHash<QString, QCFCompiledTemplateItem> m_CompiledTemplates;
	QLocalServer m_LocalServer;
	QReadWriteLock m_runningTemplatesLock;
	QList<QThread*> m_runningTemplates;
	QString compileTemplate(const QString&, const QString&);
	QString m_MKFusionPath;
	int m_mainTimer;
	int m_MaxSimulRunningTemplates;
private slots:
	void on_newConnection();
	void on_workerTerminated();
};

#endif // QCFSERVER_H
