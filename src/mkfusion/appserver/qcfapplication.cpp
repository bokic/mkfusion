#include "qcfapplication.h"

QCFApplication::QCFApplication()
    : m_sessionManagement(false)
    , m_setClientCookies(false)
    , m_callOnApplicationEnd(false)
{
}

QCFApplication::QCFApplication(const QCFApplication &other)
    : m_name(other.m_name)
    , m_path(other.m_path)
    , m_applicationTemplate(other.m_applicationTemplate)
    , m_sessionManagement(other.m_sessionManagement)
    , m_setClientCookies(other.m_setClientCookies)
    , m_callOnApplicationEnd(other.m_callOnApplicationEnd)
    , m_data(other.m_data)
    //, m_mutexHash(other.m_mutexHash)
    , m_timeout(other.m_timeout)
    //, m_mutex(other.m_mutex)
{
}

QCFApplication &QCFApplication::operator=(const QCFApplication &other)
{
    m_name = other.m_name;
    m_path = other.m_path;
    m_applicationTemplate = other.m_applicationTemplate;
    m_sessionManagement = other.m_sessionManagement;
    m_setClientCookies = other.m_setClientCookies;
    m_callOnApplicationEnd = other.m_callOnApplicationEnd;
    m_data = other.m_data;
    //m_mutexHash = other.m_mutexHash;
    m_timeout = other.m_timeout;
    //m_mutex = other.m_mutex

    return *this;
}
