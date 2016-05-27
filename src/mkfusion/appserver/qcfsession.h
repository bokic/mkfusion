#pragma once

#include "qcfvariant.h"

#include <QReadWriteLock>
#include <QDateTime>
#include <QString>
#include <QHash>

class QCFSession
{
    QCFSession() : m_callOnSessionEnd(false) {}
    QString m_name;
    QString m_application;
    bool m_callOnSessionEnd;
    QCFVariant m_data;
    QHash<QString, QReadWriteLock> m_lockHash;
    QDateTime m_timeout;
    QReadWriteLock m_lock;
};
