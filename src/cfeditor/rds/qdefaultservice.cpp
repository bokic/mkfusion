#include "qdefaultservice.h"
#include <QByteArray>
#include <QVector>
#include <QString>
#include <QMap>

QByteArray QDefaultService::ExecuteRDSCommand(const QRDSServer &rdsserver, quint8 command, const QMap<QString, QString> &map)
{
    Q_UNUSED(map);

    QByteArray ret;

    switch (command)
    {
    case 0:
        return IdeDefault(rdsserver);
        break;
    }

    return ret;
}

QByteArray QDefaultService::IdeDefault(QRDSServer rdsserver)
{
    QVector<QString> vector;

    vector.append("Configurations");
    vector.append("7, 0, 0, 0");

    QByteArray ba = executeRDSCommandForByteArray("IDE_DEFAULT", rdsserver, vector);

    if (BreakByteArrayIntoVector(ba).size() >= 3)
        rdsserver.setAuthenticated(true);
    else
        rdsserver.setAuthenticated(false);

    return ba;
}
