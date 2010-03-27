#ifndef QCFSERVER_H
#define QCFSERVER_H

#include "qcfrunningtemplate.h"
#include "qcftemplate.h"

#include <QReadWriteLock>
#include <QLocalServer>
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
	void start();
	void stop();
protected:
	void timerEvent(QTimerEvent*);
public:
	QHash<QString, QCFCompiledTemplateItem> m_CompiledTemplates;
	QLocalServer m_LocalServer;
	QReadWriteLock m_runningTemplatesLock;
	QList<QCFRunningTemplate> m_runningTemplates;
	QString compileTemplate(const QString&);
	QString m_MKFusionPath;
	int m_mainTimer;
	int m_MaxSimulRunningTemplates;
private slots:
	void on_newConnection();
};

#endif // QCFSERVER_H
