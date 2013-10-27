#ifndef QCFTEMPLATE_H
#define QCFTEMPLATE_H

#include "qcftemplateinfo.h"
#include "qcfworkerthread.h"

#include <QDateTime>
#include <QLibrary>


class QCFTemplate
{
public:
    QCFTemplate(const QString &filePath = "", const QCFTemplateInfo &templateInfo = QCFTemplateInfo(),bool compiling = true);
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
    void setCompiling(bool compiling);
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
};

#endif // QCFTEMPLATE_H
