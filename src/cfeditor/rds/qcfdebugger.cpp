#include "qcfdebugger.h"
#include "qdebuggerservice.h"
#include "qdefaultservice.h"
#include "qwddxutils.h"

QCFDebugger::QCFDebugger(const QRDSServer &server)
    : QObject()
    , m_RDSServer(server)
    , m_ServerPort(0)
    , m_EventReconect(false)
{
    connect(&m_EventSocket, &QTcpSocket::connected, this, &QCFDebugger::onEventConnected);
    connect(&m_EventSocket, &QTcpSocket::disconnected, this, &QCFDebugger::onEventDisconnected);
    connect(&m_EventSocket, &QTcpSocket::errorOccurred, this, &QCFDebugger::onEventError);
    connect(&m_EventSocket, &QTcpSocket::readyRead, this, &QCFDebugger::onEventReadyRead);
    connect(&m_EventSocket, &QTcpSocket::bytesWritten, this, &QCFDebugger::onEventBytesWritten);
}

quint16 QCFDebugger::debuggerPort()
{
    if (m_ServerPort == 0)
    {
        QMap<QString, QString> map;
        QByteArray ba;

        //m_RDSServer.setPort(8000); // This is needed for CF7
        m_ServerPort = m_RDSServer.port();

        QDebuggerService dbgService;
        QWDDXUtils wddxUtils;
        ba = dbgService.ExecuteRDSCommand(m_RDSServer, QDebuggerService::getServerInfo, map);
        QVector<QByteArray> vec = dbgService.BreakByteArrayIntoVector(ba);
        if (vec.size() <= 0)
            return m_ServerPort;

        QWDDX result = wddxUtils.deserialize(vec[0]);
        m_ServerPort = result[0][QStringLiteral("DEBUG_SERVER_PORT")].toNumber();
    }
    return m_ServerPort;
}

QString QCFDebugger::sessionID() const
{
    return QString();
}

bool QCFDebugger::startDebugger()
{
    if (!m_SessionID.isEmpty())
        return false;

    QMap<QString, QString> map;
    QDefaultService defaultService;
    QByteArray ba = defaultService.ExecuteRDSCommand(m_RDSServer, QDefaultService::IdeDefaultCommand, map);

    if (m_RDSServer.authenticated() == false)
        return false;

    m_RDSServer.setPort(debuggerPort());

    QDebuggerService debuggerService;

    QWDDXUtils wddxUtils;
    QWDDX wddx(QWDDX::Array);

    wddx[0][QStringLiteral("REMOTE_SESSION")] = true;
    map.insert(QStringLiteral("WDDX"), wddxUtils.serialize(wddx));
    ba = debuggerService.ExecuteRDSCommand(m_RDSServer, QDebuggerService::doDebugStart, map);
    QVector<QByteArray> vec = debuggerService.BreakByteArrayIntoVector(ba);

    if (vec.size() < 2)
        return false;

    QWDDX result = wddxUtils.deserialize(vec[1]);

    if ((result[0][QStringLiteral("COMMAND")].toString() != QStringLiteral("DBG_START"))||(result[0][QStringLiteral("SESSION")].toString() != vec[0])||(result[0][QStringLiteral("STATUS")].toString() != QStringLiteral("RDS_OK")))
        return false;

    m_SessionID = vec[0];

    breakOnException(true);
    setMonitorScopes(QStringLiteral("VARIABLES"));
    setBreakpoint(QStringLiteral("/home/projects/boro_test/test.cfm"), 1, true);

    m_EventReconect = true;
    m_EventSocket.connectToHost(m_RDSServer.hostname(), m_ServerPort);

    return true;
}

bool QCFDebugger::stopDebugger()
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

    map[QStringLiteral("DEBUG_SERVER_PORT")] = QString(m_ServerPort);
    map[QStringLiteral("SESSION")] = m_SessionID;

    QDebuggerService dbgService;
    ba = dbgService.ExecuteRDSCommand(m_RDSServer, QDebuggerService::doDebugStop, map);
    QVector<QByteArray> vec = dbgService.BreakByteArrayIntoVector(ba);

    if (vec.size() <= 0)
        return false;

    QWDDXUtils wddxUtils;
    QWDDX result = wddxUtils.deserialize(vec[0]);
    if ((result[0][QStringLiteral("SESSION")].toString() != m_SessionID)||(result[0][QStringLiteral("STATUS")].toString() != QStringLiteral("RDS_OK"))||(result[0][QStringLiteral("COMMAND")].toString() != QStringLiteral("DBG_STOP")))
        return false;

    m_SessionID = "";

    return true;
}

bool QCFDebugger::setMonitorScopes(const QString &scopes)
{
    if ((m_ServerPort == 0)||(m_SessionID == ""))
        return false;

    QDebuggerService dbgService;
    QMap<QString, QString> map;
    QByteArray ba;
    QWDDX wddx(QWDDX::Array);
    QWDDXUtils wddxUtils;

    wddx[0][QStringLiteral("COMMAND")] = QStringLiteral("SET_SCOPE_FILTER");
    wddx[0][QStringLiteral("FILTER")] = scopes;

    map[QStringLiteral("SESSION")] = m_SessionID;
    map[QStringLiteral("WDDX")] = wddxUtils.serialize(wddx);

    ba = dbgService.ExecuteRDSCommand(m_RDSServer, QDebuggerService::doDebugRequest, map);
    QVector<QByteArray> vec = dbgService.BreakByteArrayIntoVector(ba);

    if (vec.size() != 0)
        return false;

    return true;
}

bool QCFDebugger::breakOnException(bool brk)
{
    if ((m_ServerPort == 0)||(m_SessionID == ""))
        return false;

    QDebuggerService dbgService;
    QMap<QString, QString> map;
    QByteArray ba;
    QWDDX wddx(QWDDX::Array);
    QWDDXUtils wddxUtils;

    wddx[0][QStringLiteral("COMMAND")] = QStringLiteral("SESSION_BREAK_ON_EXCEPTION");
    wddx[0][QStringLiteral("BREAK_ON_EXCEPTION")] = brk;

    map[QStringLiteral("SESSION")] = m_SessionID;
    map[QStringLiteral("WDDX")] = wddxUtils.serialize(wddx);

    ba = dbgService.ExecuteRDSCommand(m_RDSServer, QDebuggerService::doDebugRequest, map);
    QVector<QByteArray> vec = dbgService.BreakByteArrayIntoVector(ba);

    if (vec.size() != 0)
        return false;

    return true;
}

bool QCFDebugger::setBreakpoint(const QString &file, int line, bool state, int sequence)
{
    if ((m_ServerPort == 0)||(m_SessionID == ""))
        return false;

    QDebuggerService dbgService;
    QMap<QString, QString> map;
    QByteArray ba;
    QWDDX wddx(QWDDX::Array);
    QWDDXUtils wddxUtils;

    if (state == true)
        wddx[0][QStringLiteral("COMMAND")] = QStringLiteral("SET_BREAKPOINT");
    else
        wddx[0][QStringLiteral("COMMAND")] = QStringLiteral("UNSET_BREAKPOINT");

    wddx[0][QStringLiteral("SEQ")] = (double)sequence; // Todo: Yet don't know what is this, maybe hit at number(SEQ) of passes.
    wddx[0][QStringLiteral("FILE")] = file;
    wddx[0][QStringLiteral("Y")] = (double)line;

    map[QStringLiteral("SESSION")] = m_SessionID;
    map[QStringLiteral("WDDX")] = wddxUtils.serialize(wddx);

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

    map.append(QStringLiteral("DBG_EVENTS"));
    map.append(m_SessionID);

    QByteArray ba = dbgService.generateRDSCommandSocketOutput(dbgService.prepareURL(m_RDSServer, QStringLiteral("DBGREQUEST"), m_RDSServer.port()), dbgService.generatePostFromVector(m_RDSServer, map));

    //ba[ba.indexOf("HTTP/1.0") + 7] = '1';
    //ba.insert(ba.indexOf("Connection: close") + 17, ", TE\r\nTE: trailers, deflate, gzip, compress");
    //ba.insert(ba.indexOf("Accept-Encoding:") + 24, ", gzip, x-gzip, compress, x-compress");

    m_EventSocket.write(ba);
}

void QCFDebugger::onEventDisconnected()
{
    qDebug("QCFDebugger::onEventDisconnected");

    if (m_EventReconect == true)
        m_EventSocket.connectToHost(m_RDSServer.hostname(), m_ServerPort);
}

void QCFDebugger::onEventError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error);

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

void QCFDebugger::onEventBytesWritten(qint64 bytes)
{
    Q_UNUSED(bytes);

    qDebug("QCFDebugger::onEventBytesWritten");
}
