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

quint32 QJDWPClassesBySignatureCommand::sendCommand(const QString &className) // "Ljava/io/File;"
{
    if (strcmp(parent()->metaObject()->className(), "QJDWPDebugger") != 0)
    {
        qDebug("parent() is not QJDWPDebugger");
        return 0;
    }

    m_CommandID = static_cast<QJDWPDebugger *>(parent())->sendCommand(1, 2, QJDWPSocket::encodeString(className));

    return m_CommandID;
}

void QJDWPClassesBySignatureCommand::processRecivedCommand(const QByteArray &data)
{
    if (data.length() < 4)
    {
        qDebug("Packet size should be >= 4");
        return;
    }

    int l_Size = QJDWPSocket::decodeInt(data);

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
