#include "qjdwpclassesbysignaturecommand.h"
#include "qjdwpsocket.h"
#include "qjdwpdebugger.h"

QJDWPClassesBySignatureCommand::QJDWPClassesBySignatureCommand(QObject *parent)
    : QJDWPCommand(parent)
{
}

QJDWPClassesBySignatureCommand::~QJDWPClassesBySignatureCommand()
{
}

quint32 QJDWPClassesBySignatureCommand::sendCommand(const QString &p_ClassName) // "Ljava/io/File;"
{
    if (strcmp(parent()->metaObject()->className(), "QJDWPDebugger") != 0)
    {
        qDebug("parent() is not QJDWPDebugger");
        return 0;
    }

    m_CommandID = ((QJDWPDebugger *)parent())->sendCommand(1, 2, QJDWPSocket::encodeString(p_ClassName));

    return m_CommandID;
}

void QJDWPClassesBySignatureCommand::processRecivedCommand(const QByteArray &p_Data)
{
    if (p_Data.length() < 4)
    {
        qDebug("Packet size should be >= 4");
        return;
    }

    int l_Size = QJDWPSocket::decodeInt(p_Data);

    for(int c = 0; c <  l_Size; c++)
    {
        QJDWPClassesBySignature item;

        m_Result.append(item);
    }

    m_CommandID = 0;
}

QList<QJDWPClassesBySignature> QJDWPClassesBySignatureCommand::result() const
{
    return m_Result;
}
