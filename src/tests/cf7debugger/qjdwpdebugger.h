#pragma once

#include <QObject>
#include "qjdwpsocket.h"
#include "qjdwpcommand.h"

class QJDWPDebugger : public QObject
{
    Q_OBJECT
public:
    explicit QJDWPDebugger(QObject *parent=0);
    void connectToHost(QString, quint16);
    void addCommand(QJDWPCommand*p_Command);
    quint32 sendCommand(quint8, quint8, const QByteArray&);
signals:
    void recieveCommand(QJDWPCommand*);
    void connected();
private:
    QList<QJDWPCommand*> m_Commands;
    bool m_Initialized;
    char m_PathSeparator;
    QJDWPSocket m_JDWP;
    quint32 m_TempCommand1, m_TempCommand2;
private slots:
    void on_m_JDWP_ready();
    void on_m_JDWP_gotPacket(quint32, quint8, quint16, QByteArray);
};
