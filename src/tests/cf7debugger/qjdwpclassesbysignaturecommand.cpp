#include "QJDWPClassesBySignatureCommand.h"
#include "QJDWPSocket.h"
#include "QJDWPDebugger.h"

QJDWPClassesBySignatureCommand::QJDWPClassesBySignatureCommand(QObject* parent)
	: QJDWPCommand(parent)
{
}

quint32 QJDWPClassesBySignatureCommand::sendCommand(QString p_ClassName) // "Ljava/io/File;"
{
	if (strcmp(parent()->metaObject()->className(), "QJDWPDebugger") != 0)
	{
		qDebug("parent() is not QJDWPDebugger");
		return 0;
	}

	m_CommandID = ((QJDWPDebugger *)parent())->sendCommand(1, 2, QJDWPSocket::encodeString(p_ClassName));

	return m_CommandID;
}

void QJDWPClassesBySignatureCommand::processRecivedCommand(QByteArray p_Data)
{
	if (p_Data.length() < 4)
	{
		qDebug("Packet size should be >= 4");
		return;
	}

	int l_Size = QJDWPSocket::decodeInt(p_Data);

	for(int c = 0; c <  l_Size; c++)
	{
		QJDWPClassesBySignature* item = new QJDWPClassesBySignature();

		m_Result.append(item);
	}

	m_CommandID = 0;
}

const QList<QJDWPClassesBySignature*> QJDWPClassesBySignatureCommand::getResult()
{
	return m_Result;
}