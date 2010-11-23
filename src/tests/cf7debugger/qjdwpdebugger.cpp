#include "qjdwpdebugger.h"
#include "qjdwpgetpathseparatorcommand.h"

QJDWPDebugger::QJDWPDebugger(QObject *parent)
	: QObject(parent)
{
	m_Initialized = false;
	m_PathSeparator = 0;

	connect(&m_JDWP, SIGNAL(ready()), this, SLOT(on_m_JDWP_ready()));
	connect(&m_JDWP, SIGNAL(gotPacket(quint32, quint8, quint16, QByteArray)), this, SLOT(on_m_JDWP_gotPacket(quint32, quint8, quint16, QByteArray)));
}

void QJDWPDebugger::connectToHost(QString p_Host, quint16 p_Port)
{
	m_JDWP.connectToHost(p_Host, p_Port);
}

void QJDWPDebugger::addCommand(QJDWPCommand* m_Command)
{
	m_Command->setParent(this);
	m_Commands.append(m_Command);
	//m_Command->se
}

quint32 QJDWPDebugger::sendCommand(quint8 p_CommandSet, quint8 p_Command, const QByteArray& p_Data)
{
	return m_JDWP.sendCommand(p_CommandSet, p_Command, p_Data);
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

void QJDWPDebugger::on_m_JDWP_gotPacket(quint32 p_Id, quint8 p_Flags, quint16 p_ErrorCode, QByteArray p_Data)
{
	qDebug("gotPacket");

	if (p_Flags != 0x80)
	{
        qDebug() << QString("Bad JDWP Flag got. It should be 0x80, but it\'s 0x%1").arg(QString::number(p_Flags, 16));
		return;
	}

	if (p_ErrorCode != 0)
	{
        qDebug() << QString("JDWP Error code 0x%1").arg(QString::number(p_ErrorCode, 16));
		return;
	}

	QJDWPCommand* l_Command = NULL;

	foreach(QJDWPCommand* l_Item, m_Commands)
	{
		if (l_Item->getCommandID() == p_Id)
		{
			l_Command = l_Item;
			break;
		}
	}

	if (l_Command == NULL)
	{
		qDebug("Unknown command ID arrived.");
		return;
	}

	l_Command->processRecivedCommand(p_Data);

	if (l_Command->getCommandID() == 0)
	{
		m_Commands.removeOne(l_Command);
		if (m_Initialized)
		{
			emit recieveCommand(l_Command);
		} else {
			if ((m_PathSeparator == 0)&&(strcmp(l_Command->metaObject()->className(), "QJDWPGetPathSeparatorCommand") == 0))
			{
				m_PathSeparator = ((QJDWPGetPathSeparatorCommand*)l_Command)->getPathSeparator();
			} else {
				emit connected();
			}
		}
		l_Command->deleteLater();
	}
}
