#ifndef QCFLOG_H
#define QCFLOG_H

#include <QString>


#define QCFLOG(_file, _level, _text) if(_level & QCFLog::level()) QCFLog::write(_file, _level, QStringLiteral(_text));
#define QCFLOG_QSTRING(_file, _level, _text) if(_level & QCFLog::level()) QCFLog::write(_file, _level, _text);

#define QCFLOG_NO_LOG    (0x00)
#define QCFLOG_CRITICAL  (0x01)
#define QCFLOG_ERROR     (0x02)
#define QCFLOG_WARNING   (0x04)
#define QCFLOG_INFO      (0x08)
#define QCFLOG_DEBUG     (0x10)
#define QCFLOG_PERF      (0x20)

#define QCFLOG_INFO_PERF (QCFLOG_INFO | QCFLOG_PERF)

#define QCFLOG_DAEMON QStringLiteral("daemon.log")
#define CFLOG_WORKER QStringLiteral("worker.log")
#define QQCFLOG_SESSION QStringLiteral("session.log")
#define QCFLOG_APPLICATION QStringLiteral("application.log")
#define QCFLOG_SCHEDULER (QStringLiteral("scheduler.log"))

class QCFLog
{
public:

    static void init(const QString &log_path, int level);
    static void write(const QString &filename, int level, const QString &text);
    static int level();

private:
    static QString m_logPath;
    static int m_level;
};

#endif // QCFLOG_H
