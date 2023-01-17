#pragma once

#include <QTcpSocket>
#include <QByteArray>
#include <QTimerEvent>


class QJDWPCommandVersion
{
public:
    bool m_Error = false;
    QString m_Description;
    qint32 m_jdwpMajor = 0;
    qint32 m_jdwpMinor = 0;
    QString m_vmVersion;
    QString m_vmName;
};

class QJDWPCommandIDSizes
{
public:
    bool m_Error = false;
    qint32 m_fieldIDSize = 0;
    qint32 m_methodIDSize = 0;
    qint32 m_objectIDSize = 0;
    qint32 m_referenceTypeIDSize = 0;
    qint32 m_frameIDSize = 0;
};

class QJDWPSocket : public QObject
{
    Q_OBJECT
public:
    QJDWPSocket();
    virtual ~QJDWPSocket();
    void connectToHost(const QString &host, quint16 port);
    quint32 sendCommand(quint8 commandSet, quint8 command, const QByteArray &data);
    virtual void timerEvent(QTimerEvent *event);

    static int decodeInt(const QByteArray &data, int offset = 0);
    static qint64 decodeInt(const QByteArray &data, int offset, int size);
    static QByteArray encodeInt(int value);
    static QString decodeString(const QByteArray &data, int offset = 0);
    static QByteArray encodeString(const QString &value);
    static QJDWPCommandVersion decodeCommandVersion(const QByteArray &data);
    static QJDWPCommandIDSizes decodeCommandIDSizes(const QByteArray &data);
    qint32 getFieldIDSize();
    qint32 getMethodIDSize();
    qint32 getObjectIDSize();
    qint32 getReferenceTypeIDSize();
    qint32 getFrameIDSize();

private:
    QByteArray m_reciveBuf;
    QTcpSocket m_Socket;
    QJDWPCommandIDSizes m_IDSizes;
    int m_InitTimer = 0;
    bool m_Initialized = 0;
    quint32 m_CommandCounter = 0;

private slots:
    void on_m_Socket_connected();
    void on_m_Socket_readyRead();

signals:
    void ready();
    void gotPacket(quint32 id, quint8 flags, quint16 errorCode, QByteArray data);
};
