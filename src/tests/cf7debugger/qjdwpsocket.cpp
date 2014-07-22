#include "qjdwpsocket.h"

QJDWPSocket::QJDWPSocket()
{
    m_InitTimer = 0;

    connect(&m_Socket, &QTcpSocket::connected, this, &QJDWPSocket::on_m_Socket_connected);
    connect(&m_Socket, &QTcpSocket::readyRead, this, &QJDWPSocket::on_m_Socket_readyRead);
}

QJDWPSocket::~QJDWPSocket()
{
}

void QJDWPSocket::connectToHost(const QString& p_Host, quint16 p_Port)
{
    m_Socket.disconnectFromHost();

    m_Socket.connectToHost(p_Host, p_Port, QIODevice::ReadWrite);

    if (m_InitTimer != 0)
    {
        killTimer(m_InitTimer);
    }
    m_InitTimer = startTimer(5000);
}

quint32 QJDWPSocket::sendCommand(quint8 p_CommandSet, quint8 p_Command, const QByteArray& p_Data)
{
    QByteArray l_Packet;
    int l_PacketSize = p_Data.length() + 11;
    m_CommandCounter++;

    l_Packet.append((char)(l_PacketSize >> 24));
    l_Packet.append((char)(l_PacketSize >> 16));
    l_Packet.append((char)(l_PacketSize >> 8));
    l_Packet.append((char)(l_PacketSize));

    l_Packet.append((char)(m_CommandCounter >> 24));
    l_Packet.append((char)(m_CommandCounter >> 16));
    l_Packet.append((char)(m_CommandCounter >> 8));
    l_Packet.append((char)(m_CommandCounter));

    l_Packet.append('\0');
    l_Packet.append(p_CommandSet);
    l_Packet.append(p_Command);
    l_Packet.append(p_Data);

    m_Socket.write(l_Packet);
    m_Socket.flush();

    return m_CommandCounter;
}

void QJDWPSocket::on_m_Socket_connected()
{
    qDebug("connected");

    m_Initialized = false;
    m_CommandCounter = 0;
    m_Socket.write(QByteArray("JDWP-Handshake"));
}

void QJDWPSocket::on_m_Socket_readyRead()
{
    int l_BufSize;
    quint32 l_Id;
    quint16 l_Error;

    qDebug("readyRead");

    m_reciveBuf.append(m_Socket.readAll());

    qDebug() << QString::number(m_reciveBuf.length());

    if (m_Initialized)
    {
        if (m_reciveBuf.length() > 4)
        {
            l_BufSize = ((quint8)m_reciveBuf[0] << 24) + ((quint8)m_reciveBuf[1] << 16) + ((quint8)m_reciveBuf[2] << 8) + ((quint8)m_reciveBuf[3]);

            qDebug() << QString::number(l_BufSize);

            if (m_reciveBuf.length() >= l_BufSize)
            {
                l_Id = ((quint8)m_reciveBuf[4] << 24) + ((quint8)m_reciveBuf[5] << 16) + ((quint8)m_reciveBuf[6] << 8) + ((quint8)m_reciveBuf[7]);
                l_Error = ((quint8)m_reciveBuf[9] << 24) + ((quint8)m_reciveBuf[10] << 16);

                if (l_Id == 1)
                {
                    m_IDSizes = decodeCommandIDSizes(m_reciveBuf.mid(11, l_BufSize - 11));
                    m_reciveBuf = m_reciveBuf.right(m_reciveBuf.length() - l_BufSize);
                    emit ready();
                }
                else
                {
                    emit gotPacket(l_Id, (quint8)m_reciveBuf[8], l_Error, m_reciveBuf.mid(11, l_BufSize - 11));
                    m_reciveBuf = m_reciveBuf.right(m_reciveBuf.length() - l_BufSize);
                }
            }
        }
    }
    else
    {
        if (m_reciveBuf == "JDWP-Handshake")
        {
            if (m_InitTimer != 0)
            {
                killTimer(m_InitTimer);
                m_InitTimer = 0;
            }

            m_reciveBuf.clear();
            m_Initialized = true;

            //sendCommand(1, 7, "");

            emit ready();
        }
        else
        {
            qDebug("got bad response");
        }
    }
}

void QJDWPSocket::timerEvent(QTimerEvent* event)
{
    qDebug("timerEvent");
    if (event->timerId() == m_InitTimer)
    {
        qDebug("m_InitTimer hit");
        m_Socket.disconnectFromHost();
    }
}

int QJDWPSocket::decodeInt(QByteArray p_Data, int p_Offset)
{
    if (p_Data.length() < p_Offset + 4)
    {
        return -1;
    }

    return ((qint8)p_Data[p_Offset + 0] << 24) + ((quint8)p_Data[p_Offset + 1] << 16) + ((quint8)p_Data[p_Offset + 2] << 8) + ((quint8)p_Data[p_Offset + 3]);
}

qint64 QJDWPSocket::decodeInt(QByteArray p_Data, int p_Offset, int p_Size)
{
    if ((p_Size != 1)&&(p_Size != 2)&&(p_Size != 4)&&(p_Size != 8))
    {
        return -1;
    }

    if (p_Data.length() < p_Offset + p_Size)
    {
        return -1;
    }

    return ((qint8)p_Data[p_Offset + 0] << 24) + ((quint8)p_Data[p_Offset + 1] << 16) + ((quint8)p_Data[p_Offset + 2] << 8) + ((quint8)p_Data[p_Offset + 3]);
}


QByteArray QJDWPSocket::encodeInt(int p_Integer)
{
    QByteArray ret;

    ret.append((char)(p_Integer >> 24));
    ret.append((char)(p_Integer >> 16));
    ret.append((char)(p_Integer >> 8));
    ret.append((char)p_Integer);
    return ret;
}

QString QJDWPSocket::decodeString(QByteArray p_Data, int p_Offset)
{
    int l_Size = decodeInt(p_Data, p_Offset + 4);

    if (l_Size <=0)
    {
        return "";
    }

    return QString::fromUtf8(p_Data.mid(p_Offset + 4, l_Size));
}

QByteArray QJDWPSocket::encodeString(QString p_String)
{
    QByteArray l_Temp = p_String.toUtf8();
    return encodeInt(l_Temp.length()) + l_Temp;
}

QJDWPCommandVersion QJDWPSocket::decodeCommandVersion(QByteArray p_Data)
{
    QJDWPCommandVersion ret;
    int l_DescriptionSize = decodeInt(p_Data);
    int l_Version = decodeInt(p_Data, l_DescriptionSize + 12);

    ret.m_Error = false;
    ret.m_Description = decodeString(p_Data);
    ret.m_jdwpMajor = decodeInt(p_Data, l_DescriptionSize + 4);
    ret.m_jdwpMinor = decodeInt(p_Data, l_DescriptionSize + 8);
    ret.m_vmVersion = decodeString(p_Data, l_DescriptionSize + 12);
    ret.m_vmName = decodeString(p_Data, l_DescriptionSize + l_Version + 16);

    return ret;
}

QJDWPCommandIDSizes QJDWPSocket::decodeCommandIDSizes(QByteArray p_Data)
{
    QJDWPCommandIDSizes ret;

    if (p_Data.length() != 20)
    {
        ret.m_Error = true;
        ret.m_fieldIDSize = 0;
        ret.m_methodIDSize = 0;
        ret.m_objectIDSize = 0;
        ret.m_referenceTypeIDSize = 0;
        ret.m_frameIDSize = 0;
        return ret;
    }

    ret.m_Error = false;
    ret.m_fieldIDSize = decodeInt(p_Data, 0);
    ret.m_methodIDSize = decodeInt(p_Data, 4);
    ret.m_objectIDSize = decodeInt(p_Data, 8);
    ret.m_referenceTypeIDSize = decodeInt(p_Data, 12);
    ret.m_frameIDSize = decodeInt(p_Data, 16);

    return ret;
}

qint32 QJDWPSocket::getFieldIDSize()
{
    return m_IDSizes.m_fieldIDSize;
}

qint32 QJDWPSocket::getMethodIDSize()
{
    return m_IDSizes.m_methodIDSize;
}

qint32 QJDWPSocket::getObjectIDSize()
{
    return m_IDSizes.m_objectIDSize;
}

qint32 QJDWPSocket::getReferenceTypeIDSize()
{
    return m_IDSizes.m_referenceTypeIDSize;
}

qint32 QJDWPSocket::getFrameIDSize()
{
    return m_IDSizes.m_frameIDSize;
}

