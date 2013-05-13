#ifndef QMKFUSIONEXCEPTION_H
#define QMKFUSIONEXCEPTION_H

#include "qwddx.h"

#include <qtconcurrentexception.h>
#include <QDateTime>
#include <QString>

class Q_DECL_EXPORT QMKFusionException : public QException
{
public:
    QMKFusionException(QString p_message, QString p_Detail = "") : QException()
	{ // TODO: Please find a smarter way to keep and destroy QStrings inside exception class;
		m_Type = new QString("Any");
		m_message = new QString(p_message);
		m_Detail = new QString(p_Detail);
	}
	void raise() const { throw *this; }
    QException *clone() const { return new QMKFusionException(*this); }
	QWDDX GenerateCFCatch()
	{
		QWDDX ret(QWDDX::Struct);

		ret[L"Type"] = *m_Type;
		ret[L"Message"] = *m_message;
		ret[L"Detail"] = *m_Detail;
		ret[L"StackTrace"] = L"Todo, schedule for v1.1";
		ret[L"TagContext"] = L"Todo, schedule for v1.1";

		return ret;
	}

	QString *m_Type;
	QString *m_message;
	QString *m_Detail;
};

class QMKFusionCFAbortException : public QException
{
public:
    QMKFusionCFAbortException() : QException() {}
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
        Q_UNUSED(p_Value);
        Q_UNUSED(p_MinValue);
        Q_UNUSED(p_MaxValue);

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
        Q_UNUSED(p_Size);
        Q_UNUSED(p_Index);
	}
};

class QMKFusionBadArrayDimensionException : public QMKFusionException
{
public:
	QMKFusionBadArrayDimensionException(int p_Dimension):QMKFusionException("", "")
	{
        Q_UNUSED(p_Dimension);
	}
};

class QMKFusionArraySetRangeException : public QMKFusionException
{
public:
	QMKFusionArraySetRangeException(int p_Start, int p_End):QMKFusionException("", "")
	{
        Q_UNUSED(p_Start);
        Q_UNUSED(p_End);
	}
};

class QMKFusionArraySwapRangeException : public QMKFusionException
{
public:
	QMKFusionArraySwapRangeException(int p_Start, int p_End):QMKFusionException("", "")
	{
        Q_UNUSED(p_Start);
        Q_UNUSED(p_End);
    }
};

class QMKFusionInvalidArgumentException : public QMKFusionException
{
public:
	QMKFusionInvalidArgumentException(QString p_Function, int p_argument, double p_argumentValue, double p_minValue, double p_maxValue):QMKFusionException("", "")
	{
        Q_UNUSED(p_Function);
        Q_UNUSED(p_argument);
        Q_UNUSED(p_argumentValue);
        Q_UNUSED(p_minValue);
        Q_UNUSED(p_maxValue);
	}
	QMKFusionInvalidArgumentException(QString p_Function, int p_argument, double p_argumentValue, QString p_Error):QMKFusionException("", "")
	{
        Q_UNUSED(p_Function);
        Q_UNUSED(p_argument);
        Q_UNUSED(p_argumentValue);
        Q_UNUSED(p_Error);
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
