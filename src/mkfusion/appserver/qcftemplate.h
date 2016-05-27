#pragma once

#include "qcftemplateinfo.h"
#include "qcfworkerthread.h"
#include "qcfvariant.h"

#include <QDateTime>
#include <QLibrary>


class QCFTemplate
{
public:
    QCFTemplate();
    QCFTemplate(const QString &filePath, const QCFTemplateInfo &templateInfo = QCFTemplateInfo(),bool compiling = true);
    QCFTemplate(const QCFTemplate &other);
#ifdef Q_COMPILER_RVALUE_REFS
    inline QCFTemplate &operator=(QCFTemplate &&other)
    {
        qSwap(m_pathName, other.m_pathName);
        qSwap(m_library, other.m_library);
        qSwap(m_modified, other.m_modified);
        qSwap(m_fileSize, other.m_fileSize);
        qSwap(m_error, other.m_error);
        qSwap(m_usage, other.m_usage);
        qSwap(m_valid, other.m_valid);
        qSwap(m_compiling, other.m_compiling);
        qSwap(m_lastAccess, other.m_lastAccess);

        return *this;
    }
#endif
    QCFTemplate &operator=(const QCFTemplate &other);
    virtual ~QCFTemplate();
    int usageCount() const;
    uint modified() const;
    bool load();
    bool unload();
    bool isLoaded() const;
    int fileSize() const;
    bool strip();
    QString error() const;
    void setError(QString error);
    bool isValid() const;
    bool isCompiling() const;
    QDateTime lastAccess() const;
    void setCompiling(bool compiling);
    bool setLibrary(const QString &libName);
    QCFWorkerThread * createWorkerThread();
    QCFVariant createComponent(QCFWorkerThread &worker);

private:
    QString m_pathName;
    QLibrary *m_library;
    uint m_modified;
    volatile qint64 m_fileSize;
    QString m_error;
    volatile int m_usage;
    bool m_valid;
    bool m_compiling;
    QDateTime m_lastAccess;
};
