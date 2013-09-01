#ifndef QCFAPPLICATION_H
#define QCFAPPLICATION_H

#include <QReadWriteLock>
#include <QString>
#include <QObject>

#include "qwddx.h"

class QCFApplication : public QObject
{
    Q_OBJECT
public:
    explicit QCFApplication(QObject *parent = 0);
    ~QCFApplication();

    double ApplicationTimeout;
    bool ClientManagement;
    QString ClientStorage;
    QString LoginStorage;
    QString ScriptProtect;
    bool SessionManagement;
    double SessionTimeout;
    bool SetClientCookies;
    bool SetDomainCookies;

    QReadWriteLock lock;
    QWDDX data;
};

#endif // QCFAPPLICATION_H
