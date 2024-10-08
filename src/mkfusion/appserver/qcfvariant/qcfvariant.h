#pragma once

#include <QDateTime>
#include <QVector>
#include <QString>
#include <QMap>

class QCFVariantComponent;
class QCFVariantFunction;
class QCFWorkerThread;

class Q_DECL_EXPORT QCFVariant
{
public:
    enum QCFVariantType
    {
        Null,
        Boolean,
        Number,
        String,
        DateTime,
        Array,
        Struct,
        Binary,
        Query,
        Component,
        Function,
        NotImplemented,
        Error
    };

public:
    QCFVariant();
    virtual ~QCFVariant();

    QCFVariant(bool value);
    QCFVariant(int value);
    QCFVariant(double value);
    QCFVariant(const char *value);
    QCFVariant(const wchar_t *value);
    QCFVariant(const QString &value);
    QCFVariant(const QDateTime &value);
    QCFVariant(const QCFVariantComponent &value);
    QCFVariant(const QCFVariantFunction &value);
    QCFVariant(const QCFVariant &value);
    QCFVariant(const QCFVariantType type);

#ifdef Q_COMPILER_RVALUE_REFS
    inline QCFVariant &operator=(QCFVariant &&other)
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
            break;
        case Function:
            qSwap(m_Function, other.m_Function);
            break;
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
        qSwap(m_AddMissingMember, other.m_AddMissingMember);

        return *this;
    }
#endif

    operator bool();
    operator int();
    operator double();
    operator QString();
    operator QDateTime();

    QCFVariant operator+(bool);
    QCFVariant operator+(int);
    QCFVariant operator+(double);
    QCFVariant operator+(const wchar_t *);
    QCFVariant operator+(const QString &);
    QCFVariant operator+(const QCFVariant &);
    friend QCFVariant operator+(bool, const QCFVariant &);
    friend QCFVariant operator+(int, const QCFVariant &);
    friend QCFVariant operator+(double, const QCFVariant &);
    friend QCFVariant operator+(const wchar_t *, const QCFVariant &);
    friend QCFVariant operator+(const QString &, const QCFVariant &);

    //QCFVariant operator+=(int);
    //QCFVariant operator+=(double);
    //QCFVariant operator+=(const wchar_t *);
    //QCFVariant operator+=(const QString &);
    //QCFVariant operator+=(const QCFVariant &);
    //friend QCFVariant operator+=(int, const QCFVariant &);
    //friend QCFVariant operator+=(double, const QCFVariant &);
    //friend QCFVariant operator+=(const QString &, const QCFVariant &);

    QCFVariant operator++();
    QCFVariant operator++(int);

    QCFVariant operator-(bool);
    QCFVariant operator-(int);
    QCFVariant operator-(double);
    QCFVariant operator-(const wchar_t *);
    QCFVariant operator-(const QString &);
    QCFVariant operator-(const QCFVariant &);
    friend QCFVariant operator-(bool, const QCFVariant &);
    friend QCFVariant operator-(int, const QCFVariant &);
    friend QCFVariant operator-(double, const QCFVariant &);
    friend QCFVariant operator-(const wchar_t *, const QCFVariant &);
    friend QCFVariant operator-(const QString &, const QCFVariant &);

    //QCFVariant operator-=(int);
    //QCFVariant operator-=(double);
    //QCFVariant operator-=(const QString &);
    //QCFVariant operator-=(const QCFVariant &);
    //friend QCFVariant operator-=(int, const QCFVariant &);
    //friend QCFVariant operator-=(double, const QCFVariant &);
    //friend QCFVariant operator-=(const QString &, const QCFVariant &);

    QCFVariant operator--();
    QCFVariant operator--(int);

    QCFVariant operator*(int);
    QCFVariant operator*(double);
    QCFVariant operator*(const QString &);
    QCFVariant operator*(const QCFVariant &);
    friend QCFVariant operator*(int, const QCFVariant &);
    friend QCFVariant operator*(double, const QCFVariant &);
    friend QCFVariant operator*(const QString &, const QCFVariant &);

    //QCFVariant operator*=(int);
    //QCFVariant operator*=(double);
    //QCFVariant operator*=(const QString &);
    //QCFVariant operator*=(const QCFVariant &);
    //friend QCFVariant operator*=(int, const QCFVariant &);
    //friend QCFVariant operator*=(double, const QCFVariant &);
    //friend QCFVariant operator*=(const QString &, const QCFVariant &);

    QCFVariant operator/(int);
    QCFVariant operator/(double);
    QCFVariant operator/(const QString &);
    QCFVariant operator/(const QCFVariant &);

    //QCFVariant operator/=(int);
    //QCFVariant operator/=(double);
    //QCFVariant operator/=(const QString &);
    //QCFVariant operator/=(const QCFVariant &);
    //friend QCFVariant operator/=(int, const QCFVariant &);
    //friend QCFVariant operator/=(double, const QCFVariant &);
    //friend QCFVariant operator/=(const QString &, const QCFVariant &);

    QCFVariant operator&(int);
    QCFVariant operator&(double);
    QCFVariant operator&(const wchar_t *);
    QCFVariant operator&(const QString &);
    QCFVariant operator&(const QCFVariant &);

    //QCFVariant operator&=(int);
    //QCFVariant operator&=(double);
    //QCFVariant operator&=(const wchar_t *);
    //QCFVariant operator&=(const QString &);
    //QCFVariant operator&=(const QCFVariant &);
    //friend QCFVariant operator&=(int, const QCFVariant &);
    //friend QCFVariant operator&=(double, const QCFVariant &);
    //friend QCFVariant operator&=(const QString &, const QCFVariant &);

    QCFVariant &_();

    QCFVariant &operator[](int index);
    QCFVariant &operator[](const double index);
    QCFVariant &operator[](const QString &key);
    QCFVariant &operator[](const char *key);
    QCFVariant &operator[](const wchar_t *key);
    QCFVariant &operator[](const QCFVariant &key);

    bool operator==(bool);
    bool operator==(int);
    bool operator==(double);
    bool operator==(const QString &);
    bool operator==(const QCFVariant &);

    //bool operator!();
    QCFVariant operator!();
    //friend bool operator!(const QCFVariant &);
    friend QCFVariant operator!(const QCFVariant &);

    bool operator!=(int);
    bool operator!=(double);
    bool operator!=(const QString &);
    bool operator!=(const QCFVariant &);

    bool operator<=(int);
    bool operator<=(double);
    bool operator<=(const QString &);
    bool operator<=(const QCFVariant &);

    bool operator>=(int);
    bool operator>=(double);
    bool operator>=(const QString &);
    bool operator>=(const QCFVariant &);

    bool operator<(int);
    bool operator<(double);
    bool operator<(const QString &);
    bool operator<(const QCFVariant &);

    bool operator>(int);
    bool operator>(double);
    bool operator>(const QString &);
    bool operator>(const QCFVariant &);

    QCFVariant &operator=(const bool);
    QCFVariant &operator=(const int);
    QCFVariant &operator=(const double);
    QCFVariant &operator=(const char *);
    QCFVariant &operator=(const wchar_t *);
    QCFVariant &operator=(const QString &);
    QCFVariant &operator=(const QDateTime &);
    QCFVariant &operator=(const QCFVariantComponent &);
    QCFVariant &operator=(const QCFVariantFunction &);
    QCFVariant &operator=(const QCFVariant &);

    QCFVariant join(const QCFVariant &);
    void setType(QCFVariantType);
    QCFVariantType type() const;
    int size();
    QString StructKeyAt(const int);
    QString toString() const;
    QByteArray toBinary() const;
    double toNumber() const;
    int toInt() const;
    bool canConvertToNumber();
    bool canConvertToDate();
    QDateTime toDateTime() const;
    bool toBool() const;

    QCFVariant call(QCFWorkerThread &worker, const QString &function, QList<QCFVariant> params);
    QCFVariant call(QCFWorkerThread &worker, const QString &function, QHash<QString, QCFVariant> params);


    // Member Variables
    QCFVariantType m_Type = Null;
    QVector<QCFVariant> *m_Array = nullptr;
    QMap<QString, QCFVariant> *m_Struct = nullptr;
    QString *m_String = nullptr;
    QByteArray *m_ByteArray = nullptr;
    double m_Number = 0;
    bool m_Bool = false;
    QDateTime *m_DateTime = nullptr;
    QCFVariantComponent *m_Component = nullptr;
    QCFVariantFunction *m_Function = nullptr;
    quint32 m_ArrayDimension = 1;
    QCFVariant *m_HiddenScopeFirst = nullptr;
    QCFVariant *m_HiddenScopeLast1 = nullptr;
    QCFVariant *m_HiddenScopeLast2 = nullptr;
    mutable bool m_AddMissingMember = false;
};

Q_DECL_EXPORT bool operator!=(int, const QCFVariant &);
Q_DECL_EXPORT bool operator!=(double, const QCFVariant &);
Q_DECL_EXPORT bool operator!=(const QString &, const QCFVariant &);

Q_DECL_EXPORT bool operator<=(int, const QCFVariant &);
Q_DECL_EXPORT bool operator<=(double, const QCFVariant &);
Q_DECL_EXPORT bool operator<=(const QString &, const QCFVariant &);

Q_DECL_EXPORT bool operator>=(int, const QCFVariant &);
Q_DECL_EXPORT bool operator>=(double, const QCFVariant &);
Q_DECL_EXPORT bool operator>=(const QString &, const QCFVariant &);

Q_DECL_EXPORT bool operator<(int, const QCFVariant &);
Q_DECL_EXPORT bool operator<(double, const QCFVariant &);
Q_DECL_EXPORT bool operator<(const QString &, const QCFVariant &);

Q_DECL_EXPORT bool operator>(int, const QCFVariant &);
Q_DECL_EXPORT bool operator>(double, const QCFVariant &);
Q_DECL_EXPORT bool operator>(const QString &, const QCFVariant &);

Q_DECL_EXPORT bool operator==(int, const QCFVariant &);
//Q_DECL_EXPORT bool operator==(const QString &, int);
//Q_DECL_EXPORT bool operator==(const QString &, double);

Q_DECL_EXPORT QCFVariant operator/(int, const QCFVariant &);
Q_DECL_EXPORT QCFVariant operator/(double, const QCFVariant &);
Q_DECL_EXPORT QCFVariant operator/(const QString &, const QCFVariant &);
Q_DECL_EXPORT double operator/(const QCFVariant &, const QCFVariant &);

Q_DECL_EXPORT QCFVariant operator&(int, const QCFVariant &);
Q_DECL_EXPORT QCFVariant operator&(double, const QCFVariant &);
Q_DECL_EXPORT QCFVariant operator&(const QString &, const QCFVariant &);
