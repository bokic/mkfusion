#include "qcfvariantfunction.h"

QCFVariantFunction::QCFVariantFunction()
    : m_Functor(nullptr)
{
}

QCFVariantFunction::QCFVariantFunction(const QCFVariantFunction &other)
    : m_Name(other.m_Name)
    , m_Access(other.m_Access)
    , m_Description(other.m_Description)
    , m_DisplayName(other.m_DisplayName)
    , m_Hint(other.m_Hint)
    , m_Output(other.m_Output)
    , m_ReturnFormat(other.m_ReturnFormat)
    , m_ReturnType(other.m_ReturnType)
    , m_Roles(other.m_Roles)
    , m_SecureJSON(other.m_SecureJSON)
    , m_VerifyClients(other.m_VerifyClients)
    , m_Arguments(other.m_Arguments)
    , m_Functor(other.m_Functor)
{
}

QCFVariantFunction::QCFVariantFunction(
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
)
    : m_Name(name)
    , m_Access(access)
    , m_Description(desc)
    , m_DisplayName(dispName)
    , m_Hint(hint)
    , m_Output(output)
    , m_ReturnFormat(returnFormat)
    , m_ReturnType(returnType)
    , m_Roles(roles)
    , m_SecureJSON(secureJSON)
    , m_VerifyClients(verifyClients)
    , m_Arguments(args)
    , m_Functor(function)
{
}

#ifdef Q_COMPILER_RVALUE_REFS
QCFVariantFunction &QCFVariantFunction::operator=(QCFVariantFunction &&other)
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

QCFVariantFunction &QCFVariantFunction::operator=(const QCFVariantFunction &other)
{
    m_Name = other.m_Name;
    m_Access = other.m_Access;
    m_Description = other.m_Description;
    m_DisplayName = other.m_DisplayName;
    m_Hint = other.m_Hint;
    m_Output = other.m_Output;
    m_ReturnFormat = other.m_ReturnFormat;
    m_ReturnType = other.m_ReturnType;
    m_Roles = other.m_Roles;
    m_SecureJSON = other.m_SecureJSON;
    m_VerifyClients = other.m_VerifyClients;
    m_Arguments = other.m_Arguments;
    m_Functor = other.m_Functor;

    return *this;
}
