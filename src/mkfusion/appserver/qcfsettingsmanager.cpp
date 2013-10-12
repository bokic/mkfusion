#include "qcfsettingsmanager.h"
#include "qcfsettings.h"
#include "qcflog.h"

#include <QSqlDatabase>
#include <QSettings>
#include <QString>
#include <QDebug>
#include <QDir>


QCFSettingsManager::QCFSettingsManager()
{
    loadFromFile();
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

        if (connectionDriver == "QSQLITE")
        {
        }
        else if (connectionDriver == "QODBC")
        {
        }
        else if (connectionDriver == "QMYSQL")
        {
            for(const QString item : connectionString.split(';'))
            {
                QStringList key_value = item.split(':');

                if (key_value.count() != 2)
                {
                    continue;
                }

                QString key = key_value.first();
                QString value = QByteArray::fromBase64(key_value.last().toLatin1());

                if (key.compare("hostname", Qt::CaseInsensitive) == 0)
                {
                    //db.setHostName(value);
                }
                else if (key.compare("databasename", Qt::CaseInsensitive) == 0)
                {
                    //db.setDatabaseName(value);
                }
                else if (key.compare("username", Qt::CaseInsensitive) == 0)
                {
                    //db.setUserName(value);
                }
                else if (key.compare("password", Qt::CaseInsensitive) == 0)
                {
                    //db.setPassword(value);
                }
                else if (key.compare("port", Qt::CaseInsensitive) == 0)
                {
                    //db.setPort(value.toInt());
                }
                else
                {
                    QCFLOG_QSTRING(QCFLOG_DAEMON, QCFLOG_ERROR, QString("Unsupported QMYSQL connection parameter(" + key + ")"));
                }
            }
        }
        else
        {
            QCFLOG_QSTRING(QCFLOG_DAEMON, QCFLOG_ERROR, QString("Unsupported database connection(" + connectionDriver + ")"));
        }
    }
}

void QCFSettingsManager::saveToFile() const
{

}
