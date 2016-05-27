#pragma once

#include "qcfdatabaseconnection.h"

#include <QString>
#include <QList>


class QCFSettings
{
public:
    QCFSettings();
    bool setCustomTagsPath(const QString &value);
    QString customTagsPath();

    void setDatabaseConnections(const QList<QCFDatabaseConnection> &db_connections);
    QList<QCFDatabaseConnection> databaseConnections();


private:
    QString m_customTagsPath;
    QList<QCFDatabaseConnection> m_databaseConnections;
    int m_schedulerThreadIntervalMS;
};
