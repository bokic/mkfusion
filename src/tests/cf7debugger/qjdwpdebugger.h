#pragma once

#include <QObject>
#include "qjdwpsocket.h"
#include "qjdwpcommand.h"


class QJDWPDebugger : public QObject
{
    Q_OBJECT
public:
    explicit QJDWPDebugger(QObject *parent = nullptr);
    void connectToHost(const QString &host, quint16 port);
    void addCommand(QJDWPCommand *command);
    quint32 sendCommand(quint8 commandSet, quint8 command, const QByteArray &data);

signals:
    void recieveCommand(QJDWPCommand *command);
    void connected();

private:
    QList<QJDWPCommand *> m_Commands;
    bool m_Initialized = false;
    char m_PathSeparator = '/';
    QJDWPSocket m_JDWP;
    quint32 m_TempCommand1 = 0, m_TempCommand2 = 0;

private slots:
    void on_m_JDWP_ready();
    void on_m_JDWP_gotPacket(quint32 id, quint8 flags, quint16 errorCode, const QByteArray &data);
};
