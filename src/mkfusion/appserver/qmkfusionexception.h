#ifndef QMKFUSIONEXCEPTION_H
#define QMKFUSIONEXCEPTION_H

#include <qtconcurrentexception.h>
#include <QDateTime>
#include <QString>


class Q_DECL_EXPORT QMKFusionCFAbortException : public QException
{
public:
    QMKFusionCFAbortException() : QException() {}
};

class Q_DECL_EXPORT QMKFusionException : public QException
{
public:
    QMKFusionException(const QMKFusionException &other)
        : QException()
        , m_Message(other.m_Message)
        , m_Detail(other.m_Detail)
    {
    }

    QMKFusionException(const QString &message, const QString &detail = "")
        : QException()
        , m_Message(message)
        , m_Detail(detail)
    {
	}

    ~QMKFusionException() throw() {}

	void raise() const { throw *this; }
    QException *clone() const { return new QMKFusionException(*this); }

    QString m_Message;
    QString m_Detail;
};

class Q_DECL_EXPORT QMKFusionApplictionException : public QMKFusionException
{
public:
    QMKFusionApplictionException(QString message, QString detail = "")
        : QMKFusionException(message, detail)
    {
    }
};

class Q_DECL_EXPORT QMKFusionDatabaseException : public QMKFusionException
{
public:
    QMKFusionDatabaseException(QString message, QString detail = "")
        : QMKFusionException(message, detail)
    {
    }
};

class Q_DECL_EXPORT QMKFusionSecurityException : public QMKFusionException
{
public:
    QMKFusionSecurityException(QString message, QString detail = "")
        : QMKFusionException(message, detail)
    {
    }
};

class Q_DECL_EXPORT QMKFusionObjectException : public QMKFusionException
{
public:
    QMKFusionObjectException(QString message, QString detail = "")
        : QMKFusionException(message, detail)
    {
    }
};

class Q_DECL_EXPORT QMKFusionMissingIncludeException : public QMKFusionException
{
public:
    QMKFusionMissingIncludeException(QString message, QString detail = "")
        : QMKFusionException(message, detail)
    {
    }
};

class Q_DECL_EXPORT QMKFusionTemplateException : public QMKFusionException
{
public:
    QMKFusionTemplateException(QString message, QString detail = "")
        : QMKFusionException(message, detail)
    {
    }
};

class Q_DECL_EXPORT QMKFusionExpressionException : public QMKFusionException
{
public:
    QMKFusionExpressionException(QString message = "", QString detail = "", qint32 errorNumber = 0)
        : QMKFusionException(message, detail)
    {
        m_ErrorNumber = errorNumber;
    }

    qint32 m_ErrorNumber;
};

class Q_DECL_EXPORT QMKFusionLockException : public QMKFusionException
{
public:
    QMKFusionLockException(QString message = "", QString detail = "")
        : QMKFusionException(message, detail)
    {
    }
};

class Q_DECL_EXPORT QMKFusionSearchEngineException : public QMKFusionException
{
public:
    QMKFusionSearchEngineException(QString message = "", QString detail = "")
        : QMKFusionException(message, detail)
    {
    }
};

class Q_DECL_EXPORT QMKFusionIllegalNumRangeException : public QMKFusionException
{
public:
    QMKFusionIllegalNumRangeException(double value, double minValue, double maxValue)
        :QMKFusionException("", "")
    {
        m_Value = value;
        m_minValue = minValue;
        m_maxValue = maxValue;
	}

    double m_Value;
    double m_minValue;
    double m_maxValue;
};

class Q_DECL_EXPORT QMKFusionArrayGenericMultiDimException : public QMKFusionException
{
public:
    QMKFusionArrayGenericMultiDimException()
        : QMKFusionException("", "")
    {
    }
};

class Q_DECL_EXPORT QMKFusionArrayNotOneDimensionException : public QMKFusionException
{
public:
    QMKFusionArrayNotOneDimensionException()
        : QMKFusionException("", "")
    {

    }
};

class Q_DECL_EXPORT QMKFusionInvalidArrayIndexException : public QMKFusionException
{
public:
    QMKFusionInvalidArrayIndexException(int size, int index)
        : QMKFusionException("", "")
    {
        m_Size = size;
        m_Index = index;
	}

    int m_Size;
    int m_Index;
};

class Q_DECL_EXPORT QMKFusionBadArrayDimensionException : public QMKFusionException
{
public:
    explicit QMKFusionBadArrayDimensionException(int dimension)
        : QMKFusionException("", "")
	{
        m_Dimension = dimension;
	}

    int m_Dimension;
};

class Q_DECL_EXPORT QMKFusionArraySetRangeException : public QMKFusionException
{
public:
    QMKFusionArraySetRangeException(int start, int end)
        : QMKFusionException("", "")
    {
        m_Start = start;
        m_End = end;
	}

    int m_Start;
    int m_End;
};

class Q_DECL_EXPORT QMKFusionArraySwapRangeException : public QMKFusionException
{
public:
    QMKFusionArraySwapRangeException(int start, int end)
        : QMKFusionException("", "")
    {
        m_Start = start;
        m_End = end;
    }

    int m_Start;
    int m_End;
};

class Q_DECL_EXPORT QMKFusionInvalidArgumentException : public QMKFusionException
{
public:
    QMKFusionInvalidArgumentException(QString p_Function, int p_argument, double p_argumentValue, double p_minValue, double p_maxValue)
        : QMKFusionException("", "")
	{
        Q_UNUSED(p_Function);
        Q_UNUSED(p_argument);
        Q_UNUSED(p_argumentValue);
        Q_UNUSED(p_minValue);
        Q_UNUSED(p_maxValue);
	}
    QMKFusionInvalidArgumentException(QString p_Function, int p_argument, double p_argumentValue, QString p_Error)
        : QMKFusionException("", "")
	{
        Q_UNUSED(p_Function);
        Q_UNUSED(p_argument);
        Q_UNUSED(p_argumentValue);
        Q_UNUSED(p_Error);
	}
};

class Q_DECL_EXPORT QMKFusionCustomException : public QMKFusionException
{
public:
    QMKFusionCustomException(QString message, QString detail = "")
        : QMKFusionException(message, detail)
    {
    }
};

#endif // QMKFUSIONEXCEPTION_H
