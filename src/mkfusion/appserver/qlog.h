#ifndef QLOG_H
#define QLOG_H

#include <QString>
#include <QMutex>


class QLog
{
public:
    static void init(const QString &log_path, int level);
    static void write(int level, const QString &text);

private:
    static QString m_logPath;
    static QMutex m_lock;
    static int m_level;
};

#endif // QLOG_H
