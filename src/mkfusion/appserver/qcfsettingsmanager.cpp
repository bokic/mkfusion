#include "qcfsettingsmanager.h"
#include "qcfdatabaseconnection.h"
#include "qcfsettings.h"
#include "qcfserver.h"
#include "qcflog.h"

#include <QSqlDatabase>
#include <QSettings>
#include <QString>
#include <QDebug>
#include <QList>
#include <QDir>


QCFSettingsManager::QCFSettingsManager()
{
}

QCFSettings QCFSettingsManager::readSettings() const
{
    return m_settings;
}

void QCFSettingsManager::writeSettings(const QCFSettings &settings)
{
}

void QCFSettingsManager::loadFromFile()
{
    QSettings iniFile("mkfusion.ini", QSettings::IniFormat);
    QList<QCFDatabaseConnection> db_connections;

    iniFile.beginGroup("Setup");

    m_settings.setCustomTagsPath(iniFile.value("CustomTagsDir", "../CustomTags").toString().trimmed());

    iniFile.beginGroup("Database");
    for(const QString &group : iniFile.childKeys())
    {
        int sep = group.lastIndexOf('_');

        if (sep < 1)
        {
            QCFLOG(QCFLOG_DAEMON, QCFLOG_ERROR, "Invalid database connection.");

            continue;
        }

        const QString &connectionName = group.left(sep).trimmed();
        const QString &connectionDriver = group.right(group.length() - sep - 1).trimmed();
        const QString &connectionString = iniFile.value(group).toString().trimmed();

        db_connections.append(QCFDatabaseConnection(connectionName, connectionDriver, connectionString));
    }

    m_settings.setDatabaseConnections(db_connections);
}

void QCFSettingsManager::saveToFile() const
{

}
