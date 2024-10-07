#include "qjdwpdebugger.h"
#include "qjdwpgetpathseparatorcommand.h"

QJDWPDebugger::QJDWPDebugger(QObject *parent)
    : QObject(parent)
{
    m_Initialized = false;
    m_PathSeparator = 0;

    connect(&m_JDWP, &QJDWPSocket::ready, this, &QJDWPDebugger::on_m_JDWP_ready);
    connect(&m_JDWP, &QJDWPSocket::gotPacket, this, &QJDWPDebugger::on_m_JDWP_gotPacket);
}

void QJDWPDebugger::connectToHost(const QString &host, quint16 port)
{
    m_JDWP.connectToHost(host, port);
}

void QJDWPDebugger::addCommand(QJDWPCommand *command)
{
    command->setParent(this);
    m_Commands.append(command);
    //m_Command->se
}

quint32 QJDWPDebugger::sendCommand(quint8 commandSet, quint8 command, const QByteArray &data)
{
    return m_JDWP.sendCommand(commandSet, command, data);
}

void QJDWPDebugger::on_m_JDWP_ready()
{
    //m_JDWP.sendCommand(1, 1, "");
    //m_JDWP.sendCommand(1, 7, "");

    addCommand(new QJDWPGetPathSeparatorCommand(this));
    // 1. Get sizes
    // 2. Get JavaVersion
    // 3. get Capatibilities New
    // 4. get PathSeparator
    //m_TempCommand1 = m_JDWP.sendCommand(1, 2, QJDWPSocket::encodeString("Ljava/io/File;"));
}

void QJDWPDebugger::on_m_JDWP_gotPacket(quint32 id, quint8 flags, quint16 errorCode, const QByteArray &data)
{
    qDebug("gotPacket");

    if (flags != 0x80)
    {
        qDebug() << QString("Bad JDWP Flag got. It should be 0x80, but it\'s 0x%1").arg(QString::number(flags, 16));
        return;
    }

    if (errorCode != 0)
    {
        qDebug() << QString("JDWP Error code 0x%1").arg(QString::number(errorCode, 16));
        return;
    }

    QJDWPCommand *command = nullptr;

    for(QJDWPCommand *item: std::as_const(m_Commands))
    {
        if (item->getCommandID() == id)
        {
            command = item;
            break;
        }
    }

    if (command == nullptr)
    {
        qDebug("Unknown command ID arrived.");
        return;
    }

    command->processRecivedCommand(data);

    if (command->getCommandID() == 0)
    {
        m_Commands.removeOne(command);
        if (m_Initialized)
        {
            emit recieveCommand(command);
        }
        else
        {
            if ((m_PathSeparator == 0)&&(strcmp(command->metaObject()->className(), "QJDWPGetPathSeparatorCommand") == 0))
            {
                m_PathSeparator = static_cast<QJDWPGetPathSeparatorCommand *>(command)->getPathSeparator();
            }
            else
            {
                emit connected();
            }
        }

        command->deleteLater();
    }
}
