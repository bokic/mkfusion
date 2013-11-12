#ifndef QCFVARIANTFUNCTION_H
#define QCFVARIANTFUNCTION_H

#include "qcfvariantargument.h"
#include "qcfworkerthread.h"
#include "qcfvariant.h"

#include <QString>
#include <QHash>


#define QCFVariantFunctor std::function<QCFVariant (QCFVariantComponent &, QCFWorkerThread &, const QList<QCFVariant> &)>

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
    QCFVariantFunction &operator=(QCFVariantFunction &&other);
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
    QCFVariantFunctor m_Function;
};

#endif // QCFVARIANTFUNCTION_H
