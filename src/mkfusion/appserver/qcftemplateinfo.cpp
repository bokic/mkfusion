#include "qcftemplateinfo.h"

QCFTemplateInfo::QCFTemplateInfo()
    : m_FileSize(-1)
    , m_FileModified(-1)
{
}

QCFTemplateInfo::QCFTemplateInfo(const QString &FilePath, int FileSize, int FileModified)
    : m_FilePath(FilePath)
    , m_FileSize(FileSize)
    , m_FileModified(FileModified)
{
}

QCFTemplateInfo::QCFTemplateInfo(const QCFTemplateInfo &other)
    : m_FilePath(other.m_FilePath)
    , m_FileSize(other.m_FileSize)
    , m_FileModified(other.m_FileModified)
{
}

#ifdef Q_COMPILER_RVALUE_REFS
QCFTemplateInfo &QCFTemplateInfo::operator=(QCFTemplateInfo &&other)
{
    qSwap(m_FilePath, other.m_FilePath);
    qSwap(m_FileSize, other.m_FileSize);
    qSwap(m_FileModified, other.m_FileModified);

    return *this;
}
#endif

QCFTemplateInfo &QCFTemplateInfo::operator=(const QCFTemplateInfo &other)
{
    m_FilePath = other.m_FilePath;
    m_FileSize = other.m_FileSize;
    m_FileModified = other.m_FileModified;

    return *this;
}
