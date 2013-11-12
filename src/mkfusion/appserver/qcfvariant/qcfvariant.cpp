#include "qcfvariant.h"
#include "qcfvariantcomponent.h"
#include "qcfvariantfunction.h"
#include "qmkfusionexception.h"

#include <QDebug>
#include <math.h>


Q_DECL_EXPORT QCFVariant::QCFVariant()
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(nullptr)
    , m_ByteArray(nullptr)
    , m_Number(0)
	, m_Bool(false)
    , m_DateTime(nullptr)
    , m_Component(nullptr)
    , m_Function(nullptr)
	, m_Type(Null)
    , m_ArrayDimension(1)
    , m_HiddenScopeFirst(nullptr)
    , m_HiddenScopeLast1(nullptr)
    , m_HiddenScopeLast2(nullptr)
{
}

Q_DECL_EXPORT QCFVariant::~QCFVariant()
{
    setType(Null);
    m_HiddenScopeFirst = nullptr;
    m_HiddenScopeLast1 = nullptr;
    m_HiddenScopeLast2 = nullptr;
}

Q_DECL_EXPORT QCFVariant::QCFVariant(bool value)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(nullptr)
    , m_ByteArray(nullptr)
    , m_Number(0)
    , m_Bool(value)
    , m_DateTime(nullptr)
    , m_Component(nullptr)
    , m_Function(nullptr)
	, m_Type(Boolean)
    , m_ArrayDimension(1)
    , m_HiddenScopeFirst(nullptr)
    , m_HiddenScopeLast1(nullptr)
    , m_HiddenScopeLast2(nullptr)
{
}

Q_DECL_EXPORT QCFVariant::QCFVariant(int value)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(nullptr)
    , m_ByteArray(nullptr)
    , m_Number(value)
	, m_Bool(false)
    , m_DateTime(nullptr)
    , m_Component(nullptr)
    , m_Function(nullptr)
	, m_Type(Number)
    , m_ArrayDimension(1)
    , m_HiddenScopeFirst(nullptr)
    , m_HiddenScopeLast1(nullptr)
    , m_HiddenScopeLast2(nullptr)
{
}

Q_DECL_EXPORT QCFVariant::QCFVariant(double value)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(nullptr)
    , m_ByteArray(nullptr)
    , m_Number(value)
	, m_Bool(false)
    , m_DateTime(nullptr)
    , m_Component(nullptr)
    , m_Function(nullptr)
	, m_Type(Number)
    , m_ArrayDimension(1)
    , m_HiddenScopeFirst(nullptr)
    , m_HiddenScopeLast1(nullptr)
    , m_HiddenScopeLast2(nullptr)
{
}

Q_DECL_EXPORT QCFVariant::QCFVariant(const char *value)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(new QString(value))
    , m_ByteArray(nullptr)
	, m_Number(0)
	, m_Bool(false)
    , m_DateTime(nullptr)
    , m_Component(nullptr)
    , m_Function(nullptr)
	, m_Type(String)
    , m_ArrayDimension(1)
    , m_HiddenScopeFirst(nullptr)
    , m_HiddenScopeLast1(nullptr)
    , m_HiddenScopeLast2(nullptr)
{
    qDebug() << "QCFVariant::QCFVariant(const char *value) called. to be deleted soon.";
}

Q_DECL_EXPORT QCFVariant::QCFVariant(const wchar_t *value)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(new QString(QString::fromWCharArray(value)))
    , m_ByteArray(nullptr)
	, m_Number(0)
	, m_Bool(false)
    , m_DateTime(nullptr)
    , m_Component(nullptr)
    , m_Function(nullptr)
	, m_Type(String)
    , m_ArrayDimension(1)
    , m_HiddenScopeFirst(nullptr)
    , m_HiddenScopeLast1(nullptr)
    , m_HiddenScopeLast2(nullptr)
{
}

Q_DECL_EXPORT QCFVariant::QCFVariant(const QString &value)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(new QString(value))
    , m_ByteArray(nullptr)
	, m_Number(0)
	, m_Bool(false)
    , m_DateTime(nullptr)
    , m_Component(nullptr)
    , m_Function(nullptr)
	, m_Type(String)
    , m_ArrayDimension(1)
    , m_HiddenScopeFirst(nullptr)
    , m_HiddenScopeLast1(nullptr)
    , m_HiddenScopeLast2(nullptr)
{
}

Q_DECL_EXPORT QCFVariant::QCFVariant(const QDateTime &value)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(nullptr)
    , m_ByteArray(nullptr)
	, m_Number(0)
	, m_Bool(false)
    , m_DateTime(new QDateTime(value))
    , m_Component(nullptr)
    , m_Function(nullptr)
	, m_Type(DateTime)
    , m_ArrayDimension(1)
    , m_HiddenScopeFirst(nullptr)
    , m_HiddenScopeLast1(nullptr)
    , m_HiddenScopeLast2(nullptr)
{
}

Q_DECL_EXPORT QCFVariant::QCFVariant(const QCFVariantComponent &value)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(nullptr)
    , m_ByteArray(nullptr)
    , m_Number(0)
    , m_Bool(false)
    , m_DateTime(nullptr)
    , m_Component(new QCFVariantComponent(value))
    , m_Function(nullptr)
    , m_Type(Component)
    , m_ArrayDimension(1)
    , m_HiddenScopeFirst(nullptr)
    , m_HiddenScopeLast1(nullptr)
    , m_HiddenScopeLast2(nullptr)
{
}

Q_DECL_EXPORT QCFVariant::QCFVariant(const QCFVariantFunction &value)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(nullptr)
    , m_ByteArray(nullptr)
    , m_Number(0)
    , m_Bool(false)
    , m_DateTime(nullptr)
    , m_Component(nullptr)
    , m_Function(new QCFVariantFunction(value))
    , m_Type(Function)
    , m_ArrayDimension(1)
    , m_HiddenScopeFirst(nullptr)
    , m_HiddenScopeLast1(nullptr)
    , m_HiddenScopeLast2(nullptr)
{
}

Q_DECL_EXPORT QCFVariant::QCFVariant(const QCFVariant &other)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(nullptr)
    , m_ByteArray(nullptr)
    , m_Number(0)
    , m_Bool(false)
    , m_DateTime(nullptr)
    , m_Component(nullptr)
    , m_Function(nullptr)
    , m_Type(other.m_Type)
    , m_ArrayDimension(1)
    , m_HiddenScopeFirst(nullptr)
    , m_HiddenScopeLast1(nullptr)
    , m_HiddenScopeLast2(nullptr)
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
    case Component:
        m_Component = new QCFVariantComponent(*other.m_Component);
        break;
    case Function:
        m_Function = new QCFVariantFunction(*other.m_Function);
        break;
    case Array:
        m_Array = new QVector<QCFVariant>();
        *m_Array = *other.m_Array;
        m_ArrayDimension = other.m_ArrayDimension;
        m_Number = other.m_Number;
        break;
    case Struct:
        m_Struct = new QMap<QString, QCFVariant>();
        *m_Struct = *other.m_Struct;
        m_HiddenScopeFirst = other.m_HiddenScopeFirst;
        m_HiddenScopeLast1 = other.m_HiddenScopeLast1;
        m_HiddenScopeLast2 = other.m_HiddenScopeLast2;
        break;
    case Binary:
        m_ByteArray = new QByteArray();
        *m_ByteArray = *other.m_ByteArray;
        break;
    case Query:
        m_Struct = new QMap<QString, QCFVariant>();
        *m_Struct = *other.m_Struct;
        break;
    case NotImplemented:
        break;
    case Error:
        break;
    }
}

Q_DECL_EXPORT QCFVariant::QCFVariant(const QCFVariantType type)
    : m_Array(nullptr)
    , m_Struct(nullptr)
    , m_String(nullptr)
    , m_ByteArray(nullptr)
	, m_Number(0)
	, m_Bool(false)
    , m_DateTime(nullptr)
    , m_Component(nullptr)
    , m_Type(Null)
    , m_ArrayDimension(1)
    , m_HiddenScopeFirst(nullptr)
    , m_HiddenScopeLast1(nullptr)
    , m_HiddenScopeLast2(nullptr)
{
    setType(type);
}

#ifdef Q_COMPILER_RVALUE_REFS
Q_DECL_EXPORT QCFVariant &QCFVariant::operator=(QCFVariant &&other)
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
    case Component:
        qSwap(m_Component, other.m_Component);
    case Function:
        qSwap(m_Function, other.m_Function);
    case Array:
        qSwap(m_Array, other.m_Array);
        qSwap(m_ArrayDimension, other.m_ArrayDimension);
        qSwap(m_Number, other.m_Number);
        break;
    case Struct:
        qSwap(m_Struct, other.m_Struct);
        qSwap(m_HiddenScopeFirst, other.m_HiddenScopeFirst);
        qSwap(m_HiddenScopeLast1, other.m_HiddenScopeLast1);
        qSwap(m_HiddenScopeLast2, other.m_HiddenScopeLast2);
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

Q_DECL_EXPORT void QCFVariant::setType(QCFVariantType type)
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
        m_HiddenScopeFirst = nullptr;
        m_HiddenScopeLast1 = nullptr;
        m_HiddenScopeLast2 = nullptr;
        break;
    case Binary:
        delete m_ByteArray;
        m_ByteArray = nullptr;
        break;
    case Query:
        delete m_Struct;
        m_Struct = nullptr;
        break;
    case Component:
        delete m_Component;
        m_Component = nullptr;
    case Function:
        delete m_Function;
        m_Function = nullptr;
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
        m_Array = new QVector<QCFVariant>();
        m_ArrayDimension = 1;
        break;
    case Struct:
        m_Struct = new QMap<QString, QCFVariant>();
        break;
    case Binary:
        m_ByteArray = new QByteArray;
        break;
    case Query:
        m_Struct = new QMap<QString, QCFVariant>();
        break;
    case Component:
        m_Component = new QCFVariantComponent();
    case Function:
        m_Function = new QCFVariantFunction();
    case NotImplemented:
        break;
    case Error:
        break;
    default:
        break;
    }
}

Q_DECL_EXPORT QCFVariant::QCFVariantType QCFVariant::type() const
{
	return m_Type;
}

Q_DECL_EXPORT QCFVariant::operator bool()
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

Q_DECL_EXPORT QCFVariant::operator int()
{
	return (int)toNumber();
}

Q_DECL_EXPORT QCFVariant::operator double()
{
	return toNumber();
}

Q_DECL_EXPORT QCFVariant::operator QString()
{
	return toString();
}

Q_DECL_EXPORT QCFVariant::operator QDateTime()
{
	return toDateTime();
}

Q_DECL_EXPORT int QCFVariant::size()
{
	switch(m_Type)
	{
    case QCFVariant::Array:
        return m_Array->size();
    case QCFVariant::Struct:
        return m_Struct->size();
	default:
		return 1;
	}
}

Q_DECL_EXPORT QCFVariant &QCFVariant::operator[](const double index)
{
    if ((m_Type != QCFVariant::Struct)&&(m_Type != QCFVariant::Array)&&(m_Type != QCFVariant::Query))
	{
        throw QMKFusionExpressionException("You have attempted to dereference a scalar variable of type class java.lang.String as a structure with members.");
	}

    if (m_Type == QCFVariant::Array)
	{
        if ((int)index < 1)
		{
            throw QMKFusionExpressionException("The element at position " + QString::number((int)index) + " of array variable \"xxx\" cannot be found.");
		}

        if (m_Array->size() < (int)index)
		{
            m_Array->resize((int)index);
		}

        return (*m_Array)[(int)index - 1];
	}
	else
	{
        QString key = QString::number(index);

        if (m_HiddenScopeFirst)
        {
            if (m_HiddenScopeFirst->m_Struct->contains(key))
            {
                return (*m_HiddenScopeFirst->m_Struct)[key];
            }
        }

        if (m_Struct->contains(key) == false)
		{
            if (m_HiddenScopeLast1)
            {
                if (m_HiddenScopeLast1->m_Struct->contains(key))
                {
                    return (*m_HiddenScopeLast1->m_Struct)[key];
                }

                if (m_HiddenScopeLast2)
                {
                    if (m_HiddenScopeLast2->m_Struct->contains(key))
                    {
                        return (*m_HiddenScopeLast2->m_Struct)[key];
                    }
                }
            }

            m_Struct->insert(key, QCFVariant(QCFVariant::Null));
		}

        return (*m_Struct)[key];
	}
}

Q_DECL_EXPORT QCFVariant &QCFVariant::operator[](const QString &key)
{
    if ((m_Type != QCFVariant::Struct)&&(m_Type != QCFVariant::Array)&&(m_Type != QCFVariant::Query))
	{
        throw QMKFusionExpressionException("You have attempted to dereference a scalar variable of type class \'QString\' as a structure with members.");
	}

    if (m_Type == QCFVariant::Struct)
	{
        if (m_HiddenScopeFirst)
        {
            if (m_HiddenScopeFirst->m_Struct->contains(key))
            {
                return (*m_HiddenScopeFirst->m_Struct)[key];
            }
        }

        if (m_Struct->contains(key) == false)
		{
            if (m_HiddenScopeLast1)
            {
                if (m_HiddenScopeLast1->m_Struct->contains(key))
                {
                    return (*m_HiddenScopeLast1->m_Struct)[key];
                }

                if (m_HiddenScopeLast2)
                {
                    if (m_HiddenScopeLast2->m_Struct->contains(key))
                    {
                        return (*m_HiddenScopeLast2->m_Struct)[key];
                    }
                }
            }

            throw QMKFusionException(QString("Variable %1 is undefined.").arg(key));
		}

        return (*m_Struct)[key];
	}
    else if (m_Type == QCFVariant::Query)
    {
        if (!m_Struct->contains(key))
        {
            if ((*this)[L"RESULTSET"].m_Struct->contains(key))
            {
                (*this)[L"RESULTSET"][key].m_Number = (*this)[L"CURRENTROW"];
                return (*this)[L"RESULTSET"][key];
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

Q_DECL_EXPORT QCFVariant &QCFVariant::operator[](const char *key)
{
    qDebug() << "QCFVariant::operator[](const char *key) called. to be deleted soon.";

    if ((m_Type != QCFVariant::Struct)&&(m_Type != QCFVariant::Array)&&(m_Type != QCFVariant::Query))
	{
		throw QMKFusionExpressionException("You have attempted to dereference a scalar variable of type class wchar_t* as a structure with members.");
	}

    QString l_key = QString::fromLatin1(key);

    if (m_Type == QCFVariant::Struct)
	{
        if (m_HiddenScopeFirst)
        {
            if (m_HiddenScopeFirst->m_Struct->contains(key))
            {
                return (*m_HiddenScopeFirst->m_Struct)[key];
            }
        }

        if (m_Struct->contains(l_key) == false)
		{
            if (m_HiddenScopeLast1)
            {
                if (m_HiddenScopeLast1->m_Struct->contains(key))
                {
                    return (*m_HiddenScopeLast1->m_Struct)[key];
                }

                if (m_HiddenScopeLast2)
                {
                    if (m_HiddenScopeLast2->m_Struct->contains(key))
                    {
                        return (*m_HiddenScopeLast2->m_Struct)[key];
                    }
                }
            }

            throw QMKFusionException(QString("Variable %1 is undefined.").arg(l_key));
		}

        return (*m_Struct)[l_key];
	}
    else if (m_Type == QCFVariant::Query)
    {
        if (!m_Struct->contains(l_key))
        {
            if ((*this)[L"RESULTSET"].m_Struct->contains(l_key))
            {
                (*this)[L"RESULTSET"][l_key].m_Number = (*this)[L"CURRENTROW"];
                return (*this)[L"RESULTSET"][l_key];
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

Q_DECL_EXPORT QCFVariant &QCFVariant::operator[](const wchar_t *key)
{
    QString l_key;
    qint32 val;
    bool ok;

    switch(m_Type)
    {
    case QCFVariant::Struct:
        l_key = QString::fromStdWString(key).toUpper();

        if (m_HiddenScopeFirst)
        {
            if (m_HiddenScopeFirst->m_Struct->contains(l_key))
            {
                return (*m_HiddenScopeFirst->m_Struct)[l_key];
            }
        }

        if (m_Struct->contains(l_key) == false)
        {
            if (m_HiddenScopeLast1)
            {
                if (m_HiddenScopeLast1->m_Struct->contains(l_key))
                {
                    return (*m_HiddenScopeLast1->m_Struct)[l_key];
                }

                if (m_HiddenScopeLast2)
                {
                    if (m_HiddenScopeLast2->m_Struct->contains(l_key))
                    {
                        return (*m_HiddenScopeLast2->m_Struct)[l_key];
                    }
                }
            }

            throw QMKFusionException(QString("Variable %1 is undefined.").arg(l_key));
        }

        return (*m_Struct)[l_key];
        break;
    case QCFVariant::Query:
        l_key = QString::fromStdWString(key).toUpper();

        if (!m_Struct->contains(l_key))
        {
            if ((*this)[L"RESULTSET"].m_Struct->contains(l_key))
            {
                (*this)[L"RESULTSET"][l_key].m_Number = (*this)[L"CURRENTROW"];
                return (*this)[L"RESULTSET"][l_key];
            }

            throw QMKFusionException(QString("Variable %1 is undefined.").arg(l_key));
        }

        return (*m_Struct)[l_key];
        break;
    case QCFVariant::Array:
        l_key = QString::fromStdWString(key).toUpper();

        val = (qint32)l_key.toDouble(&ok);
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
        break;
    default:
        throw QMKFusionExpressionException("You have attempted to dereference a scalar variable of type class wchar_t* as a structure with members.");
        break;
    }
}

Q_DECL_EXPORT QCFVariant &QCFVariant::operator[](const QCFVariant &key)
{
    QString l_keyStr;
    int l_keyInt;

    switch(m_Type)
    {
    case QCFVariant::Struct:
        l_keyStr = key.toString();

        if (m_HiddenScopeFirst)
        {
            if (m_HiddenScopeFirst->m_Struct->contains(l_keyStr))
            {
                return (*m_HiddenScopeFirst->m_Struct)[l_keyStr];
            }
        }

        if (m_Struct->contains(l_keyStr) == false)
        {
            if (m_HiddenScopeLast1)
            {
                if (m_HiddenScopeLast1->m_Struct->contains(l_keyStr))
                {
                    return (*m_HiddenScopeLast1->m_Struct)[l_keyStr];
                }

                if (m_HiddenScopeLast2)
                {
                    if (m_HiddenScopeLast2->m_Struct->contains(l_keyStr))
                    {
                        return (*m_HiddenScopeLast2->m_Struct)[l_keyStr];
                    }
                }
            }

            throw QMKFusionException(QString("Variable %1 is undefined.").arg(l_keyStr));
        }

        return (*m_Struct)[l_keyStr];
        break;
    case QCFVariant::Query:
        l_keyStr = key.toString();

        if (!m_Struct->contains(l_keyStr))
        {
            if ((*this)[L"RESULTSET"].m_Struct->contains(l_keyStr))
            {
                (*this)[L"RESULTSET"][l_keyStr].m_Number = (*this)[L"CURRENTROW"];
                return (*this)[L"RESULTSET"][l_keyStr];
            }

            throw QMKFusionException(QString("Variable %1 is undefined.").arg(l_keyStr));
        }

        return (*m_Struct)[l_keyStr];
        break;
    case QCFVariant::Array:
        l_keyInt = (int)key.toNumber();

        if (l_keyInt < 1)
        {
            throw QMKFusionExpressionException("The element at position " + QString::number(l_keyInt) + " of array variable \"xxx\" cannot be found.");
        }

        if (m_Array->size() < l_keyInt)
        {
            m_Array->resize(l_keyInt);
        }

        if (((*m_Array)[l_keyInt - 1].m_Type != QCFVariant::Array)&&(m_ArrayDimension > 1))
        {
            (*m_Array)[l_keyInt - 1] = QCFVariant(QCFVariant::Array);
            (*m_Array)[l_keyInt - 1].m_ArrayDimension = m_ArrayDimension - 1;
        }

        return (*m_Array)[l_keyInt - 1];
        break;
    default:
        throw QMKFusionExpressionException("You have attempted to dereference a scalar variable of type class java.lang.String as a structure with members.");
        break;
    }
}

Q_DECL_EXPORT bool QCFVariant::operator==(bool p_Value)
{
    if ((m_Type == Boolean))
    {
        return m_Bool == p_Value;
    }

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QCFVariant::operator==(int p_Value)
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

Q_DECL_EXPORT bool QCFVariant::operator==(double p_Value)
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

Q_DECL_EXPORT bool QCFVariant::operator==(const QString &p_Value)
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

Q_DECL_EXPORT bool QCFVariant::operator==(const QCFVariant &p_Value)
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
        QCFVariant l_temp1 = *this;
        QCFVariant l_temp2 = p_Value;

        return l_temp1.toNumber() == l_temp2.toNumber();
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

/*Q_DECL_EXPORT bool operator!()
{
    if ((m_Type == Boolean))
    {
        return QCFVariant(!m_Bool);
    }

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}*/

Q_DECL_EXPORT QCFVariant QCFVariant::operator!()
{
    return QCFVariant(!toBool());
}

/*Q_DECL_EXPORT bool operator!(const QCFVariant &operand)
{
    if ((operand.m_Type == QCFVariant::Boolean))
    {
        return !operand.m_Bool;
    }

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}*/

Q_DECL_EXPORT QCFVariant operator!(const QCFVariant &operand)
{
    if ((operand.m_Type == QCFVariant::Boolean))
    {
        return QCFVariant(!operand.m_Bool);
    }

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool QCFVariant::operator!=(int p_Value)
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

Q_DECL_EXPORT bool QCFVariant::operator!=(double p_Value)
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

Q_DECL_EXPORT bool QCFVariant::operator!=(const QString &p_Value)
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

Q_DECL_EXPORT bool QCFVariant::operator!=(const QCFVariant &p_Value)
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
        QCFVariant l_temp1 = *this;
        QCFVariant l_temp2 = p_Value;

        return l_temp1.toNumber() != l_temp2.toNumber();
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool operator!=(int p_Value1, const QCFVariant &p_Value2)
{
    return p_Value1 != p_Value2.toInt();
}

Q_DECL_EXPORT bool operator!=(double p_Value1, const QCFVariant &p_Value2)
{
    return p_Value1 != p_Value2.toNumber();
}

Q_DECL_EXPORT bool operator!=(const QString &p_Value1, const QCFVariant &p_Value2)
{
    return p_Value1 != p_Value2.toString();
}

Q_DECL_EXPORT bool QCFVariant::operator<=(int p_Value)
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

Q_DECL_EXPORT bool QCFVariant::operator<=(double p_Value)
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

Q_DECL_EXPORT bool QCFVariant::operator<=(const QString &p_Value)
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

Q_DECL_EXPORT bool QCFVariant::operator<=(const QCFVariant &p_Value)
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
        QCFVariant l_temp1 = *this;
        QCFVariant l_temp2 = p_Value;

        return l_temp1.toNumber() <= l_temp2.toNumber();
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool operator<=(int p_Value1, const QCFVariant &p_Value2)
{
    return p_Value1 <= p_Value2.toInt();
}

Q_DECL_EXPORT bool operator<=(double p_Value1, const QCFVariant &p_Value2)
{
    return p_Value1 <= p_Value2.toNumber();
}

Q_DECL_EXPORT bool operator<=(const QString &p_Value1, const QCFVariant &p_Value2)
{
    return p_Value1 <= p_Value2.toString();
}

Q_DECL_EXPORT bool QCFVariant::operator>=(int p_Value)
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

Q_DECL_EXPORT bool QCFVariant::operator>=(double p_Value)
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

Q_DECL_EXPORT bool QCFVariant::operator>=(const QString &p_Value)
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

Q_DECL_EXPORT bool QCFVariant::operator>=(const QCFVariant &p_Value)
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
        QCFVariant l_temp1 = *this;
        QCFVariant l_temp2 = p_Value;

        return l_temp1.toNumber() >= l_temp2.toNumber();
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool operator>=(int p_Value1, const QCFVariant &p_Value2)
{
    return p_Value1 >= p_Value2.toInt();
}

Q_DECL_EXPORT bool operator>=(double p_Value1, const QCFVariant &p_Value2)
{
    return p_Value1 >= p_Value2.toNumber();
}

Q_DECL_EXPORT bool operator>=(const QString &p_Value1, const QCFVariant &p_Value2)
{
    return p_Value1 >= p_Value2.toString();
}

Q_DECL_EXPORT bool QCFVariant::operator<(int p_Value)
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

Q_DECL_EXPORT bool QCFVariant::operator<(double p_Value)
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

Q_DECL_EXPORT bool QCFVariant::operator<(const QString &p_Value)
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

Q_DECL_EXPORT bool QCFVariant::operator<(const QCFVariant &p_Value)
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
        QCFVariant l_temp1 = *this;
        QCFVariant l_temp2 = p_Value;

        return l_temp1.toNumber() < l_temp2.toNumber();
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool operator<(int p_Value1, const QCFVariant &p_Value2)
{
    return p_Value1 < p_Value2.toInt();
}

Q_DECL_EXPORT bool operator<(double p_Value1, const QCFVariant &p_Value2)
{
    return p_Value1 < p_Value2.toNumber();
}

Q_DECL_EXPORT bool operator<(const QString &p_Value1, const QCFVariant &p_Value2)
{
    return p_Value1 < p_Value2.toString();
}

Q_DECL_EXPORT bool QCFVariant::operator>(int p_Value)
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

Q_DECL_EXPORT bool QCFVariant::operator>(double p_Value)
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

Q_DECL_EXPORT bool QCFVariant::operator>(const QString &p_Value)
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

Q_DECL_EXPORT bool QCFVariant::operator>(const QCFVariant &p_Value)
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
        QCFVariant l_temp1 = *this;
        QCFVariant l_temp2 = p_Value;

        return l_temp1.toNumber() > l_temp2.toNumber();
	}

    throw QMKFusionExpressionException(QString("Unsupported compare(%1).").arg(__PRETTY_FUNCTION__));
}

Q_DECL_EXPORT bool operator>(int p_Value1, const QCFVariant &p_Value2)
{
    return p_Value1 > p_Value2.toInt();
}

Q_DECL_EXPORT bool operator>(double p_Value1, const QCFVariant &p_Value2)
{
    return p_Value1 > p_Value2.toNumber();
}

Q_DECL_EXPORT bool operator>(const QString &p_Value1, const QCFVariant &p_Value2)
{
    return p_Value1 > p_Value2.toString();
}

Q_DECL_EXPORT bool operator==(int p_Value1, const QCFVariant &p_Value2)
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

Q_DECL_EXPORT QCFVariant &QCFVariant::operator=(const bool p_newValue)
{
    setType(Boolean);
    m_Bool = p_newValue;

    return *this;
}

Q_DECL_EXPORT QCFVariant &QCFVariant::operator=(const int p_newValue)
{
    setType(Number);
	m_Number = p_newValue;

	return *this;
}

Q_DECL_EXPORT QCFVariant &QCFVariant::operator=(const double p_newValue)
{
    setType(Number);
	m_Number = p_newValue;

	return *this;
}

Q_DECL_EXPORT QCFVariant &QCFVariant::operator=(const char *p_newValue)
{
    qDebug() << "QCFVariant::operator=(const char *p_newValue) called. to be deleted soon.";

    setType(String);
    *m_String = QString::fromLatin1(p_newValue);

    return *this;
}

Q_DECL_EXPORT QCFVariant &QCFVariant::operator=(const wchar_t *p_newValue)
{
    setType(String);
    *m_String = QString::fromWCharArray(p_newValue);

	return *this;
}

Q_DECL_EXPORT QCFVariant &QCFVariant::operator=(const QString &p_newValue)
{
    setType(String);
    *m_String = p_newValue;

	return *this;
}

Q_DECL_EXPORT QCFVariant &QCFVariant::operator=(const QDateTime &p_newValue)
{
    setType(DateTime);
    *m_DateTime = p_newValue;

	return *this;
}

Q_DECL_EXPORT QCFVariant &QCFVariant::operator=(const QCFVariantComponent &p_newValue)
{
    setType(Component);
    *m_Component = p_newValue;

    return *this;
}

Q_DECL_EXPORT QCFVariant &QCFVariant::operator=(const QCFVariantFunction &p_newValue)
{
    setType(Function);
    *m_Function = p_newValue;

    return *this;
}

Q_DECL_EXPORT QCFVariant &QCFVariant::operator=(const QCFVariant &p_newValue)
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
        case Component:
            *m_Component = *p_newValue.m_Component;
            break;
        case Function:
            *m_Function = *p_newValue.m_Function;
            break;
        case Array:
			*m_Array = *p_newValue.m_Array;
			m_ArrayDimension = p_newValue.m_ArrayDimension;
            m_Number = p_newValue.m_Number;
			break;
		case Struct:
			*m_Struct = *p_newValue.m_Struct;
            m_HiddenScopeFirst = p_newValue.m_HiddenScopeFirst;
            m_HiddenScopeLast1 = p_newValue.m_HiddenScopeLast1;
            m_HiddenScopeLast2 = p_newValue.m_HiddenScopeLast2;
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

Q_DECL_EXPORT QCFVariant QCFVariant::operator+(bool p_Value)
{
    Q_UNUSED(p_Value);

    throw QMKFusionExpressionException("Illegal operation. Can\'t accumulate bool.");
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator+(int p_Value)
{
	if (m_Type == Number)
	{
        return QCFVariant(m_Number + p_Value);
	}
	else
	{
        return QCFVariant(toNumber() + p_Value);
	}
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator+(double p_Value)
{
	if (m_Type == Number)
	{
        return QCFVariant(m_Number + p_Value);
	}
	else
	{
        return QCFVariant(toNumber() + p_Value);
	}
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator+(const wchar_t *p_Value)
{
    QCFVariant tmp = QCFVariant(p_Value);

	if (m_Type == Number)
	{
        return QCFVariant(m_Number + tmp.toNumber());
	}
	else
	{
        return QCFVariant(toNumber() + tmp.toNumber());
	}
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator+(const QString &p_Value)
{
    QCFVariant tmp = QCFVariant(p_Value);

	if (m_Type == Number)
	{
        return QCFVariant(m_Number + tmp.toNumber());
	}
	else
	{
        return QCFVariant(toNumber() + tmp.toNumber());
	}
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator+(const QCFVariant &p_Value)
{
	if (m_Type == Number)
	{
        return QCFVariant(m_Number + p_Value.toNumber());
	}
	else
	{
        return QCFVariant(this->toNumber() + p_Value.toNumber());
	}
}

Q_DECL_EXPORT QCFVariant operator+(bool p_Value1, const QCFVariant &p_Value2)
{
    Q_UNUSED(p_Value1);
    Q_UNUSED(p_Value2);

    throw QMKFusionExpressionException("Illegal operation. Can\'t accumulate bool.");
}

Q_DECL_EXPORT QCFVariant operator+(int p_Value1, const QCFVariant &p_Value2)
{
    return QCFVariant(p_Value1 + p_Value2.toNumber());
}

Q_DECL_EXPORT QCFVariant operator+(double p_Value1, const QCFVariant &p_Value2)
{
    return QCFVariant(p_Value1 + p_Value2.toNumber());
}

Q_DECL_EXPORT QCFVariant operator+(const wchar_t *p_Value1, const QCFVariant &p_Value2)
{
    QCFVariant tmp = QCFVariant(p_Value1);

    return QCFVariant(tmp.toNumber() + p_Value2.toNumber());
}

Q_DECL_EXPORT QCFVariant operator+(const QString &p_Value1, const QCFVariant &p_Value2)
{
    QCFVariant tmp = QCFVariant(p_Value1);

    return QCFVariant(tmp.toNumber() + p_Value2.toNumber());
}

/*Q_DECL_EXPORT QCFVariant QCFVariant::operator+=(int p_Value)
{
    if (m_Type == QCFVariant::Number)
	{
		m_Number += p_Value;
	}
	else
	{
		m_Number = toNumber() + p_Value;
	}

	return *this;
}*/

Q_DECL_EXPORT QCFVariant QCFVariant::operator++()
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

Q_DECL_EXPORT QCFVariant QCFVariant::operator++(int tmp)
{
    QCFVariant ret = *this;

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

Q_DECL_EXPORT QCFVariant QCFVariant::operator-(int p_Value)
{
	if (m_Type == Number)
	{
        return QCFVariant(m_Number - p_Value);
	}
	else
	{
        return QCFVariant(toNumber() - p_Value);
    }
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator-(double p_Value)
{
	if (m_Type == Number)
	{
        return QCFVariant(m_Number - p_Value);
	}
	else
	{
        return QCFVariant(toNumber() - p_Value);
    }
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator-(const QString &p_Value)
{
    QCFVariant tmp = QCFVariant(p_Value);

    return QCFVariant(toNumber() - tmp.toNumber());
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator-(const QCFVariant &p_Value)
{
    return QCFVariant(this->toNumber() - p_Value.toNumber());
}

Q_DECL_EXPORT QCFVariant operator-(int p_Value1, const QCFVariant &p_Value2)
{
    return QCFVariant(p_Value1 - p_Value2.toNumber());
}

Q_DECL_EXPORT QCFVariant operator-(double p_Value1, const QCFVariant &p_Value2)
{
    return QCFVariant(p_Value1 - p_Value2.toNumber());
}

Q_DECL_EXPORT QCFVariant operator-(const QString &p_Value1, const QCFVariant &p_Value2)
{
    QCFVariant temp = QCFVariant(p_Value1);

    return QCFVariant(temp.toNumber() - p_Value2.toNumber());
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator--()
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

Q_DECL_EXPORT QCFVariant QCFVariant::operator--(int tmp)
{
    QCFVariant ret = *this;

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

Q_DECL_EXPORT QCFVariant QCFVariant::operator*(int p_Value)
{
    return QCFVariant(toNumber() * p_Value);
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator*(double p_Value)
{
    return QCFVariant(toNumber() * p_Value);
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator*(const QString &p_Value)
{
    QCFVariant temp = QCFVariant(p_Value);

    return QCFVariant(toNumber() * temp.toNumber());
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator*(const QCFVariant &p_Value)
{
    QCFVariant temp = p_Value;

    return QCFVariant(toNumber() * temp.toNumber());
}

Q_DECL_EXPORT QCFVariant operator*(int p_Value1, const QCFVariant &p_Value2)
{
    QCFVariant temp = p_Value2;

    return QCFVariant(p_Value1 * temp.toNumber());
}

Q_DECL_EXPORT QCFVariant operator*(double p_Value1, const QCFVariant &p_Value2)
{
    QCFVariant temp = p_Value2;

    return QCFVariant(p_Value1 * temp.toNumber());
}

Q_DECL_EXPORT QCFVariant operator*(const QString &p_Value1, const QCFVariant &p_Value2)
{
    QCFVariant tmp = QCFVariant(p_Value1);

    return QCFVariant(tmp.toNumber() * p_Value2.toNumber());
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator/(int p_Value)
{
    return QCFVariant(toNumber() / p_Value);
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator/(double p_Value)
{
    return QCFVariant(toNumber() / p_Value);
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator/(const QString &p_Value)
{
    QCFVariant temp = QCFVariant(p_Value);

    return QCFVariant(toNumber() / temp.toNumber());
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator/(const QCFVariant &p_Value)
{
    return QCFVariant(this->toNumber() / p_Value.toNumber());
}

Q_DECL_EXPORT QCFVariant operator/(int p_Value1, const QCFVariant &p_Value2)
{
    return QCFVariant(p_Value1 / p_Value2.toNumber());
}

Q_DECL_EXPORT QCFVariant operator/(double p_Value1, const QCFVariant &p_Value2)
{
    return QCFVariant(p_Value1 / p_Value2.toNumber());
}

Q_DECL_EXPORT QCFVariant operator/(const QString &p_Value1, const QCFVariant &p_Value2)
{
    QCFVariant temp = QCFVariant(p_Value1);

    return QCFVariant(temp.toNumber() / p_Value2.toNumber());
}

Q_DECL_EXPORT double operator/(const QCFVariant &p_Value1, const QCFVariant &p_Value2)
{
    return p_Value1.toNumber() / p_Value2.toNumber();
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator&(int p_Value)
{
    return QCFVariant(toString() + QString::number(p_Value));
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator&(double p_Value)
{
    return QCFVariant(toString() + QString::number(p_Value));
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator&(const wchar_t *p_Value)
{
    return QCFVariant(toString() + p_Value);
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator&(const QString &p_Value)
{
    return QCFVariant(toString() + p_Value);
}

Q_DECL_EXPORT QCFVariant QCFVariant::operator&(const QCFVariant &p_Value)
{
    return QCFVariant(toString() + p_Value.toString());
}

Q_DECL_EXPORT QCFVariant operator&(int p_Value1, const QCFVariant &p_Value2)
{
    return QCFVariant(QString::number(p_Value1) + p_Value2.toString());
}

Q_DECL_EXPORT QCFVariant operator&(double p_Value1, const QCFVariant &p_Value2)
{
    return QCFVariant(QString::number(p_Value1) + p_Value2.toString());
}

Q_DECL_EXPORT QCFVariant operator&(const QString &p_Value1, const QCFVariant &p_Value2)
{
    return QCFVariant(p_Value1 + p_Value2.toString());
}

Q_DECL_EXPORT QCFVariant QCFVariant::join(const QCFVariant &p_Value)
{
    return QCFVariant(toString() + p_Value.toString());
}

Q_DECL_EXPORT QString QCFVariant::StructKeyAt(const int p_Index)
{
    if (m_Struct->size() <= p_Index)
    {
        return QString();
    }

    return m_Struct->keys().at(p_Index);
}

Q_DECL_EXPORT QString QCFVariant::toString() const
{
	switch(m_Type)
	{
    case QCFVariant::Null:
            return "";
    case QCFVariant::String:
		break;

    case QCFVariant::Number:
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
                    forever
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

    case QCFVariant::DateTime:
        return m_DateTime->toString("MMMM, dd yyyy hh:mm:ss");
		break;

    case QCFVariant::Boolean:
		if (m_Bool == true)
			return "true";
		else
			return "false";
		break;
    case QCFVariant::Array:
        if (m_Number > 0)
        {
            return m_Array->at(m_Number - 1).toString();
        }
        default:
			throw QMKFusionExpressionException("Complex object types cannot be converted to simple values.", "The expression has requested a variable or an intermediate expression result as a simple value, however, the result cannot be converted to a simple value. Simple values are strings, numbers, boolean values, and date/time values. Queries, arrays, and COM objects are examples of complex values. <p> The most likely cause of the error is that you are trying to use a complex value as a simple one. For example, you might be trying to use a query variable in a cfif tag.");
		break;
	}

    return *m_String;
}

Q_DECL_EXPORT QByteArray QCFVariant::toBinary() const
{
    switch(m_Type)
    {
    case QCFVariant::Binary:
        return *m_ByteArray;
    default:
        throw QMKFusionExpressionException("The value  cannot be converted to binary.");
    }
}

Q_DECL_EXPORT double QCFVariant::toNumber() const
{
	double ret;
    int diff;
	bool ok;

	switch(m_Type)
	{
    case QCFVariant::Number:
        return m_Number;
        break;
    case QCFVariant::String:
        ret = m_String->toDouble(&ok);
		if (ok == false)
		{
            throw QMKFusionExpressionException("The value " + *m_String + " cannot be converted to a number.");
		}

		return ret;
		break;
    case QCFVariant::DateTime:
        diff = QDateTime(QDate(1899, 12, 29), QTime(0, 0)).secsTo(*m_DateTime);
        return diff / (60 * 60 * 24);
        break;
    case QCFVariant::Array:
        if (m_Number > 0)
        {
            return m_Array->at(m_Number - 1).toNumber();
        }
	default:
		throw QMKFusionExpressionException("The value cannot be converted to a number.");
	}
}

Q_DECL_EXPORT int QCFVariant::toInt() const
{
    int ret;
    int diff;
    bool ok;

    switch(m_Type)
    {
    case QCFVariant::Number:
        return (int)m_Number;
        break;
    case QCFVariant::String:
        ret = m_String->toInt(&ok);
        if (ok == false)
        {
            throw QMKFusionExpressionException("The value [" + *m_String + "] cannot be converted to a int.");
        }

        return ret;
        break;
    case QCFVariant::DateTime:
        diff = QDateTime(QDate(1899, 12, 29), QTime(0, 0)).secsTo(*m_DateTime);
        return diff / (60 * 60 * 24);
        break;
    case QCFVariant::Array:
        if (m_Number > 0)
        {
            return m_Array->at(m_Number - 1).toInt();
        }
    default:
        throw QMKFusionExpressionException("The value cannot be converted to a int.");
    }
}

Q_DECL_EXPORT bool QCFVariant::canConvertToNumber()
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

Q_DECL_EXPORT bool QCFVariant::canConvertToDate()
{
    // TODO: Implement QCFVariant::canConvertToDate()
    throw QMKFusionException("QCFVariant::canConvertToDate() is not implemented");
}

Q_DECL_EXPORT QDateTime QCFVariant::toDateTime() const
{
    if (m_Type == QCFVariant::DateTime)
    {
        return *m_DateTime;
    }

    if (m_Type == QCFVariant::String)
    {
        QDateTime dateTime = QDateTime::fromString(*m_String, Qt::ISODate);

        if (dateTime.isValid())
        {
            return dateTime;
        }
    }

    throw QMKFusionExpressionException("The value cannot be converted to a datetime.");
}

Q_DECL_EXPORT bool QCFVariant::toBool() const
{
	switch(m_Type)
	{
        case QCFVariant::Boolean:
			return m_Bool;
        case QCFVariant::String:
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
        case QCFVariant::Number:
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

Q_DECL_EXPORT QCFVariant QCFVariant::createComponent(const QString &path, const QString &name)
{
    return QCFVariant();
}

Q_DECL_EXPORT QCFVariant QCFVariant::call(const QString &function, QList<QCFVariant> params)
{
    if (m_Type != Component)
    {
        throw QMKFusionException("Variable is not component.");
    }



    return QCFVariant();
}

Q_DECL_EXPORT QCFVariant QCFVariant::call(const QString &function, QHash<QString, QCFVariant> params)
{
    return QCFVariant();
}
