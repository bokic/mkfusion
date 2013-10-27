#ifndef QCFCOMPILER_H
#define QCFCOMPILER_H

#include <QString>


class QCFCompiler
{
public:
    QCFCompiler();
    void setTargetPath(const QString &target);
    QString compile(const QString &cppFile, QString &libFile);
    QString generateCpp(const QString &cfmlFilePath, QString &cppFilePath);

private:
    QString m_TargetPath;
    bool m_Strip;
};

#endif // QCFCOMPILER_H
