#include "qdebuggerservice.h"
#include <QByteArray>
#include <QVector>
#include <QString>
#include <QMap>

QByteArray QDebuggerService::ExecuteRDSCommand(QRDSServer &rdsserver, quint8 command, const QMap<QString, QString> &map)
{
    QByteArray ret;

    switch (command)
    {
    case 0:
        return GetServerInfo(rdsserver);
        break;
    case 1:
        return DoDebugStart(rdsserver, map);
        break;
    case 2:
        return DoDebugStop(rdsserver, map);
        break;
    case 3:
        return DoDebugRequest(rdsserver, map);
        break;
    case 4:
        return DoDebugEvents(rdsserver, map);
        break;
    }

    return ret;
}

QByteArray QDebuggerService::GetServerInfo(QRDSServer rdsserver)
{
    QVector<QString> vector;

    vector.append(QStringLiteral("DBG_GET_DEBUG_SERVER_INFO"));

    return executeRDSCommandForByteArray(QStringLiteral("DBGREQUEST"), rdsserver, vector);
}

QByteArray QDebuggerService::DoDebugStart(QRDSServer rdsserver, QMap<QString, QString> map)
{
    QVector<QString> vector;

    vector.append(QStringLiteral("DBG_START"));
    vector.append(map[QStringLiteral("WDDX")]);

    return executeRDSCommandForByteArray(QStringLiteral("DBGREQUEST"), rdsserver, vector);
}

QByteArray QDebuggerService::DoDebugStop(QRDSServer rdsserver, QMap<QString, QString> map)
{
    QVector<QString> vector;

    vector.append(QStringLiteral("DBG_STOP"));
    vector.append(map[QStringLiteral("SESSION")]);

    return executeRDSCommandForByteArray(QStringLiteral("DBGREQUEST"), rdsserver, vector);
}

QByteArray QDebuggerService::DoDebugRequest(QRDSServer rdsserver, QMap<QString, QString> map)
{
    QVector<QString> vector;

    vector.append(QStringLiteral("DBG_REQUEST"));
    vector.append(map[QStringLiteral("SESSION")]);
    vector.append(map[QStringLiteral("WDDX")]);

    return executeRDSCommandForByteArray(QStringLiteral("DBGREQUEST"), rdsserver, vector);
}

QByteArray QDebuggerService::DoDebugEvents(QRDSServer rdsserver, QMap<QString, QString> map)
{
    QVector<QString> vector;

    vector.append(QStringLiteral("DBG_EVENTS"));
    vector.append(map[QStringLiteral("SESSION")]);

    return executeRDSCommandForByteArray(QStringLiteral("DBGREQUEST"), rdsserver, vector);
}
