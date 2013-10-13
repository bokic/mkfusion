#include "qcfsettings.h"
#include "qcfserver.h"

#include <QString>


QCFSettings::QCFSettings()
    : m_customTagsPath()
    , m_schedulerThreadIntervalMS(5000)
{
}

bool QCFSettings::setCustomTagsPath(const QString &value)
{
    m_customTagsPath = value;

    return true;
}

QString QCFSettings::customTagsPath()
{
    return m_customTagsPath;
}

void QCFSettings::setDatabaseConnections(const QList<QCFDatabaseConnection> &db_connections)
{
    m_databaseConnections = db_connections;

    QCFServer::instance()->m_DatabasePool.setConnectionDefinition(m_databaseConnections);
}

QList<QCFDatabaseConnection> QCFSettings::databaseConnections()
{
    return m_databaseConnections;
}
