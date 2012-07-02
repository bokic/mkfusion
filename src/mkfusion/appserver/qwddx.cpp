#include "qwddx.h"
#include "qmkfusionexception.h"
#include <math.h>

Q_DECL_EXPORT QWDDX::QWDDX()
	: m_ArrayDimension(1)
	, m_Number(0)
	, m_Bool(false)
	, m_Type(Null)
{
}

Q_DECL_EXPORT QWDDX::QWDDX(bool p_NewValue)
	: m_ArrayDimension(1)
	, m_Number(0)
	, m_Bool(p_NewValue)
	, m_Type(Boolean)
{
}

Q_DECL_EXPORT QWDDX::QWDDX(int p_NewValue)
	: m_ArrayDimension(1)
	, m_Number(p_NewValue)
	, m_Bool(false)
	, m_Type(Number)
{
}

Q_DECL_EXPORT QWDDX::QWDDX(double p_NewValue)
	: m_ArrayDimension(1)
	, m_Number(p_NewValue)
	, m_Bool(false)
	, m_Type(Number)
{
}

Q_DECL_EXPORT QWDDX::QWDDX(const char *p_NewValue)
	: m_ArrayDimension(1)
	, m_String(p_NewValue)
	, m_Number(0)
	, m_Bool(false)
	, m_Type(String)
{
}

Q_DECL_EXPORT QWDDX::QWDDX(const wchar_t *p_NewValue)
	: m_ArrayDimension(1)
	, m_String(QString::fromWCharArray(p_NewValue))
	, m_Number(0)
	, m_Bool(false)
	, m_Type(String)
{
}

Q_DECL_EXPORT QWDDX::QWDDX(const QString& p_NewValue)
	: m_ArrayDimension(1)
	, m_String(p_NewValue)
	, m_Number(0)
	, m_Bool(false)
	, m_Type(String)
{
}

Q_DECL_EXPORT QWDDX::QWDDX(const QDateTime& p_NewValue)
	: m_ArrayDimension(1)
	, m_Number(0)
	, m_Bool(false)
	, m_DateTime(p_NewValue)
	, m_Type(DateTime)
{
}

Q_DECL_EXPORT QWDDX::QWDDX(const QWDDXType p_Type)
	: m_ArrayDimension(1)
	, m_Number(0)
	, m_Bool(false)
	, m_Type(p_Type)
{
}

Q_DECL_EXPORT QWDDX::QWDDXType QWDDX::getType()
{
	return m_Type;
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
		return m_Array.size();
	case QWDDX::Struct:
		return m_Struct.size();
	default:
		return 1;
	}
}

Q_DECL_EXPORT QWDDX& QWDDX::operator[](const double p_Index)
{
	if ((m_Type != QWDDX::Struct)&&(m_Type != QWDDX::Array))
	{
		throw QMKFusionExpressionException("You have attempted to dereference a scalar variable of type class java.lang.String as a structure with members.", "");
	}

	if (m_Type != QWDDX::Array)
	{
		if ((int)p_Index < 1)
		{
			throw QMKFusionExpressionException("The element at position " + QString::number((int)p_Index) + " of array variable \"xxx\" cannot be found.", "");
		}

		if (m_Array.size() <= (int)p_Index)
		{
			m_Array.resize((int)p_Index + 1);
		}

		return m_Array[(int)p_Index];
	}
	else
	{
		if (m_Struct.contains(QString::number(p_Index)) == false)
		{
			m_Struct.insert(QString::number(p_Index), QWDDX(QWDDX::Null));
		}

		return m_Struct[QString::number(p_Index)];
	}
}

Q_DECL_EXPORT QWDDX& QWDDX::operator[](const QString& key)
{
	if ((m_Type != QWDDX::Struct)&&(m_Type != QWDDX::Array))
	{
		throw QMKFusionExpressionException("You have attempted to dereference a scalar variable of type class char* as a structure with members.");
	}

	if (m_Type == QWDDX::Struct)
	{
		if (m_Struct.contains(key) == false)
		{
			m_Struct.insert(key, QWDDX(QWDDX::Null));
		}

		return m_Struct[key];
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

		if (m_Array.size() > val)
		{
			m_Array.resize(val);
		}

		return m_Array[val - 1];
	}
}

Q_DECL_EXPORT QWDDX& QWDDX::operator[](const char* key)
{
	QString l_key = QString::fromLatin1(key);

	if ((m_Type != QWDDX::Struct)&&(m_Type != QWDDX::Array))
	{
		throw QMKFusionExpressionException("You have attempted to dereference a scalar variable of type class wchar_t* as a structure with members.");
	}

	if (m_Type == QWDDX::Struct)
	{
		if (m_Struct.contains(l_key) == false)
		{
			m_Struct.insert(l_key, QWDDX(QWDDX::Null));
		}

		return m_Struct[l_key];
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

		if (m_Array.size() > val)
		{
			m_Array.resize(val);
		}

		return m_Array[val - 1];
	}
}

Q_DECL_EXPORT QWDDX& QWDDX::operator[](const wchar_t* key)
{
	QString l_key = QString::fromStdWString(key);

	if ((m_Type != QWDDX::Struct)&&(m_Type != QWDDX::Array))
	{
		throw QMKFusionExpressionException("You have attempted to dereference a scalar variable of type class wchar_t* as a structure with members.");
	}

	if (m_Type == QWDDX::Struct)
	{
		if (m_Struct.contains(l_key) == false)
		{
			m_Struct.insert(l_key, QWDDX(QWDDX::Null));
		}

		return m_Struct[l_key];
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

		if (m_Array.size() > val)
		{
			m_Array.resize(val);
		}

		return m_Array[val - 1];
	}
}

Q_DECL_EXPORT QWDDX& QWDDX::operator[](const QWDDX& key)
{
	if ((m_Type != QWDDX::Struct)&&(m_Type != QWDDX::Array))
	{
		throw QMKFusionExpressionException("You have attempted to dereference a scalar variable of type class java.lang.String as a structure with members.", "");
	}

	QWDDX temp = key;

	double l_key = temp.toNumber();

	if (m_Type == QWDDX::Array)
	{
		if ((int)l_key < 1)
		{
			throw QMKFusionExpressionException("The element at position " + QString::number((int)l_key) + " of array variable \"xxx\" cannot be found.", "");
		}

		if (m_Array.size() < (int)l_key)
		{
			m_Array.resize((int)l_key);
		}

		return m_Array[(int)l_key - 1];
	}
	else
	{
		if (m_Struct.contains(QString::number(l_key)) == false)
		{
			m_Struct.insert(QString::number(l_key), QWDDX(QWDDX::Null));
		}

		return m_Struct[QString::number(l_key)];
	}
}

Q_DECL_EXPORT bool QWDDX::operator ==(int p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number == (double)p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() == (double)p_Value;
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator ==(double p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number == p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() == p_Value;
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator ==(const QString& p_Value)
{
	if ((m_Type == Number))
	{
		return toString() == p_Value;
	}

	if ((m_Type == String))
	{
		return m_String == p_Value;
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator ==(const QWDDX& p_Value)
{
	QWDDX l_temp1, l_temp2;

	if ((m_Type == Number)&&(p_Value.m_Type == Number))
	{
		return m_Number == p_Value.m_Number;
	}

	if ((m_Type == String)&&(p_Value.m_Type == String))
	{
		return m_String == p_Value.m_String;
	}

	if (((m_Type == Number)||(m_Type == String))&&((p_Value.m_Type == Number)||(p_Value.m_Type == String)))
	{
		l_temp1 = *this;
		l_temp2 = p_Value;

		return l_temp1.toString() == l_temp2.toString();
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator !=(int p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number != (double)p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() != (double)p_Value;
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator !=(double p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number != p_Value;
	}

	if ((m_Type == String))
	{
		return m_Number != p_Value;
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator !=(const QString& p_Value)
{
	if ((m_Type == Number))
	{
		return toString() != p_Value;
	}

	if ((m_Type == String))
	{
		return m_String != p_Value;
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator !=(const QWDDX& p_Value)
{
	QWDDX l_temp1, l_temp2;

	if ((m_Type == Number)&&(p_Value.m_Type == Number))
	{
		return m_Number != p_Value.m_Number;
	}

	if ((m_Type == String)&&(p_Value.m_Type == String))
	{
		return m_String != p_Value.m_String;
	}

	if (((m_Type == Number)||(m_Type == String))&&((p_Value.m_Type == Number)||(p_Value.m_Type == String)))
	{
		l_temp1 = *this;
		l_temp2 = p_Value;

		return l_temp1.toString() != l_temp2.toString();
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator <=(int p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number <= (double)p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() <=(double)p_Value;
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator <=(double p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number <= p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() <= p_Value;
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator <=(const QString& p_Value)
{
	if ((m_Type == Number))
	{
		return toString() <= p_Value;
	}

	if ((m_Type == String))
	{
		return m_String <= p_Value;
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator <=(const QWDDX& p_Value)
{
	QWDDX l_temp1, l_temp2;

	if ((m_Type == Number)&&(p_Value.m_Type == Number))
	{
		return m_Number <= p_Value.m_Number;
	}

	if ((m_Type == String)&&(p_Value.m_Type == String))
	{
		return m_String <= p_Value.m_String;
	}

	if (((m_Type == Number)||(m_Type == String))&&((p_Value.m_Type == Number)||(p_Value.m_Type == String)))
	{
		l_temp1 = *this;
		l_temp2 = p_Value;

		return l_temp1.toString() <= l_temp2.toString();
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator >=(int p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number >= (double)p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() >= (double)p_Value;
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator >=(double p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number >= p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() >= p_Value;
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator >=(const QString& p_Value)
{
	if ((m_Type == Number))
	{
		return toString() >= p_Value;
	}

	if ((m_Type == String))
	{
		return m_String >= p_Value;
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator >=(const QWDDX& p_Value)
{
	QWDDX l_temp1, l_temp2;

	if ((m_Type == Number)&&(p_Value.m_Type == Number))
	{
		return m_Number >= p_Value.m_Number;
	}

	if ((m_Type == String)&&(p_Value.m_Type == String))
	{
		return m_String >= p_Value.m_String;
	}

	if (((m_Type == Number)||(m_Type == String))&&((p_Value.m_Type == Number)||(p_Value.m_Type == String)))
	{
		l_temp1 = *this;
		l_temp2 = p_Value;

		return l_temp1.toString() >= l_temp2.toString();
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator <(int p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number < (double)p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() < (double)p_Value;
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator <(double p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number < p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() < p_Value;
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator <(const QString& p_Value)
{
	if ((m_Type == Number))
	{
		return toString() < p_Value;
	}

	if ((m_Type == String))
	{
		return m_String < p_Value;
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator <(const QWDDX& p_Value)
{
	QWDDX l_temp1, l_temp2;

	if ((m_Type == Number)&&(p_Value.m_Type == Number))
	{
		return m_Number < p_Value.m_Number;
	}

	if ((m_Type == String)&&(p_Value.m_Type == String))
	{
		return m_String < p_Value.m_String;
	}

	if (((m_Type == Number)||(m_Type == String))&&((p_Value.m_Type == Number)||(p_Value.m_Type == String)))
	{
		l_temp1 = *this;
		l_temp2 = p_Value;

		return l_temp1.toString() < l_temp2.toString();
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator >(int p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number > (double)p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() > (double)p_Value;
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator >(double p_Value)
{
	if ((m_Type == Number))
	{
		return m_Number > p_Value;
	}

	if ((m_Type == String))
	{
		return toNumber() > p_Value;
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator >(const QString& p_Value)
{
	if ((m_Type == Number))
	{
		return toString() > p_Value;
	}

	if ((m_Type == String))
	{
		return m_String > p_Value;
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

Q_DECL_EXPORT bool QWDDX::operator >(const QWDDX& p_Value)
{
	QWDDX l_temp1, l_temp2;

	if ((m_Type == Number)&&(p_Value.m_Type == Number))
	{
		return m_Number > p_Value.m_Number;
	}

	if ((m_Type == String)&&(p_Value.m_Type == String))
	{
		return m_String > p_Value.m_String;
	}

	if (((m_Type == Number)||(m_Type == String))&&((p_Value.m_Type == Number)||(p_Value.m_Type == String)))
	{
		l_temp1 = *this;
		l_temp2 = p_Value;

		return l_temp1.toString() > l_temp2.toString();
	}

	throw new QMKFusionExpressionException("Unsupported compare.");
}

/*Q_DECL_EXPORT QWDDX& QWDDX::operator=(int p_newValue)
{
	m_Type = Number;
	m_Number = p_newValue;

	return *this;
}

Q_DECL_EXPORT QWDDX& QWDDX::operator=(double p_newValue)
{
	m_Type = Number;
	m_Number = p_newValue;

	return *this;
}


Q_DECL_EXPORT QWDDX& QWDDX::operator=(const wchar_t *p_newValue)
{
	m_Type = String;
	m_String = QString::fromWCharArray(p_newValue);

	return *this;
}

Q_DECL_EXPORT QWDDX& QWDDX::operator=(const QString& p_newValue)
{
	m_Type = String;
	m_String = p_newValue;

	return *this;
}

Q_DECL_EXPORT QWDDX& QWDDX::operator=(const QDateTime& p_newValue)
{
	m_Type = DateTime;
	m_DateTime = p_newValue;

	return *this;
}

Q_DECL_EXPORT QWDDX& QWDDX::operator=(const QDateTime& p_newValue)
{
	toDateTime()p_newValue);

	return *this;
}*/

Q_DECL_EXPORT QWDDX& QWDDX::operator+(int p_Value)
{
	if (m_Type == Number)
	{
		return *(new QWDDX(m_Number + p_Value));
	}
	else
	{
		return *(new QWDDX(toNumber() + p_Value));
	}
}

Q_DECL_EXPORT QWDDX& QWDDX::operator+(double p_Value)
{
	if (m_Type == Number)
	{
		return *(new QWDDX(m_Number + p_Value));
	}
	else
	{
		return *(new QWDDX(toNumber() + p_Value));
	}
}

Q_DECL_EXPORT QWDDX& QWDDX::operator+(const wchar_t* p_Value)
{
	QWDDX tmp = QWDDX(p_Value);

	if (m_Type == Number)
	{
		return *(new QWDDX(m_Number + tmp.toNumber()));
	}
	else
	{
		return *(new QWDDX(toNumber() + tmp.toNumber()));
	}
}

Q_DECL_EXPORT QWDDX& QWDDX::operator+(const QString& p_Value)
{
	QWDDX tmp = QWDDX(p_Value);

	if (m_Type == Number)
	{
		return *(new QWDDX(m_Number + tmp.toNumber()));
	}
	else
	{
		return *(new QWDDX(toNumber() + tmp.toNumber()));
	}
}

Q_DECL_EXPORT QWDDX& QWDDX::operator+(const QWDDX& p_Value)
{
	QWDDX tmp = QWDDX(p_Value);

	if (m_Type == Number)
	{
		return *(new QWDDX(m_Number + tmp.toNumber()));
	}
	else
	{
		return *(new QWDDX(toNumber() + tmp.toNumber()));
	}
}

QWDDX& operator+(int p_Value1, const QWDDX &p_Value2)
{
	QWDDX temp = p_Value2;

	return *(new QWDDX(p_Value1 + temp.toNumber()));
}

QWDDX& operator+(double p_Value1, const QWDDX &p_Value2)
{
	QWDDX temp = p_Value2;

	return *(new QWDDX(p_Value1 + temp.toNumber()));
}

QWDDX& operator+(const QString& p_Value1, const QWDDX &p_Value2)
{
	QWDDX temp1 = QWDDX(p_Value1);
	QWDDX temp2 = p_Value2;

	return *(new QWDDX(temp1.toNumber() + temp2.toNumber()));
}

/*Q_DECL_EXPORT QWDDX& QWDDX::operator+=(int p_Value)
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

Q_DECL_EXPORT QWDDX& QWDDX::operator-(int p_Value)
{
	if (m_Type == Number)
	{
		m_Number -= p_Value;
	}
	else
	{
		m_Number = toNumber() - p_Value;
	}

	return *this;
}

Q_DECL_EXPORT QWDDX& QWDDX::operator-(double p_Value)
{
	if (m_Type == Number)
	{
		m_Number += p_Value;
	}
	else
	{
		m_Number = toNumber() + p_Value;
	}

	return *this;
}

Q_DECL_EXPORT QWDDX& QWDDX::operator-(const QString& p_Value)
{
	QWDDX tmp = QWDDX(p_Value);

	m_Number = toNumber() - tmp.toNumber();

	return *this;
}

Q_DECL_EXPORT QWDDX& QWDDX::operator-(const QWDDX& p_Value)
{
	QWDDX temp = p_Value;
	return *(new QWDDX(toNumber() - temp.toNumber()));
}

QWDDX& operator-(int p_Value1, const QWDDX &p_Value2)
{
	QWDDX temp = p_Value2;

	return *(new QWDDX(p_Value1 - temp.toNumber()));
}

QWDDX& operator-(double p_Value1, const QWDDX &p_Value2)
{
	QWDDX temp = p_Value2;

	return *(new QWDDX(p_Value1 - temp.toNumber()));
}

QWDDX& operator-(const QString& p_Value1, const QWDDX &p_Value2)
{
	QWDDX temp1 = QWDDX(p_Value1);
	QWDDX temp2 = p_Value2;

	return *(new QWDDX(temp1.toNumber() - temp2.toNumber()));
}

Q_DECL_EXPORT QWDDX& QWDDX::operator*(int p_Value)
{
	return *(new QWDDX(toNumber() * p_Value));
}

Q_DECL_EXPORT QWDDX& QWDDX::operator*(double p_Value)
{
	return *(new QWDDX(toNumber() * p_Value));
}

Q_DECL_EXPORT QWDDX& QWDDX::operator*(const QString& p_Value)
{
	QWDDX temp = QWDDX(p_Value);
	return *(new QWDDX(toNumber() * temp.toNumber()));
}

Q_DECL_EXPORT QWDDX& QWDDX::operator*(const QWDDX& p_Value)
{
	QWDDX temp = p_Value;
	return *(new QWDDX(toNumber() * temp.toNumber()));
}

QWDDX& operator*(int p_Value1, const QWDDX &p_Value2)
{
	QWDDX temp = p_Value2;
	return *(new QWDDX(p_Value1 * temp.toNumber()));
}

QWDDX& operator*(double p_Value1, const QWDDX &p_Value2)
{
	QWDDX temp = p_Value2;
	return *(new QWDDX(p_Value1 * temp.toNumber()));
}

QWDDX& operator*(const QString& p_Value1, const QWDDX &p_Value2)
{
	QWDDX temp1 = QWDDX(p_Value1);
	QWDDX temp2 = p_Value2;
	return *(new QWDDX(temp1.toNumber() * temp2.toNumber()));
}

Q_DECL_EXPORT QWDDX& QWDDX::operator/(int p_Value)
{
	return *(new QWDDX(toNumber() / p_Value));
}

Q_DECL_EXPORT QWDDX& QWDDX::operator/(double p_Value)
{
	return *(new QWDDX(toNumber() / p_Value));
}

Q_DECL_EXPORT QWDDX& QWDDX::operator/(const QString& p_Value)
{
	QWDDX temp = QWDDX(p_Value);
	return *(new QWDDX(toNumber() / temp.toNumber()));
}

Q_DECL_EXPORT QWDDX& QWDDX::operator/(const QWDDX& p_Value)
{
	QWDDX temp = p_Value;
	return *(new QWDDX(toNumber() / temp.toNumber()));
}

/*Q_DECL_EXPORT QWDDX& QWDDX::operator/(int p_Value1, const QWDDX &p_Value2)
{
	QWDDX temp = p_Value2;
	return *(new QWDDX(p_Value1 / temp.toNumber()));
}

Q_DECL_EXPORT QWDDX& QWDDX::operator/(double p_Value1, const QWDDX &p_Value2)
{
	QWDDX temp = p_Value2;
	return *(new QWDDX(p_Value1 / temp.toNumber()));
}

Q_DECL_EXPORT QWDDX& QWDDX::operator/(const QString& p_Value1, const QWDDX &p_Value2)
{
	QWDDX temp1 = QWDDX(p_Value1);
	QWDDX temp2 = p_Value2;
	return *(new QWDDX(temp1.toNumber() / temp2.toNumber()));
}*/

Q_DECL_EXPORT QWDDX& QWDDX::operator&(int p_Value)
{
	return *(new QWDDX(toString() + QString::number(p_Value)));
}

Q_DECL_EXPORT QWDDX& QWDDX::operator&(double p_Value)
{
	return *(new QWDDX(toString() + QString::number(p_Value)));
}

Q_DECL_EXPORT QWDDX& QWDDX::operator&(const wchar_t* p_Value)
{
	return *(new QWDDX(toString() + p_Value));
}


Q_DECL_EXPORT QWDDX& QWDDX::operator&(const QString& p_Value)
{
	return *(new QWDDX(toString() + p_Value));
}

Q_DECL_EXPORT QWDDX& QWDDX::operator&(const QWDDX& p_Value)
{
	QWDDX temp = QWDDX(p_Value);
	return *(new QWDDX(toString() + temp.toString()));
}

Q_DECL_EXPORT QWDDX& operator&(int p_Value1, const QWDDX& p_Value2)
{
	QWDDX temp = QWDDX(p_Value2);
	return *(new QWDDX(QString::number(p_Value1) + temp.toString()));
}

Q_DECL_EXPORT QWDDX& operator&(double p_Value1, const QWDDX& p_Value2)
{
	QWDDX temp = QWDDX(p_Value2);
	return *(new QWDDX(QString::number(p_Value1) + temp.toString()));
}

Q_DECL_EXPORT QWDDX& operator&(const QString& p_Value1, const QWDDX& p_Value2)
{
	QWDDX temp = QWDDX(p_Value2);
	return *(new QWDDX(p_Value1 + temp.toString()));
}

Q_DECL_EXPORT QWDDX& QWDDX::join(const QWDDX& p_Value)
{
	QWDDX temp = p_Value;
	return *(new QWDDX(toString() + temp.toString()));
}

Q_DECL_EXPORT QString QWDDX::StructKeyAt(const int p_Index)
{
	if (m_Struct.size() <= p_Index)
		return "";

	return m_Struct.keys().at(p_Index);
}

Q_DECL_EXPORT QString QWDDX::toString()
{
	QString temp;

	switch(m_Type)
	{
	case QWDDX::String:
		break;

	case QWDDX::Number:
		if (fabs(m_Number) >= 1000000000000.0)
		{
			temp = QString::number(m_Number, 'E', 11);

			if ((temp.length() > 3)&&(temp.at(temp.length() - 3) == '+'))
			{
				temp.insert(temp.length() - 2, '0');
			}

			return temp;
		}
		else
		{
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
		return "{ts \'"+m_DateTime.toString("yyyy-MM-dd hh:mm:ss")+"\'}";
		break;

	case QWDDX::Boolean:
		if (m_Bool == true)
			return "true";
		else
			return "false";
		break;
        default:
			throw QMKFusionExpressionException("Complex object types cannot be converted to simple values.", "The expression has requested a variable or an intermediate expression result as a simple value, however, the result cannot be converted to a simple value. Simple values are strings, numbers, boolean values, and date/time values. Queries, arrays, and COM objects are examples of complex values. <p> The most likely cause of the error is that you are trying to use a complex value as a simple one. For example, you might be trying to use a query variable in a cfif tag.");
		break;
	}

	return m_String;
}

Q_DECL_EXPORT double QWDDX::toNumber()
{
	double ret;
	bool ok;

	switch(m_Type)
	{
	case QWDDX::Number:
		break;
	case QWDDX::String:
		ret = m_String.toDouble(&ok);
		if (ok == false)
		{
			throw QMKFusionExpressionException("The value " + m_String + " cannot be converted to a number.");
		}

		return ret;
		break;
	case QWDDX::DateTime:
		ret = m_DateTime.toTime_t(); // TODO: What here?
		break;
	default:
		throw QMKFusionExpressionException("The value cannot be converted to a number.");
	}

	return m_Number;
}

Q_DECL_EXPORT bool QWDDX::canToNumber()
{
	if (m_Type == Number)
	{
		return true;
	}

	if (m_Type == String)
	{
		if (m_String.isEmpty())
		{
			return false;
		}

		bool ok;
		m_String.toDouble(&ok);

		return ok;
	}

	return false;
}

Q_DECL_EXPORT QDateTime QWDDX::toDateTime()
{
	if (m_Type != QWDDX::DateTime)
		throw QMKFusionExpressionException("The value cannot be converted to a datetime.");

	return m_DateTime;
}

Q_DECL_EXPORT bool QWDDX::toBool()
{
	switch(m_Type)
	{
		case QWDDX::Boolean:
			return m_Bool;
		case QWDDX::String:
			if (m_String.compare("true", Qt::CaseInsensitive) == 0)
			{
				return true;
			}
			else if (m_String.compare("false", Qt::CaseInsensitive) == 0)
			{
				return false;
			}
			else
			{
				break;
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
