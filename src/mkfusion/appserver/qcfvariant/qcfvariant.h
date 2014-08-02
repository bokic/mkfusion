#ifndef QCFVARIANT_H
#define QCFVARIANT_H

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
    QCFVariant &operator=(QCFVariant &&other);
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
    QVector<QCFVariant> *m_Array;
    QMap<QString, QCFVariant> *m_Struct;
    QString *m_String;
    QByteArray *m_ByteArray;
    double m_Number;
    bool m_Bool;
    QDateTime *m_DateTime;
    QCFVariantComponent *m_Component;
    QCFVariantFunction *m_Function;
    QCFVariantType m_Type;
    quint32 m_ArrayDimension;
    QCFVariant *m_HiddenScopeFirst;
    QCFVariant *m_HiddenScopeLast1;
    QCFVariant *m_HiddenScopeLast2;
    mutable bool m_AddMissingMember;
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

#endif // QCFVARIANT_H
