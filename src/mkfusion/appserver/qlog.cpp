#include "qlog.h"

#include <QMutexLocker>
#include <QDateTime>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QDir>


QString QLog::m_logPath;
QMutex QLog::m_lock;
int QLog::m_level = 0;


void QLog::init(const QString &log_path, int level)
{
    m_logPath = log_path;
    m_level = level;

    if (m_logPath.isEmpty())
    {
        qDebug() << "Warning: QLog::m_logPath is empty.";
    }
}

void QLog::write(int level, const QString &text)
{
    if (level >= m_level)
    {
        QMutexLocker locker(&m_lock);

        if (m_logPath.isEmpty())
        {
            qDebug() << "Warning: QLog::m_logPath is empty.";
            return;
        }

        QFile file(m_logPath + QDir::separator() + "mkfusion.log");

        if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
        {
            qDebug() << "Can't open log file.";
            return;
        }

        QString timeStamp = QDateTime::currentDateTime().toString();
        QString type;

        switch(level)
        {
        case 0:
            type = QObject::tr("Information");
            break;
        case 1:
            type = QObject::tr("Warning");
            break;
        case 2:
            type = QObject::tr("Error");
            break;
        case 3:
            type = QObject::tr("Critical");
            break;
        default:
            type = QObject::tr("Unknown(%1)").arg(level);
            break;
        }

#ifdef Q_OS_WIN
        file.write(QByteArray(timeStamp.toUtf8()).append('\t').append(type).append('\t').append(text.toUtf8()).append('\r').append('\n'));
#else
        file.write(QByteArray(timeStamp.toUtf8()).append('\t').append(type).append('\t').append(text.toUtf8()).append('\n'));
#endif

        file.close();
    }
}
