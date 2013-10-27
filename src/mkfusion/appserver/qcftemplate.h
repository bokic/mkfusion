#ifndef QCFTEMPLATE_H
#define QCFTEMPLATE_H

#include "qcftemplateinfo.h"
#include "qcfworkerthread.h"

#include <QDateTime>
#include <QLibrary>


class QCFTemplate
{
public:
    QCFTemplate();
    QCFTemplate(const QString &filePath, const QCFTemplateInfo &templateInfo = QCFTemplateInfo(),bool compiling = true);
    QCFTemplate(const QCFTemplate &other);
#ifdef Q_COMPILER_RVALUE_REFS
    QCFTemplate &operator=(QCFTemplate &&other);
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
    QCFWorkerThread * getTemplateObject();

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

#endif // QCFTEMPLATE_H
