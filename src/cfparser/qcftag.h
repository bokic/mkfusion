#pragma once

#include <QObject>
#include <QString>

class QCFTagArgument : public QObject
{
public:
    enum ArgumentType {TypeConstantNumber, TypeConstantString, TypeExpression, TypeVariable, TypeAny};

    QCFTagArgument();
    QCFTagArgument(const QCFTagArgument &p_TagArgument);
    QCFTagArgument(const QString &p_Name, bool p_Required = false, ArgumentType p_Type = TypeAny, const QString &p_MustBeValue = "");
    QCFTagArgument &operator=(const QCFTagArgument &p_TagArgument);
#ifdef Q_COMPILER_RVALUE_REFS
    inline QCFTagArgument &operator=(QCFTagArgument &&other)
    {
        qSwap(m_Name, other.m_Name);
        qSwap(m_Required, other.m_Required);
        qSwap(m_Type, other.m_Type);
        qSwap(m_MustBeValue, other.m_MustBeValue);

        return *this;
    }
#endif

    QString m_Name;
    bool m_Required;
    ArgumentType m_Type;
    QString m_MustBeValue;
};

class QCFTag : public QObject
{
public:
    enum CloseTagType {TagTypeNoRestriction, TagTypeWithCloseTag, TagTypeWithoutCloseTag};
    enum ArgumentsType {ArgumentsTypeArguments, ArgumentsTypeExpression};
    enum ExpressionInside {WithoutExpressionInside, WithExpressionInside};
    QCFTag();
    QCFTag(const QCFTag &other);
    QCFTag(const QString &p_TagName, CloseTagType p_CloseTagType, ArgumentsType p_ArgumentsType, ExpressionInside p_ExpressionInside = WithoutExpressionInside, bool p_AnyParam = false);
    QCFTag &operator=(const QCFTag &other);
#ifdef Q_COMPILER_RVALUE_REFS
    inline QCFTag &operator=(QCFTag &&other)
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

    QString m_Name;
    enum CloseTagType m_CloseTagType;
    enum ArgumentsType m_ArgumentsType;
    enum ExpressionInside m_ExpressionInside;
    bool m_AnyParam;
    QList<QList<QCFTagArgument>> m_ArgumentVariants;
};
