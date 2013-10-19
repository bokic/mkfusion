#include "qcftemplate.h"

#include <QProcess>


QCFTemplate::QCFTemplate(const QString &filePath)
    : m_fileSize(0)
    , m_usage(0)
    , m_valid(false)
    , m_compiling(true)
{
    m_library = new QLibrary(filePath);

    if (m_library->load())
    {
        //m_library->

        m_valid = true;
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

bool QCFTemplate::strip()
{
    if (m_usage > 0)
    {
        return false;
    }

    bool reload = false;

    if (m_library->isLoaded())
    {
        m_library->unload();
        reload = true;
    }

    // TODO: do strip process here.
    QProcess strip_process;

    strip_process.start("strip", QStringList() << m_pathName);

    if (!strip_process.waitForFinished(10000))
    {

    }

    if (reload)
    {
        m_library->load();
    }

    return true;
}

QString QCFTemplate::error() const
{
    return m_error;
}

bool QCFTemplate::isValid() const
{
    return m_valid;
}

bool QCFTemplate::isCompiling() const
{
    return m_compiling;
}

void QCFTemplate::setCompiling(bool compiling)
{
    m_compiling = compiling;
}
