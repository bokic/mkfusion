#include "qcflog.h"

#include <QCoreApplication>
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

    QTextStream out(&file);

    QString timeStamp = QDateTime::currentDateTime().toString("ddd MMMM d yy hh:mm:ss.zzz");
    QString type;
    QString processID = QString::number(QCoreApplication::applicationPid(), 16);
    QString threadID = QString::number((unsigned long)QThread::currentThreadId(), 16);

    if (level & QCFLOG_CRITICAL)
    {
        type = QObject::tr("CRITICAL");
    }
    else if (level & QCFLOG_ERROR)
    {
        type = QObject::tr("ERROR");
    }
    else if (level & QCFLOG_WARNING)
    {
        type = QObject::tr("WARNING");
    }
    else if (level & QCFLOG_INFO)
    {
        type = QObject::tr("INFO");
    }
    else if (level & QCFLOG_DEBUG)
    {
        type = QObject::tr("DEBUG");
    }
    else if (level & QCFLOG_PERF)
    {
        type = QObject::tr("PERFORMANCE");
    }
    else
    {
        type = QObject::tr("UNKNOWN(%1)").arg(QString::number(level, 16));
    }

    out << timeStamp << '\t' << processID << '\t' << threadID << '\t' << type << '\t' << text; Qt::endl(out);

    file.close();
}

int QCFLog::level()
{
    return m_level;
}
