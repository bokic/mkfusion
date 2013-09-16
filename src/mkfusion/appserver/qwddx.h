#ifndef QWDDX_H
#define QWDDX_H

#include <QDateTime>
#include <QVector>
#include <QString>
#include <QMap>

class Q_DECL_EXPORT QWDDX
{
public:
	enum QWDDXType {
		Null,
		Boolean,
		Number,
		String,
		DateTime,
		Array,
		Struct,
		Binary,
        Query,
		NotImplemented,
		Error
	};

public:
	QWDDX();
    virtual ~QWDDX();

    QWDDX(bool);
    QWDDX(int);
    QWDDX(double);
    QWDDX(const char *);
    QWDDX(const wchar_t *);
    QWDDX(const QString &);
    QWDDX(const QDateTime &);
    QWDDX(const QWDDX &);
    QWDDX(const QWDDXType);

#ifdef Q_COMPILER_RVALUE_REFS
    QWDDX &operator=(QWDDX &&other);
#endif

	operator bool();
	operator int();
	operator double();
	operator QString();
	operator QDateTime();

    QWDDX operator+(bool);
    QWDDX operator+(int);
    QWDDX operator+(double);
    QWDDX operator+(const wchar_t *);
    QWDDX operator+(const QString &);
    QWDDX operator+(const QWDDX &);
    friend QWDDX operator+(bool, const QWDDX &);
    friend QWDDX operator+(int, const QWDDX &);
    friend QWDDX operator+(double, const QWDDX &);
    friend QWDDX operator+(const wchar_t *, const QWDDX &);
    friend QWDDX operator+(const QString &, const QWDDX &);

    //QWDDX operator+=(int);
    //QWDDX operator+=(double);
    //QWDDX operator+=(const wchar_t *);
    //QWDDX operator+=(const QString &);
    //QWDDX operator+=(const QWDDX &);
    //friend QWDDX operator+=(int, const QWDDX &);
    //friend QWDDX operator+=(double, const QWDDX &);
    //friend QWDDX operator+=(const QString &, const QWDDX &);

    QWDDX operator++();
    QWDDX operator++(int);

    QWDDX operator-(bool);
    QWDDX operator-(int);
    QWDDX operator-(double);
    QWDDX operator-(const wchar_t *);
    QWDDX operator-(const QString &);
    QWDDX operator-(const QWDDX &);
    friend QWDDX operator-(bool, const QWDDX &);
    friend QWDDX operator-(int, const QWDDX &);
    friend QWDDX operator-(double, const QWDDX &);
    friend QWDDX operator-(const wchar_t *, const QWDDX &);
    friend QWDDX operator-(const QString &, const QWDDX &);

    //QWDDX operator-=(int);
    //QWDDX operator-=(double);
    //QWDDX operator-=(const QString &);
    //QWDDX operator-=(const QWDDX &);
    //friend QWDDX operator-=(int, const QWDDX &);
    //friend QWDDX operator-=(double, const QWDDX &);
    //friend QWDDX operator-=(const QString &, const QWDDX &);

    QWDDX operator--();
    QWDDX operator--(int);

    QWDDX operator*(int);
    QWDDX operator*(double);
    QWDDX operator*(const QString &);
    QWDDX operator*(const QWDDX &);
    friend QWDDX operator*(int, const QWDDX &);
    friend QWDDX operator*(double, const QWDDX &);
    friend QWDDX operator*(const QString &, const QWDDX &);

    //QWDDX operator*=(int);
    //QWDDX operator*=(double);
    //QWDDX operator*=(const QString &);
    //QWDDX operator*=(const QWDDX &);
    //friend QWDDX operator*=(int, const QWDDX &);
    //friend QWDDX operator*=(double, const QWDDX &);
    //friend QWDDX operator*=(const QString &, const QWDDX &);

    QWDDX operator/(int);
    QWDDX operator/(double);
    QWDDX operator/(const QString &);
    QWDDX operator/(const QWDDX &);

    //QWDDX operator/=(int);
    //QWDDX operator/=(double);
    //QWDDX operator/=(const QString &);
    //QWDDX operator/=(const QWDDX &);
    //friend QWDDX operator/=(int, const QWDDX &);
    //friend QWDDX operator/=(double, const QWDDX &);
    //friend QWDDX operator/=(const QString &, const QWDDX &);

    QWDDX operator&(int);
    QWDDX operator&(double);
    QWDDX operator&(const wchar_t *);
    QWDDX operator&(const QString &);
    QWDDX operator&(const QWDDX &);

    //QWDDX operator&=(int);
    //QWDDX operator&=(double);
    //QWDDX operator&=(const wchar_t *);
    //QWDDX operator&=(const QString &);
    //QWDDX operator&=(const QWDDX &);
    //friend QWDDX operator&=(int, const QWDDX &);
    //friend QWDDX operator&=(double, const QWDDX &);
    //friend QWDDX operator&=(const QString &, const QWDDX &);

    QWDDX &operator[](const double);
    QWDDX &operator[](const QString &);
    QWDDX &operator[](const char *);
    QWDDX &operator[](const wchar_t *);
    QWDDX &operator[](const QWDDX &);

    bool operator==(bool);
    bool operator==(int);
    bool operator==(double);
    bool operator==(const QString &);
    bool operator==(const QWDDX &);

    //bool operator!();
    QWDDX operator!();
    //friend bool operator!(const QWDDX &);
    friend QWDDX operator!(const QWDDX &);

    bool operator!=(int);
	bool operator!=(double);
    bool operator!=(const QString &);
    bool operator!=(const QWDDX &);

	bool operator<=(int);
	bool operator<=(double);
    bool operator<=(const QString &);
    bool operator<=(const QWDDX &);

	bool operator>=(int);
	bool operator>=(double);
    bool operator>=(const QString &);
    bool operator>=(const QWDDX &);

	bool operator<(int);
	bool operator<(double);
    bool operator<(const QString &);
    bool operator<(const QWDDX &);

	bool operator>(int);
	bool operator>(double);
    bool operator>(const QString &);
    bool operator>(const QWDDX &);

    QWDDX &operator=(const bool);
    QWDDX &operator=(const int);
    QWDDX &operator=(const double);
    QWDDX &operator=(const char *);
    QWDDX &operator=(const wchar_t *);
    QWDDX &operator=(const QString &);
    QWDDX &operator=(const QDateTime &);
    QWDDX &operator=(const QWDDX &);

    QWDDX join(const QWDDX &);
    void setType(QWDDXType);
    QWDDXType type() const;
	int size();
	QString StructKeyAt(const int);
    QString toString() const;
    QByteArray toBinary() const;
    double toNumber() const;
    int toInt() const;
    bool canConvertToNumber();
    QDateTime toDateTime() const;
    bool toBool() const;


	// Member Variables
    QVector<QWDDX> *m_Array;
    QMap<QString, QWDDX> *m_Struct;
    QString *m_String;
    QByteArray *m_ByteArray;
	double m_Number;
	bool m_Bool;
    QDateTime *m_DateTime;
	QWDDXType m_Type;
    quint32 m_ArrayDimension;
    QWDDX *m_HiddenScopeFirst;
    QWDDX *m_HiddenScopeLast;
};

Q_DECL_EXPORT bool operator!=(int, const QWDDX &);
Q_DECL_EXPORT bool operator!=(double, const QWDDX &);
Q_DECL_EXPORT bool operator!=(const QString &, const QWDDX &);

Q_DECL_EXPORT bool operator<=(int, const QWDDX &);
Q_DECL_EXPORT bool operator<=(double, const QWDDX &);
Q_DECL_EXPORT bool operator<=(const QString &, const QWDDX &);

Q_DECL_EXPORT bool operator>=(int, const QWDDX &);
Q_DECL_EXPORT bool operator>=(double, const QWDDX &);
Q_DECL_EXPORT bool operator>=(const QString &, const QWDDX &);

Q_DECL_EXPORT bool operator<(int, const QWDDX &);
Q_DECL_EXPORT bool operator<(double, const QWDDX &);
Q_DECL_EXPORT bool operator<(const QString &, const QWDDX &);

Q_DECL_EXPORT bool operator>(int, const QWDDX &);
Q_DECL_EXPORT bool operator>(double, const QWDDX &);
Q_DECL_EXPORT bool operator>(const QString &, const QWDDX &);

Q_DECL_EXPORT bool operator==(int, const QWDDX &);
//Q_DECL_EXPORT bool operator==(const QString &, int);
//Q_DECL_EXPORT bool operator==(const QString &, double);

Q_DECL_EXPORT QWDDX operator/(int, const QWDDX &);
Q_DECL_EXPORT QWDDX operator/(double, const QWDDX &);
Q_DECL_EXPORT QWDDX operator/(const QString &, const QWDDX &);
Q_DECL_EXPORT double operator/(const QWDDX &, const QWDDX &);

Q_DECL_EXPORT QWDDX operator&(int, const QWDDX &);
Q_DECL_EXPORT QWDDX operator&(double, const QWDDX &);
Q_DECL_EXPORT QWDDX operator&(const QString &, const QWDDX &);

#endif // QWDDX_H
