#ifndef QCFRUNNINGTEMPLATE_H
#define QCFRUNNINGTEMPLATE_H

#include "qwddx.h"
#include "common.h"

#include <QLocalSocket>
#include <QLibrary>
#include <QHash>

class QCFRunningTemplate : public QObject
{
	Q_OBJECT
public:
    friend class QCFTemplate;

    enum OutputType {OutputTypeContent, OutputTypeQuery};

	QCFRunningTemplate();

	// Class members
	QWDDX m_CGI;
	QWDDX m_SERVER;
	QWDDX m_APPLICATION;
	QWDDX m_SESSION;
	QWDDX m_URL;
	QWDDX m_FORM;
	QWDDX m_VARIABLES;
	QString m_Output;
    QString m_QueryOutput;
    QList<QWDDX> m_QueryParams;
	qint32 m_CFOutput;
	QString m_ContentType;
	int m_Status;
	QHash<QString, QString> m_Header;
	bool m_HeadersSent;
	QLocalSocket *m_Socket;
	QObject *m_CFServer;
	QCFRunningTemplate_Request m_Request;
    OutputType m_OutputType;
    QHash<QString, QString> m_CustomFunctions;

signals:
	void finished();

public slots:
	void worker();
private:
    void * compileAndLoadTemplate(const QString &filename, const QString &uri, QLibrary &templateLib);
    void runApplicationTemplate();
};

#endif // QCFRUNNINGTEMPLATE_H
