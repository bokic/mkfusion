#ifndef QCFTAG_H
#define QCFTAG_H

#include <QObject>
#include <QString>

class QCFTagArgument : public QObject
{
public:
	enum ArgumentType {TypeConstantNumber, TypeConstantString, TypeExpression, TypeVariable, TypeAny};

	QCFTagArgument();
	QCFTagArgument(const QCFTagArgument&);
	QCFTagArgument(const QString&, bool = false, ArgumentType = TypeAny, const QString& = "");
	QCFTagArgument& operator=(const QCFTagArgument&);
	QString m_Name;
	bool m_Required;
	ArgumentType m_Type;
	QString m_MustBeValue;
};

class QCFTag : public QObject
{
public:
	enum CloseTagType{TagTypeNoRestriction, TagTypeWithCloseTag, TagTypeWithoutCloseTag};
	enum ArgumentsType{ArgumentsTypeArguments, ArgumentsTypeExpression};
	enum ExpressionInside{WithoutExpressionInside, WithExpressionInside};
	QCFTag();
    QCFTag(const QCFTag&);
    QCFTag(const QString&, CloseTagType, ArgumentsType, ExpressionInside = WithoutExpressionInside, bool = false);
	QCFTag& operator=(const QCFTag&);
	QString m_Name;
	enum CloseTagType m_CloseTagType;
	enum ArgumentsType m_ArgumentsType;
	enum ExpressionInside m_ExpressionInside;
    bool m_AnyParam;
	QList<QList<QCFTagArgument> > m_ArgumentVariants;
};

#endif // QCFTAG_H
