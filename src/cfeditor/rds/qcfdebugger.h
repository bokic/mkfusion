#pragma once

#include "qrdsserver.h"
#include <QTcpSocket>
#include <QDomNode>

class QCFDebugger: public QObject
{
    Q_OBJECT
public:
    QCFDebugger(const QRDSServer &server);
    quint16 debuggerPort();
    QString sessionID() const;
    bool startDebugger();
    bool stopDebugger();
    bool setMonitorScopes(const QString &scopes);
    bool breakOnException(bool brk);
    bool setBreakpoint(const QString &file, int line, bool state, int sequence = 1);
protected:
private:
    QRDSServer m_RDSServer;
    quint16 m_ServerPort;
    QString m_SessionID;
    QTcpSocket m_EventSocket;
    bool m_EventReconect;
    QByteArray m_EventReadData;
private slots:
    void onEventConnected();
    void onEventDisconnected();
    void onEventError(QAbstractSocket::SocketError error);
    void onEventReadyRead();
    void onEventBytesWritten(qint64 bytes);
};
