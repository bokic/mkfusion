#ifndef QCFVARIANTFUNCTION_H
#define QCFVARIANTFUNCTION_H

#include "qcfvariantargument.h"

#include <QString>
#include <QHash>


class QCFVariantFunction
{
public:
    QCFVariantFunction();
    QCFVariantFunction(const QCFVariantFunction &other);
#ifdef Q_COMPILER_RVALUE_REFS
    QCFVariantFunction &operator=(QCFVariantFunction &&other);
#endif
    QCFVariantFunction &operator=(const QCFVariantFunction &other);

    QHash<QString, QCFVariantArgument> m_Arguments;
    QString m_ReturnType;
    QString m_Roles;
    QString m_Access;
    QString m_Output;
    QString m_DisplayName;
    QString m_Hint;
    QString m_Description;
};

#endif // QCFVARIANTFUNCTION_H
