#pragma once

#include <QTcpSocket>
#include <QByteArray>
#include <QTimerEvent>

class QJDWPCommandVersion
{
public:
    bool m_Error;
    QString m_Description;
    qint32 m_jdwpMajor;
    qint32 m_jdwpMinor;
    QString m_vmVersion;
    QString m_vmName;
};

class QJDWPCommandIDSizes
{
public:
    bool m_Error;
    qint32 m_fieldIDSize;
    qint32 m_methodIDSize;
    qint32 m_objectIDSize;
    qint32 m_referenceTypeIDSize;
    qint32 m_frameIDSize;
};

class QJDWPSocket : public QObject
{
    Q_OBJECT
public:
    QJDWPSocket();
    virtual ~QJDWPSocket();
    void connectToHost(const QString&, quint16);
    quint32 sendCommand(quint8, quint8, const QByteArray&);
    virtual void timerEvent(QTimerEvent*);

    static int decodeInt(QByteArray, int = 0);
    static qint64 decodeInt(QByteArray, int, int);
    static QByteArray encodeInt(int);
    static QString decodeString(QByteArray, int = 0);
    static QByteArray encodeString(QString);
    static QJDWPCommandVersion decodeCommandVersion(QByteArray);
    static QJDWPCommandIDSizes decodeCommandIDSizes(QByteArray);
    qint32 getFieldIDSize();
    qint32 getMethodIDSize();
    qint32 getObjectIDSize();
    qint32 getReferenceTypeIDSize();
    qint32 getFrameIDSize();
private:
    QByteArray m_reciveBuf;
    QTcpSocket m_Socket;
    QJDWPCommandIDSizes m_IDSizes;
    int m_InitTimer;
    bool m_Initialized;
    quint32 m_CommandCounter;
private slots:
    void on_m_Socket_connected();
    void on_m_Socket_readyRead();
signals:
    void ready();
    void gotPacket(quint32, quint8, quint16, QByteArray);
};
