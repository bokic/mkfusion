#include "qcftemplate.h"


QCFTemplate::QCFTemplate(const QString &filePath)
    : m_fileSize(0)
    , m_usage(0)
    , m_isVaild(false)
{
    m_library = new QLibrary(filePath);


    if (m_library->load())
    {
        //m_library->

        m_isVaild = true;
    }
}

QCFTemplate::~QCFTemplate()
{
    if (m_library->isLoaded())
    {


        m_library->unload();
    }

    delete m_library;
    m_library = nullptr;

}

int QCFTemplate::usageCount() const
{
    return m_usage;
}

QDateTime QCFTemplate::modified() const
{
    return m_modified;
}

bool QCFTemplate::load()
{
    return false;
}

bool QCFTemplate::unload()
{
    return false;
}

bool QCFTemplate::isLoaded() const
{
    return m_library->isLoaded();
}

int QCFTemplate::fileSize() const
{
    return m_fileSize;
}

bool QCFTemplate::strip() const
{
    bool reload = false;

    if ((m_usage == 0)&&(m_library->isLoaded()))
    {
        m_library->unload();
        reload = true;
    }

    if (m_library->isLoaded())
    {
        return false;
    }

    // TODO: do strip process here.


    if (reload)
    {
        m_library->load();
    }

    return true;
}

QString QCFTemplate::error() const
{
    m_error;
}
