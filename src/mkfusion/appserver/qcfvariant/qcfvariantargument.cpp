#include "qcfvariantargument.h"

QCFVariantArgument::QCFVariantArgument()
{
}

QCFVariantArgument::QCFVariantArgument(const QCFVariantArgument &other)
    : m_Name(other.m_Name)
    , m_Required(other.m_Required)
    , m_Type(other.m_Type)
    , m_Default(other.m_Default)
{
}

#ifdef Q_COMPILER_RVALUE_REFS
QCFVariantArgument &QCFVariantArgument::operator=(QCFVariantArgument &&other)
{
    qSwap(m_Name, other.m_Name);
    qSwap(m_Required, other.m_Required);
    qSwap(m_Type, other.m_Type);
    qSwap(m_Default, other.m_Default);

    return *this;
}
#endif

QCFVariantArgument &QCFVariantArgument::operator=(const QCFVariantArgument &other)
{
    m_Name = other.m_Name;
    m_Required = other.m_Required;
    m_Type = other.m_Type;
    m_Default = other.m_Default;

    return *this;
}
