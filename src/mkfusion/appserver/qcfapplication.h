#ifndef QCFAPPLICATION_H
#define QCFAPPLICATION_H

#include "qcfvariant.h"

#include <QDateTime>
#include <QString>
#include <QMutex>
#include <QHash>

class QCFApplication
{
public:
    QCFApplication();
    QCFApplication(const QCFApplication &other);
#ifdef Q_COMPILER_RVALUE_REFS
    QCFApplication &operator=(QCFApplication &&other);
#endif
    QCFApplication &operator=(const QCFApplication &other);

    QString m_name;
    QString m_path;
    QString m_applicationTemplate;
    bool m_sessionManagement;
    bool m_setClientCookies;
    bool m_callOnApplicationEnd;
    QCFVariant m_data;
    QHash<QString, QMutex> m_mutexHash;
    QDateTime m_timeout;
    QMutex m_mutex;
};

#endif // QCFAPPLICATION_H
