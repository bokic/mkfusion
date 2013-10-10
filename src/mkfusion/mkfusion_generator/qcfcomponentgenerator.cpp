#include "qcfcomponentgenerator.h"
#include "qcfgeneratorexception.h"

#include <QString>


QCFComponentGenerator::QCFComponentGenerator()
{
}

void QCFComponentGenerator::generateCpp(const QString &dstFilePath)
{
    Q_UNUSED(dstFilePath);

    throw QCFGeneratorException("unimplemented.", 0);
}
