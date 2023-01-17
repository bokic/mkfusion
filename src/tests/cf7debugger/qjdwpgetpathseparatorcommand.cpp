#include "qjdwpgetpathseparatorcommand.h"
#include "qjdwpclassesbysignaturecommand.h"

QJDWPGetPathSeparatorCommand::QJDWPGetPathSeparatorCommand(QJDWPDebugger *parent)
    : QJDWPCommand(parent)
{
    m_Progress = CLASSES_BY_SIGNATURE;
    m_SubCommand = new QJDWPClassesBySignatureCommand(parent);
    static_cast<QJDWPClassesBySignatureCommand *>(m_SubCommand)->sendCommand("Ljava/io/File;");
    m_CommandID = m_SubCommand->getCommandID();
    //parent->
}

QJDWPGetPathSeparatorCommand::~QJDWPGetPathSeparatorCommand()
{
}

char QJDWPGetPathSeparatorCommand::getPathSeparator()
{
    return this->m_PathSeparator;
}

void QJDWPGetPathSeparatorCommand::processRecivedCommand(const QByteArray &data)
{
    Q_UNUSED(data);

    switch (m_Progress)
    {
    case CLASSES_BY_SIGNATURE:
        break;
    default:
        break;
    }
}
