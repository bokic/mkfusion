#include "qwddx.h"

QWDDX::QWDDX()
    : m_Number(0)
    , m_Bool(false)
    , m_Type(Null)
{
}

QWDDX::QWDDX(QWDDXType type)
    : m_Number(0)
    , m_Bool(false)
    , m_Type(type)
{
}

QWDDX &QWDDX::operator=(const QString &value)
{
    m_Type = QWDDX::String;
    m_String = value;

    return *this;
}

QWDDX &QWDDX::operator=(const char *value)
{
    m_Type = QWDDX::String;
    m_String = value;

    return *this;
}

QWDDX &QWDDX::operator=(const QByteArray &value)
{
    m_Type = QWDDX::Binary;
    m_ByteArray = value;

    return *this;
}

QWDDX::QWDDXType QWDDX::type() const
{
    return m_Type;
}

int QWDDX::size() const
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

QWDDX & QWDDX::operator[](int index)
{
    if (m_Type == QWDDX::Null)
        m_Type = QWDDX::Array;

    switch(m_Type)
    {
    case QWDDX::Array:
        if (m_Array.size() <= index)
            m_Array.resize(index + 1);

        return m_Array[index];
        break;

    case QWDDX::Struct:
        if (m_Struct.size() <= index)
            return *(new QWDDX(QWDDX::Error));

        return m_Struct[m_Struct.keys().at(index)];

    default:
        return *(new QWDDX(QWDDX::Error));

    }
}

QWDDX & QWDDX::operator[](const QString &key)
{
    if (m_Type == QWDDX::Null)
        m_Type = QWDDX::Struct;

    if (m_Type != QWDDX::Struct)
        return *(new QWDDX(QWDDX::Error));

    if (m_Struct.contains(key) == false)
        m_Struct.insert(key, QWDDX());

    return m_Struct[key];
}

QWDDX &QWDDX::operator[](const char *key)
{
    if (m_Type == QWDDX::Null)
        m_Type = QWDDX::Struct;

    if (m_Type != QWDDX::Struct)
        return *(new QWDDX(QWDDX::Error));

    if (m_Struct.contains(key) == false)
        m_Struct.insert(key, QWDDX());

    return m_Struct[key];
}

QWDDX &QWDDX::operator=(const QDateTime &value)
{
    m_Type = QWDDX::DateTime;
    m_DateTime = value;

    return *this;
}

QWDDX &QWDDX::operator=(double value)
{
    m_Type = QWDDX::Number;
    m_Number = value;

    return *this;
}

QWDDX &QWDDX::operator=(bool value)
{
    m_Type = QWDDX::Boolean;
    m_Bool = value;

    return *this;
}

QWDDX QWDDX::at(int index) const
{
    if (m_Type != QWDDX::Array)
    {
        return QWDDX(Error);
    }

    if ((index < 0)||(m_Array.size() <= index))
    {
        return QWDDX(Error);
    }

    return m_Array.at(index);
}

QString QWDDX::StructKeyAt(int index) const
{
    if (m_Struct.size() <= index)
        return "";

    return m_Struct.keys().at(index);
}

QString QWDDX::toString() const
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
            return QStringLiteral("true");
        else
            return QStringLiteral("false");
        break;
    default:
        break;
    }

    return "";
}

double QWDDX::toNumber() const
{
    if (m_Type != QWDDX::Number)
        return 0;

    return m_Number;
}

QDateTime QWDDX::toDateTime() const
{
    if (m_Type != QWDDX::DateTime)
        return QDateTime();

    return m_DateTime;
}

bool QWDDX::toBool() const
{
    if (m_Type != QWDDX::Boolean)
        return false;

    return m_Bool;
}
