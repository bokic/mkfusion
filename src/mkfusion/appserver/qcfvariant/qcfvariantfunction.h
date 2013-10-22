#ifndef QCFVariantFUNCTION_H
#define QCFVariantFUNCTION_H

#include "qcfvariantargument.h"

#include <QString>
#include <QHash>


class QCFVariantFunction
{
public:
    QCFVariantFunction();

    QHash<QString, QCFVariantArgument> m_Methods;

    QString m_ReturnType;
    QString m_Roles;
    QString m_Access;
    QString m_Output;
    QString m_DisplayName;
    QString m_Hint;
    QString m_Description;
};

#endif // QCFVariantFUNCTION_H
