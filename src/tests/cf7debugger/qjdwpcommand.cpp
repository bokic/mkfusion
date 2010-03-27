#include "QJDWPCommand.h"

QJDWPCommand::QJDWPCommand(QObject* parent)
	: QObject(parent)
{
	m_CommandID = 0;
}

quint32 QJDWPCommand::getCommandID()
{
	return this->m_CommandID;
}
