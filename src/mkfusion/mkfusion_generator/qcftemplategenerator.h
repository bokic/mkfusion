#ifndef QCFTEMPLATEGENERATOR_H
#define QCFTEMPLATEGENERATOR_H

#include "qcfgenerator.h"
#include "qcfparser.h"

#include <QString>
#include <QObject>


class QCFTemplateGenerator : public QCFGenerator
{
public:
    QCFTemplateGenerator();
    virtual void generateCpp(const QString &dstFilePath) override;
};

#endif // QCFTEMPLATEGENERATOR_H
