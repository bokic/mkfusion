#pragma once

#include "qwddx.h"

#include <QVariant>
#include <QDomNode>
#include <QVector>
#include <QString>

class QWDDXUtils
{
public:
    QString serialize(const QWDDX &node);
    QWDDX deserialize(const QString &txt);
    QString getLastError();
protected:
private:
    QString m_Error;
};
