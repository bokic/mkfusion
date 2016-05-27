#pragma once

#include "qcfgenerator.h"
#include "qcfparser.h"

#include <QString>
#include <QObject>


class QCFComponentGenerator : public QCFGenerator
{
public:
    QCFComponentGenerator();
    virtual void generateCpp(const QString &dstFilePath) override;

private:
    bool m_EnableComponentOutput;
    bool m_EnableFunctionOutput;
};
