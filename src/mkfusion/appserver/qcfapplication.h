#ifndef QCFAPPLICATION_H
#define QCFAPPLICATION_H

//#include "qwddx.h"

#include <QDateTime>
#include <QString>
#include <QMutex>
#include <QHash>

class QCFApplication
{
    QString m_name;
    QString m_path;
    QString m_applicationTemplate;
    bool m_callOnApplicationEnd;
    //QWDDX m_data;
    QHash<QString, QMutex> m_mutexHash;
    QDateTime m_timeout;
    QMutex m_mutex;
};

#endif // QCFAPPLICATION_H
