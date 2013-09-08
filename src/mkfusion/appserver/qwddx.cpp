#include "qwddx.h"
#include "qmkfusionexception.h"
#include <QDebug>
#include <math.h>

Q_DECL_EXPORT QWDDX::QWDDX()
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(nullptr)
    , m_ByteArray(nullptr)
    , m_Number(0)
	, m_Bool(false)
    , m_DateTime(nullptr)
	, m_Type(Null)
    , m_ArrayDimension(1)
    , m_HiddenScope(nullptr)
{
}

Q_DECL_EXPORT QWDDX::~QWDDX()
{
    setType(Null);
    m_HiddenScope = nullptr;
}

Q_DECL_EXPORT QWDDX::QWDDX(bool p_NewValue)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(nullptr)
    , m_ByteArray(nullptr)
    , m_Number(0)
	, m_Bool(p_NewValue)
    , m_DateTime(nullptr)
	, m_Type(Boolean)
    , m_ArrayDimension(1)
    , m_HiddenScope(nullptr)
{
}

Q_DECL_EXPORT QWDDX::QWDDX(int p_NewValue)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(nullptr)
    , m_ByteArray(nullptr)
	, m_Number(p_NewValue)
	, m_Bool(false)
    , m_DateTime(nullptr)
	, m_Type(Number)
    , m_ArrayDimension(1)
    , m_HiddenScope(nullptr)
{
}

Q_DECL_EXPORT QWDDX::QWDDX(double p_NewValue)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(nullptr)
    , m_ByteArray(nullptr)
	, m_Number(p_NewValue)
	, m_Bool(false)
    , m_DateTime(nullptr)
	, m_Type(Number)
    , m_ArrayDimension(1)
    , m_HiddenScope(nullptr)
{
}

Q_DECL_EXPORT QWDDX::QWDDX(const char *p_NewValue)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(new QString(p_NewValue))
    , m_ByteArray(nullptr)
	, m_Number(0)
	, m_Bool(false)
    , m_DateTime(nullptr)
	, m_Type(String)
    , m_ArrayDimension(1)
    , m_HiddenScope(nullptr)
{
    qDebug() << "QWDDX::QWDDX(const char *p_NewValue) called. to be deleted soon.";
}

Q_DECL_EXPORT QWDDX::QWDDX(const wchar_t *p_NewValue)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(new QString(QString::fromWCharArray(p_NewValue)))
    , m_ByteArray(nullptr)
	, m_Number(0)
	, m_Bool(false)
    , m_DateTime(nullptr)
	, m_Type(String)
    , m_ArrayDimension(1)
    , m_HiddenScope(nullptr)
{
}

Q_DECL_EXPORT QWDDX::QWDDX(const QString &p_NewValue)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(new QString(p_NewValue))
    , m_ByteArray(nullptr)
	, m_Number(0)
	, m_Bool(false)
    , m_DateTime(nullptr)
	, m_Type(String)
    , m_ArrayDimension(1)
    , m_HiddenScope(nullptr)
{
}

Q_DECL_EXPORT QWDDX::QWDDX(const QDateTime &p_NewValue)

    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(nullptr)
    , m_ByteArray(nullptr)
	, m_Number(0)
	, m_Bool(false)
    , m_DateTime(new QDateTime(p_NewValue))
	, m_Type(DateTime)
    , m_ArrayDimension(1)
    , m_HiddenScope(nullptr)
{
}

Q_DECL_EXPORT QWDDX::QWDDX(const QWDDX &other)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(nullptr)
    , m_ByteArray(nullptr)
    , m_Number(0)
    , m_Bool(false)
    , m_DateTime(nullptr)
    , m_Type(other.m_Type)
    , m_ArrayDimension(1)
    , m_HiddenScope(nullptr)
{
    switch(other.m_Type)
    {
    case Null:
        break;
    case Boolean:
        m_Bool = other.m_Bool;
        break;
    case Number:
        m_Number = other.m_Number;
        break;
    case String:
        m_String = new QString(*other.m_String);
        break;
    case DateTime:
        m_DateTime = new QDateTime(*other.m_DateTime);
        break;
    case Array:
        m_Array = new QVector<QWDDX>();
        *m_Array = *other.m_Array;
        m_ArrayDimension = other.m_ArrayDimension;
        break;
    case Struct:
        m_Struct = new QMap<QString, QWDDX>();
        *m_Struct = *other.m_Struct;
        m_HiddenScope = other.m_HiddenScope;
        break;
    case Binary:
        m_ByteArray = new QByteArray();
        *m_ByteArray = *other.m_ByteArray;
        break;
    case Query:
        m_Struct = new QMap<QString, QWDDX>();
        *m_Struct = *other.m_Struct;
        break;
    case NotImplemented:
        break;
    case Error:
        break;
    }
}

Q_DECL_EXPORT QWDDX::QWDDX(const QWDDXType p_Type)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(nullptr)
    , m_ByteArray(nullptr)
	, m_Number(0)
	, m_Bool(false)
    , m_DateTime(nullptr)
    , m_Type(Null)
    , m_ArrayDimension(1)
    , m_HiddenScope(nullptr)
{
    setType(p_Type);
}

#ifdef Q_COMPILER_RVALUE_REFS
Q_DECL_EXPORT QWDDX &QWDDX::operator=(QWDDX &&other)
{
    switch(other.m_Type)
    {
    case Null:
        break;
    case Boolean:
        qSwap(m_Bool, other.m_Bool);
        break;
    case Number:
        qSwap(m_Number, other.m_Number);
        break;
    case String:
        qSwap(m_String, other.m_String);
        break;
    case DateTime:
        qSwap(m_DateTime, other.m_DateTime);
        break;
    case Array:
        qSwap(m_Array, other.m_Array);
        qSwap(m_ArrayDimension, other.m_ArrayDimension);
        break;
    case Struct:
        qSwap(m_Struct, other.m_Struct);
        qSwap(m_HiddenScope, other.m_HiddenScope);
        break;
    case Binary:
        qSwap(m_ByteArray, other.m_ByteArray);
        break;
    case Query:
        qSwap(m_Struct, other.m_Struct);
        break;
    case NotImplemented:
        break;
    case Error:
        break;
    }

    qSwap(m_Type, other.m_Type);

    return *this;
}
#endif

Q_DECL_EXPORT void QWDDX::setType(QWDDXType type)
{
    if (m_Type == type)
    {
        return;
    }

    switch(m_Type)
    {
    case String:
        delete m_String;
        m_String = nullptr;
        break;
    case DateTime:
        delete m_DateTime;
        m_DateTime = nullptr;
        break;
    case Array:
        delete m_Array;
        m_Array = nullptr;
        break;
    case Struct:
        delete m_Struct;
        m_Struct = nullptr;
        m_HiddenScope = nullptr;
        break;
    case Binary:
        delete m_ByteArray;
        m_ByteArray = nullptr;
        break;
    case Query:
        delete m_Struct;
        m_Struct = nullptr;
        break;
    case NotImplemented:
        break;
    case Error:
        break;
    default:
        break;
    }

    m_Type = type;

    switch(m_Type)
    {
    case String:
        m_String = new QString();
        break;
    case DateTime:
        m_DateTime = new QDateTime();
        break;
    case Array:
        m_Array = new QVector<QWDDX>();
        m_ArrayDimension = 1;
        break;
    case Struct:
        m_Struct = new QMap<QString, QWDDX>();
        break;
    case Binary:
        m_ByteArray = new QByteArray;
        break;
    case Query:
        m_Struct = new QMap<QString, QWDDX>();
        break;
    case NotImplemented:
        break;
    case Error:
        break;
    default:
        break;
    }
}

Q_DECL_EXPORT QWDDX::QWDDXType QWDDX::type() const
{
	return m_Type;
}

Q_DECL_EXPORT QWDDX::operator bool()
{
    switch(m_Type)
    {
    case Boolean:
        return m_Bool;
    case Number:
        return m_Number != 0;
    case String:
        return toBool();
    default:
        throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
    }
}

Q_DECL_EXPORT QWDDX::operator int()
{
	return (int)toNumber();
}

Q_DECL_EXPORT QWDDX::operator double()
{
	return toNumber();
}

Q_DECL_EXPORT QWDDX::operator QString()
{
	return toString();
}

Q_DECL_EXPORT QWDDX::operator QDateTime()
{
	return toDateTime();
}

Q_DECL_EXPORT int QWDDX::size()
{
	switch(m_Type)
	{
	case QWDDX::Array:
        return m_Array->size();
	case QWDDX::Struct:
        return m_Struct->size();
	default:
		return 1;
	}
}

Q_DECL_EXPORT QWDDX &QWDDX::operator[](const double p_Index)
{
    if ((m_Type != QWDDX::Struct)&&(m_Type != QWDDX::Array)&&(m_Type != QWDDX::Query))
	{
        throw QMKFusionExpressionException("You have attempted to dereference a scalar variable of type class java.lang.String as a structure with members.");
	}

	if (m_Type != QWDDX::Array)
	{
		if ((int)p_Index < 1)
		{
            throw QMKFusionExpressionException("The element at position " + QString::number((int)p_Index) + " of array variable \"xxx\" cannot be found.");
		}

        if (m_Array->size() <= (int)p_Index)
		{
            m_Array->resize((int)p_Index + 1);
		}

        return (*m_Array)[(int)p_Index];
	}
	else
	{
        QString key = QString::number(p_Index);

        if (m_Struct->contains(key) == false)
		{
            if (m_HiddenScope)
            {
                if (m_HiddenScope->m_Struct->contains(key))
                {
                    return (*m_HiddenScope->m_Struct)[key];
                }
            }

            m_Struct->insert(key, QWDDX(QWDDX::Null));
		}

        return (*m_Struct)[key];
	}
}

Q_DECL_EXPORT QWDDX &QWDDX::operator[](const QString &key)
{
    if ((m_Type != QWDDX::Struct)&&(m_Type != QWDDX::Array)&&(m_Type != QWDDX::Query))
	{
        throw QMKFusionExpressionException("You have attempted to dereference a scalar variable of type class \'QString\' as a structure with members.");
	}

    if ((m_Type == QWDDX::Struct)||(m_Type == QWDDX::Query))
	{
        if (m_Struct->contains(key) == false)
		{
            if (m_HiddenScope)
            {
                if (m_HiddenScope->m_Struct->contains(key))
                {
                    return (*m_HiddenScope->m_Struct)[key];
                }
            }

            throw QMKFusionException(QString("Variable %1 is undefined.").arg(key));
		}

        return (*m_Struct)[key];
	}
	else
	{
		bool ok;
		qint32 val = (qint32)key.toDouble(&ok);
		if (ok == false)
		{
			throw QMKFusionExpressionException("The value " + key + " cannot be converted to a number.");
		}

		if (val < 1)
		{
			throw QMKFusionExpressionException("The element at position " + QString::number(val) + " of array variable xxx cannot be found.");
		}

        if (m_Array->size() > val)
		{
            m_Array->resize(val);
		}

        return (*m_Array)[val - 1];
	}
}

Q_DECL_EXPORT QWDDX &QWDDX::operator[](const char *key)
{
    qDebug() << "QWDDX::operator[](const char *key) called. to be deleted soon.";

    if ((m_Type != QWDDX::Struct)&&(m_Type != QWDDX::Array)&&(m_Type != QWDDX::Query))
	{
		throw QMKFusionExpressionException("You have attempted to dereference a scalar variable of type class wchar_t* as a structure with members.");
	}

    QString l_key = QString::fromLatin1(key);

    if ((m_Type == QWDDX::Struct)||(m_Type == QWDDX::Query))
	{
        if (m_Struct->contains(l_key) == false)
		{
            if (m_HiddenScope)
            {
                if (m_HiddenScope->m_Struct->contains(key))
                {
                    return (*m_HiddenScope->m_Struct)[key];
                }
            }

            throw QMKFusionException(QString("Variable %1 is undefined.").arg(l_key));
		}

        return (*m_Struct)[l_key];
	}
	else
	{
		bool ok;
		qint32 val = (qint32)l_key.toDouble(&ok);
		if (ok == false)
		{
			throw QMKFusionExpressionException("The value " + l_key + " cannot be converted to a number.");
		}

		if (val < 1)
		{
			throw QMKFusionExpressionException("The element at position " + QString::number(val) + " of array variable xxx cannot be found.");
		}

        if (m_Array->size() > val)
		{
            m_Array->resize(val);
		}

        return (*m_Array)[val - 1];
	}
}

Q_DECL_EXPORT QWDDX &QWDDX::operator[](const wchar_t *key)
{
    if ((m_Type != QWDDX::Struct)&&(m_Type != QWDDX::Array)&&(m_Type != QWDDX::Query))
	{
		throw QMKFusionExpressionException("You have attempted to dereference a scalar variable of type class wchar_t* as a structure with members.");
	}

    QString l_key = QString::fromStdWString(key).toUpper();

    if ((m_Type == QWDDX::Struct)||(m_Type == QWDDX::Query))
	{
        if (m_Struct->contains(l_key) == false)
		{
            if (m_HiddenScope)
            {
                if (m_HiddenScope->m_Struct->contains(l_key))
                {
                    return (*m_HiddenScope->m_Struct)[l_key];
                }
            }

            throw QMKFusionException(QString("Variable %1 is undefined.").arg(l_key));
		}

        return (*m_Struct)[l_key];
	}
	else
	{
		bool ok;
		qint32 val = (qint32)l_key.toDouble(&ok);
		if (ok == false)
		{
			throw QMKFusionExpressionException("The value " + l_key + " cannot be converted to a number.");
		}

		if (val < 1)
		{
			throw QMKFusionExpressionException("The element at position " + QString::number(val) + " of array variable xxx cannot be found.");
		}

        if (m_Array->size() > val)
		{
            m_Array->resize(val);
		}

        return (*m_Array)[val - 1];
	}
}

Q_DECL_EXPORT QWDDX &QWDDX::operator[](const QWDDX &key)
{
    if ((m_Type != QWDDX::Struct)&&(m_Type != QWDDX::Array)&&(m_Type != QWDDX::Query))
	{
        throw QMKFusionExpressionException("You have attempted to dereference a scalar variable of type class java.lang.String as a structure with members.");
	}

	if (m_Type == QWDDX::Array)
	{
        int l_key = (int)key.toNumber();

        if (l_key < 1)
		{
            throw QMKFusionExpressionException("The element at position " + QString::number(l_key) + " of array variable \"xxx\" cannot be found.");
		}

        if (m_Array->size() < l_key)
		{
            m_Array->resize(l_key);
		}

        if (((*m_Array)[l_key - 1].m_Type != QWDDX::Array)&&(m_ArrayDimension > 1))
        {
            (*m_Array)[l_key - 1] = QWDDX(QWDDX::Array);
            (*m_Array)[l_key - 1].m_ArrayDimension = m_ArrayDimension - 1;
        }

        return (*m_Array)[l_key - 1];
	}
	else
	{
        const QString &l_key = key.toString();

        if (m_Struct->contains(l_key) == false)
		{
            if (m_HiddenScope)
            {
                if (m_HiddenScope->m_Struct->contains(l_key))
                {
                    return (*m_HiddenScope->m_Struct)[l_key];
                }
            }

            throw QMKFusionException(QString("Variable %1 is undefined.").arg(l_key));
		}

        return (*m_Struct)[l_key];
	}
}

Q_DECL_EXPORT bool QWDDX::operator==(bool p_Value)
{
    if ((m_Type == Boolean))
    {
        return m_Bool == p_Value;
    }

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator==(int p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number == (double)p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() == (double)p_Value;
	}

    if ((m_Type == Array))
    {
        if (m_Array->count() > 0)
        {
            return m_Array->first().toInt() == p_Value;
        }
    }

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator==(double p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number == p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() == p_Value;
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator==(const QString &p_Value)
{
	if ((m_Type == Number))
	{
		return toString() == p_Value;
	}

	if ((m_Type == String))
	{
		return m_String == p_Value;
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator==(const QWDDX &p_Value)
{
    if ((m_Type == Boolean)&&(p_Value.m_Type == Boolean))
    {
        return m_Bool == p_Value.m_Bool;
    }

	if ((m_Type == Number)&&(p_Value.m_Type == Number))
	{
		return m_Number == p_Value.m_Number;
	}

	if ((m_Type == String)&&(p_Value.m_Type == String))
	{
        return *m_String == *p_Value.m_String;
	}

	if (((m_Type == Number)||(m_Type == String))&&((p_Value.m_Type == Number)||(p_Value.m_Type == String)))
	{
        QWDDX l_temp1 = *this;
        QWDDX l_temp2 = p_Value;

		return l_temp1.toString() == l_temp2.toString();
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

/*Q_DECL_EXPORT bool operator!()
{
    if ((m_Type == Boolean))
    {
        return QWDDX(!m_Bool);
    }

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}*/

Q_DECL_EXPORT QWDDX QWDDX::operator!()
{
    if ((m_Type == Boolean))
    {
        return QWDDX(!m_Bool);
    }

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

/*Q_DECL_EXPORT bool operator!(const QWDDX &operand)
{
    if ((operand.m_Type == QWDDX::Boolean))
    {
        return !operand.m_Bool;
    }

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}*/

Q_DECL_EXPORT QWDDX operator!(const QWDDX &operand)
{
    if ((operand.m_Type == QWDDX::Boolean))
    {
        return QWDDX(!operand.m_Bool);
    }

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator!=(int p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number != (double)p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() != (double)p_Value;
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator!=(double p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number != p_Value;
	}

	if ((m_Type == String))
	{
        return toNumber() != p_Value;
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator!=(const QString &p_Value)
{
	if ((m_Type == Number))
	{
		return toString() != p_Value;
	}

	if ((m_Type == String))
	{
        return *m_String != p_Value;
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator!=(const QWDDX &p_Value)
{
	if ((m_Type == Number)&&(p_Value.m_Type == Number))
	{
		return m_Number != p_Value.m_Number;
	}

	if ((m_Type == String)&&(p_Value.m_Type == String))
	{
        return *m_String != *p_Value.m_String;
	}

	if (((m_Type == Number)||(m_Type == String))&&((p_Value.m_Type == Number)||(p_Value.m_Type == String)))
	{
        QWDDX l_temp1 = *this;
        QWDDX l_temp2 = p_Value;

		return l_temp1.toString() != l_temp2.toString();
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool operator!=(int p_Value1, const QWDDX &p_Value2)
{
    return p_Value1 != p_Value2.toInt();
}

Q_DECL_EXPORT bool operator!=(double p_Value1, const QWDDX &p_Value2)
{
    return p_Value1 != p_Value2.toNumber();
}

Q_DECL_EXPORT bool operator!=(const QString &p_Value1, const QWDDX &p_Value2)
{
    return p_Value1 != p_Value2.toString();
}

Q_DECL_EXPORT bool QWDDX::operator<=(int p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number <= (double)p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() <=(double)p_Value;
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator<=(double p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number <= p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() <= p_Value;
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator<=(const QString &p_Value)
{
	if ((m_Type == Number))
	{
		return toString() <= p_Value;
	}

	if ((m_Type == String))
	{
        return *m_String <= p_Value;
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator<=(const QWDDX &p_Value)
{
	if ((m_Type == Number)&&(p_Value.m_Type == Number))
	{
		return m_Number <= p_Value.m_Number;
	}

	if ((m_Type == String)&&(p_Value.m_Type == String))
	{
        return *m_String <= *p_Value.m_String;
	}

	if (((m_Type == Number)||(m_Type == String))&&((p_Value.m_Type == Number)||(p_Value.m_Type == String)))
	{
        QWDDX l_temp1 = *this;
        QWDDX l_temp2 = p_Value;

		return l_temp1.toString() <= l_temp2.toString();
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool operator<=(int p_Value1, const QWDDX &p_Value2)
{
    return p_Value1 <= p_Value2.toInt();
}

Q_DECL_EXPORT bool operator<=(double p_Value1, const QWDDX &p_Value2)
{
    return p_Value1 <= p_Value2.toNumber();
}

Q_DECL_EXPORT bool operator<=(const QString &p_Value1, const QWDDX &p_Value2)
{
    return p_Value1 <= p_Value2.toString();
}

Q_DECL_EXPORT bool QWDDX::operator>=(int p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number >= (double)p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() >= (double)p_Value;
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator>=(double p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number >= p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() >= p_Value;
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator>=(const QString &p_Value)
{
	if ((m_Type == Number))
	{
		return toString() >= p_Value;
	}

	if ((m_Type == String))
	{
        return *m_String >= p_Value;
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator>=(const QWDDX &p_Value)
{
	if ((m_Type == Number)&&(p_Value.m_Type == Number))
	{
		return m_Number >= p_Value.m_Number;
	}

	if ((m_Type == String)&&(p_Value.m_Type == String))
	{
        return *m_String >= *p_Value.m_String;
	}

	if (((m_Type == Number)||(m_Type == String))&&((p_Value.m_Type == Number)||(p_Value.m_Type == String)))
	{
        QWDDX l_temp1 = *this;
        QWDDX l_temp2 = p_Value;

		return l_temp1.toString() >= l_temp2.toString();
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool operator>=(int p_Value1, const QWDDX &p_Value2)
{
    return p_Value1 >= p_Value2.toInt();
}

Q_DECL_EXPORT bool operator>=(double p_Value1, const QWDDX &p_Value2)
{
    return p_Value1 >= p_Value2.toNumber();
}

Q_DECL_EXPORT bool operator>=(const QString &p_Value1, const QWDDX &p_Value2)
{
    return p_Value1 >= p_Value2.toString();
}

Q_DECL_EXPORT bool QWDDX::operator<(int p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number < (double)p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() < (double)p_Value;
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator<(double p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number < p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() < p_Value;
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator<(const QString &p_Value)
{
	if ((m_Type == Number))
	{
		return toString() < p_Value;
	}

	if ((m_Type == String))
	{
        return *m_String < p_Value;
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator<(const QWDDX &p_Value)
{
	if ((m_Type == Number)&&(p_Value.m_Type == Number))
	{
		return m_Number < p_Value.m_Number;
	}

	if ((m_Type == String)&&(p_Value.m_Type == String))
	{
        return *m_String < *p_Value.m_String;
	}

	if (((m_Type == Number)||(m_Type == String))&&((p_Value.m_Type == Number)||(p_Value.m_Type == String)))
	{
        QWDDX l_temp1 = *this;
        QWDDX l_temp2 = p_Value;

		return l_temp1.toString() < l_temp2.toString();
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool operator<(int p_Value1, const QWDDX &p_Value2)
{
    return p_Value1 < p_Value2.toInt();
}

Q_DECL_EXPORT bool operator<(double p_Value1, const QWDDX &p_Value2)
{
    return p_Value1 < p_Value2.toNumber();
}

Q_DECL_EXPORT bool operator<(const QString &p_Value1, const QWDDX &p_Value2)
{
    return p_Value1 < p_Value2.toString();
}

Q_DECL_EXPORT bool QWDDX::operator>(int p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number > (double)p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() > (double)p_Value;
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator>(double p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number > p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() > p_Value;
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator>(const QString &p_Value)
{
	if ((m_Type == Number))
	{
		return toString() > p_Value;
	}

	if ((m_Type == String))
	{
        return *m_String > p_Value;
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QWDDX::operator>(const QWDDX &p_Value)
{
	if ((m_Type == Number)&&(p_Value.m_Type == Number))
	{
		return m_Number > p_Value.m_Number;
	}

	if ((m_Type == String)&&(p_Value.m_Type == String))
	{
        return *m_String > *p_Value.m_String;
	}

	if (((m_Type == Number)||(m_Type == String))&&((p_Value.m_Type == Number)||(p_Value.m_Type == String)))
	{
        QWDDX l_temp1 = *this;
        QWDDX l_temp2 = p_Value;

		return l_temp1.toString() > l_temp2.toString();
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool operator>(int p_Value1, const QWDDX &p_Value2)
{
    return p_Value1 > p_Value2.toInt();
}

Q_DECL_EXPORT bool operator>(double p_Value1, const QWDDX &p_Value2)
{
    return p_Value1 > p_Value2.toNumber();
}

Q_DECL_EXPORT bool operator>(const QString &p_Value1, const QWDDX &p_Value2)
{
    return p_Value1 > p_Value2.toString();
}

Q_DECL_EXPORT bool operator==(int p_Value1, const QWDDX &p_Value2)
{
    return p_Value1 == p_Value2.toInt();
}

/*Q_DECL_EXPORT bool operator==(const QString &p_Value1, int p_Value2)
{
    bool ok;

    int i = p_Value1.toInt(&ok);

    if (ok == false)
    {
        return false;
    }

    return i == p_Value2;
}

Q_DECL_EXPORT bool operator==(const QString &p_Value1, double p_Value2)
{
    bool ok;

    double d = p_Value1.toDouble(&ok);

    if (ok == false)
    {
        return false;
    }

    return d == p_Value2;
}*/

Q_DECL_EXPORT QWDDX &QWDDX::operator=(const bool p_newValue)
{
    setType(Boolean);
    m_Bool = p_newValue;

    return *this;
}

Q_DECL_EXPORT QWDDX &QWDDX::operator=(const int p_newValue)
{
    setType(Number);
	m_Number = p_newValue;

	return *this;
}

Q_DECL_EXPORT QWDDX &QWDDX::operator=(const double p_newValue)
{
    setType(Number);
	m_Number = p_newValue;

	return *this;
}

Q_DECL_EXPORT QWDDX &QWDDX::operator=(const char *p_newValue)
{
    qDebug() << "QWDDX::operator=(const char *p_newValue) called. to be deleted soon.";

    setType(String);
    *m_String = QString::fromLatin1(p_newValue);

    return *this;
}

Q_DECL_EXPORT QWDDX &QWDDX::operator=(const wchar_t *p_newValue)
{
    setType(String);
    *m_String = QString::fromWCharArray(p_newValue);

	return *this;
}

Q_DECL_EXPORT QWDDX &QWDDX::operator=(const QString &p_newValue)
{
    setType(String);
    *m_String = p_newValue;

	return *this;
}

Q_DECL_EXPORT QWDDX &QWDDX::operator=(const QDateTime &p_newValue)
{
    setType(DateTime);
    *m_DateTime = p_newValue;

	return *this;
}

Q_DECL_EXPORT QWDDX &QWDDX::operator=(const QWDDX &p_newValue)
{
    if (this != &p_newValue)
	{
		setType(p_newValue.type());

		switch(type())
		{
		case Null:
			break;
		case Boolean:
			m_Bool = p_newValue.m_Bool;
			break;
		case Number:
			m_Number = p_newValue.m_Number;
			break;
		case String:
			*m_String = *p_newValue.m_String;
			break;
		case DateTime:
			*m_DateTime = *p_newValue.m_DateTime;
			break;
		case Array:
			*m_Array = *p_newValue.m_Array;
			m_ArrayDimension = p_newValue.m_ArrayDimension;
			break;
		case Struct:
			*m_Struct = *p_newValue.m_Struct;
            m_HiddenScope  = p_newValue.m_HiddenScope;
			break;
		case Binary:
			*m_ByteArray = *p_newValue.m_ByteArray;
			break;
        case Query:
            *m_Struct = *p_newValue.m_Struct;
			break;
		case NotImplemented:
			break;
		case Error:
			break;
		}
	}

	return *this;
}

Q_DECL_EXPORT QWDDX QWDDX::operator+(bool p_Value)
{
    Q_UNUSED(p_Value);

    throw QMKFusionExpressionException("Illegal operation. Can\'t accumulate bool.");
}

Q_DECL_EXPORT QWDDX QWDDX::operator+(int p_Value)
{
	if (m_Type == Number)
	{
        return QWDDX(m_Number + p_Value);
	}
	else
	{
        return QWDDX(toNumber() + p_Value);
	}
}

Q_DECL_EXPORT QWDDX QWDDX::operator+(double p_Value)
{
	if (m_Type == Number)
	{
        return QWDDX(m_Number + p_Value);
	}
	else
	{
        return QWDDX(toNumber() + p_Value);
	}
}

Q_DECL_EXPORT QWDDX QWDDX::operator+(const wchar_t *p_Value)
{
	QWDDX tmp = QWDDX(p_Value);

	if (m_Type == Number)
	{
        return QWDDX(m_Number + tmp.toNumber());
	}
	else
	{
        return QWDDX(toNumber() + tmp.toNumber());
	}
}

Q_DECL_EXPORT QWDDX QWDDX::operator+(const QString &p_Value)
{
	QWDDX tmp = QWDDX(p_Value);

	if (m_Type == Number)
	{
        return QWDDX(m_Number + tmp.toNumber());
	}
	else
	{
        return QWDDX(toNumber() + tmp.toNumber());
	}
}

Q_DECL_EXPORT QWDDX QWDDX::operator+(const QWDDX &p_Value)
{
	if (m_Type == Number)
	{
        return QWDDX(m_Number + p_Value.toNumber());
	}
	else
	{
        return QWDDX(this->toNumber() + p_Value.toNumber());
	}
}

Q_DECL_EXPORT QWDDX operator+(bool p_Value1, const QWDDX &p_Value2)
{
    Q_UNUSED(p_Value1);
    Q_UNUSED(p_Value2);

    throw QMKFusionExpressionException("Illegal operation. Can\'t accumulate bool.");
}

Q_DECL_EXPORT QWDDX operator+(int p_Value1, const QWDDX &p_Value2)
{
    return QWDDX(p_Value1 + p_Value2.toNumber());
}

Q_DECL_EXPORT QWDDX operator+(double p_Value1, const QWDDX &p_Value2)
{
    return QWDDX(p_Value1 + p_Value2.toNumber());
}

Q_DECL_EXPORT QWDDX operator+(const wchar_t *p_Value1, const QWDDX &p_Value2)
{
    QWDDX tmp = QWDDX(p_Value1);

    return QWDDX(tmp.toNumber() + p_Value2.toNumber());
}

Q_DECL_EXPORT QWDDX operator+(const QString &p_Value1, const QWDDX &p_Value2)
{
    QWDDX tmp = QWDDX(p_Value1);

    return QWDDX(tmp.toNumber() + p_Value2.toNumber());
}

/*Q_DECL_EXPORT QWDDX QWDDX::operator+=(int p_Value)
{
	if (m_Type == QWDDX::Number)
	{
		m_Number += p_Value;
	}
	else
	{
		m_Number = toNumber() + p_Value;
	}

	return *this;
}*/

Q_DECL_EXPORT QWDDX QWDDX::operator++()
{
    if (type() != Number)
    {
        double tmp = toNumber();

        setType(Number);

        m_Number = tmp;
    }

    m_Number++;

    return *this;
}

Q_DECL_EXPORT QWDDX QWDDX::operator++(int tmp)
{
    QWDDX ret = *this;

    Q_UNUSED(tmp);

    if (type() != Number)
    {
        double tmp = toNumber();

        setType(Number);

        m_Number = tmp;
    }

    m_Number++;

    return ret;
}

Q_DECL_EXPORT QWDDX QWDDX::operator-(int p_Value)
{
	if (m_Type == Number)
	{
        return QWDDX(m_Number - p_Value);
	}
	else
	{
        return QWDDX(toNumber() - p_Value);
    }
}

Q_DECL_EXPORT QWDDX QWDDX::operator-(double p_Value)
{
	if (m_Type == Number)
	{
        return QWDDX(m_Number - p_Value);
	}
	else
	{
        return QWDDX(toNumber() - p_Value);
    }
}

Q_DECL_EXPORT QWDDX QWDDX::operator-(const QString &p_Value)
{
	QWDDX tmp = QWDDX(p_Value);

    return QWDDX(toNumber() - tmp.toNumber());
}

Q_DECL_EXPORT QWDDX QWDDX::operator-(const QWDDX &p_Value)
{
    return QWDDX(this->toNumber() - p_Value.toNumber());
}

Q_DECL_EXPORT QWDDX operator-(int p_Value1, const QWDDX &p_Value2)
{
    return QWDDX(p_Value1 - p_Value2.toNumber());
}

Q_DECL_EXPORT QWDDX operator-(double p_Value1, const QWDDX &p_Value2)
{
    return QWDDX(p_Value1 - p_Value2.toNumber());
}

Q_DECL_EXPORT QWDDX operator-(const QString &p_Value1, const QWDDX &p_Value2)
{
    QWDDX temp = QWDDX(p_Value1);

    return QWDDX(temp.toNumber() - p_Value2.toNumber());
}

Q_DECL_EXPORT QWDDX QWDDX::operator--()
{
    if (type() != Number)
    {
        double tmp = toNumber();

        setType(Number);

        m_Number = tmp;
    }

    m_Number--;

    return *this;
}

Q_DECL_EXPORT QWDDX QWDDX::operator--(int tmp)
{
    QWDDX ret = *this;

    Q_UNUSED(tmp);

    if (type() != Number)
    {
        double tmp = toNumber();

        setType(Number);

        m_Number = tmp;
    }

    m_Number--;

    return ret;
}

Q_DECL_EXPORT QWDDX QWDDX::operator*(int p_Value)
{
    return QWDDX(toNumber() * p_Value);
}

Q_DECL_EXPORT QWDDX QWDDX::operator*(double p_Value)
{
    return QWDDX(toNumber() * p_Value);
}

Q_DECL_EXPORT QWDDX QWDDX::operator*(const QString &p_Value)
{
	QWDDX temp = QWDDX(p_Value);

    return QWDDX(toNumber() * temp.toNumber());
}

Q_DECL_EXPORT QWDDX QWDDX::operator*(const QWDDX &p_Value)
{
	QWDDX temp = p_Value;

    return QWDDX(toNumber() * temp.toNumber());
}

Q_DECL_EXPORT QWDDX operator*(int p_Value1, const QWDDX &p_Value2)
{
	QWDDX temp = p_Value2;

    return QWDDX(p_Value1 * temp.toNumber());
}

Q_DECL_EXPORT QWDDX operator*(double p_Value1, const QWDDX &p_Value2)
{
	QWDDX temp = p_Value2;

    return QWDDX(p_Value1 * temp.toNumber());
}

Q_DECL_EXPORT QWDDX operator*(const QString &p_Value1, const QWDDX &p_Value2)
{
    QWDDX tmp = QWDDX(p_Value1);

    return QWDDX(tmp.toNumber() * p_Value2.toNumber());
}

Q_DECL_EXPORT QWDDX QWDDX::operator/(int p_Value)
{
    return QWDDX(toNumber() / p_Value);
}

Q_DECL_EXPORT QWDDX QWDDX::operator/(double p_Value)
{
    return QWDDX(toNumber() / p_Value);
}

Q_DECL_EXPORT QWDDX QWDDX::operator/(const QString &p_Value)
{
    QWDDX temp = QWDDX(p_Value);

    return QWDDX(toNumber() / temp.toNumber());
}

Q_DECL_EXPORT QWDDX QWDDX::operator/(const QWDDX &p_Value)
{
    return QWDDX(this->toNumber() / p_Value.toNumber());
}

Q_DECL_EXPORT QWDDX operator/(int p_Value1, const QWDDX &p_Value2)
{
    return QWDDX(p_Value1 / p_Value2.toNumber());
}

Q_DECL_EXPORT QWDDX operator/(double p_Value1, const QWDDX &p_Value2)
{
    return QWDDX(p_Value1 / p_Value2.toNumber());
}

Q_DECL_EXPORT QWDDX operator/(const QString &p_Value1, const QWDDX &p_Value2)
{
    QWDDX temp = QWDDX(p_Value1);

    return QWDDX(temp.toNumber() / p_Value2.toNumber());
}

Q_DECL_EXPORT double operator/(const QWDDX &p_Value1, const QWDDX &p_Value2)
{
    return p_Value1.toNumber() / p_Value2.toNumber();
}

Q_DECL_EXPORT QWDDX QWDDX::operator&(int p_Value)
{
    return QWDDX(toString() + QString::number(p_Value));
}

Q_DECL_EXPORT QWDDX QWDDX::operator&(double p_Value)
{
    return QWDDX(toString() + QString::number(p_Value));
}

Q_DECL_EXPORT QWDDX QWDDX::operator&(const wchar_t *p_Value)
{
    return QWDDX(toString() + p_Value);
}

Q_DECL_EXPORT QWDDX QWDDX::operator&(const QString &p_Value)
{
    return QWDDX(toString() + p_Value);
}

Q_DECL_EXPORT QWDDX QWDDX::operator&(const QWDDX &p_Value)
{
    return QWDDX(toString() + p_Value.toString());
}

Q_DECL_EXPORT QWDDX operator&(int p_Value1, const QWDDX &p_Value2)
{
    return QWDDX(QString::number(p_Value1) + p_Value2.toString());
}

Q_DECL_EXPORT QWDDX operator&(double p_Value1, const QWDDX &p_Value2)
{
    return QWDDX(QString::number(p_Value1) + p_Value2.toString());
}

Q_DECL_EXPORT QWDDX operator&(const QString &p_Value1, const QWDDX &p_Value2)
{
    return QWDDX(p_Value1 + p_Value2.toString());
}

Q_DECL_EXPORT QWDDX QWDDX::join(const QWDDX &p_Value)
{
    return QWDDX(toString() + p_Value.toString());
}

Q_DECL_EXPORT QString QWDDX::StructKeyAt(const int p_Index)
{
    if (m_Struct->size() <= p_Index)
    {
        return QString();
    }

    return m_Struct->keys().at(p_Index);
}

Q_DECL_EXPORT QString QWDDX::toString() const
{
	switch(m_Type)
	{
	case QWDDX::String:
		break;

	case QWDDX::Number:
		if (fabs(m_Number) >= 1000000000000.0)
		{
            QString temp;

            temp = QString::number(m_Number, 'E', 11);

            if ((temp.length() > 3)&&(temp.at(temp.length() - 3) == QChar('+')))
			{
				temp.insert(temp.length() - 2, '0');
			}

			return temp;
		}
		else
		{
            QString temp;

            temp = QString::number(fabs(m_Number), 'f', 0);
			if (temp.length() > 11)
			{
				return QString::number(m_Number, 'f', 0);
			}
			else
			{
				temp = QString::number(m_Number, 'f', 13 - temp.length());

				if (temp.indexOf('.') >= 0)
				{
					for(; ; )
					{
						if ((temp.length() == 0)||(temp[temp.length() - 1] != '0'))
						{
							break;
						}

						temp = temp.left(temp.length() - 1);
					}
				}

				if ((temp.length() > 0)&&(temp[temp.length() - 1] == '.'))
				{
					temp = temp.left(temp.length() - 1);
				}

				return temp;
			}
		}
		break;

	case QWDDX::DateTime:
        return m_DateTime->toString("MMMM, dd yyyy hh:mm:ss");
		break;

	case QWDDX::Boolean:
		if (m_Bool == true)
			return "true";
		else
			return "false";
		break;
    case QWDDX::Array:
        return m_Array->first().toString();
        break;
    case QWDDX::Null:
            return "";
        default:
			throw QMKFusionExpressionException("Complex object types cannot be converted to simple values.", "The expression has requested a variable or an intermediate expression result as a simple value, however, the result cannot be converted to a simple value. Simple values are strings, numbers, boolean values, and date/time values. Queries, arrays, and COM objects are examples of complex values. <p> The most likely cause of the error is that you are trying to use a complex value as a simple one. For example, you might be trying to use a query variable in a cfif tag.");
		break;
	}

    return *m_String;
}

Q_DECL_EXPORT QByteArray QWDDX::toBinary() const
{
    switch(m_Type)
    {
    case QWDDX::Binary:
        return *m_ByteArray;
    default:
        throw QMKFusionExpressionException("The value  cannot be converted to binary.");
    }
}

Q_DECL_EXPORT double QWDDX::toNumber() const
{
	double ret;
    int diff;
	bool ok;

	switch(m_Type)
	{
	case QWDDX::Number:
        return m_Number;
        break;
	case QWDDX::String:
        ret = m_String->toDouble(&ok);
		if (ok == false)
		{
            throw QMKFusionExpressionException("The value " + *m_String + " cannot be converted to a number.");
		}

		return ret;
		break;
    case QWDDX::DateTime:
        diff = QDateTime(QDate(1899, 12, 29), QTime(0, 0)).secsTo(*m_DateTime);
        return diff / (60 * 60 * 24);
        break;
	default:
		throw QMKFusionExpressionException("The value cannot be converted to a number.");
	}
}

Q_DECL_EXPORT int QWDDX::toInt() const
{
    int ret;
    int diff;
    bool ok;

    switch(m_Type)
    {
    case QWDDX::Number:
        return (int)m_Number;
        break;
    case QWDDX::String:
        ret = m_String->toInt(&ok);
        if (ok == false)
        {
            throw QMKFusionExpressionException("The value [" + *m_String + "] cannot be converted to a int.");
        }

        return ret;
        break;
    case QWDDX::DateTime:
        diff = QDateTime(QDate(1899, 12, 29), QTime(0, 0)).secsTo(*m_DateTime);
        return diff / (60 * 60 * 24);
        break;
    default:
        throw QMKFusionExpressionException("The value cannot be converted to a int.");
    }
}

Q_DECL_EXPORT bool QWDDX::canConvertToNumber()
{
	if (m_Type == Number)
	{
		return true;
	}

	if (m_Type == String)
	{
        if (m_String->isEmpty())
		{
			return false;
		}

		bool ok;
        m_String->toDouble(&ok);

		return ok;
	}

	return false;
}

Q_DECL_EXPORT QDateTime QWDDX::toDateTime() const
{
    if (m_Type == QWDDX::DateTime)
    {
        return *m_DateTime;
    }

    if (m_Type == QWDDX::String)
    {
        QDateTime dateTime = QDateTime::fromString(*m_String, Qt::ISODate);

        if (dateTime.isValid())
        {
            return dateTime;
        }
    }

    throw QMKFusionExpressionException("The value cannot be converted to a datetime.");
}

Q_DECL_EXPORT bool QWDDX::toBool() const
{
	switch(m_Type)
	{
		case QWDDX::Boolean:
			return m_Bool;
		case QWDDX::String:
            if (m_String->compare("true", Qt::CaseInsensitive) == 0)
			{
				return true;
			}
            else if (m_String->compare("false", Qt::CaseInsensitive) == 0)
			{
				return false;
			}
			else
			{
                return toInt() != 0;
			}

			break;
		case QWDDX::Number:
			if (m_Number == 0)
			{
				return false;
			}
			else
			{
				return true;
			}
			break;
		default:;
	}
	throw QMKFusionExpressionException("The value cannot be converted to a boolean.");
}
