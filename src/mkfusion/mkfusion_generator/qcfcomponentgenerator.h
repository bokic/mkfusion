#ifndef QCFCOMPONENTGENERATOR_H
#define QCFCOMPONENTGENERATOR_H

#include "qcfgenerator.h"
#include "qcfparser.h"
#include <QString>


class QCFComponentGenerator : public QCFGenerator
{
public:
    QCFComponentGenerator();
    virtual void generateCpp(const QString &dstFilePath) override;

private:
    bool m_EnableComponentOutput;
    bool m_EnableFunctionOutput;
};

#endif // QCFCOMPONENTGENERATOR_H
