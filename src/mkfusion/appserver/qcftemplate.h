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
    bool strip() const;
    QString error() const;

private:
    QString m_pathName;
    QLibrary *m_library;
    QDateTime m_modified;
    int m_fileSize;
    QString m_error;
    int m_usage;
    bool m_isVaild;
};

#endif // QCFTEMPLATE_H
