#ifndef QWDDXUTILS_H
#define QWDDXUTILS_H

#include "qwddx.h"

#include <QVariant>
#include <QDomNode>
#include <QVector>
#include <QString>

class QWDDXUtils
{
public:
    QWDDXUtils();
    QString serialize(QWDDX);
    QWDDX deserialize(QString);
    QString getLastError();
protected:
private:
    QString m_Error;
};

#endif // QWDDXUTILS_H
