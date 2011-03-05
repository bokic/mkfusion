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
	QWDDX(const wchar_t*);
	QWDDX(const QString&);
	QWDDX(const QDateTime&);

	QWDDX(const QWDDXType);

	operator bool();
	operator int();
	operator double();
	operator QString();
	operator QDateTime();

	QWDDX& operator+(bool);
	QWDDX& operator+(int);
	QWDDX& operator+(double);
	QWDDX& operator+(const wchar_t*);
	QWDDX& operator+(const QString&);
	QWDDX& operator+(const QWDDX&);
	friend QWDDX& operator+(int, const QWDDX&);
	friend QWDDX& operator+(double, const QWDDX&);
	friend QWDDX& operator+(const wchar_t*, const QWDDX&);
	friend QWDDX& operator+(const QString&, const QWDDX&);

	QWDDX& operator+=(int);
	//QWDDX& operator+=(double);
	//QWDDX& operator+=(const wchar_t*);
	//QWDDX& operator+=(const QString&);
	//QWDDX& operator+=(const QWDDX&);
	//friend QWDDX& operator+=(int, const QWDDX&);
	//friend QWDDX& operator+=(double, const QWDDX&);
	//friend QWDDX& operator+=(const QString&, const QWDDX&);

	QWDDX& operator-(int);
	QWDDX& operator-(double);
	QWDDX& operator-(const QString&);
	QWDDX& operator-(const QWDDX&);
	friend QWDDX& operator-(int, const QWDDX&);
	friend QWDDX& operator-(double, const QWDDX&);
	friend QWDDX& operator-(const QString&, const QWDDX&);

	//QWDDX& operator-=(int);
	//QWDDX& operator-=(double);
	//QWDDX& operator-=(const QString&);
	//QWDDX& operator-=(const QWDDX&);
	//friend QWDDX& operator-=(int, const QWDDX&);
	//friend QWDDX& operator-=(double, const QWDDX&);
	//friend QWDDX& operator-=(const QString&, const QWDDX&);

	QWDDX& operator*(int);
	QWDDX& operator*(double);
	QWDDX& operator*(const QString&);
	QWDDX& operator*(const QWDDX&);
	friend QWDDX& operator*(int, const QWDDX&);
	friend QWDDX& operator*(double, const QWDDX&);
	friend QWDDX& operator*(const QString&, const QWDDX&);

	//QWDDX& operator*=(int);
	//QWDDX& operator*=(double);
	//QWDDX& operator*=(const QString&);
	//QWDDX& operator*=(const QWDDX&);
	//friend QWDDX& operator*=(int, const QWDDX&);
	//friend QWDDX& operator*=(double, const QWDDX&);
	//friend QWDDX& operator*=(const QString&, const QWDDX&);

	QWDDX& operator/(int);
	QWDDX& operator/(double);
	QWDDX& operator/(const QString&);
	QWDDX& operator/(const QWDDX&);
	friend QWDDX& operator/(int, const QWDDX&);
	friend QWDDX& operator/(double, const QWDDX&);
	friend QWDDX& operator/(const QString&, const QWDDX&);

	//QWDDX& operator/=(int);
	//QWDDX& operator/=(double);
	//QWDDX& operator/=(const QString&);
	//QWDDX& operator/=(const QWDDX&);
	//friend QWDDX& operator/=(int, const QWDDX&);
	//friend QWDDX& operator/=(double, const QWDDX&);
	//friend QWDDX& operator/=(const QString&, const QWDDX&);

	QWDDX& operator&(int);
	QWDDX& operator&(double);
	QWDDX& operator&(const wchar_t*);
	QWDDX& operator&(const QString&);
	QWDDX& operator&(const QWDDX&);
	friend QWDDX& operator&(int, const QWDDX&);
	friend QWDDX& operator&(double, const QWDDX&);
	friend QWDDX& operator&(const QString&, const QWDDX&);

	//QWDDX& operator&=(int);
	//QWDDX& operator&=(double);
	//QWDDX& operator&=(const wchar_t*);
	//QWDDX& operator&=(const QString&);
	//QWDDX& operator&=(const QWDDX&);
	//friend QWDDX& operator&=(int, const QWDDX&);
	//friend QWDDX& operator&=(double, const QWDDX&);
	//friend QWDDX& operator&=(const QString&, const QWDDX&);

	QWDDX& operator[](const double);
	QWDDX& operator[](const QString&);
	QWDDX& operator[](const wchar_t*);
	QWDDX& operator[](const QWDDX&);

	bool operator==(int);
	bool operator==(double);
	bool operator==(const QString&);
	bool operator==(const QWDDX&);

	bool operator!=(int);
	bool operator!=(double);
	bool operator!=(const QString&);
	bool operator!=(const QWDDX&);

	bool operator<=(int);
	bool operator<=(double);
	bool operator<=(const QString&);
	bool operator<=(const QWDDX&);

	bool operator>=(int);
	bool operator>=(double);
	bool operator>=(const QString&);
	bool operator>=(const QWDDX&);

	bool operator<(int);
	bool operator<(double);
	bool operator<(const QString&);
	bool operator<(const QWDDX&);

	bool operator>(int);
	bool operator>(double);
	bool operator>(const QString&);
	bool operator>(const QWDDX&);

	QWDDX& operator=(int);
	QWDDX& operator=(double);
	QWDDX& operator=(const wchar_t*);
	QWDDX& operator=(const QString&);
	QWDDX& operator=(const QDateTime&);

	QWDDX& join(const QWDDX&);
	QWDDXType getType();
	int size();
	QWDDX& wr(bool);
	QString StructKeyAt(const int);
	QString toString();
	QByteArray toBinary();
	double toNumber();
	bool canToNumber();
	QDateTime toDateTime();
	bool toBool();

	// Member Variables
	QVector<QWDDX> m_Array;
	quint32 m_ArrayDimension;
	QMap<QString, QWDDX> m_Struct;
	QString m_String;
	QByteArray m_ByteArray;
	double m_Number;
	bool m_Bool;
	QDateTime m_DateTime;
	QWDDXType m_Type;
};

#endif // QWDDX_H
