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

};

#endif // QCFCOMPONENTGENERATOR_H
