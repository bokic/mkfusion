#ifndef QCFCOMPONENTGENERATOR_H
#define QCFCOMPONENTGENERATOR_H

#include "qcfgenerator.h"
#include "qcfparser.h"

#include <QString>
#include <QObject>


class QCFComponentGenerator : public QCFGenerator
{
public:
    QCFComponentGenerator(QObject *parent = 0);
    virtual void generateCpp(const QString &dstFilePath) override;

private:
    bool m_EnableComponentOutput;
    bool m_EnableFunctionOutput;
};

#endif // QCFCOMPONENTGENERATOR_H
