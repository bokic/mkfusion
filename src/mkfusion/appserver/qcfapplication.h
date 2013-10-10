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
    QCFApplication(QObject *parent = 0);
    QCFApplication(const QCFApplication &other);
#ifdef Q_COMPILER_RVALUE_REFS
    QCFApplication &operator=(QCFApplication &&other);
#endif
    QCFApplication &operator=(const QCFApplication &other);

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
