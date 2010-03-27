#ifndef QWDDX_H
#define QWDDX_H

#include <QDateTime>
#include <QVariant>
#include <QVector>
#include <QString>
#include <QHash>

class QWDDX
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
	QWDDX(QWDDXType);
	const QWDDX & operator=(QString);
	const QWDDX & operator=(char*);
	const QWDDX & operator=(double);
	const QWDDX & operator=(bool);
	const QWDDX & operator=(QDateTime);
	const QWDDX & operator=(QByteArray);
	QWDDXType getType();
	int size();
	QWDDX & operator[](const int);
	QWDDX & operator[](QString);
	QWDDX & operator[](char*);
	QString StructKeyAt(int);
	QString toString();
	QByteArray toBinary();
	double toNumber();
	QDateTime toDateTime();
	bool toBool();
protected:
private:
	QVector<QWDDX> m_Array;
	QHash<QString, QWDDX> m_Struct;
	QString m_String;
	QByteArray m_ByteArray;
	double m_Number;
	bool m_Bool;
	QDateTime m_DateTime;
	QWDDXType m_Type;
};

#endif // QWDDX_H