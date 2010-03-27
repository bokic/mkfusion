#include "qcfdebugger.h"
#include "qdebuggerservice.h"
#include "qdefaultservice.h"
#include "qwddxutils.h"

QCFDebugger::QCFDebugger(QRDSServer rdsServer):QObject()
{
	m_RDSServer = rdsServer;
	m_ServerPort = 0;
	m_SessionID = "";
	m_EventReconect = false;

    connect(&m_EventSocket, SIGNAL(connected()), SLOT(onEventConnected()));
    connect(&m_EventSocket, SIGNAL(disconnected()), SLOT(onEventDisconnected()));    
    connect(&m_EventSocket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(onEventError(QAbstractSocket::SocketError)));
    connect(&m_EventSocket, SIGNAL(readyRead()), SLOT(onEventReadyRead()));
	connect(&m_EventSocket, SIGNAL(bytesWritten(qint64)), SLOT(onEventBytesWritten(qint64)));
}

quint16 QCFDebugger::getDebuggerPort()
{
	if (m_ServerPort == 0)
	{
		QMap<QString, QString> map;
		QByteArray ba;

		//m_RDSServer.setPort(8000); // This is needed for CF7
		m_ServerPort = m_RDSServer.getPort();

		QDebuggerService dbgService;
		QWDDXUtils wddxUtils;
		ba = dbgService.ExecuteRDSCommand(m_RDSServer, QDebuggerService::getServerInfo, map);
		QVector<QByteArray> vec = dbgService.BreakByteArrayIntoVector(ba);
		if (vec.size() <= 0)
			return m_ServerPort;

		QWDDX result = wddxUtils.deserialize(vec[0]);
		m_ServerPort = result[0][(char *)"DEBUG_SERVER_PORT"].toNumber();
	}
	return m_ServerPort;
}

QString QCFDebugger::getSessionID()
{
	return "";
}

bool QCFDebugger::StartDebugger()
{
	if (m_SessionID != "")
		return false;

	QMap<QString, QString> map;
	QDefaultService defaultService;
	QByteArray ba = defaultService.ExecuteRDSCommand(m_RDSServer, QDefaultService::IdeDefaultCommand, map);

	if (m_RDSServer.getAuthenticated() == false)
		return false;

	m_RDSServer.setPort(getDebuggerPort());

	QDebuggerService debuggerService;

	QWDDXUtils wddxUtils;
	QWDDX wddx(QWDDX::Array);

	wddx[0][(char *)"REMOTE_SESSION"] = true;
	map.insert("WDDX", wddxUtils.serialize(wddx));
	ba = debuggerService.ExecuteRDSCommand(m_RDSServer, QDebuggerService::doDebugStart, map);
	QVector<QByteArray> vec = debuggerService.BreakByteArrayIntoVector(ba);

	if (vec.size() < 2)
		return false;

	QWDDX result = wddxUtils.deserialize(vec[1]);

	if ((result[0][(char *)"COMMAND"].toString() != "DBG_START")||(result[0][(char *)"SESSION"].toString() != vec[0])||(result[0][(char *)"STATUS"].toString() != "RDS_OK"))
		return false;

	m_SessionID = vec[0];

	BreakOnException(true);
	SetMonitorScopes("VARIABLES");
	SetBreakpoint("/home/projects/boro_test/test.cfm", 1, true);

	m_EventReconect = true;
	m_EventSocket.connectToHost(m_RDSServer.getHostName(), m_ServerPort);

	return true;
}

bool QCFDebugger::StopDebugger()
{
	if (m_EventSocket.isOpen())
	{
		m_EventSocket.disconnectFromHost();
		m_EventSocket.close();
	}

	if ((m_ServerPort == 0)||(m_SessionID == ""))
		return false;

	QMap<QString, QString> map;
	QByteArray ba;

	map["DEBUG_SERVER_PORT"] = QString(m_ServerPort);
	map["SESSION"] = m_SessionID;

	QDebuggerService dbgService;
	ba = dbgService.ExecuteRDSCommand(m_RDSServer, QDebuggerService::doDebugStop, map);
	QVector<QByteArray> vec = dbgService.BreakByteArrayIntoVector(ba);
	
	if (vec.size() <= 0)
		return false;

	QWDDXUtils wddxUtils;
	QWDDX result = wddxUtils.deserialize(vec[0]);
	if ((result[0][(char *)"SESSION"].toString() != m_SessionID)||(result[0][(char *)"STATUS"].toString() != "RDS_OK")||(result[0][(char *)"COMMAND"].toString() != "DBG_STOP"))
		return false;

	m_SessionID = "";

	return true;
}

bool QCFDebugger::SetMonitorScopes(QString scopes)
{
	if ((m_ServerPort == 0)||(m_SessionID == ""))
		return false;

	QDebuggerService dbgService;
	QMap<QString, QString> map;
	QByteArray ba;
	QWDDX wddx(QWDDX::Array);
	QWDDXUtils wddxUtils;

	wddx[0][(char *)"COMMAND"] = (char *)"SET_SCOPE_FILTER";
	wddx[0][(char *)"FILTER"] = scopes;

	map["SESSION"] = m_SessionID;
	map["WDDX"] = wddxUtils.serialize(wddx);

	ba = dbgService.ExecuteRDSCommand(m_RDSServer, QDebuggerService::doDebugRequest, map);
	QVector<QByteArray> vec = dbgService.BreakByteArrayIntoVector(ba);
	
	if (vec.size() != 0)
		return false;

	return true;
}

bool QCFDebugger::BreakOnException(bool Break)
{
	if ((m_ServerPort == 0)||(m_SessionID == ""))
		return false;

	QDebuggerService dbgService;
	QMap<QString, QString> map;
	QByteArray ba;
	QWDDX wddx(QWDDX::Array);
	QWDDXUtils wddxUtils;

	wddx[0][(char *)"COMMAND"] = (char *)"SESSION_BREAK_ON_EXCEPTION";
	wddx[0][(char *)"BREAK_ON_EXCEPTION"] = Break;

	map["SESSION"] = m_SessionID;
	map["WDDX"] = wddxUtils.serialize(wddx);

	ba = dbgService.ExecuteRDSCommand(m_RDSServer, QDebuggerService::doDebugRequest, map);
	QVector<QByteArray> vec = dbgService.BreakByteArrayIntoVector(ba);
	
	if (vec.size() != 0)
		return false;

	return true;
}

bool QCFDebugger::SetBreakpoint(QString file, int line, bool State, int Sequence)
{
	if ((m_ServerPort == 0)||(m_SessionID == ""))
		return false;

	QDebuggerService dbgService;
	QMap<QString, QString> map;
	QByteArray ba;
	QWDDX wddx(QWDDX::Array);
	QWDDXUtils wddxUtils;

	if (State == true)
		wddx[0][(char *)"COMMAND"] = (char *)"SET_BREAKPOINT";
	else
		wddx[0][(char *)"COMMAND"] = (char *)"UNSET_BREAKPOINT";

	wddx[0][(char *)"SEQ"] = (double)Sequence; // Todo: Yet don't know what is this, maybe hit at number(SEQ) of passes.
	wddx[0][(char *)"FILE"] = file;
	wddx[0][(char *)"Y"] = (double)line;

	map["SESSION"] = m_SessionID;
	map["WDDX"] = wddxUtils.serialize(wddx);

	ba = dbgService.ExecuteRDSCommand(m_RDSServer, QDebuggerService::doDebugRequest, map);
	QVector<QByteArray> vec = dbgService.BreakByteArrayIntoVector(ba);
	
	if (vec.size() != 0)
		return false;

	return true;
}

void QCFDebugger::onEventConnected()
{
	qDebug("QCFDebugger::onEventConnected");
	QDebuggerService dbgService;

	QVector<QString> map;

	map.append("DBG_EVENTS");
	map.append(m_SessionID);

	QByteArray ba = dbgService.generateRDSCommandSocketOutput(dbgService.prepareURL(m_RDSServer, "DBGREQUEST", m_RDSServer.getPort()), dbgService.generatePostFromVector(m_RDSServer, map));

	//ba[ba.indexOf("HTTP/1.0") + 7] = '1';
	//ba.insert(ba.indexOf("Connection: close") + 17, ", TE\r\nTE: trailers, deflate, gzip, compress");
	//ba.insert(ba.indexOf("Accept-Encoding:") + 24, ", gzip, x-gzip, compress, x-compress");

	QString ttt = ba;

	m_EventSocket.write(ba);
}

void QCFDebugger::onEventDisconnected()
{
	qDebug("QCFDebugger::onEventDisconnected");
	
	QString rec = m_EventReadData;

	if (m_EventReconect == true)
		m_EventSocket.connectToHost(m_RDSServer.getHostName(), m_ServerPort);
}

void QCFDebugger::onEventError(QAbstractSocket::SocketError p_Error)
{
	qDebug("QCFDebugger::onEventError");
	m_EventReconect = false;
}

void QCFDebugger::onEventReadyRead()
{
	qDebug("QCFDebugger::onEventReadyRead");
	m_EventReadData += m_EventSocket.readAll();

	QString ttt = m_EventReadData;

	m_EventSocket.disconnectFromHost();
}

void QCFDebugger::onEventBytesWritten(qint64)
{
}
