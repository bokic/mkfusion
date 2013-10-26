#include "qcffunction.h"
#include <QString>
#include <QObject>
#include <QList>

QCFFunctionArgument::QCFFunctionArgument()
	: QObject()
	, m_DataType(ArgumentDataTypeAny)
	, m_Type(TypeAny)
	, m_Required(false)
{
}

QCFFunctionArgument::QCFFunctionArgument(const QCFFunctionArgument &other)
	: QObject()
{
	m_DataType = other.m_DataType;
	m_Type = other.m_Type;
	m_Required = other.m_Required;
}

QCFFunctionArgument::QCFFunctionArgument(QCFFunctionArgumentDataType p_DataType, bool p_Required, QCFFunctionArgumentType p_Type)
	: QObject()
{
	m_DataType = p_DataType;
	m_Required = p_Required;
	m_Type = p_Type;
}

QCFFunctionArgument &QCFFunctionArgument::operator=(const QCFFunctionArgument &other)
{
	if (this != &other)
	{
		m_DataType = other.m_DataType;
		m_Required = other.m_Required;
		m_Type = other.m_Type;
	}

	return *this;
}

#ifdef Q_COMPILER_RVALUE_REFS
QCFFunctionArgument &QCFFunctionArgument::operator=(QCFFunctionArgument &&other)
{
    qSwap(m_DataType, other.m_DataType);
    qSwap(m_Required, other.m_Required);
    qSwap(m_Type, other.m_Type);

    return *this;
}
#endif


QCFFunction::QCFFunction()
	: QObject()
    , m_NeedsThis(false)
	, m_ReturnType(ReturnVoid)
{
}

QCFFunction::QCFFunction(const QCFFunction &other)
	: QObject()
    , m_Name(other.m_Name)
    , m_NeedsThis(other.m_NeedsThis)
    , m_ReturnType(other.m_ReturnType)
    , m_Arguments(other.m_Arguments)
{
}

QCFFunction::QCFFunction(const QString &p_FunctionName, QCFFunctionReturnType p_ReturnType, bool p_NeedsThis)
	: QObject()
    , m_Name(p_FunctionName)
    , m_NeedsThis(p_NeedsThis)
    , m_ReturnType(p_ReturnType)
{
}

QCFFunction &QCFFunction::operator=(const QCFFunction &other)
{
	if (this != &other)
	{
		m_Name = other.m_Name;
        m_NeedsThis = other.m_NeedsThis;
		m_ReturnType = other.m_ReturnType;
		m_Arguments = other.m_Arguments;
	}

	return *this;
}

#ifdef Q_COMPILER_RVALUE_REFS
QCFFunction &QCFFunction::operator=(QCFFunction &&other)
{
    qSwap(m_Name, other.m_Name);
    qSwap(m_NeedsThis, other.m_NeedsThis);
    qSwap(m_ReturnType, other.m_ReturnType);
    qSwap(m_Arguments, other.m_Arguments);

    return *this;
}
#endif

void QCFFunction::setName(const QString &p_FunctionName)
{
	m_Name = p_FunctionName;
}

const QString &QCFFunction::getName()
{
	return m_Name;
}
