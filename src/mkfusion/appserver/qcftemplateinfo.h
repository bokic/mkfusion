#pragma once

#include <QString>


class QCFTemplateInfo
{
public:
    QCFTemplateInfo();
    QCFTemplateInfo(const QString &FilePath, int FileSize, int FileModified);
    QCFTemplateInfo(const QCFTemplateInfo &other);
#ifdef Q_COMPILER_RVALUE_REFS
    inline QCFTemplateInfo &operator=(QCFTemplateInfo &&other)
    {
        qSwap(m_FilePath, other.m_FilePath);
        qSwap(m_FileSize, other.m_FileSize);
        qSwap(m_FileModified, other.m_FileModified);

        return *this;
    }
#endif
    QCFTemplateInfo &operator=(const QCFTemplateInfo &other);

    QString m_FilePath;
    qint64 m_FileSize;
    qint64 m_FileModified;
};
