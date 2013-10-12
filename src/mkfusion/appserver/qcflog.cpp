#include "qcflog.h"

#include <QDateTime>
#include <QThread>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QDir>


QString QCFLog::m_logPath;
int QCFLog::m_level = QCFLOG_CRITICAL | QCFLOG_ERROR | QCFLOG_WARNING | QCFLOG_INFO;


void QCFLog::init(const QString &log_path, int level)
{
    m_logPath = log_path;
    m_level = level;
}

void QCFLog::write(const QString &filename, int level, const QString &text)
{
    QFile file;
    if (m_logPath.isEmpty())
    {
        file.setFileName(filename);
    }
    else
    {
        file.setFileName(m_logPath + QDir::separator() + filename);
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << "Can't open log:" << file.fileName() << ".";

        return;
    }

    QString timeStamp = QDateTime::currentDateTime().toString("ddd MMMM d yy hh:mm:ss.zzz");
    QString type;
    QString threadID = QString::number((unsigned long)QThread::currentThreadId(), 16);

    switch(level)
    {
    case QCFLOG_CRITICAL:
        type = QObject::tr("CRITICAL");
        break;
    case QCFLOG_ERROR:
        type = QObject::tr("ERROR");
        break;
    case QCFLOG_WARNING:
        type = QObject::tr("WARNING");
        break;
    case QCFLOG_INFO:
        type = QObject::tr("INFO");
        break;
    case QCFLOG_DEBUG:
        type = QObject::tr("DEBUG");
        break;
    case QCFLOG_PERF:
        type = QObject::tr("PERFORMANCE");
        break;
    default:
        type = QObject::tr("UNKNOWN(%1)").arg(QString::number(level, 16));
        break;
    }

#ifdef Q_OS_WIN
    file.write(QByteArray(timeStamp.toUtf8()).append('\t').append(threadID).append('\t').append(type).append('\t').append(text.toUtf8()).append('\r').append('\n'));
#else
    file.write(QByteArray(timeStamp.toUtf8()).append('\t').append(threadID).append('\t').append(type).append('\t').append(text.toUtf8()).append('\n'));
#endif

    file.close();
}

int QCFLog::level()
{
    return m_level;
}
