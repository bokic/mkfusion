#ifndef QCFCOMPILER_H
#define QCFCOMPILER_H

#include <QString>
#include <QHash>


class QCFCompiler
{
public:
    QCFCompiler();
    void setTargetPath(const QString &target);
    QString compile(const QString &cppFile, QString &libFile);
    QString generateCpp(const QString &cfmlFilePath, QString &cppFilePath);
    static void rebuildPrecompiledHeader(const QString &p_MKFusionPath);
    static QStringList commonCompileSwitches(const QString &p_MKFusionPath);
    static int buildPrecompiledHeader();
    static int deletePrecompiledHeader();
    static QHash<QString, QString> qmakeQuery();

private:
    QString m_TargetPath;
    bool m_Strip;
};

#endif // QCFCOMPILER_H
