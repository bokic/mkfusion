#include "qcftag.h"

QCFTagArgument::QCFTagArgument():QObject()
{
}

QCFTagArgument::QCFTagArgument(const QCFTagArgument& p_TagArgument):QObject()
{
	m_Name = p_TagArgument.m_Name;
	m_Required = p_TagArgument.m_Required;
	m_Type = p_TagArgument.m_Type;
	m_MustBeValue = p_TagArgument.m_MustBeValue;
}

QCFTagArgument::QCFTagArgument(const QString& p_Name, bool p_Required, ArgumentType p_Type, const QString& p_MustBeValue):QObject()
{
	m_Name = p_Name;
	m_Required = p_Required;
	m_Type = p_Type;
	m_MustBeValue = p_MustBeValue;
}

QCFTagArgument& QCFTagArgument::operator=(const QCFTagArgument& p_TagArgument)
{
	m_Name = p_TagArgument.m_Name;
	m_Required = p_TagArgument.m_Required;
	m_Type = p_TagArgument.m_Type;
	m_MustBeValue = p_TagArgument.m_MustBeValue;

	return *this;
}


QCFTag::QCFTag():QObject()
{
}

QCFTag::QCFTag(const QCFTag& p_Tag):QObject()
{
	m_Name = p_Tag.m_Name;
	m_CloseTagType = p_Tag.m_CloseTagType;
	m_ArgumentsType = p_Tag.m_ArgumentsType;
	m_ExpressionInside = p_Tag.m_ExpressionInside;

}

QCFTag::QCFTag(const QString& p_TagName, CloseTagType p_CloseTagType, ArgumentsType p_ArgumentsType, ExpressionInside p_ExpressionInside):QObject()
{
	m_Name = p_TagName;
	m_CloseTagType = p_CloseTagType;
	m_ArgumentsType = p_ArgumentsType;
	m_ExpressionInside = p_ExpressionInside;
}

QCFTag& QCFTag::operator=(const QCFTag& p_Tag)
{
	m_Name = p_Tag.m_Name;
	m_CloseTagType = p_Tag.m_CloseTagType;
	m_ArgumentsType = p_Tag.m_ArgumentsType;
	m_ExpressionInside = p_Tag.m_ExpressionInside;

	return *this;
}
