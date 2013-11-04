#include "qcfvariantfunction.h"

QCFVariantFunction::QCFVariantFunction()
{
}

QCFVariantFunction::QCFVariantFunction(const QCFVariantFunction &other)
    : m_Arguments(other.m_Arguments)
    , m_ReturnType(other.m_ReturnType)
    , m_Roles(other.m_Roles)
    , m_Access(other.m_Access)
    , m_Output(other.m_Output)
    , m_DisplayName(other.m_DisplayName)
    , m_Hint(other.m_Hint)
    , m_Description(other.m_Description)
{
}

#ifdef Q_COMPILER_RVALUE_REFS
QCFVariantFunction &QCFVariantFunction::operator=(QCFVariantFunction &&other)
{
    qSwap(m_Arguments, other.m_Arguments);
    qSwap(m_ReturnType, other.m_ReturnType);
    qSwap(m_Roles, other.m_Roles);
    qSwap(m_Access, other.m_Access);
    qSwap(m_Output, other.m_Output);
    qSwap(m_DisplayName, other.m_DisplayName);
    qSwap(m_Hint, other.m_Hint);
    qSwap(m_Description, other.m_Description);

    return *this;
}
#endif

QCFVariantFunction &QCFVariantFunction::operator=(const QCFVariantFunction &other)
{
    m_Arguments = other.m_Arguments;
    m_ReturnType = other.m_ReturnType;
    m_Roles = other.m_Roles;
    m_Access = other.m_Access;
    m_Output = other.m_Output;
    m_DisplayName = other.m_DisplayName;
    m_Hint = other.m_Hint;
    m_Description = other.m_Description;

    return *this;
}
