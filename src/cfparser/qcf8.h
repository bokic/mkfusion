#ifndef QCF8_H
#define QCF8_H

#include "qcftag.h"
#include "qcffunction.h"

#include <QObject>
#include <QString>
#include <QHash>

class QCF8 : public QObject
{
public:
    static QHash<QString, QCFTag> generateCFTags();
	static QHash<QString, QCFFunction> generateCFFunctions();
};

#endif // QCF8_H
