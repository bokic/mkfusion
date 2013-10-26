#ifndef QCFTEMPLATE_H
#define QCFTEMPLATE_H

#include <QDateTime>
#include <QLibrary>


class QCFTemplate
{
public:
    QCFTemplate(const QString &filePath = "");
    virtual ~QCFTemplate();
    int usageCount() const;
    QDateTime modified() const;
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

private:
    QString m_pathName;
    QLibrary *m_library;
    QDateTime m_modified;
    volatile int m_fileSize;
    QString m_error;
    volatile int m_usage;
    volatile bool m_valid;
    volatile bool m_compiling;
};

#endif // QCFTEMPLATE_H
