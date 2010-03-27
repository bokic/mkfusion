#ifndef QMKFUSIONEXCEPTION_H
#define QMKFUSIONEXCEPTION_H

#include "qwddx.h"

#include <qtconcurrentexception.h>
#include <QDateTime>
#include <QString>

class Q_DECL_EXPORT QMKFusionException : public QtConcurrent::Exception
{
public:
	QMKFusionException(QString p_message, QString p_Detail = "") : QtConcurrent::Exception()
	{ // TODO: Please find a smarter way to keep and destroy QStrings inside exception class;
		m_Type = new QString("Any");
		m_message = new QString(p_message);
		m_Detail = new QString(p_Detail);
	}
	void raise() const { throw *this; }
	Exception *clone() const { return new QMKFusionException(*this); }
	QWDDX GenerateCFCatch()
	{
		QWDDX ret(QWDDX::Struct);

		ret["Type"] = *m_Type;
		ret["Message"] = *m_message;
		ret["Detail"] = *m_Detail;
		ret["StackTrace"] = "Todo, schedule for v1.1";
		ret["TagContext"] = "Todo, schedule for v1.1";

		return ret;
	}

	QString *m_Type;
	QString *m_message;
	QString *m_Detail;
};

class QMKFusionCFAbortException : public QtConcurrent::Exception
{
public:
	QMKFusionCFAbortException() : QtConcurrent::Exception() {}
};

/*class QMKFusionApplictionException : public QMKFusionException
{
public:
	QMKFusionApplictionException(QString p_Detail = "", QString p_errorCode = "", QString p_extendedInfo = "", QString p_message = "", QString p_object = ""):QMKFusionException(p_Detail, p_Detail, p_extendedInfo, p_message, p_object) { m_Type = new QString("application");}
};

class QMKFusionDatabaseException : public QMKFusionException
{
public:
	QMKFusionDatabaseException(QString p_Detail = "", QString p_errorCode = "", QString p_extendedInfo = "", QString p_message = "", QString p_object = ""):QMKFusionException(p_Detail, p_Detail, p_extendedInfo, p_message, p_object) { m_Type = new QString("database");}
};*/

class QMKFusionIllegalNumRangeException : public QMKFusionException
{
public:
	QMKFusionIllegalNumRangeException(double p_Value, double p_MinValue, double p_MaxValue):QMKFusionException("", "")
	{
		m_Type = new QString("template");
	}
};


class QMKFusionArrayGenericMultiDimException : public QMKFusionException
{
public:
	QMKFusionArrayGenericMultiDimException():QMKFusionException("", ""){}
};

class QMKFusionArrayNotOneDimensionException : public QMKFusionException
{
public:
	QMKFusionArrayNotOneDimensionException():QMKFusionException("", ""){}
};

class QMKFusionInvalidArrayIndexException : public QMKFusionException
{
public:
	QMKFusionInvalidArrayIndexException(int p_Size, int p_Index):QMKFusionException("", "")
	{
	}
};

class QMKFusionBadArrayDimensionException : public QMKFusionException
{
public:
	QMKFusionBadArrayDimensionException(int p_Dimension):QMKFusionException("", "")
	{

	}
};

class QMKFusionArraySetRangeException : public QMKFusionException
{
public:
	QMKFusionArraySetRangeException(int p_Start, int p_End):QMKFusionException("", "")
	{

	}
};

class QMKFusionArraySwapRangeException : public QMKFusionException
{
public:
	QMKFusionArraySwapRangeException(int p_Start, int p_End):QMKFusionException("", "")
	{

	}
};

class QMKFusionInvalidArgumentException : public QMKFusionException
{
public:
	QMKFusionInvalidArgumentException(QString p_Function, int p_argument, double p_argumentValue, double p_minValue, double p_maxValue):QMKFusionException("", "")
	{

	}
	QMKFusionInvalidArgumentException(QString p_Function, int p_argument, double p_argumentValue, QString p_Error):QMKFusionException("", "")
	{

	}
};

class QMKFusionTemplateException : public QMKFusionException
{
public:
	QMKFusionTemplateException(QString p_message = "", QString p_Detail = ""):QMKFusionException(p_message, p_Detail)
	{
		m_Type = new QString("template");
	}
};

/*class QMKFusionSecurityException : public QMKFusionException
{
public:
	QMKFusionSecurityException(QString p_Detail = "", QString p_errorCode = "", QString p_extendedInfo = "", QString p_message = "", QString p_object = ""):QMKFusionException(p_Detail, p_Detail, p_extendedInfo, p_message, p_object) { m_Type = new QString("security");}
};

class QMKFusionObjectException : public QMKFusionException
{
public:
	QMKFusionObjectException(QString p_Detail = "", QString p_errorCode = "", QString p_extendedInfo = "", QString p_message = "", QString p_object = ""):QMKFusionException(p_Detail, p_Detail, p_extendedInfo, p_message, p_object) { m_Type = new QString("object");}
};

class QMKFusionMissingIncludeException : public QMKFusionException
{
public:
	QMKFusionMissingIncludeException(QString p_Detail = "", QString p_errorCode = "", QString p_extendedInfo = "", QString p_message = "", QString p_object = ""):QMKFusionException(p_Detail, p_Detail, p_extendedInfo, p_message, p_object) { m_Type = new QString("missingInclude");}
};*/

class QMKFusionExpressionException : public QMKFusionException
{
	qint32 m_errorNumber;
public:
	QMKFusionExpressionException(QString p_message, QString p_Detail = "", qint32 p_errorNumber = 0):QMKFusionException(p_message, p_Detail)
	{
		*m_Type = "expression";
		m_errorNumber = p_errorNumber;
	}
};

/*class QMKFusionLockException : public QMKFusionException
{
public:
	QMKFusionLockException(QString p_Detail = "", QString p_errorCode = "", QString p_extendedInfo = "", QString p_message = "", QString p_object = ""):QMKFusionException(p_Detail, p_Detail, p_extendedInfo, p_message, p_object) { m_Type = new QString("lock");}
};

class QMKFusionCustomException : public QMKFusionException
{
public:
	QMKFusionCustomException(QString p_Detail = "", QString p_errorCode = "", QString p_extendedInfo = "", QString p_message = "", QString p_object = ""):QMKFusionException(p_Detail, p_Detail, p_extendedInfo, p_message, p_object) { m_Type = new QString("custom_type");}
};

class QMKFusionSearchEngineException : public QMKFusionException
{
public:
	QMKFusionSearchEngineException(QString p_Detail = "", QString p_errorCode = "", QString p_extendedInfo = "", QString p_message = "", QString p_object = ""):QMKFusionException(p_Detail, p_Detail, p_extendedInfo, p_message, p_object) { m_Type = new QString("searchgengine");}
};*/

#endif // QMKFUSIONEXCEPTION_H