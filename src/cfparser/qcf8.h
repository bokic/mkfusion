#pragma once

#include "qcftag.h"
#include "qcffunction.h"

#include <QObject>
#include <QString>
#include <QHash>

class QCF8
{
public:
    static QHash<QString, QCFTag> generateCFTags();
    static QHash<QString, QCFFunction> generateCFFunctions();

private:
    static QHash<QString, QCFTag> m_generateCFTags;
    static QHash<QString, QCFFunction> m_generateCFFunctions;
};
