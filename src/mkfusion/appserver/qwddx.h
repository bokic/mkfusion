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
		Recordset,
		NotImplemented,
		Error
	};

public:
	QWDDX();

	QWDDX(bool);
	QWDDX(int);
	QWDDX(double);
	QWDDX(const char*);
	QWDDX(const wchar_t*);
    QWDDX(const QString &);
    QWDDX(const QDateTime &);

    QWDDX(const QWDDX &);

	QWDDX(const QWDDXType);

    ~QWDDX();

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

    QWDDX operator=(bool);
    QWDDX operator=(int);
    QWDDX operator=(double);
    QWDDX operator=(const char *);
    QWDDX operator=(const wchar_t *);
    QWDDX operator=(const QString &);
    QWDDX operator=(const QDateTime &);
    QWDDX operator=(const QWDDX &);

    QWDDX join(const QWDDX &);
    void setType(QWDDXType);
    QWDDXType type() const;
	int size();
	QString StructKeyAt(const int);
    QString toString() const;
    QByteArray toBinary() const;
    double toNumber() const;
    bool canConvertToNumber();
    QDateTime toDateTime() const;
    bool toBool() const;


	// Member Variables
    QVector<QWDDX> *m_Array;
	quint32 m_ArrayDimension;
    QMap<QString, QWDDX> *m_Struct;
    QString *m_String;
    QByteArray *m_ByteArray;
	double m_Number;
	bool m_Bool;
    QDateTime *m_DateTime;
	QWDDXType m_Type;
};

Q_DECL_EXPORT QWDDX operator/(int, const QWDDX &);
Q_DECL_EXPORT QWDDX operator/(double, const QWDDX &);
Q_DECL_EXPORT QWDDX operator/(const QString &, const QWDDX &);
Q_DECL_EXPORT QWDDX operator&(int, const QWDDX &);
Q_DECL_EXPORT QWDDX operator&(double, const QWDDX &);
Q_DECL_EXPORT QWDDX operator&(const QString &, const QWDDX &);

#endif // QWDDX_H
