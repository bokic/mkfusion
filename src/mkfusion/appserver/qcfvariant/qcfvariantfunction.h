#ifndef QCFVARIANTFUNCTION_H
#define QCFVARIANTFUNCTION_H

#include "qcfvariantargument.h"
#include "qcfworkerthread.h"
#include "qcfvariant.h"

#include <QString>
#include <QHash>

#include <functional>


#define QCFVariantFunctor std::function<QCFVariant (QCFVariant &, QCFWorkerThread &, QCFVariant &)>

class QCFVariantFunction
{
public:
    QCFVariantFunction();
    QCFVariantFunction(const QCFVariantFunction &other);
    QCFVariantFunction(
        const QString &name,
        const QString &access,
        const QString &desc,
        const QString &dispName,
        const QString &hint,
        const QString &output,
        const QString &returnFormat,
        const QString &returnType,
        const QString &roles,
        const QString &secureJSON,
        const QString &verifyClients,
        const QCFVariantArgumentList &args,
        QCFVariantFunctor function
    );
#ifdef Q_COMPILER_RVALUE_REFS
    inline QCFVariantFunction &operator=(QCFVariantFunction &&other)
    {
        qSwap(m_Name, other.m_Name);
        qSwap(m_Access, other.m_Access);
        qSwap(m_Description, other.m_Description);
        qSwap(m_DisplayName, other.m_DisplayName);
        qSwap(m_Hint, other.m_Hint);
        qSwap(m_Output, other.m_Output);
        qSwap(m_ReturnFormat, other.m_ReturnFormat);
        qSwap(m_ReturnType, other.m_ReturnType);
        qSwap(m_Roles, other.m_Roles);
        qSwap(m_SecureJSON, other.m_SecureJSON);
        qSwap(m_VerifyClients, other.m_VerifyClients);
        qSwap(m_Arguments, other.m_Arguments);
        qSwap(m_Functor, other.m_Functor);

        return *this;
    }
#endif
    QCFVariantFunction &operator=(const QCFVariantFunction &other);

    QString m_Name;
    QString m_Access;
    QString m_Description;
    QString m_DisplayName;
    QString m_Hint;
    QString m_Output;
    QString m_ReturnFormat;
    QString m_ReturnType;
    QString m_Roles;
    QString m_SecureJSON;
    QString m_VerifyClients;
    QCFVariantArgumentList m_Arguments;
    QCFVariantFunctor m_Functor;
};

#endif // QCFVARIANTFUNCTION_H
