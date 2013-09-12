#include "qcfapplication.h"

QCFApplication::QCFApplication(QObject *parent)
    : QObject(parent)
    , data(QWDDX::Struct)
{
}

QCFApplication::QCFApplication(const QCFApplication &other)
    : QObject(other.parent())
    , ApplicationTimeout(other.ApplicationTimeout)
    , ClientManagement(other.ClientManagement)
    , ClientStorage(other.ClientStorage)
    , LoginStorage(other.LoginStorage)
    , ScriptProtect(other.ScriptProtect)
    , SessionManagement(other.SessionManagement)
    , SessionTimeout(other.SessionTimeout)
    , SetClientCookies(other.SetClientCookies)
    , SetDomainCookies(other.SetDomainCookies)
    //, lock(other.lock)
    , data(other.data)
{
}

#ifdef Q_COMPILER_RVALUE_REFS
QCFApplication &QCFApplication::operator=(QCFApplication &&other)
{
    qSwap(ApplicationTimeout, other.ApplicationTimeout);
    qSwap(ClientManagement, other.ClientManagement);
    qSwap(ClientStorage, other.ClientStorage);
    qSwap(LoginStorage, other.LoginStorage);
    qSwap(ScriptProtect, other.ScriptProtect);
    qSwap(SessionManagement, other.SessionManagement);
    qSwap(SessionTimeout, other.SessionTimeout);
    qSwap(SetClientCookies, other.SetClientCookies);
    qSwap(SetDomainCookies, other.SetDomainCookies);
    //qSwap(lock, other.lock);
    qSwap(data, other.data);

    return *this;
}
#endif

QCFApplication &QCFApplication::operator=(const QCFApplication &other)
{
    ApplicationTimeout = other.ApplicationTimeout;
    ClientManagement = other.ClientManagement;
    ClientStorage = other.ClientStorage;
    LoginStorage = other.LoginStorage;
    ScriptProtect = other.ScriptProtect;
    SessionManagement = other.SessionManagement;
    SessionTimeout = other.SessionTimeout;
    SetClientCookies = other.SetClientCookies;
    SetDomainCookies = other.SetDomainCookies;
    //lock = other.lock;
    data = other.data;

    return *this;
}


QCFApplication::~QCFApplication()
{
}
