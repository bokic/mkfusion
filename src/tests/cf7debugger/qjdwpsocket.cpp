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

void QJDWPSocket::connectToHost(const QString &host, quint16 port)
{
    if (m_Socket.isOpen())
        m_Socket.disconnectFromHost();

    m_Socket.connectToHost(host, port, QIODevice::ReadWrite);

    if (m_InitTimer != 0)
    {
        killTimer(m_InitTimer);
    }

    m_InitTimer = startTimer(5000);
}

quint32 QJDWPSocket::sendCommand(quint8 commandSet, quint8 command, const QByteArray &data)
{
    QByteArray l_Packet;

    int l_PacketSize = data.length() + 11;

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
    l_Packet.append(commandSet);
    l_Packet.append(command);
    l_Packet.append(data);

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
    qDebug("readyRead");

    m_reciveBuf.append(m_Socket.readAll());

    qDebug() << QString::number(m_reciveBuf.length());

    if (m_Initialized)
    {
        if (m_reciveBuf.length() > 4)
        {
            int l_BufSize = ((quint8)m_reciveBuf[0] << 24) + ((quint8)m_reciveBuf[1] << 16) + ((quint8)m_reciveBuf[2] << 8) + ((quint8)m_reciveBuf[3]);

            qDebug() << QString::number(l_BufSize);

            if (m_reciveBuf.length() >= l_BufSize)
            {
                quint32 id = ((quint8)m_reciveBuf[4] << 24) + ((quint8)m_reciveBuf[5] << 16) + ((quint8)m_reciveBuf[6] << 8) + ((quint8)m_reciveBuf[7]);

                if (id == 1)
                {
                    m_IDSizes = decodeCommandIDSizes(m_reciveBuf.mid(11, l_BufSize - 11));
                    m_reciveBuf = m_reciveBuf.right(m_reciveBuf.length() - l_BufSize);
                    emit ready();
                }
                else
                {
                    quint16 error = ((quint8)m_reciveBuf[9] << 24) + ((quint8)m_reciveBuf[10] << 16);

                    emit gotPacket(id, (quint8)m_reciveBuf[8], error, m_reciveBuf.mid(11, l_BufSize - 11));
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

void QJDWPSocket::timerEvent(QTimerEvent *event)
{
    qDebug("timerEvent");

    if (event->timerId() == m_InitTimer)
    {
        qDebug("m_InitTimer hit");
        m_Socket.disconnectFromHost();
    }
}

int QJDWPSocket::decodeInt(const QByteArray &data, int offset)
{
    if (data.length() < offset + 4)
    {
        return -1;
    }

    return ((qint8)data[offset + 0] << 24) + ((quint8)data[offset + 1] << 16) + ((quint8)data[offset + 2] << 8) + ((quint8)data[offset + 3]);
}

qint64 QJDWPSocket::decodeInt(const QByteArray &data, int offset, int size)
{
    if ((size != 1)&&(size != 2)&&(size != 4)&&(size != 8))
    {
        return -1;
    }

    if (data.length() < offset + size)
    {
        return -1;
    }

    return ((qint8)data[offset + 0] << 24) + ((quint8)data[offset + 1] << 16) + ((quint8)data[offset + 2] << 8) + ((quint8)data[offset + 3]);
}


QByteArray QJDWPSocket::encodeInt(int value)
{
    QByteArray ret;

    ret.append((char)(value >> 24));
    ret.append((char)(value >> 16));
    ret.append((char)(value >> 8));
    ret.append((char)value);

    return ret;
}

QString QJDWPSocket::decodeString(const QByteArray &data, int offset)
{
    int l_Size = decodeInt(data, offset + 4);

    if (l_Size <= 0)
    {
        return QString();
    }

    return QString::fromUtf8(data.mid(offset + 4, l_Size));
}

QByteArray QJDWPSocket::encodeString(const QString &value)
{
    QByteArray l_Temp = value.toUtf8();

    return encodeInt(l_Temp.length()) + l_Temp;
}

QJDWPCommandVersion QJDWPSocket::decodeCommandVersion(const QByteArray &data)
{
    QJDWPCommandVersion ret;

    int l_DescriptionSize = decodeInt(data);
    int l_Version = decodeInt(data, l_DescriptionSize + 12);

    ret.m_Error = false;
    ret.m_Description = decodeString(data);
    ret.m_jdwpMajor = decodeInt(data, l_DescriptionSize + 4);
    ret.m_jdwpMinor = decodeInt(data, l_DescriptionSize + 8);
    ret.m_vmVersion = decodeString(data, l_DescriptionSize + 12);
    ret.m_vmName = decodeString(data, l_DescriptionSize + l_Version + 16);

    return ret;
}

QJDWPCommandIDSizes QJDWPSocket::decodeCommandIDSizes(const QByteArray &data)
{
    QJDWPCommandIDSizes ret;

    if (data.length() != 20)
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
    ret.m_fieldIDSize = decodeInt(data, 0);
    ret.m_methodIDSize = decodeInt(data, 4);
    ret.m_objectIDSize = decodeInt(data, 8);
    ret.m_referenceTypeIDSize = decodeInt(data, 12);
    ret.m_frameIDSize = decodeInt(data, 16);

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

