#include "qcftemplate.h"
#include "qcftemplateinfo.h"
#include "qcflog.h"

#include <QFileInfo>
#include <QProcess>


QCFTemplate::QCFTemplate(const QString &filePath, const QCFTemplateInfo &templateInfo, bool compiling)
    : m_pathName(filePath)
    , m_library(new QLibrary(filePath))
    , m_modified(templateInfo.m_FileModified)
    , m_fileSize(templateInfo.m_FileSize)
    , m_usage(0)
    , m_valid(true)
    , m_compiling(compiling)
{
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

uint QCFTemplate::modified() const
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

    QProcess strip_process;

#ifdef Q_OS_WIN
// TODO: do strip process here.
#warning Implement QCFTemplate::strip() for Windows
#elif defined Q_OS_LINUX
    strip_process.start("strip", QStringList() << m_pathName);
#else
#error Windows and Linux OSs are currently supported.
#endif

    if (!strip_process.waitForFinished(10000))
    {
        QCFLOG(QCFLOG_DAEMON, QCFLOG_CRITICAL, "Strip process did not finished in 10 seconds.");
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

void QCFTemplate::setError(QString error)
{
    m_error = error;
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

QCFWorkerThread * QCFTemplate::getTemplateObject()
{
    if ((m_usage <= 0)||(!m_valid))
    {
        return nullptr;
    }

    typedef QCFWorkerThread * (*createTemplateDef)();

    createTemplateDef getTemplateInfo = (createTemplateDef) m_library->resolve("createTemplate");

    if (getTemplateInfo == nullptr)
    {
        m_valid = false;

        m_error = "Could not resolve getTemplateInfo function.";

        return nullptr;
    }

    return getTemplateInfo();
}
