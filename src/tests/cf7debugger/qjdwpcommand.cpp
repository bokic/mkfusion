#include "qjdwpcommand.h"

QJDWPCommand::QJDWPCommand(QObject *parent)
    : QObject(parent)
{
}

quint32 QJDWPCommand::getCommandID() const
{
    return this->m_CommandID;
}
