#include "QJDWPGetPathSeparatorCommand.h"
#include "QJDWPClassesBySignatureCommand.h"

QJDWPGetPathSeparatorCommand::QJDWPGetPathSeparatorCommand(QJDWPDebugger* parent)
	: QJDWPCommand(parent)
{
	m_Progress = CLASSES_BY_SIGNATURE;
	m_SubCommand = new QJDWPClassesBySignatureCommand(parent);
	((QJDWPClassesBySignatureCommand*)m_SubCommand)->sendCommand("Ljava/io/File;");
	m_CommandID = m_SubCommand->getCommandID();
	//parent->
}

char QJDWPGetPathSeparatorCommand::getPathSeparator()
{
	return this->m_PathSeparator;
}

void QJDWPGetPathSeparatorCommand::processRecivedCommand(QByteArray p_Data)
{
	switch (m_Progress)
	{
		case CLASSES_BY_SIGNATURE:
			break;
		default:
			break;
	}
}