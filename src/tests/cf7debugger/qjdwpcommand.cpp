#include "qjdwpcommand.h"

QJDWPCommand::QJDWPCommand(QObject* parent)
	: QObject(parent)
	, m_CommandID(0)
{	
}

QJDWPCommand::~QJDWPCommand()
{
}

quint32 QJDWPCommand::getCommandID() const
{
	return this->m_CommandID;
}
