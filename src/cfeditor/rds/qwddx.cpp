#include "qwddx.h"

QWDDX::QWDDX()
{
	m_Type = QWDDX::Null;
}

QWDDX::QWDDX(QWDDXType p_Type)
{
	m_Type = p_Type;
}

QWDDX &QWDDX::operator= (const QString &p_NewValue)
{
	m_Type = QWDDX::String;
	m_String = p_NewValue;

	return *this;
}

QWDDX &QWDDX::operator= (const char *p_NewValue)
{
	m_Type = QWDDX::String;
	m_String = p_NewValue;

	return *this;
}

QWDDX &QWDDX::operator=(const QByteArray &p_NewValue)
{
	m_Type = QWDDX::Binary;
	m_ByteArray = p_NewValue;

	return *this;
}

QWDDX::QWDDXType QWDDX::getType()
{
	return m_Type;
}

int QWDDX::size()
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

QWDDX & QWDDX::operator[](const int p_Index)
{
	if (m_Type == QWDDX::Null)
		m_Type = QWDDX::Array;

	switch(m_Type)
	{
	case QWDDX::Array:
		if (m_Array.size() <= p_Index)
			m_Array.resize(p_Index + 1);

		return m_Array[p_Index];
		break;
	
	case QWDDX::Struct:
		if (m_Struct.size() <= p_Index)
			return *(new QWDDX(QWDDX::Error));

		return m_Struct[m_Struct.keys().at(p_Index)];

	default:
		return *(new QWDDX(QWDDX::Error));

	}
}

QWDDX & QWDDX::operator[](QString key)
{
	if (m_Type == QWDDX::Null)
		m_Type = QWDDX::Struct;

	if (m_Type != QWDDX::Struct)
		return *(new QWDDX(QWDDX::Error));

	if (m_Struct.contains(key) == false)
		m_Struct.insert(key, QWDDX());

	return m_Struct[key];
}

QWDDX &QWDDX::operator[](char *key)
{
	if (m_Type == QWDDX::Null)
		m_Type = QWDDX::Struct;

	if (m_Type != QWDDX::Struct)
		return *(new QWDDX(QWDDX::Error));

	if (m_Struct.contains(key) == false)
		m_Struct.insert(key, QWDDX());

	return m_Struct[key];
}

QWDDX &QWDDX::operator=(const QDateTime &p_DateTime)
{
	m_Type = QWDDX::DateTime;
	m_DateTime = p_DateTime;

	return *this;
}

QWDDX &QWDDX::operator=(const double p_NewValue)
{
	m_Type = QWDDX::Number;
	m_Number = p_NewValue;

	return *this;
}

QWDDX &QWDDX::operator=(const bool p_NewValue)
{
	m_Type = QWDDX::Boolean;
	m_Bool = p_NewValue;

	return *this;
}

QString QWDDX::StructKeyAt(int p_Index)
{
	if (m_Struct.size() <= p_Index)
		return "";

	return m_Struct.keys().at(p_Index);
}

QString QWDDX::toString()
{
	switch(m_Type)
	{
	case QWDDX::String:
		return m_String;
		break;

	case QWDDX::Number:
		return QString::number(m_Number);
		break;

	case QWDDX::DateTime:
		return m_DateTime.toString();
		break;

	case QWDDX::Boolean:
		if (m_Bool == true)
			return "true";
		else
			return "false";
		break;
	default:
		break;
	}

	return "";
}

double QWDDX::toNumber()
{
	if (m_Type != QWDDX::Number)
		return 0;

	return m_Number;
}

QDateTime QWDDX::toDateTime()
{
	if (m_Type != QWDDX::DateTime)
		return QDateTime();

	return m_DateTime;
}

bool QWDDX::toBool()
{
	if (m_Type != QWDDX::Boolean)
		return false;

	return m_Bool;
}
