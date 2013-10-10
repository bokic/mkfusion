#ifndef QCFCOMPILER_H
#define QCFCOMPILER_H

#include <QString>


class QCFCompiler
{
public:
    QCFCompiler(const QString &p_MKFusionPath);
    QString compile(const QString &p_Target);

private:
    QString m_MKFusionPath;
};

#endif // QCFCOMPILER_H
