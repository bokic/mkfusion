#include "qcftag.h"

QCFTagArgument::QCFTagArgument()
    : QObject()
{
}

QCFTagArgument::QCFTagArgument(const QCFTagArgument &p_TagArgument)
    : QObject()
{
    m_Name = p_TagArgument.m_Name;
    m_Required = p_TagArgument.m_Required;
    m_Type = p_TagArgument.m_Type;
    m_MustBeValue = p_TagArgument.m_MustBeValue;
}

QCFTagArgument::QCFTagArgument(const QString &p_Name, bool p_Required, ArgumentType p_Type, const QString &p_MustBeValue)
    : QObject()
{
    m_Name = p_Name;
    m_Required = p_Required;
    m_Type = p_Type;
    m_MustBeValue = p_MustBeValue;
}

QCFTagArgument &QCFTagArgument::operator=(const QCFTagArgument &p_TagArgument)
{
    if (this != &p_TagArgument)
    {
        m_Name = p_TagArgument.m_Name;
        m_Required = p_TagArgument.m_Required;
        m_Type = p_TagArgument.m_Type;
        m_MustBeValue = p_TagArgument.m_MustBeValue;
    }

    return *this;
}

#ifdef Q_COMPILER_RVALUE_REFS
QCFTagArgument &QCFTagArgument::operator=(QCFTagArgument &&other)
{
    qSwap(m_Name, other.m_Name);
    qSwap(m_Required, other.m_Required);
    qSwap(m_Type, other.m_Type);
    qSwap(m_MustBeValue, other.m_MustBeValue);

    return *this;
}
#endif


QCFTag::QCFTag()
    : QObject()
{
}

QCFTag::QCFTag(const QCFTag &other)
    : QObject()
{
    m_Name = other.m_Name;
    m_CloseTagType = other.m_CloseTagType;
    m_ArgumentsType = other.m_ArgumentsType;
    m_ExpressionInside = other.m_ExpressionInside;
    m_ArgumentVariants = other.m_ArgumentVariants;
    m_AnyParam = other.m_AnyParam;
}

QCFTag::QCFTag(const QString &p_TagName, CloseTagType p_CloseTagType, ArgumentsType p_ArgumentsType, ExpressionInside p_ExpressionInside, bool p_AnyParam)
    : QObject()
{
    m_Name = p_TagName;
    m_CloseTagType = p_CloseTagType;
    m_ArgumentsType = p_ArgumentsType;
    m_ExpressionInside = p_ExpressionInside;
    m_AnyParam = p_AnyParam;
}

QCFTag &QCFTag::operator=(const QCFTag &other)
{
    if (this != &other)
    {
        m_Name = other.m_Name;
        m_CloseTagType = other.m_CloseTagType;
        m_ArgumentsType = other.m_ArgumentsType;
        m_ExpressionInside = other.m_ExpressionInside;
        m_ArgumentVariants = other.m_ArgumentVariants;
        m_AnyParam = other.m_AnyParam;
    }

    return *this;
}

#ifdef Q_COMPILER_RVALUE_REFS
QCFTag &QCFTag::operator=(QCFTag &&other)
{
    qSwap(m_Name, other.m_Name);
    qSwap(m_CloseTagType, other.m_CloseTagType);
    qSwap(m_ArgumentsType, other.m_ArgumentsType);
    qSwap(m_ExpressionInside, other.m_ExpressionInside);
    qSwap(m_AnyParam, other.m_AnyParam);
    qSwap(m_ArgumentVariants, other.m_ArgumentVariants);

    return *this;
}
#endif
