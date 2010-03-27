#include "qcffunction.h"

QCFFunctionArgument::QCFFunctionArgument():QObject()
{
}

QCFFunctionArgument::QCFFunctionArgument(const QCFFunctionArgument& p_FunctionArgument):QObject()
{
	m_DataType = p_FunctionArgument.m_DataType;
	m_Type = p_FunctionArgument.m_Type;
	m_Required = p_FunctionArgument.m_Required;
}

QCFFunctionArgument::QCFFunctionArgument(ArgumentDataType p_DataType, bool p_Required, ArgumentType p_Type):QObject()
{
	m_DataType = p_DataType;
	m_Required = p_Required;
	m_Type = p_Type;
}

QCFFunctionArgument& QCFFunctionArgument::operator=(const QCFFunctionArgument& p_FunctionArgument)
{
	m_DataType = p_FunctionArgument.m_DataType;
	m_Required = p_FunctionArgument.m_Required;
	m_Type = p_FunctionArgument.m_Type;

	return *this;
}

QCFFunction::QCFFunction():QObject()
{
}

QCFFunction::QCFFunction(const QCFFunction& p_Function):QObject()
{
	m_Name = p_Function.m_Name;
	m_ReturnType = p_Function.m_ReturnType;
}

QCFFunction::QCFFunction(const QString& p_FunctionName, ReturnType p_ReturnType):QObject()
{
	m_Name = p_FunctionName;
	m_ReturnType = p_ReturnType;
}

QCFFunction& QCFFunction::operator=(const QCFFunction& p_Function)
{
	m_Name = p_Function.m_Name;
	m_ReturnType = p_Function.m_ReturnType;

	return *this;
}


void QCFFunction::setName(const QString& p_FunctionName)
{
	m_Name = p_FunctionName;
}

const QString& QCFFunction::getName()
{
	return m_Name;
}
