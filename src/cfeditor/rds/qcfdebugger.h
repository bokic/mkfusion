#ifndef QCFDEBUGGER_H
#define QCFDEBUGGER_H

#include "qrdsserver.h"
#include <QTcpSocket>
#include <QDomNode>

class QCFDebugger: public QObject
{
    Q_OBJECT
public:
    QCFDebugger(QRDSServer);
    quint16 getDebuggerPort();
    QString getSessionID();
    bool StartDebugger();
    bool StopDebugger();
    bool SetMonitorScopes(QString);
    bool BreakOnException(bool);
    bool SetBreakpoint(QString, int, bool, int = 1);
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
    void onEventError(QAbstractSocket::SocketError);
    void onEventReadyRead();
    void onEventBytesWritten(qint64);
};

#endif // QCFDEBUGGER_H
