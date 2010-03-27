#ifndef QCFRUNNINGTEMPLATE_H
#define QCFRUNNINGTEMPLATE_H

#include "qwddx.h"
#include "common.h"
#include <QLocalSocket>
#include <QThread>
#include <QObject>
#include <QHash>

class QCFRunningTemplate : public QThread
{
	Q_OBJECT
public:
	QCFRunningTemplate();
	QCFRunningTemplate(QObject *);
	QCFRunningTemplate(const QCFRunningTemplate &);
	QCFRunningTemplate &operator=(const QCFRunningTemplate &);
	void startSocket(QLocalSocket *);
protected:
	void run();
public:
	QString m_Output;
	qint32 m_CFOutput;

	QWDDX m_CGI;
	QWDDX m_SERVER;
	QWDDX m_APPLICATION;
	QWDDX m_SESSION;
	QWDDX m_URL;
	QWDDX m_FORM;
	QWDDX m_VARIABLE;
	QString m_ContentType;
	int m_Status;
	QHash<QString, QString> m_Header;
	bool m_HeadersSent;
	QLocalSocket *m_Socket;
	QCFRunningTemplate_Request m_Request;
};

#endif // QCFRUNNINGTEMPLATE_H
