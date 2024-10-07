#include "qcftemplate.h"
#include "qcfvariantcomponent.h"
#include "qcftemplateinfo.h"
#include "qcflog.h"

#include <QFileInfo>
#include <QProcess>


QCFTemplate::QCFTemplate()
    : m_library(new QLibrary())
    , m_modified(0)
    , m_fileSize(0)
    , m_usage(0)
    , m_valid(false)
    , m_compiling(false)
    , m_lastAccess(QDateTime::currentDateTime())
{
}

QCFTemplate::QCFTemplate(const QString &filePath, const QCFTemplateInfo &templateInfo, bool compiling)
    : m_pathName(filePath)
    , m_library(new QLibrary(filePath))
    , m_modified(templateInfo.m_FileModified)
    , m_fileSize(templateInfo.m_FileSize)
    , m_usage(0)
    , m_valid(true)
    , m_compiling(compiling)
    , m_lastAccess(QDateTime::currentDateTime())
{
}

QCFTemplate::QCFTemplate(const QCFTemplate &other)
{
    m_pathName = other.m_pathName;
    m_library = new QLibrary(other.m_library->fileName());
    m_modified = other.m_modified;
    m_fileSize = other.m_fileSize;
    m_error = other.m_error;
    m_usage = other.m_usage;
    m_valid = other.m_valid;
    m_compiling = other.m_compiling;
    m_lastAccess = other.m_lastAccess;
}

QCFTemplate &QCFTemplate::operator=(const QCFTemplate &other)
{
    if (&other != this)
    {
        m_pathName = other.m_pathName;

        if (m_library) delete m_library;
        m_library = new QLibrary(other.m_library->fileName());

        m_modified = other.m_modified;
        m_fileSize = other.m_fileSize;
        m_error = other.m_error;
        m_usage = other.m_usage;
        m_valid = other.m_valid;
        m_compiling = other.m_compiling;
        m_lastAccess = other.m_lastAccess;
    }

    return *this;
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

qint64 QCFTemplate::modified() const
{
    return m_modified;
}

bool QCFTemplate::load()
{
    if (!m_valid)
    {
        return false;
    }

    if (m_usage == 0)
    {
        bool loaded = m_library->load();

        if (!loaded)
        {
            m_error = QString("Error loading library: %1").arg(m_library->errorString());

            return false;
        }
    }

    m_usage++;

    m_lastAccess = QDateTime::currentDateTime();

    return true;
}

bool QCFTemplate::unload()
{
    m_usage--;

    if (m_usage < 0)
    {
        return false;
    }

    m_lastAccess = QDateTime::currentDateTime();

    return true;
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

QDateTime QCFTemplate::lastAccess() const
{
    return m_lastAccess;
}

void QCFTemplate::setCompiling(bool compiling)
{
    m_compiling = compiling;
}

bool QCFTemplate::setLibrary(const QString &libName)
{
    if (m_library->isLoaded())
    {
        return false;
    }

    m_library->setFileName(libName);

    m_valid = true; // Assumption that is valid

    return true;
}

QCFWorkerThread * QCFTemplate::createWorkerThread()
{
    if ((m_usage <= 0)||(!m_valid))
    {
        m_error = "Template is invalid.";

        return nullptr;
    }

    typedef QCFWorkerThread * (*createTemplateDef)();

    createTemplateDef createTemplateFunct = (createTemplateDef) m_library->resolve("createTemplate");

    if (createTemplateFunct == nullptr)
    {
        m_valid = false;

        m_error = "Could not resolve createTemplate function.";

        return nullptr;
    }

    return createTemplateFunct();
}

QCFVariant QCFTemplate::createComponent(QCFWorkerThread &worker)
{
    QCFVariantComponent component;

    if ((m_usage <= 0)||(!m_valid))
    {
        m_error = "Template is invalid.";

        return QCFVariant(QCFVariant::Error);
    }

    typedef QCFVariantComponent (*createComponentDef)(QCFWorkerThread &);

    createComponentDef createComponentFunct = (createComponentDef) m_library->resolve("createComponent");

    if (createComponentFunct == nullptr)
    {
        m_valid = false;

        m_error = "Could not resolve createComponent function.";

        return QCFVariant(QCFVariant::Error);
    }

    component = createComponentFunct(worker);

    return QCFVariant(component);
}
