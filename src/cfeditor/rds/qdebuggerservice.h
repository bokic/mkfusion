#ifndef QDEBUGGERSERVICE_H
#define QDEBUGGERSERVICE_H

#include "qabstractrdsservice.h"
#include <QObject>
#include <QString>
#include <QVector>
#include <QList>
#include <QMap>

class QDebuggerService : public QAbstractRDSService
{
public:
    enum Command
    {
        getServerInfo,
        doDebugStart,
        doDebugStop,
        doDebugRequest,
        doDebugEvents
    };

    QDebuggerService() : QAbstractRDSService() {};
    virtual ~QDebuggerService() {};

    virtual QByteArray ExecuteRDSCommand(QRDSServer, quint8, QMap<QString, QString>);
protected:
private:
    QByteArray GetServerInfo(QRDSServer);
    QByteArray DoDebugStart(QRDSServer, QMap<QString, QString>);
    QByteArray DoDebugStop(QRDSServer, QMap<QString, QString>);
    QByteArray DoDebugRequest(QRDSServer, QMap<QString, QString>);
    QByteArray DoDebugEvents(QRDSServer, QMap<QString, QString>);
};

#endif // QDEBUGGERSERVICE_H
