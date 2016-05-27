#pragma once

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
    inline QCFApplication &operator=(QCFApplication &&other)
    {
        qSwap(m_name, other.m_name);
        qSwap(m_path, other.m_path);
        qSwap(m_applicationTemplate, other.m_applicationTemplate);
        qSwap(m_sessionManagement, other.m_sessionManagement);
        qSwap(m_setClientCookies, other.m_setClientCookies);
        qSwap(m_callOnApplicationEnd, other.m_callOnApplicationEnd);
        qSwap(m_data, other.m_data);
        //qSwap(m_mutexHash, other.m_mutexHash);
        qSwap(m_timeout, other.m_timeout);
        //qSwap(m_mutex, other.m_mutex);

        return *this;
    }
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
