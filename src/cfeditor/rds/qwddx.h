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
    enum QWDDXType
    {
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
    QWDDX(QWDDXType type);
    QWDDX &operator=(const QString &value);
    QWDDX &operator=(const char *value);
    QWDDX &operator=(double value);
    QWDDX &operator=(bool value);
    QWDDX &operator=(const QDateTime &value);
    QWDDX &operator=(const QByteArray &value);
    QWDDXType type() const;
    int size() const;
    QWDDX &operator[](int index);
    QWDDX &operator[](const QString &index);
    QWDDX &operator[](const char *index);
    QWDDX at(int index) const;
    QString StructKeyAt(int index) const;
    QString toString() const;
    QByteArray toBinary() const;
    double toNumber() const;
    QDateTime toDateTime() const;
    bool toBool() const;
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
