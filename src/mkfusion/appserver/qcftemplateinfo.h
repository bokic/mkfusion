#ifndef QCFTEMPLATEINFO_H
#define QCFTEMPLATEINFO_H

#include <QString>


class QCFTemplateInfo
{
public:
    QCFTemplateInfo();
    QCFTemplateInfo(const QString &FilePath, int FileSize, int FileModified);
    QCFTemplateInfo(const QCFTemplateInfo &other);
#ifdef Q_COMPILER_RVALUE_REFS
    QCFTemplateInfo &operator=(QCFTemplateInfo &&other);
#endif
    QCFTemplateInfo &operator=(const QCFTemplateInfo &other);

    QString m_FilePath;
    int m_FileSize;
    int m_FileModified;
};

#endif // QCFTEMPLATEINFO_H
