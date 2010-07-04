#ifndef QWDDX_H
#define QWDDX_H

#include <QDateTime>
#include <QVariant>
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
	QWDDX(int);
	QWDDX(double);
	QWDDX(const char*);
	QWDDX(const wchar_t*);
	QWDDX(const QString&);
	QWDDX(const QDateTime&);
	QWDDX(const QWDDXType);
	operator int();
	operator double();
	operator QString();
	operator QDateTime();
	QWDDX& operator+(int);
	QWDDX& operator+(double);
	QWDDX& operator+(const char*);
	QWDDX& operator+(const wchar_t*);
	QWDDX& operator+(const QString&);
	QWDDX& operator+(const QWDDX&);
	friend QWDDX& operator+(int, const QWDDX&);
	friend QWDDX& operator+(double, const QWDDX&);
	friend QWDDX& operator+(const QString&, const QWDDX&);
	QWDDX& operator-(int);
	QWDDX& operator-(double);
	QWDDX& operator-(const QString&);
	QWDDX& operator-(const QWDDX&);
	friend QWDDX& operator-(int, const QWDDX&);
	friend QWDDX& operator-(double, const QWDDX&);
	friend QWDDX& operator-(const QString&, const QWDDX&);
	QWDDX& operator*(int);
	QWDDX& operator*(double);
	QWDDX& operator*(const QString&);
	QWDDX& operator*(const QWDDX&);
	friend QWDDX& operator*(int, const QWDDX&);
	friend QWDDX& operator*(double, const QWDDX&);
	friend QWDDX& operator*(const QString&, const QWDDX&);
	QWDDX& operator/(int);
	QWDDX& operator/(double);
	QWDDX& operator/(const QString&);
	QWDDX& operator/(const QWDDX&);
	friend QWDDX& operator/(int, const QWDDX&);
	friend QWDDX& operator/(double, const QWDDX&);
	friend QWDDX& operator/(const QString&, const QWDDX&);
	QWDDX& operator&(int);
	QWDDX& operator&(double);
	QWDDX& operator&(const char*);
	QWDDX& operator&(const wchar_t*);
	QWDDX& operator&(const QString&);
	QWDDX& operator&(const QWDDX&);
	friend QWDDX& operator&(int, const QWDDX&);
	friend QWDDX& operator&(double, const QWDDX&);
	friend QWDDX& operator&(const QString&, const QWDDX&);
	QWDDX& join(const QWDDX&);
	QWDDXType getType();
	int size();
	QWDDX& operator[](const double);
	QWDDX& operator[](const QString&);
	QWDDX& operator[](const char*);
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
	QWDDX& operator=(const char*);
	QWDDX& operator=(const wchar_t*);
	QWDDX& operator=(const QString&);
	QWDDX& operator=(const QDateTime&);
	QWDDX& wr(bool);
	QString StructKeyAt(const int);
	QString toString();
	QByteArray toBinary();
	double toNumber();
	bool canToNumber();
	QDateTime toDateTime();
	bool toBool();

	QVector<QWDDX> m_Array;
	quint32 m_ArrayDimension;
	QMap<QString, QWDDX> m_Struct;
	QString m_String;
	QByteArray m_ByteArray;
	double m_Number;
	bool m_Bool;
	QDateTime m_DateTime;
	QWDDXType m_Type;
	bool m_CanCreateChildren;
};

#endif // QWDDX_H
