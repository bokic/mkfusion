#include "qcftemplate.h"
#include "cffunctions.h"
#include "qmkfusionexception.h"
#include <QStringList>
#include <QDateTime>
#include <QDate>
#include <QFile>
#include <QDir>

#include <math.h>

#ifdef Q_OS_WIN
#include <windows.h>
#elif defined Q_OS_LINUX
#include <unistd.h>
#include <time.h>
#else
#error Windows and Linux OSs are currently supported.
#endif

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

Q_DECL_EXPORT double cf_Abs(double number)
{
    return fabs(number);
}

Q_DECL_EXPORT double cf_ACos(double number)
{
    if ((number < -1)||(number > 1))
    {
        throw QMKFusionInvalidArgumentException("ACos", 1, number, -1, 1);
    }

    return acos(number);
}

Q_DECL_EXPORT void cf_AddSOAPRequestHeader(QWDDX &webservice, const QString &_namespace, const QString &name, const QWDDX &value, bool mustunderstand)
{
    Q_UNUSED(webservice);
    Q_UNUSED(_namespace);
    Q_UNUSED(name);
    Q_UNUSED(value);
    Q_UNUSED(mustunderstand);

    throw QMKFusionException("Not Implemented", "AddSOAPRequestHeader is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_AddSOAPResponseHeader(const QString &_namespace, const QString &name, const QWDDX &value, bool mustunderstand)
{
    Q_UNUSED(_namespace);
    Q_UNUSED(name);
    Q_UNUSED(value);
    Q_UNUSED(mustunderstand);

    throw QMKFusionException("Not Implemented", "AddSOAPResponseHeader is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_AjaxLink(const QString &URL)
{
    Q_UNUSED(URL);

    throw QMKFusionException("Not Implemented", "AjaxLink is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_AjaxOnLoad(const QString &functionName)
{
    Q_UNUSED(functionName);

    throw QMKFusionException("Not Implemented", "AjaxOnLoad is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_ArrayAppend(QWDDX &array, const QWDDX &value)
{
    if (array.type() != QWDDX::Array)
    {
        throw QMKFusionException("Not Array", "Not Array");
    }

    if (array.m_ArrayDimension > 1)
    {
        if (value.type() != QWDDX::Array)
        {
            throw QMKFusionArrayGenericMultiDimException();
        }
        if (array.m_ArrayDimension != value.m_ArrayDimension + 1)
        {
            throw QMKFusionArrayGenericMultiDimException();
        }
    }

    array.m_Array->append(value);

    return true;
}

Q_DECL_EXPORT double cf_ArrayAvg(const QWDDX &array)
{
    if (array.type() != QWDDX::Array)
    {
        throw QMKFusionException("Not Array", "Not Array");
    }

    if (array.m_ArrayDimension != 1)
    {
        throw QMKFusionArrayNotOneDimensionException();
    }

    if (array.m_Array->size() == 0)
    {
        return 0;
    }

    double sum = 0;

    for (const QWDDX &item : *array.m_Array)
    {
        sum += item.toNumber();
    }

    return sum / array.m_Array->size();
}

Q_DECL_EXPORT bool cf_ArrayClear(QWDDX &array)
{
    if (array.type() != QWDDX::Array)
    {
        throw QMKFusionException("Not Array", "Not Array");
    }

    array.m_Array->clear();

    return true;
}

Q_DECL_EXPORT bool cf_ArrayDeleteAt(QWDDX &array, int position)
{
    if (array.type() != QWDDX::Array)
    {
        throw QMKFusionException("Not Array", "Not Array");
    }

    if ((position < 1)||(position > array.m_Array->size()))
    {
        throw QMKFusionInvalidArrayIndexException(position, array.m_Array->size());
    }

    array.m_Array->remove(position - 1);

    return true;
}

Q_DECL_EXPORT bool cf_ArrayInsertAt(QWDDX &array, int position, const QWDDX &value)
{
    if (array.type() != QWDDX::Array)
    {
        throw QMKFusionException("Not Array", "Not Array");
    }

    if (array.m_ArrayDimension > 1)
    {
        if (value.type() != QWDDX::Array)
        {
            throw QMKFusionArrayGenericMultiDimException();
        }
        if (array.m_ArrayDimension != value.m_ArrayDimension + 1)
        {
            throw QMKFusionArrayGenericMultiDimException();
        }
    }

    if ((position < 1)||(position > array.m_Array->size()))
    {
        throw QMKFusionInvalidArrayIndexException(position, array.m_Array->size());
    }

    array.m_Array->insert(position - 1, value);

    return true;
}

Q_DECL_EXPORT bool cf_ArrayIsDefined(const QWDDX &array, int elementIndex)
{
    if (array.type() != QWDDX::Array)
    {
        throw QMKFusionException("Not Array", "Not Array");
    }

    if ((elementIndex < 1)||(elementIndex > array.m_Array->size()))
    {
        throw QMKFusionInvalidArrayIndexException(elementIndex, array.m_Array->size());
    }

    if (array.m_Array->at(elementIndex - 1).type() == QWDDX::Null)
    {
        return false;
    }

    return true;
}

Q_DECL_EXPORT bool cf_ArrayIsEmpty(const QWDDX &array)
{
    if (array.type() != QWDDX::Array)
    {
        throw QMKFusionException("Not Array", "Not Array");
    }

    if (array.m_Array->size() == 0)
    {
        return true;
    }

    return false;
}

Q_DECL_EXPORT int cf_ArrayLen(const QWDDX &array)
{
    if (array.type() != QWDDX::Array)
    {
        throw QMKFusionException("Not Array", "Not Array");
    }

    return array.m_Array->size();
}

Q_DECL_EXPORT double cf_ArrayMax(const QWDDX &array)
{
    if (array.type() != QWDDX::Array)
    {
        throw QMKFusionException("Not Array", "Not Array");
    }

    if (array.m_ArrayDimension != 1)
    {
        throw QMKFusionArrayNotOneDimensionException();
    }

    double ret = 0;

    // TODO: Optimize with c11 for container iterator.
    for(int c = 0; c < array.m_Array->size(); c++)
    {
        const QWDDX &temp = array.m_Array->at(c);

        if (c == 0)
        {
            ret = temp.toNumber();
        }
        else
        {
            if (temp.toNumber() > ret)
            {
                ret = temp.toNumber();
            }
        }
    }

    return ret;
}

Q_DECL_EXPORT double cf_ArrayMin(const QWDDX &array)
{
    if (array.type() != QWDDX::Array)
    {
        throw QMKFusionException("Not Array", "Not Array");
    }

    if (array.m_ArrayDimension != 1)
    {
        throw QMKFusionArrayNotOneDimensionException();
    }

    double ret = 0;

    // TODO: Optimize with c11 for container iterator.
    for(int c = 0; c < array.m_Array->size(); c++)
    {
        const QWDDX &temp = array.m_Array->at(c);

        if (c == 0)
        {
            ret = temp.toNumber();
        }
        else
        {
            if (temp.toNumber() < ret)
            {
                ret = temp.toNumber();
            }
        }
    }

    return ret;
}

Q_DECL_EXPORT QWDDX cf_ArrayNew(int dimension)
{
    if ((dimension < 1)||(dimension > 3))
    {
        throw QMKFusionBadArrayDimensionException(dimension);
    }

    QWDDX ret(QWDDX::Array);

    ret.m_ArrayDimension = dimension;

    return ret;
}

Q_DECL_EXPORT bool cf_ArrayPrepend(QWDDX &array, const QWDDX &value)
{
    if (array.type() != QWDDX::Array)
    {
        throw QMKFusionException("Not Array", "Not Array");
    }

    if (array.m_ArrayDimension > 1)
    {
        if (value.type() != QWDDX::Array)
        {
            throw QMKFusionArrayGenericMultiDimException();
        }
        if (array.m_ArrayDimension != value.m_ArrayDimension + 1)
        {
            throw QMKFusionArrayGenericMultiDimException();
        }
    }

    QWDDX temp = value;

    array.m_Array->insert(0, temp);

    return true;
}

Q_DECL_EXPORT bool cf_ArrayResize(QWDDX &array, int minSize)
{
    if (array.type() != QWDDX::Array)
    {
        throw QMKFusionException("Not Array", "Not Array");
    }

    if (array.m_Array->size() < minSize)
    {
        array.m_Array->resize(minSize);
    }

    return true;
}

Q_DECL_EXPORT bool cf_ArraySet(QWDDX &array, int start, int end, const QWDDX &value)
{
    if (array.type() != QWDDX::Array)
    {
        throw QMKFusionException("Not Array", "Not Array");
    }

    if((start > end)||(start <= 0))
    {
        throw QMKFusionArraySetRangeException(start, end);
    }

    if (array.m_ArrayDimension > 1)
    {
        if (value.type() != QWDDX::Array)
        {
            throw QMKFusionArrayGenericMultiDimException();
        }
        if (array.m_ArrayDimension != value.m_ArrayDimension + 1)
        {
            throw QMKFusionArrayGenericMultiDimException();
        }
    }

    QWDDX temp = value;

    for(int c = start - 1; c < end; c++)
    {
        array.m_Array->replace(c, temp);
    }

    return true;
}

Q_DECL_EXPORT bool cf_ArraySort(QWDDX &array, const QString &sort_type, const QString &sort_order)
{
    if (array.type() != QWDDX::Array)
    {
        throw QMKFusionException("Error Occurred While Processing Request", "Parameter should be array.");
    }

    if (array.m_ArrayDimension != 1)
    {
        throw QMKFusionException("Error Occurred While Processing Request", "The array passed cannot contain more than one dimension.");
    }

    if ((sort_type.compare("Text", Qt::CaseInsensitive) != 0)&&(sort_type.compare("TextNoCase", Qt::CaseInsensitive) != 0)&&(sort_type.compare("Numeric", Qt::CaseInsensitive) != 0))
    {
        throw QMKFusionException("Invalid sort type " + sort_type + ".", "Valid sort type values are: Text, TextNoCase, and Numeric.");
    }

    if ((sort_order.compare("Asc", Qt::CaseInsensitive) != 0)&&(sort_order.compare("Desc", Qt::CaseInsensitive) != 0))
    {
        throw QMKFusionException("Invalid sort order " + sort_order + ".", "Valid sort order values are: Asc and Desc.");
    }

    if ((sort_type.compare("Numeric", Qt::CaseInsensitive) == 0)&&(sort_order.compare("Asc", Qt::CaseInsensitive) == 0))
    {
        qStableSort(array.m_Array->begin(), array.m_Array->end(), [](const QWDDX &s1, const QWDDX &s2)
        {
            return s1.toNumber() < s2.toNumber();
        });

        return true;
    }
    else if ((sort_type.compare("Numeric", Qt::CaseInsensitive) == 0)&&(sort_order.compare("Desc", Qt::CaseInsensitive) == 0))
    {
        qStableSort(array.m_Array->begin(), array.m_Array->end(), [](const QWDDX &s1, const QWDDX &s2)
        {
            return s1.toNumber() > s2.toNumber();
        });

        return true;
    }
    else if ((sort_type.compare("Text", Qt::CaseInsensitive) == 0)&&(sort_order.compare("Asc", Qt::CaseInsensitive) == 0))
    {
        qStableSort(array.m_Array->begin(), array.m_Array->end(), [](const QWDDX &s1, const QWDDX &s2)
        {
            return s1.toString() < s2.toString();
        });

        return true;
    }
    else if ((sort_type.compare("Text", Qt::CaseInsensitive) == 0)&&(sort_order.compare("Desc", Qt::CaseInsensitive) == 0))
    {
        qStableSort(array.m_Array->begin(), array.m_Array->end(), [](const QWDDX &s1, const QWDDX &s2)
        {
            return s1.toString() > s2.toString();
        });

        return true;
    }
    else if ((sort_type.compare("TextNoCase", Qt::CaseInsensitive) == 0)&&(sort_order.compare("Asc", Qt::CaseInsensitive) == 0))
    {
        qStableSort(array.m_Array->begin(), array.m_Array->end(), [](const QWDDX &s1, const QWDDX &s2)
        {
            return s1.toString().compare(s2.toString(), Qt::CaseInsensitive) < 0;
        });

        return true;
    }
    else if ((sort_type.compare("TextNoCase", Qt::CaseInsensitive) == 0)&&(sort_order.compare("Desc", Qt::CaseInsensitive) == 0))
    {
        qStableSort(array.m_Array->begin(), array.m_Array->end(), [](const QWDDX &s1, const QWDDX &s2)
        {
            return s1.toString().compare(s2.toString(), Qt::CaseInsensitive) > 0;
        });

        return true;
    }

    return false;
}

Q_DECL_EXPORT double cf_ArraySum(const QWDDX &array)
{
    if (array.type() != QWDDX::Array)
    {
        throw QMKFusionException("Not Array", "Not Array");
    }

    if (array.m_ArrayDimension != 1)
    {
        throw QMKFusionArrayNotOneDimensionException();
    }

    if (array.m_Array->size() == 0)
    {
        return 0;
    }

    double sum = 0;

    for (int c = 0; c < array.m_Array->size(); c++)
    {
        sum += array.m_Array->at(c).toNumber();
    }

    return sum;
}

Q_DECL_EXPORT bool cf_ArraySwap(QWDDX &array, int position1, int position2)
{
    if (array.type() != QWDDX::Array)
    {
        throw QMKFusionException("Not Array", "Not Array");
    }

    position1--;
    position2--;

    if((position1 < 0)||(position1 >= array.m_Array->size()))
    {
        throw QMKFusionArraySwapRangeException(position1 + 1, array.m_Array->size());
    }
    if((position2 < 0)||(position2 >= array.m_Array->size()))
    {
        throw QMKFusionArraySwapRangeException(position2 + 1, array.m_Array->size());
    }

    QWDDX temp = array.m_Array->at(position1);
    array.m_Array[position1] = array.m_Array[position2];
    array.m_Array->replace(position2, temp);

    return true;
}

Q_DECL_EXPORT QString cf_ArrayToList(const QWDDX &array, const QString &delimiter)
{
    QString ret;

    if (array.type() != QWDDX::Array)
    {
        throw QMKFusionException("Not Array", "Not Array");
    }

    if (array.m_ArrayDimension != 1)
    {
        throw QMKFusionArrayNotOneDimensionException();
    }

    for(int c = 0; c < array.m_Array->size(); c++)
    {
        if (c > 0)
        {
            ret.append(delimiter);
        }

        ret.append(array.m_Array->at(c).toString());
    }

    return ret;
}

Q_DECL_EXPORT int cf_Asc(const QString &string)
{
    if (string.isEmpty())
    {
        return 0;
    }

    return string[0].unicode();
}

Q_DECL_EXPORT double cf_ASin(double number)
{
    return asin(number);
}

Q_DECL_EXPORT double cf_Atn(double number)
{
    return atan(number);
}

Q_DECL_EXPORT QString cf_BinaryDecode(const QString &string, const QString &binaryencoding)
{
    Q_UNUSED(string);
    Q_UNUSED(binaryencoding);

    throw QMKFusionException("Not Implemented", "BinaryDecode is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_BinaryEncode(const QString &binarydata, const QString &encoding)
{
    Q_UNUSED(binarydata);
    Q_UNUSED(encoding);

    throw QMKFusionException("Not Implemented", "BinaryEncode is not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_BitAnd(int number1, int number2)
{
    return number1 & number2;
}

Q_DECL_EXPORT int cf_BitMaskClear(int number, int start, int length)
{
    if((start < 0)||(start > 31))
    {
        throw QMKFusionInvalidArgumentException("BitMaskClear", 2, start, 0, 31);
    }

    if((length < 0)||(length > 31))
    {
        throw QMKFusionInvalidArgumentException("BitMaskClear", 3, length, 0, 31);
    }

    return number & ~(((1 << length) - 1) << start);
}

Q_DECL_EXPORT int cf_BitMaskRead(int number, int start, int length)
{

    if((start < 0)||(start > 31))
    {
        throw QMKFusionInvalidArgumentException("BitMaskRead", 2, start, 0, 31);
    }

    if((length < 0)||(length > 31))
    {
        throw QMKFusionInvalidArgumentException("BitMaskRead", 3, length, 0, 31);
    }

    return (number >> start) & ((1 << length) - 1);
}

Q_DECL_EXPORT int cf_BitMaskSet(int number, int mask, int start, int length)
{
    if((start < 0)||(start > 31))
    {
        throw QMKFusionInvalidArgumentException("BitMaskSet", 2, start, 0, 31);
    }

    if((length < 0)||(length > 31))
    {
        throw QMKFusionInvalidArgumentException("BitMaskSet", 3, length, 0, 31);
    }

    mask &= (1 << length) - 1;
    return number & ~((((1 << length) - 1) << start) | mask) << start;
}

Q_DECL_EXPORT int cf_BitNot(int number)
{
    return ~number;
}

Q_DECL_EXPORT int cf_BitOr(int number1, int number2)
{
    return number1 | number2;
}

Q_DECL_EXPORT int cf_BitSHLN(int number, int count)
{
    if ((count < 0)||(count > 31))
    {
        throw QMKFusionInvalidArgumentException("BitSHLN", 2, count, 0, 31);
    }

    return number << count;
}

Q_DECL_EXPORT int cf_BitSHRN(int number, int count)
{
    if ((count < 0)||(count > 31))
    {
        throw QMKFusionInvalidArgumentException("BitSHRN", 2, count, 0, 31);
    }

    return number >> count;
}

Q_DECL_EXPORT int cf_BitXor(int number1, int number2)
{
    return number1 ^ number2;
}

Q_DECL_EXPORT double cf_Ceiling(double number)
{
    return ceil(number);
}

Q_DECL_EXPORT QString cf_CharsetDecode(const QString &string, const QString &encoding)
{
    Q_UNUSED(string);
    Q_UNUSED(encoding);

    throw QMKFusionException("Not Implemented", "CharsetDecode is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_CharsetEncode(const QString &binaryobject, const QString &encoding)
{
    Q_UNUSED(binaryobject);
    Q_UNUSED(encoding);

    throw QMKFusionException("Not Implemented", "CharsetEncode is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_Chr(int number)
{
    return QString(QChar(number));
}

Q_DECL_EXPORT QString cf_CJustify(const QString &string, int length)
{
    QString ret;

    if (length < 0)
    {
        throw QMKFusionInvalidArgumentException("CJustify", 2, length, "positive integer");
    }

    if (length <= string.length())
    {
        return string;
    }

    ret = string;

    int start = (length - string.length()) / 2;

    for(int c = 0; c < start; c++)
    {
        ret = ' ' + ret;
    }

    return ret;
}

Q_DECL_EXPORT int cf_Compare(const QString &string1, const QString &string2)
{
    return string1.compare(string2, Qt::CaseSensitive);
}

Q_DECL_EXPORT int cf_CompareNoCase(const QString &string1, const QString &string2)
{
    return string1.compare(string2, Qt::CaseInsensitive);
}

Q_DECL_EXPORT double cf_Cos(double number)
{
    return cos(number);
}

Q_DECL_EXPORT QWDDX cf_CreateDate(int year, int month, int day)
{
    if ((month < 1)||(month > 12))
    {
        throw QMKFusionInvalidArgumentException("CreateDate", 2, month, 1, 12);
    }

    if ((day < 1)||(day > 31))
    {
        throw QMKFusionInvalidArgumentException("CreateDate", 3, day, 1, 31);
    }

    return QDateTime(QDate(year, month, day));
}

Q_DECL_EXPORT QWDDX cf_CreateDateTime(int year, int month, int day, int hour, int minute, int second)
{
    return QDateTime(QDate(year, month, day), QTime(hour, minute, second));
}

Q_DECL_EXPORT QWDDX cf_CreateObject(const QString &type)
{
    Q_UNUSED(type);

    throw QMKFusionException("Not Implemented", "CreateObject is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_CreateODBCDate(const QDateTime &date)
{
    return QDateTime(QDate(date.date().year(), date.date().month(), date.date().day()));
}

Q_DECL_EXPORT QWDDX cf_CreateODBCDateTime(const QDateTime &date)
{
    return date;
}

Q_DECL_EXPORT QWDDX cf_CreateODBCTime(const QDateTime &date)
{
    return QDateTime(QDate(1899, 12, 30), QTime(date.time().hour(), date.time().minute(), date.time().second()));
}

Q_DECL_EXPORT QWDDX cf_CreateTime(int hour, int minute, int second)
{
    if ((hour < 0)||(hour > 23))
    {
        throw QMKFusionInvalidArgumentException("CreateTime", 1, hour, 0, 23);
    }

    if ((minute < 0)||(minute > 59))
    {
        throw QMKFusionInvalidArgumentException("CreateTime", 2, minute, 0, 59);
    }

    if ((second < 0)||(second > 59))
    {
        throw QMKFusionInvalidArgumentException("CreateTime", 3, second, 0, 59);
    }

    return QDateTime(QDate(1899, 12, 30), QTime(hour, minute, second));
}

Q_DECL_EXPORT QWDDX cf_CreateTimeSpan(int days, int hours, int minutes, int seconds)
{
    QDateTime ret = QDateTime(QDate(1899, 12, 30));

    ret.addDays(days);
    ret.addSecs((hours * 60 * 60) + (minutes * 60) + seconds);

    return ret;
}

Q_DECL_EXPORT QString cf_CreateUUID()
{
    throw QMKFusionException("Not Implemented", "CreateUUID is not Implemented (yet:))");
}

Q_DECL_EXPORT QDateTime cf_DateAdd(const QString &datepart, int number, QDateTime &date)
{
    throw QMKFusionException("Not Implemented", "DateAdd is not Implemented (yet:))");

    QWDDX temp = date;
    QDateTime ret = temp.toDateTime();

    if(datepart.compare("yyyy", Qt::CaseInsensitive) == 0)
    {
        ret.addYears(number);
    }
    else if(datepart.compare("q", Qt::CaseInsensitive) == 0)
    {

    }
    else if(datepart.compare("m", Qt::CaseInsensitive) == 0)
    {

    }
    else if(datepart.compare("y", Qt::CaseInsensitive) == 0)
    {

    }
    else if(datepart.compare("d", Qt::CaseInsensitive) == 0)
    {

    }
    else if(datepart.compare("w", Qt::CaseInsensitive) == 0)
    {

    }
    else if(datepart.compare("ww", Qt::CaseInsensitive) == 0)
    {

    }
    else if(datepart.compare("h", Qt::CaseInsensitive) == 0)
    {

    }
    else if(datepart.compare("n", Qt::CaseInsensitive) == 0)
    {

    }
    else if(datepart.compare("s", Qt::CaseInsensitive) == 0)
    {

    }
    else if(datepart.compare("l", Qt::CaseInsensitive) == 0)
    {

    }
    else
    {

    }

    return ret;
}

Q_DECL_EXPORT int cf_DateCompare(const QDateTime &date1, const QDateTime &date2, const QString &datePart)
{
    int val1, val2;

    if (datePart.compare("yyyy", Qt::CaseInsensitive) == 0)
    {
        val1 = date1.date().year();
        val2 = date2.date().year();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        return 0;
    }
    /*else if (datePart.compare("q", Qt::CaseInsensitive) == 0)
    {
        val1 = date1.date().year();
        val2 = date2.date().year();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        val1 = date1.date().month() / 4;
        val2 = date2.date().month() / 4;
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        return 0;
    }*/
    else if (datePart.compare("m", Qt::CaseInsensitive) == 0)
    {
        val1 = date1.date().year();
        val2 = date2.date().year();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        val1 = date1.date().month();
        val2 = date2.date().month();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        return 0;
    }
    else if (datePart.compare("d", Qt::CaseInsensitive) == 0)
    {
        val1 = date1.date().year();
        val2 = date2.date().year();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        val1 = date1.date().month();
        val2 = date2.date().month();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        val1 = date1.date().day();
        val2 = date2.date().day();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        return 0;
    }
    /*else if (datePart.compare("w", Qt::CaseInsensitive) == 0)
    {
        throw QMKFusionException("Not Implemented", "DateConvert is not Implemented (yet:))");
    }
    else if (datePart.compare("ww", Qt::CaseInsensitive) == 0)
    {
        throw QMKFusionException("Not Implemented", "DateConvert is not Implemented (yet:))");
    }*/
    else if (datePart.compare("h", Qt::CaseInsensitive) == 0)
    {
        val1 = date1.date().year();
        val2 = date2.date().year();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        val1 = date1.date().month();
        val2 = date2.date().month();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        val1 = date1.date().day();
        val2 = date2.date().day();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        val1 = date1.time().hour();
        val2 = date2.time().hour();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        return 0;
    }
    else if (datePart.compare("n", Qt::CaseInsensitive) == 0)
    {
        val1 = date1.date().year();
        val2 = date2.date().year();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        val1 = date1.date().month();
        val2 = date2.date().month();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        val1 = date1.date().day();
        val2 = date2.date().day();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        val1 = date1.time().hour();
        val2 = date2.time().hour();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        val1 = date1.time().minute();
        val2 = date2.time().minute();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        return 0;
    }
    else if (datePart.compare("s", Qt::CaseInsensitive) == 0)
    {
        val1 = date1.date().year();
        val2 = date2.date().year();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        val1 = date1.date().month();
        val2 = date2.date().month();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        val1 = date1.date().day();
        val2 = date2.date().day();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        val1 = date1.time().hour();
        val2 = date2.time().hour();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        val1 = date1.time().minute();
        val2 = date2.time().minute();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        val1 = date1.time().second();
        val2 = date2.time().second();
        if (val1 < val2) return -1;
        if (val1 > val2) return 1;
        return 0;
    }

    throw QMKFusionException(datePart + " is not a valid date/time format.", "The following list contains all valid datepart masks: yyyy, m, d, h, n, s");
}

Q_DECL_EXPORT QString cf_DateConvert(const QString &conversion_type, const QDateTime &date)
{
    Q_UNUSED(conversion_type);
    Q_UNUSED(date);

    throw QMKFusionException("Not Implemented", "DateConvert is not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_DateDiff(const QString &datepart, const QDateTime &date1, const QDateTime &date2)
{
    Q_UNUSED(datepart);
    Q_UNUSED(date1);
    Q_UNUSED(date2);

    throw QMKFusionException("Not Implemented", "DateDiff is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DateFormat(const QDateTime &date, const QString &mask)
{
    QMultiHash<QString, int> segments;
    QString ret = mask;
    int pos;

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("full", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 4, "dddd, mmmm d, yyyy");
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("long", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 4, "mmmm d, yyyy");
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("medium", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 6, "mmm d, yyyy");
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("short", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 5, "m/d/y");
        pos = i + 1;
    }

    /*pos = 0;
    while(1)
    {
        int i = ret.indexOf("gg", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 2, "__");
        segments.insert("gg", i);
        pos = i + 1;
    }*/

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("yyyy", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 4, "____");
        segments.insert("yyyy", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("yy", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 2, "__");
        segments.insert("yy", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("mmmm", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 4, "____");
        segments.insert("mmmm", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("mmm", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 3, "___");
        segments.insert("mmm", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("mm", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 2, "__");
        segments.insert("mm", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("m", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 1, "_");
        segments.insert("m", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("dddd", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 4, "____");
        segments.insert("dddd", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("ddd", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 3, "___");
        segments.insert("ddd", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("dd", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 2, "__");
        segments.insert("dd", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("d", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 1, "_");
        segments.insert("d", i);
        pos = i + 1;
    }

    for(int c = 0; c < segments.count(); c++)
    {
        const QString type = segments.keys().at(c);
        int pos = segments.values().at(c);

        if (type == "yyyy") ret.replace(pos, 4, date.toString("yyyy"));
        if (type == "yy") ret.replace(pos, 2, date.toString("yy"));
        if (type == "mmmm") ret.replace(pos, 4, date.toString("MMMM"));
        if (type == "mmm") ret.replace(pos, 3, date.toString("MMM"));
        if (type == "mm") ret.replace(pos, 2, date.toString("MM"));
        if (type == "m") ret.replace(pos, 1, date.toString("M"));
        if (type == "dddd") ret.replace(pos, 4, date.toString("dddd"));
        if (type == "ddd") ret.replace(pos, 3, date.toString("ddd"));
        if (type == "dd") ret.replace(pos, 2, date.toString("dd"));
        if (type == "d") ret.replace(pos, 1, date.toString("d"));
    }

    return ret;
}

Q_DECL_EXPORT int cf_DatePart(const QString &datepart, const QDateTime &date)
{
    if (datepart.compare("yyyy", Qt::CaseInsensitive) == 0)
    {
        return date.date().year();
    }
    else if (datepart.compare("q", Qt::CaseInsensitive) == 0)
    {
        return (date.date().month() / 4) + 1;
    }
    else if (datepart.compare("m", Qt::CaseInsensitive) == 0)
    {
        return date.date().month();
    }
    else if (datepart.compare("y", Qt::CaseInsensitive) == 0)
    {
        return date.date().dayOfYear();
    }
    else if (datepart.compare("d", Qt::CaseInsensitive) == 0)
    {
        return date.date().day();
    }
    else if (datepart.compare("w", Qt::CaseInsensitive) == 0)
    {
        return date.date().dayOfWeek();
    }
    else if (datepart.compare("ww", Qt::CaseInsensitive) == 0)
    {
        return date.date().weekNumber();
    }
    else if (datepart.compare("h", Qt::CaseInsensitive) == 0)
    {
        return date.time().hour();
    }
    else if (datepart.compare("n", Qt::CaseInsensitive) == 0)
    {
        return date.time().minute();
    }
    else if (datepart.compare("s", Qt::CaseInsensitive) == 0)
    {
        return date.time().second();
    }
    else if (datepart.compare("l", Qt::CaseInsensitive) == 0)
    {
        return date.time().msec();
    }

    throw QMKFusionException("DatePart called with invalid 'part' parameter.");
}

Q_DECL_EXPORT int cf_Day(const QDateTime &date)
{
    return date.date().day();
}

Q_DECL_EXPORT int cf_DayOfWeek(const QDateTime &date)
{
    return date.date().dayOfWeek();
}

Q_DECL_EXPORT QString cf_DayOfWeekAsString(int day_of_week, const QString &locale)
{
    Q_UNUSED(day_of_week);
    Q_UNUSED(locale);

    throw QMKFusionException("Not Implemented", "DayOfWeekAsString is not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_DayOfYear(const QDateTime &date)
{
    return date.date().dayOfYear();
}

Q_DECL_EXPORT int cf_DaysInMonth(const QDateTime &date)
{
    return date.date().daysInMonth();
}

Q_DECL_EXPORT int cf_DaysInYear(const QDateTime &date)
{
    return date.date().daysInYear();
}

Q_DECL_EXPORT QString cf_DE(const QString &string)
{
    Q_UNUSED(string);

    throw QMKFusionException("Not Implemented", "DE is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DecimalFormat(double number)
{
    Q_UNUSED(number);

    throw QMKFusionException("Not Implemented", "DecimalFormat is not Implemented (yet:))");
}

Q_DECL_EXPORT double cf_DecrementValue(double number)
{
    return number - 1;
}

Q_DECL_EXPORT QString cf_Decrypt(const QString &encrypted_string, const QString &key, const QString &algorithm, const QString &encoding, const QString &IVorSalt, int iterations)
{
    Q_UNUSED(encrypted_string);
    Q_UNUSED(key);
    Q_UNUSED(algorithm);
    Q_UNUSED(encoding);
    Q_UNUSED(IVorSalt);
    Q_UNUSED(iterations);

    throw QMKFusionException("Not Implemented", "Decrypt is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DecryptBinary(const QString &bytes, const QString &key, const QString &algorithm, const QString &IVorSalt, int iterations)
{
    Q_UNUSED(bytes);
    Q_UNUSED(key);
    Q_UNUSED(algorithm);
    Q_UNUSED(IVorSalt);
    Q_UNUSED(iterations);

    throw QMKFusionException("Not Implemented", "DecryptBinary is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_DeleteClientVariable(const QString &name)
{
    Q_UNUSED(name);

    throw QMKFusionException("Not Implemented", "DeleteClientVariable is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DeserializeJSON(const QString &JSONVar, bool strictMapping)
{
    Q_UNUSED(JSONVar);
    Q_UNUSED(strictMapping);

    throw QMKFusionException("Not Implemented", "DeserializeJSON is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_DirectoryExists(const QString &absolute_path)
{
    return QDir(absolute_path).exists();
}

Q_DECL_EXPORT QString cf_DollarFormat(double number)
{
    Q_UNUSED(number);

    throw QMKFusionException("Not Implemented", "DollarFormat is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_DotNetToCFType(const QWDDX &variable_name)
{
    Q_UNUSED(variable_name);

    throw QMKFusionException("Not Implemented", "DotNetToCFType is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_Duplicate(const QWDDX &variable_name)
{
    return variable_name;
}

Q_DECL_EXPORT QString cf_Encrypt(const QString &string, const QString &key, const QString &algorithm, const QString &encoding, const QString &IVorSalt, int iterations)
{
    Q_UNUSED(string);
    Q_UNUSED(key);
    Q_UNUSED(algorithm);
    Q_UNUSED(encoding);
    Q_UNUSED(IVorSalt);
    Q_UNUSED(iterations);

    throw QMKFusionException("Not Implemented", "Encrypt is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_EncryptBinary(const QString &bytes, const QString &key, const QString &algorithm, const QString &IVorSalt, int iterations)
{
    Q_UNUSED(bytes);
    Q_UNUSED(key);
    Q_UNUSED(algorithm);
    Q_UNUSED(IVorSalt);
    Q_UNUSED(iterations);

    throw QMKFusionException("Not Implemented", "EncryptBinary is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_Evaluate(const QStringList &string_expressions)
{
    Q_UNUSED(string_expressions);

    throw QMKFusionException("Not Implemented", "Evaluate is not Implemented (yet:))");
}

Q_DECL_EXPORT double cf_Exp(double number)
{
    return exp(number);
}

Q_DECL_EXPORT QString cf_ExpandPath(const QString &relative_path)
{
    Q_UNUSED(relative_path);

    throw QMKFusionException("Not Implemented", "ExpandPath is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_FileClose(QWDDX &fileObj)
{
    Q_UNUSED(fileObj);

    throw QMKFusionException("Not Implemented", "FileClose is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_FileCopy(const QString &source, const QString &destination)
{
    Q_UNUSED(source);
    Q_UNUSED(destination);

    throw QMKFusionException("Not Implemented", "FileCopy is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_FileDelete(const QString &filepath)
{
    if (!QFile::exists(filepath))
    {
        throw QMKFusionException("File delete failed.", QString("Specified file[%1] does not exists.").arg(filepath));
    }

    if (QFile::remove(filepath) == false)
    {
        throw QMKFusionException("File delete failed.", QString("Error while deleting file[%1].").arg(filepath));
    }
}

Q_DECL_EXPORT bool cf_FileExists(const QString &absolute_path)
{
    return QFile::exists(absolute_path);
}

Q_DECL_EXPORT bool cf_FileIsEOF(QWDDX &fileObj)
{
    Q_UNUSED(fileObj);

    throw QMKFusionException("Not Implemented", "FileIsEOF is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_FileMove(const QString &source, const QString &destination)
{
    Q_UNUSED(source);
    Q_UNUSED(destination);

    throw QMKFusionException("Not Implemented", "FileMove is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_FileOpen(const QString &filepath, const QString mode, const QString charset)
{
    Q_UNUSED(filepath);
    Q_UNUSED(mode);
    Q_UNUSED(charset);

    throw QMKFusionException("Not Implemented", "FileOpen is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_FileRead(const QString &filepath, const QString charset)
{
    Q_UNUSED(filepath);
    Q_UNUSED(charset);

    throw QMKFusionException("Not Implemented", "FileRead1 is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_FileRead(QWDDX &fileObj, int buffersize)
{
    Q_UNUSED(fileObj);
    Q_UNUSED(buffersize);

    throw QMKFusionException("Not Implemented", "FileRead2 is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_FileReadBinary(const QString &filepath)
{
    Q_UNUSED(filepath);

    throw QMKFusionException("Not Implemented", "FileReadBinary is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_FileReadLine(QWDDX &fileObj)
{
    Q_UNUSED(fileObj);

    throw QMKFusionException("Not Implemented", "FileReadLine is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_FileSetAccessMode(const QString &filepath, const QString mode) // TODO: Make this available only under Linux
{
    Q_UNUSED(filepath);
    Q_UNUSED(mode);

    throw QMKFusionException("Not Implemented", "FileSetAccessMode is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_FileSetAttribute(const QString &filepath, const QString mode) // TODO: Make this available only under Windows
{
    Q_UNUSED(filepath);
    Q_UNUSED(mode);

    throw QMKFusionException("Not Implemented", "FileSetAttribute is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_FileSetLastModified(const QString &filepath, const QDateTime &date)
{
    Q_UNUSED(filepath);
    Q_UNUSED(date);

    throw QMKFusionException("Not Implemented", "FileSetLastModified is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_FileWrite(const QString &filepath, const QString &data, const QString &charset)
{
    Q_UNUSED(filepath);
    Q_UNUSED(data);
    Q_UNUSED(charset);

    throw QMKFusionException("Not Implemented", "FileWrite1 is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_FileWrite(QWDDX &fileObj, const QString &data)
{
    Q_UNUSED(fileObj);
    Q_UNUSED(data);

    throw QMKFusionException("Not Implemented", "FileWrite2 is not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_Find(const QString &substring, const QString &string, int start)
{
    if (start < 1)
    {
        throw QMKFusionException("Index out of range", QString("start is %1, when it should be 1 or more.").arg(start));
    }

    return string.indexOf(substring, start - 1, Qt::CaseSensitive) + 1;
}

Q_DECL_EXPORT int cf_FindNoCase(const QString &substring, const QString &string, int start)
{
    if (start < 1)
    {
        throw QMKFusionException("Index out of range", QString("start is %1, when it should be 1 or more.").arg(start));
    }

    return string.indexOf(substring, start - 1, Qt::CaseInsensitive) + 1;
}

Q_DECL_EXPORT int cf_FindOneOf(const QString &set, const QString &string, int start)
{
    Q_UNUSED(set);
    Q_UNUSED(string);
    Q_UNUSED(start);

    throw QMKFusionException("Not Implemented", "FindOneOf is not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_FirstDayOfMonth(const QDateTime &date)
{
    return QDate(date.date().year(), date.date().month(), 1).dayOfYear();
}

Q_DECL_EXPORT int cf_Fix(double value)
{
    if (value >= 0)
    {
        return floor(value);
    }
    else
    {
        return ceil(value);
    }
}

Q_DECL_EXPORT QString cf_FormatBaseN(int number, int radix)
{
    if ((radix < 2)||(radix > 36))
    {
        throw QMKFusionException("Invalid argument for the function FormatBaseN.", "Argument 2 of the FormatBaseN, which is now 1, must be an integer in the range of 2 to 36 inclusive.");
    }

    return QString::number(number, radix);
}

Q_DECL_EXPORT QString cf_GenerateSecretKey(const QString &algorithm, int keysize)
{
    Q_UNUSED(algorithm);
    Q_UNUSED(keysize);

    throw QMKFusionException("Not Implemented", "GenerateSecretKey is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GetAuthUser()
{
    throw QMKFusionException("Not Implemented", "GetAuthUser is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_GetBaseTagData(const QCFTemplate * const thisTemplate, const QString &tagname, int instancenumber)
{
    int found = 0;

    for(QWDDX item : thisTemplate->m_CustomTags) // TODO: QWDDX [] operator should to be const?
    {
        if (tagname == "cf_" + item[L"NAME"].toString())
        {
            found++;

            if (found == instancenumber)
            {

                QWDDX ret = item;

                cf_StructDelete(ret, "OUTPUT");
                cf_StructDelete(ret, "TYPE");
                cf_StructDelete(ret, "NAME");

                return ret;
            }
        }
    }

    throw QMKFusionException(QString("There is no basetag with name[%1] and level %2").arg(tagname).arg(instancenumber));
}

Q_DECL_EXPORT QString cf_GetBaseTagList(const QCFTemplate * const thisTemplate)
{
    QStringList items;

    for(QWDDX item : thisTemplate->m_CustomTags) // TODO: QWDDX [] operator should to be const?
    {
        items.append("cf_" + item[L"NAME"].toString());
    }

    return items.join(',');
}

Q_DECL_EXPORT QString cf_GetBaseTemplatePath()
{
    throw QMKFusionException("Not Implemented", "GetBaseTemplatePath is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GetClientVariablesList()
{
    throw QMKFusionException("Not Implemented", "GetClientVariablesList is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_GetComponentMetaData(const QString &path)
{
    throw QMKFusionException("Not Implemented", "GetComponentMetaData is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GetContextRoot()
{
    throw QMKFusionException("Not Implemented", "GetContextRoot is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GetCurrentTemplatePath()
{
    throw QMKFusionException("Not Implemented", "GetCurrentTemplatePath is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GetDirectoryFromPath(const QString &path)
{
    throw QMKFusionException("Not Implemented", "GetDirectoryFromPath is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GetEncoding(const QString &scope_name)
{
    throw QMKFusionException("Not Implemented", "GetEncoding is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_GetException(const QWDDX &object)
{
    throw QMKFusionException("Not Implemented", "GetException is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GetFileFromPath(const QString &path)
{
    throw QMKFusionException("Not Implemented", "GetFileFromPath is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_GetFileInfo(const QString &path)
{
    throw QMKFusionException("Not Implemented", "GetFileInfo is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GetFunctionList()
{
    throw QMKFusionException("Not Implemented", "GetFunctionList is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_GetGatewayHelper(const QString &gatewayID)
{
    throw QMKFusionException("Not Implemented", "GetGatewayHelper is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_GetHttpRequestData()
{
    throw QMKFusionException("Not Implemented", "GetHttpRequestData is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GetHttpTimeString(const QDateTime &date_time_object)
{
    throw QMKFusionException("Not Implemented", "GetHttpTimeString is not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_GetK2ServerDocCount()
{
    throw QMKFusionException("Not Implemented", "GetK2ServerDocCount is not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_GetK2ServerDocCountLimit()
{
    throw QMKFusionException("Not Implemented", "GetK2ServerDocCountLimit is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GetLocale()
{
    throw QMKFusionException("Not Implemented", "GetLocale is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GetLocaleDisplayName(const QString &locale, const QString &inlocale)
{
    throw QMKFusionException("Not Implemented", "GetLocaleDisplayName is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GetLocalHostIP()
{
    throw QMKFusionException("Not Implemented", "GetLocalHostIP is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_GetMetaData(const QWDDX &object)
{
    throw QMKFusionException("Not Implemented", "GetMetaData is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_GetMetricData(const QString &mode)
{
    throw QMKFusionException("Not Implemented", "GetMetricData is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_GetPageContext()
{
    throw QMKFusionException("Not Implemented", "GetPageContext is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_GetPrinterInfo(const QString &printer)
{
    throw QMKFusionException("Not Implemented", "GetPrinterInfo is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_GetProfileSections(const QString &iniFile)
{
    throw QMKFusionException("Not Implemented", "GetProfileSections is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_GetProfileString(const QString &iniFile, const QString &section, const QString &entry)
{
    throw QMKFusionException("Not Implemented", "GetProfileString is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GetReadableImageFormats()
{
    throw QMKFusionException("Not Implemented", "GetReadableImageFormats is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_GetSOAPRequest()
{
    throw QMKFusionException("Not Implemented", "GetSOAPRequest is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_GetSOAPRequestHeader(const QString &_namespace, const QString &name, bool asXML)
{
    throw QMKFusionException("Not Implemented", "GetSOAPRequestHeader is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_GetSOAPResponse(QWDDX &webservice)
{
    throw QMKFusionException("Not Implemented", "GetSOAPResponse is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_GetSOAPResponseHeader(const QString &_namespace, const QString &name, bool asXML)
{
    throw QMKFusionException("Not Implemented", "GetSOAPResponseHeader is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GetTempDirectory()
{
    return QDir::tempPath();
}

Q_DECL_EXPORT QString cf_GetTempFile(const QString &dir, const QString &prefix)
{
    throw QMKFusionException("Not Implemented", "GetTempFile is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GetTemplatePath()
{
    throw QMKFusionException("Not Implemented", "GetTemplatePath is not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_GetTickCount()
{
#ifdef Q_OS_WIN
    return (int)GetTickCount();
#elif defined Q_OS_LINUX
    struct timespec ts;
    if(clock_gettime(CLOCK_MONOTONIC,&ts) != 0)
    {
        return 0;
    }

    return (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
#else
#error Windows and Linux OSs are currently supported.
#endif
}

Q_DECL_EXPORT QWDDX cf_GetTimeZoneInfo()
{
    throw QMKFusionException("Not Implemented", "GetTimeZoneInfo is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GetToken(const QString &string, int index, const QString &delimiters)
{
    throw QMKFusionException("Not Implemented", "GetToken is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GetUserRoles()
{
    throw QMKFusionException("Not Implemented", "GetUserRoles is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GetWriteableImageFormats()
{
    throw QMKFusionException("Not Implemented", "GetWriteableImageFormats is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_Hash(const QString &string, const QString &algorithm, const QString &encoding)
{
    throw QMKFusionException("Not Implemented", "Hash is not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_Hour(const QDateTime &date)
{
    return date.time().hour();
}

Q_DECL_EXPORT QString cf_HTMLCodeFormat(const QString &string, double version)
{
    return "<pre>" + cf_HTMLEditFormat(string, version) + "</pre>";
}

Q_DECL_EXPORT QString cf_HTMLEditFormat(const QString &string, double version)
{
    Q_UNUSED(version);

    QString ret = string;

    ret = ret.replace("&", "&amp;");
    ret = ret.replace("<", "&lt;");
    ret = ret.replace(">", "&gt;");
    ret = ret.replace("\"", "&quot;");

    return ret;
}

Q_DECL_EXPORT bool cf_IIf(bool condition, const QString &string_expression1, const QString &string_expression2)
{
    throw QMKFusionException("Not Implemented", "IIf is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageAddBorder(QWDDX &name, int thickness, const QString &color, const QString &borderType)
{
    throw QMKFusionException("Not Implemented", "ImageAddBorder is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageBlur(QWDDX &name, int blurRadius)
{
    throw QMKFusionException("Not Implemented", "ImageBlur is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageClearRect(QWDDX &name, int x, int y, int width, int height)
{
    throw QMKFusionException("Not Implemented", "ImageClearRect is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_ImageCopy(QWDDX &name, int x, int y, int width, int height, int dx, int dy)
{
    throw QMKFusionException("Not Implemented", "ImageCopy is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageCrop(QWDDX &name, int x, int y, int width, int height)
{
    throw QMKFusionException("Not Implemented", "ImageCrop is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageDrawArc(QWDDX &name, int x, int y, int width, int height, int startAngle, double arcAngle, bool filled)
{
    throw QMKFusionException("Not Implemented", "ImageDrawArc is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageDrawBeveledRect(QWDDX &name, int x, int y, int width, int height, bool raised, bool filled)
{
    throw QMKFusionException("Not Implemented", "ImageDrawBeveledRect is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageDrawCubicCurve(QWDDX &name, int ctrlx1, int ctrly1, int ctrlx2, int ctrly2, int x1, int y1, int x2, int y2)
{
    throw QMKFusionException("Not Implemented", "ImageDrawCubicCurve is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageDrawLine(QWDDX &name, int x1, int y1, int x2, int y2)
{
    throw QMKFusionException("Not Implemented", "ImageDrawLine is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageDrawLines(QWDDX &name, const QWDDX &xcoords, const QWDDX &ycoords, bool isPolygon, bool filled)
{
    throw QMKFusionException("Not Implemented", "ImageDrawLines is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageDrawOval(QWDDX &name, int x, int y, int width, int height, bool filled)
{
    throw QMKFusionException("Not Implemented", "ImageDrawOval is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageDrawPoint(QWDDX &name, int x, int y)
{
    throw QMKFusionException("Not Implemented", "ImageDrawPoint is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageDrawQuadraticCurve(QWDDX &name, int ctrlx1, int ctrly1, int ctrlx2, int ctrly2, int x1, int y1, int x2, int y2)
{
    throw QMKFusionException("Not Implemented", "ImageDrawQuadraticCurve is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageDrawRect(QWDDX &name, int x, int y, int width, int height, bool filled)
{
    throw QMKFusionException("Not Implemented", "ImageDrawRect is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageDrawRoundRect(QWDDX &name, int x, int y, int width, int height, int arcWidth, int arcHeight, bool filled)
{
    throw QMKFusionException("Not Implemented", "ImageDrawRoundRect is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageDrawText(QWDDX &name, const QString &str, int x, int y, const QWDDX &attributeCollection)
{
    throw QMKFusionException("Not Implemented", "ImageDrawText is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageFlip(QWDDX &name, const QString &transpose)
{
    throw QMKFusionException("Not Implemented", "ImageFlip is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_ImageGetBlob(const QWDDX &source)
{
    throw QMKFusionException("Not Implemented", "ImageGetBlob is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_ImageGetBufferedImage(const QWDDX &name)
{
    throw QMKFusionException("Not Implemented", "ImageGetBufferedImage is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_ImageGetEXIFTag(const QWDDX &name, const QString &tagName)
{
    throw QMKFusionException("Not Implemented", "ImageGetEXIFTag is not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_ImageGetHeight(const QWDDX &name)
{
    throw QMKFusionException("Not Implemented", "ImageGetHeight is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_ImageGetIPTCTag(const QWDDX &name, const QString &tagName)
{
    throw QMKFusionException("Not Implemented", "ImageGetIPTCTag is not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_ImageGetWidth(const QWDDX &name)
{
    throw QMKFusionException("Not Implemented", "ImageGetWidth is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageGrayscale(QWDDX &name)
{
    throw QMKFusionException("Not Implemented", "ImageGrayscale is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_ImageInfo(const QWDDX &name)
{
    throw QMKFusionException("Not Implemented", "ImageInfo is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageNegative(QWDDX &name)
{
    throw QMKFusionException("Not Implemented", "ImageNegative is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_ImageNew(const QString &source, int width, int height, const QString &imageType, const QString canvasColor)
{
    throw QMKFusionException("Not Implemented", "ImageNew is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageOverlay(QWDDX &source1, const QWDDX &source2)
{
    throw QMKFusionException("Not Implemented", "ImageOverlay is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_ImagePaste(QWDDX &image1, const QWDDX &image2, int x, int y)
{
    throw QMKFusionException("Not Implemented", "ImagePaste is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_ImageRead(const QString &path)
{
    throw QMKFusionException("Not Implemented", "ImageRead is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_ImageReadBase64(const QString &string)
{
    throw QMKFusionException("Not Implemented", "ImageReadBase64 is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageResize(QWDDX &name, int width, int height, const QString &interpolation, int blurFactor)
{
    throw QMKFusionException("Not Implemented", "ImageResize is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageRotate(QWDDX &name, double angle, int x, int y, const QString &interpolation)
{
    throw QMKFusionException("Not Implemented", "ImageRotate is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_ImageRotateDrawingAxis(QWDDX &name, double angle, int x, int y)
{
    throw QMKFusionException("Not Implemented", "ImageRotateDrawingAxis is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageScaleToFit(QWDDX &name, const QString &fitWidth, const QString &fitHeight, const QString &interpolation, int blurFactor)
{
    throw QMKFusionException("Not Implemented", "ImageScaleToFit is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageSetAntialiasing(QWDDX &name, bool antialias)
{
    throw QMKFusionException("Not Implemented", "ImageSetAntialiasing is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageSetBackgroundColor(QWDDX &name, const QString &color)
{
    throw QMKFusionException("Not Implemented", "ImageSetBackgroundColor is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageSetDrawingColor(QWDDX &name, const QString &color)
{
    throw QMKFusionException("Not Implemented", "ImageSetDrawingColor is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageSetDrawingStroke(QWDDX &name, const QWDDX &attributeCollection)
{
    throw QMKFusionException("Not Implemented", "ImageSetDrawingStroke is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageSetDrawingTransparency(QWDDX &name, double percent)
{
    throw QMKFusionException("Not Implemented", "ImageSetDrawingTransparency is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageSharpen(QWDDX &name, double gain)
{
    throw QMKFusionException("Not Implemented", "ImageSharpen is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageShear(QWDDX &name, double shear, const QString &direction, const QString &interpolation)
{
    throw QMKFusionException("Not Implemented", "ImageShear is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageShearDrawingAxis(QWDDX &name, double shx, double shy)
{
    throw QMKFusionException("Not Implemented", "ImageShearDrawingAxis is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageTranslate(QWDDX &name, int xTrans, int yTrans, const QString &interpolation)
{
    throw QMKFusionException("Not Implemented", "ImageTranslate is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageTranslateDrawingAxis(QWDDX &name, int x, int y)
{
    throw QMKFusionException("Not Implemented", "ImageTranslateDrawingAxis is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageWrite(const QWDDX &name, const QString &destination, double quality)
{
    throw QMKFusionException("Not Implemented", "ImageWrite is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_ImageWriteBase64(const QWDDX &name, const QString &destination, const QString &format, bool inHTMLFormat)
{
    throw QMKFusionException("Not Implemented", "ImageWriteBase64 is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ImageXORDrawingMode(QWDDX &name, const QString &c1)
{
    throw QMKFusionException("Not Implemented", "ImageXORDrawingMode is not Implemented (yet:))");
}

Q_DECL_EXPORT double cf_IncrementValue(double number)
{
    return number + 1;
}

Q_DECL_EXPORT int cf_InputBaseN(const QString &string, int radix)
{
    if ((radix < 2)||(radix > 36))
    {
        throw QMKFusionException("Invalid argument for the function FormatBaseN.", "Argument 2 of the FormatBaseN, which is now 1, must be an integer in the range of 2 to 36 inclusive.");
    }

    return string.toInt(nullptr, radix);
}

Q_DECL_EXPORT QString cf_Insert(const QString &substring, const QString &string, int position)
{
    throw QMKFusionException("Not Implemented", "Insert is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_Int(double number)
{
    return QString::number(floor(number));
}

Q_DECL_EXPORT bool cf_IsArray(const QWDDX &var, int level)
{
    if (var.type() != QWDDX::Array)
    {
        return false;
    }

    if (level > 0)
    {
        if (var.m_ArrayDimension != (quint32)level)
        {
            return false;
        }
    }

    return true;
}

Q_DECL_EXPORT bool cf_IsBinary(const QWDDX &value)
{
    throw QMKFusionException("Not Implemented", "IsBinary is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsBoolean(const QWDDX &value)
{
    throw QMKFusionException("Not Implemented", "IsBoolean is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsCustomFunction(const QString &name)
{
    throw QMKFusionException("Not Implemented", "IsCustomFunction is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsDate(const QString &string)
{
    return QWDDX(string).canConvertToDate();
}

Q_DECL_EXPORT bool cf_IsDDX(const QString &path_or_string)
{
    throw QMKFusionException("Not Implemented", "IsDDX is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsDebugMode()
{
    throw QMKFusionException("Not Implemented", "IsDebugMode is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsDefined(QCFRunningTemplate *templ, const QString &variable_name)
{
    QStringList parts;

    if ((templ == nullptr)||(variable_name.length() == 0))
    {
        return false;
    }

    parts = variable_name.toUpper().split(".");

    if ((parts.count() == 1)||((parts.first() != "CGI")&&(parts.first() != "SERVER")&&(parts.first() != "APPLICATION")&&(parts.first() != "SESSION")&&(parts.first() != "URL")&&(parts.first() != "FORM")&&(parts.first() != "VARIABLES")))
    {
        parts.prepend("VARIABLES");
    }

    const QString &first = parts.takeFirst();
    QWDDX var;

    if (first == "CGI")
    {
        var = templ->m_CGI;
    }
    else if (first == "SERVER")
    {
        var = templ->m_SERVER;
    }
    else if (first == "APPLICATION")
    {
        if (templ->m_APPLICATION == nullptr)
        {
            throw QMKFusionException("Appication scope not enabled.");
        }

        var = *templ->m_APPLICATION;
    }
    else if (first == "SESSION")
    {
        if (templ->m_SESSION == nullptr)
        {
            throw QMKFusionException("Session scope not enabled.");
        }

        var = *templ->m_SESSION;
    }
    else if (first == "URL")
    {
        var = templ->m_URL;
    }
    else if (first == "FORM")
    {
        var = templ->m_FORM;
    }
    else if (first == "VARIABLES")
    {
        var = templ->m_VARIABLES;
    }
    else
    {
        qDebug() << "Unknown type(cf_IsDefined).";

        return false;
    }

    for(const QString &item : parts)
    {
        if (var.m_Type != QWDDX::Struct)
        {
            return false;
        }

        if (!var.m_Struct->contains(item))
        {
            if (var.m_HiddenScopeLast1)
            {
                var = *var.m_HiddenScopeLast1;

                if (!var.m_Struct->contains(item))
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }

        var = var.m_Struct->value(item);
    }

    return true;
}

Q_DECL_EXPORT bool cf_IsImage(const QWDDX &name)
{
    throw QMKFusionException("Not Implemented", "IsImage is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsImageFile(const QWDDX &path)
{
    throw QMKFusionException("Not Implemented", "IsImageFile is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsInstanceOf(const QWDDX &object, const QString &typeName)
{
    throw QMKFusionException("Not Implemented", "IsInstanceOf is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsJSON(const QWDDX &var)
{
    throw QMKFusionException("Not Implemented", "IsJSON is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsLeapYear(int year)
{
    return QDate::isLeapYear(year);
}

Q_DECL_EXPORT bool cf_IsLocalHost(const QString &ipaddress)
{
    throw QMKFusionException("Not Implemented", "IsLocalHost is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsNumeric(const QString &string)
{
    throw QMKFusionException("Not Implemented", "IsNumeric is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsNumericDate(double number)
{
    throw QMKFusionException("Not Implemented", "IsNumericDate is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsObject(const QWDDX &value)
{
    throw QMKFusionException("Not Implemented", "IsObject is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsPDFFile(const QString &path)
{
    throw QMKFusionException("Not Implemented", "IsPDFFile is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsPDFObject(const QWDDX &value)
{
    throw QMKFusionException("Not Implemented", "IsPDFObject is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsQuery(const QWDDX &value)
{
    return value.type() == QWDDX::Query;
}

Q_DECL_EXPORT bool cf_IsSimpleValue(const QWDDX &value)
{
    QWDDX::QWDDXType type = value.type();

    if ((type == QWDDX::String)||(type == QWDDX::Number)||(type == QWDDX::Boolean)||(type == QWDDX::DateTime))
    {
        return true;
    }

    return false;
}

Q_DECL_EXPORT bool cf_IsSOAPRequest()
{
    throw QMKFusionException("Not Implemented", "IsSOAPRequest is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsStruct(const QWDDX &variable)
{
    if (variable.type() == QWDDX::Struct)
    {
        return true;
    }

    return false;
}

Q_DECL_EXPORT bool cf_IsUserInAnyRole()
{
    throw QMKFusionException("Not Implemented", "IsUserInAnyRole is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsUserInRole(const QString &role_name)
{
    throw QMKFusionException("Not Implemented", "IsUserInRole is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsUserLoggedIn()
{
    throw QMKFusionException("Not Implemented", "IsUserLoggedIn is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsValid(const QString &type, const QWDDX &value)
{
    throw QMKFusionException("Not Implemented", "IsValid is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsValid(const QString &type, const QWDDX &value, int min, int max)
{
    throw QMKFusionException("Not Implemented", "IsValid is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsValid(const QString &type, const QWDDX &value, const QString &pattern)
{
    throw QMKFusionException("Not Implemented", "IsValid is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsWDDX(const QWDDX &value)
{
    throw QMKFusionException("Not Implemented", "IsWDDX is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsXML(const QWDDX &value)
{
    throw QMKFusionException("Not Implemented", "IsXML is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsXmlAttribute(const QWDDX &value)
{
    throw QMKFusionException("Not Implemented", "IsXmlAttribute is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsXmlDoc(const QWDDX &value)
{
    throw QMKFusionException("Not Implemented", "IsXmlDoc is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsXmlElem(const QWDDX &value)
{
    throw QMKFusionException("Not Implemented", "IsXmlElem is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsXmlNode(const QWDDX &value)
{
    throw QMKFusionException("Not Implemented", "IsXmlNode is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_IsXmlRoot(const QWDDX &value)
{
    throw QMKFusionException("Not Implemented", "IsXmlRoot is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_JavaCast(const QString &type, const QWDDX &value)
{
    throw QMKFusionException("Not Implemented", "JavaCast is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_JSStringFormat(const QString &string)
{
    throw QMKFusionException("Not Implemented", "JSStringFormat is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_LCase(const QString &string)
{
    return string.toLower();
}

Q_DECL_EXPORT QString cf_Left(const QString &string, int count)
{
    return string.left(count);
}

Q_DECL_EXPORT int cf_Len(const QString &string)
{
    return string.length();
}

Q_DECL_EXPORT QString cf_ListAppend(QString &list, const QString &value, const QString &delimiters)
{
    if ((delimiters.isEmpty())||(list.isEmpty()))
    {
        return value;
    }

    return list + delimiters.at(0) + value;
}

Q_DECL_EXPORT QString cf_ListChangeDelims(QString &list, const QString &new_delimiter, const QString &delimiters)
{
    QString ret;
    QWDDX tmp = cf_ListToArray(list, delimiters);

    for(int c = 0; c < tmp.m_Array->count(); c++)
    {
        if (c > 0)
        {
            ret.append(new_delimiter);
        }

        ret.append(tmp.m_Array->at(c).toString());
    }

    return ret;
}

Q_DECL_EXPORT int cf_ListContains(const QString &list, const QString &substring, const QString &delimiters)
{
    QWDDX tmp = cf_ListToArray(list, delimiters);

    for(int c = 0; c < tmp.m_Array->count(); c++)
    {
        if (tmp.m_Array->at(c).toString().contains(substring, Qt::CaseSensitive) == 0)
        {
            return c + 1;
        }
    }

    return 0;
}

Q_DECL_EXPORT int cf_ListContainsNoCase(const QString &list, const QString &substring, const QString &delimiters)
{
    QWDDX tmp = cf_ListToArray(list, delimiters);

    for(int c = 0; c < tmp.m_Array->count(); c++)
    {
        if (tmp.m_Array->at(c).toString().contains(substring, Qt::CaseInsensitive) == 0)
        {
            return c + 1;
        }
    }

    return 0;
}

Q_DECL_EXPORT QString cf_ListDeleteAt(QString &list, int position, const QString &delimiters)
{
    QString ret;
    QWDDX tmp = cf_ListToArray(list, delimiters);

    if (position < 1)
    {
        throw QMKFusionException(QString("Invalid list index %1.").arg(position));
    }

    if (position > tmp.m_Array->count())
    {
        throw QMKFusionException(QString("Invalid list index %1. The list has %2 elements").arg(position).arg(tmp.m_Array->count()));
    }

    int index = 0;
    for(int c = 0; c < tmp.m_Array->count(); c++)
    {
        if (!tmp.m_Array->at(c).toString().isEmpty())
        {
            index++;

            if (index == position)
            {
                tmp.m_Array->remove(c);
                c--;
            }
        }
        else
        {
            if (index == position)
            {
                tmp.m_Array->remove(c);
                c--;
            }
        }
    }

    // Trim empty tail.
    while(tmp.m_Array->count() > 0)
    {
        if (!tmp.m_Array->last().toString().isEmpty())
        {
            break;
        }

        tmp.m_Array->pop_back();
    }

    for(int c = 0; c < tmp.m_Array->count(); c++)
    {
        if (c > 0)
        {
            ret.append(delimiters);
        }

        ret.append(tmp.m_Array->at(c).toString());
    }

    return ret;
}

Q_DECL_EXPORT int cf_ListFind(const QString &list, const QString &value, const QString &delimiters)
{
    QWDDX tmp = cf_ListToArray(list, delimiters);

    for(int c = 0; c < tmp.m_Array->count(); c++)
    {
        if (tmp.m_Array->at(c).toString().compare(value, Qt::CaseSensitive) == 0)
        {
            return c + 1;
        }
    }

    return 0;
}

Q_DECL_EXPORT int cf_ListFindNoCase(const QString &list, const QString &value, const QString &delimiters)
{
    QWDDX tmp = cf_ListToArray(list, delimiters);

    for(int c = 0; c < tmp.m_Array->count(); c++)
    {
        if (tmp.m_Array->at(c).toString().compare(value, Qt::CaseInsensitive) == 0)
        {
            return c + 1;
        }
    }

    return 0;
}

Q_DECL_EXPORT QString cf_ListFirst(const QString &list, const QString &delimiters)
{
    QWDDX tmp = cf_ListToArray(list, delimiters);

    if (tmp.m_Array->count() < 1)
    {
        return "";
    }

    return tmp.m_Array->first().toString();
}

Q_DECL_EXPORT QString cf_ListGetAt(const QString &list, int position, const QString &delimiters)
{
    QWDDX tmp = cf_ListToArray(list, delimiters);

    if (position < 1)
    {
        throw QMKFusionException(QString("Invalid list index %1.").arg(position));
    }

    if (position > tmp.m_Array->count())
    {
        throw QMKFusionException(QString("Invalid list index %1. The list has %2 elements").arg(position).arg(tmp.m_Array->count()));
    }

    return tmp.m_Array->at(position - 1).toString();
}

Q_DECL_EXPORT QString cf_ListInsertAt(QString &list, int position, const QString value, const QString &delimiters)
{
    QString ret;
    QWDDX tmp = cf_ListToArray(list, delimiters, true);

    if (position < 1)
    {
        throw QMKFusionException(QString("Invalid list index %1.").arg(position));
    }

    if (position > tmp.m_Array->count() + 1)
    {
        throw QMKFusionException(QString("Invalid list index %1. The list has %2 elements").arg(position).arg(tmp.m_Array->count()));
    }

    tmp.m_Array->insert(position - 1, value);

    for(int c = 0; c < tmp.m_Array->count(); c++)
    {
        if (c > 0)
        {
            ret.append(delimiters);
        }

        ret.append(tmp.m_Array->at(c).toString());
    }

    return ret;
}

Q_DECL_EXPORT QString cf_ListLast(const QString &list, const QString &delimiters)
{
    QWDDX tmp = cf_ListToArray(list, delimiters);

    if (tmp.m_Array->count() < 1)
    {
        return "";
    }

    return tmp.m_Array->last().toString();
}

Q_DECL_EXPORT int cf_ListLen(const QString &list, const QString &delimiters)
{
    QWDDX tmp = cf_ListToArray(list, delimiters);

    return tmp.m_Array->count();
}

Q_DECL_EXPORT QString cf_ListPrepend(QString &list, const QString &value, const QString &delimiters)
{
    if ((delimiters.isEmpty())||(list.isEmpty()))
    {
        return value;
    }

    return value + delimiters.at(0) + list;
}

Q_DECL_EXPORT QString cf_ListQualify(QString &list, const QString &quallifier, const QString &delimiters, const QString elements)
{
    QString ret;
    QWDDX tmp = cf_ListToArray(list, delimiters);
    bool all;

    if (elements.compare("all", Qt::CaseInsensitive) == 0)
    {
        all = true;
    }
    else if (elements.compare("char", Qt::CaseInsensitive) == 0)
    {
        all = false;
    }
    else
    {
        throw QMKFusionException(QString("ListQualify elements parameter should be ether all or char. Value passed was %1").arg(elements));
    }

    for(int c = 0; c < tmp.m_Array->count(); c++)
    {
        if (c > 0)
        {
            ret.append(delimiters);
        }

        if (all)
        {
            ret.append(quallifier + tmp.m_Array->at(c).toString() + quallifier);
        }
        else
        {
            bool is_all_aphas = true;
            const QString &str = tmp.m_Array->at(c).toString();

            for(QChar ch : str)
            {
                if (!ch.isLetter())
                {
                    is_all_aphas = false;
                    break;
                }
            }

            if (is_all_aphas)
            {
                ret.append(str);
            }
            else
            {
                ret.append(quallifier + str + quallifier);
            }
        }
    }

    return ret;
}

Q_DECL_EXPORT QString cf_ListRest(const QString &list, const QString &delimiters)
{
    QString ret;
    QWDDX tmp = cf_ListToArray(list, delimiters);


    // Trim empty head.
    while(tmp.m_Array->count() > 0)
    {
        if (!tmp.m_Array->first().toString().isEmpty())
        {
            break;
        }

        tmp.m_Array->pop_front();
    }

    // Remove first item.
    if (tmp.m_Array->count() > 0)
    {
        tmp.m_Array->pop_front();
    }

    // Trim empty head.
    while(tmp.m_Array->count() > 0)
    {
        if (!tmp.m_Array->first().toString().isEmpty())
        {
            break;
        }

        tmp.m_Array->pop_front();
    }

    // Reconstruct list.
    for(int c = 0; c < tmp.m_Array->count(); c++)
    {
        if (c > 0)
        {
            ret.append(delimiters);
        }

        ret.append(tmp.m_Array->at(c).toString());
    }

    return ret;
}

Q_DECL_EXPORT QString cf_ListSetAt(QString &list, int position, const QString value, const QString &delimiters)
{
    QString ret;
    QWDDX tmp = cf_ListToArray(list, delimiters);

    if (position < 1)
    {
        throw QMKFusionException(QString("Invalid list index %1.").arg(position));
    }

    if (position > tmp.m_Array->count())
    {
        throw QMKFusionException(QString("Invalid list index %1. The list has %2 elements").arg(position).arg(tmp.m_Array->count()));
    }

    tmp.m_Array->replace(position - 1, value);

    // Reconstruct list.
    for(int c = 0; c < tmp.m_Array->count(); c++)
    {
        if (c > 0)
        {
            ret.append(delimiters);
        }

        ret.append(tmp.m_Array->at(c).toString());
    }

    return ret;
}

Q_DECL_EXPORT QString cf_ListSort(QString &list, const QString sort_type, const QString sort_order, const QString &delimiters)
{
    throw QMKFusionException("Not Implemented", "ListSort is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_ListToArray(const QString &list, const QString &delimiters, bool includeEmptyFields)
{
    QWDDX ret(QWDDX::Array);

    if (delimiters.count() == 0)
    {
        ret.m_Array->append(list);
    }
    else
    {
        QVector<int> delimiter_indexes;

        for (int c = 0; c < list.length(); c++)
        {
            for(int dc = 0; dc < delimiters.count(); dc++)
            {
                if (list.at(c) == delimiters.at(dc))
                {
                    delimiter_indexes.append(c);

                    break;
                }
            }
        }

        int last_pos = 0;

        for(int index : delimiter_indexes)
        {
            if ((index > last_pos)||(includeEmptyFields))
            {
                ret.m_Array->append(list.mid(last_pos, index - last_pos));
            }

            last_pos = index + 1;
        }

        if ((list.count() - 1 > last_pos)||(includeEmptyFields))
        {
            ret.m_Array->append(list.mid(last_pos, list.count() - 1 - last_pos));
        }
    }

    return ret;
}

Q_DECL_EXPORT int cf_ListValueCount(const QString &list, const QString value, const QString &delimiters)
{
    int ret = 0;

    for(const QWDDX &item : *(cf_ListToArray(list, delimiters).m_Array))
    {
        if (item.toString().compare(value, Qt::CaseSensitive) == 0)
        {
            ret++;
        }
    }

    return ret;
}

Q_DECL_EXPORT int cf_ListValueCountNoCase(const QString &list, const QString value, const QString &delimiters)
{
    int ret = 0;

    for(const QWDDX &item : *(cf_ListToArray(list, delimiters).m_Array))
    {
        if (item.toString().compare(value, Qt::CaseInsensitive) == 0)
        {
            ret++;
        }
    }

    return ret;
}

Q_DECL_EXPORT QString cf_LJustify(const QString &string, int length)
{
    QString ret = string;

    while(ret.length() < length)
    {
        ret = ret.append(' ');
    }

    return ret;
}

Q_DECL_EXPORT double cf_Log(double number)
{
    return log(number);
}

Q_DECL_EXPORT double cf_Log10(double number)
{
    return log10(number);
}

Q_DECL_EXPORT QString cf_LSCurrencyFormat(double number, const QString &type, const QString locale)
{
    throw QMKFusionException("Not Implemented", "LSCurrencyFormat is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_LSDateFormat(const QDateTime &date, const QString &mask, const QString &locale)
{
    throw QMKFusionException("Not Implemented", "LSDateFormat is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_LSEuroCurrencyFormat(double currency_number, const QString &locale, const QString &type)
{
    throw QMKFusionException("Not Implemented", "LSEuroCurrencyFormat is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_LSIsCurrency(const QString &string, const QString &locale)
{
    throw QMKFusionException("Not Implemented", "LSIsCurrency is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_LSIsDate(const QString &string, const QString &locale)
{
    throw QMKFusionException("Not Implemented", "LSIsDate is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_LSIsNumeric(const QString &string, const QString &locale)
{
    throw QMKFusionException("Not Implemented", "LSIsNumeric is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_LSNumberFormat(double number, const QString &mask, const QString &locale)
{
    throw QMKFusionException("Not Implemented", "LSNumberFormat is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_LSParseCurrency(const QString &string, const QString &locale)
{
    throw QMKFusionException("Not Implemented", "LSParseCurrency is not Implemented (yet:))");
}

Q_DECL_EXPORT QDateTime cf_LSParseDateTime(const QString &string, const QString &locale)
{
    throw QMKFusionException("Not Implemented", "LSParseDateTime is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_LSParseEuroCurrency(const QString &currency_string, const QString &locale)
{
    throw QMKFusionException("Not Implemented", "LSParseEuroCurrency is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_LSParseNumber(const QString &string, const QString &locale)
{
    throw QMKFusionException("Not Implemented", "LSParseNumber is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_LSTimeFormat(const QDateTime &time, const QString &locale)
{
    throw QMKFusionException("Not Implemented", "LSTimeFormat is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_LSTimeFormat(const QString &time, const QString &locale)
{
    throw QMKFusionException("Not Implemented", "LSTimeFormat is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_LTrim(const QString &string)
{
    throw QMKFusionException("Not Implemented", "LTrim is not Implemented (yet:))");
}

Q_DECL_EXPORT double cf_Max(double number1, double number2)
{
    if (number1 < number2)
    {
        return number2;
    }
    else
    {
        return number1;
    }
}

Q_DECL_EXPORT QString cf_Mid(const QString &string, int start, int count)
{
    return string.mid(start, count);
}

Q_DECL_EXPORT double cf_Min(double number1, double number2)
{
    if (number1 < number2)
    {
        return number1;
    }
    else
    {
        return number2;
    }
}

Q_DECL_EXPORT int cf_Minute(const QDateTime &date)
{
    return date.time().minute();
}

Q_DECL_EXPORT int cf_Month(const QDateTime &date)
{
    return date.date().month();
}

Q_DECL_EXPORT QString cf_MonthAsString(const QDateTime &date, const QString &locale)
{
    throw QMKFusionException("Not Implemented", "MonthAsString is not Implemented (yet:))");
}

Q_DECL_EXPORT QDateTime cf_Now()
{
    return QDateTime::currentDateTime();
}

Q_DECL_EXPORT QString cf_NumberFormat(double number, const QString &mask)
{
    throw QMKFusionException("Not Implemented", "NumberFormat is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_ParagraphFormat(const QString &string)
{
    throw QMKFusionException("Not Implemented", "ParagraphFormat is not Implemented (yet:))");
}

Q_DECL_EXPORT QDateTime cf_ParseDateTime(const QString &datetime_string, const QString &pop_conversion)
{
    throw QMKFusionException("Not Implemented", "ParseDateTime is not Implemented (yet:))");
}

Q_DECL_EXPORT double cf_Pi()
{
#ifdef __arm__
    return 3.14159265358979323846;
#else
    double ret;

    asm("fldpi" : "=t" (ret));

    return ret;
#endif
}

Q_DECL_EXPORT QWDDX cf_PrecisionEvaluate(const QStringList &string_expressions)
{
    throw QMKFusionException("Not Implemented", "PrecisionEvaluate is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_PreserveSingleQuotes(const QString &variable)
{
    throw QMKFusionException("Not Implemented", "PreserveSingleQuotes is not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_Quarter(const QDateTime &date)
{
    return ((date.date().month() - 1) / 4) + 1;
}

Q_DECL_EXPORT int cf_QueryAddColumn(QWDDX &query, const QString &column_name, const QString &datatype, const QString &array_name)
{
    Q_UNUSED(datatype);

    if (query.type() != QWDDX::Query)
    {
        throw QMKFusionException("Parameter mismatch", "query parameter is not type Query.");
    }

    const QString &column_name_upper = column_name.toUpper();

    int rows = query[L"RECORDCOUNT"];

    QWDDX new_field = QWDDX(QWDDX::Array);

    if (rows > 0)
    {
        new_field.m_Array->resize(rows);
    }

    if (query[L"RESULTSET"].m_Struct->contains(column_name_upper))
    {
        throw QMKFusionDatabaseException(QString("The column name (%1) that you specified already exists in this query.").arg(column_name_upper), "Column names must be unique.");
    }

    if (query[L"COLUMNS"].toString().length() > 0)
    {
        query[L"COLUMNS"] = query[L"COLUMNS"].toString() + "," + column_name_upper;
    }
    else
    {
        query[L"COLUMNS"] = column_name_upper;
    }

    query[L"RESULTSET"].m_Struct->insert(column_name_upper, new_field);

    if (array_name.count() > 0)
    {
        QStringList list = array_name.split(",");

        for(int c = 0; c < list.count(); c++)
        {
            cf_QuerySetCell(query, column_name_upper, list.at(c), c + 1);
        }
    }

    return query.m_Struct->count();
}

Q_DECL_EXPORT int cf_QueryAddRow(QWDDX &query, int number)
{
    if (query.type() != QWDDX::Query)
    {
        throw QMKFusionInvalidArgumentException("QueryAddRow", 1, 0, "query parameter is not type Query.");
    }

    if (number < 0)
    {
        throw QMKFusionInvalidArgumentException("QueryAddRow", 2, number, "number parameter value should be at least 1.");
    }

    int columns = query[L"RESULTSET"].m_Struct->count();

    if (columns < 1)
    {
        return 0;
    }

    QWDDX &queryData = query[L"RESULTSET"];
    int rows = query[L"RECORDCOUNT"];
    int new_rows = rows + number;

    for(int column = 0; column < columns; column++)
    {
        QString colName = query[L"RESULTSET"].m_Struct->keys().at(column);
        queryData[colName].m_Array->resize(new_rows);
    }

    query[L"RECORDCOUNT"] = new_rows;

    return new_rows;
}

Q_DECL_EXPORT QWDDX cf_QueryConvertForGrid(const QWDDX &query, int page, int pageSize)
{
    Q_UNUSED(query);
    Q_UNUSED(page);
    Q_UNUSED(pageSize);

    throw QMKFusionException("Not Implemented", "QueryConvertForGrid is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_QueryNew(const QString &columnlist, const QString &columntypelist)
{
    QWDDX ret;

    Q_UNUSED(columntypelist);

    const QString &columnlistUpper = columnlist.toUpper();

    QStringList columns;
    if (columnlistUpper.count() > 0)
    {
        columns = columnlistUpper.split(",");
    }

    //const QStringList column_types = columntypelist.split(",");

    ret = QWDDX(QWDDX::Query);

    ret.m_Struct->insert("COLUMNS", columnlistUpper);
    ret.m_Struct->insert("RESULTSET", QWDDX(QWDDX::Struct));
    ret.m_Struct->insert("RECORDCOUNT", 0);
    ret.m_Struct->insert("CURRENTROW", 1);

    for(const QString &columnName : columns)
    {
        ret[L"RESULTSET"].m_Struct->insert(columnName.trimmed(), QWDDX(QWDDX::Array));
    }

    return ret;
}

Q_DECL_EXPORT bool cf_QuerySetCell(QWDDX &query, const QString &column_name, const QWDDX &value, int row_number)
{
    if (query.type() != QWDDX::Query)
    {
        throw QMKFusionException("Parameter mismatch, Parameter query is not type Query.");
    }

    const QString upperColumnName = column_name.toUpper();

    if (!query[L"RESULTSET"].m_Struct->contains(upperColumnName))
    {
        throw QMKFusionException("Parameter mismatch, query_column has invalid column name.");
    }

    if ((row_number < 1)||(row_number > query[L"RECORDCOUNT"].toInt()))
    {
        throw QMKFusionException("Parameter mismatch, row_number is out of range.");
    }

    query[L"RESULTSET"][upperColumnName].m_Array->replace(row_number - 1, value);

    return true;
}

Q_DECL_EXPORT QString cf_QuotedValueList(const QWDDX &query_column, const QString &delimiter)
{
    if (query_column.type() != QWDDX::Array)
    {
        throw QMKFusionException("Parameter mismatch", "query_column is not column of a query.");
    }

    QStringList list;

    for(const QWDDX &item : *query_column.m_Array)
    {
        list << "'" + item.toString() + "'";
    }

    return list.join(delimiter);
}

Q_DECL_EXPORT double cf_Rand(const QString &algorithm)
{
    throw QMKFusionException("Not Implemented", "Rand is not Implemented (yet:))");
}

Q_DECL_EXPORT double cf_Randomize(int number, const QString &algorithm)
{
    throw QMKFusionException("Not Implemented", "Randomize is not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_RandRange(int number1, int number2, const QString &algorithm)
{
    throw QMKFusionException("Not Implemented", "RandRange is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_REFind(const QString &reg_expression, const QString &string, int start, bool returnsubexpressions)
{
    throw QMKFusionException("Not Implemented", "REFind is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_REFindNoCase(const QString &reg_expression, const QString &string, int start, bool returnsubexpressions)
{
    throw QMKFusionException("Not Implemented", "REFindNoCase is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_ReleaseComObject(QWDDX &objectName)
{
    throw QMKFusionException("Not Implemented", "ReleaseComObject is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_REMatch(const QString &reg_expression, const QString &string)
{
    throw QMKFusionException("Not Implemented", "REMatch is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_REMatchNoCase(const QString &reg_expression, const QString &string)
{
    throw QMKFusionException("Not Implemented", "REMatchNoCase is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_RemoveChars(const QString &string, int start, int count)
{
    throw QMKFusionException("Not Implemented", "RemoveChars is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_RepeatString(const QString &string, int count)
{
    throw QMKFusionException("Not Implemented", "RepeatString is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_Replace(const QString &string, const QString &substring1, const QString &substring2, const QString &scope)
{
    QString ret = string;

    if (scope.compare("one", Qt::CaseInsensitive) == 0)
    {
        int index = string.indexOf(substring1);

        if (index >= 0)
        {
            return ret.replace(index, substring1.length(), substring2);
        }

        return ret;
    }
    else if (scope.compare("all", Qt::CaseInsensitive) == 0)
    {
        return ret.replace(substring1, substring2);
    }
    else
    {
        throw QMKFusionException(QString("Replace unknown scope [%1]. Vaild values are: one, all").arg(scope));
    }
}

Q_DECL_EXPORT QString cf_ReplaceList(QString &list, const QString &list1, const QString &list2)
{
    throw QMKFusionException("Not Implemented", "ReplaceList is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_ReplaceNoCase(const QString &string, const QString &substring1, const QString &substring2, const QString &scope)
{
    throw QMKFusionException("Not Implemented", "ReplaceNoCase is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_REReplace(const QString &string, const QString &reg_expression, const QString &substring, const QString &scope)
{
    throw QMKFusionException("Not Implemented", "REReplace is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_REReplaceNoCase(const QString &string, const QString &reg_expression, const QString &substring, const QString &scope)
{
    throw QMKFusionException("Not Implemented", "REReplaceNoCase is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_Reverse(const QString &string)
{
    QString ret;
    int len;

    len = string.length();

    ret.resize(len);

    for(int c = 1; c <= len; c++)
    {
        ret[c] = string.at(len - c);
    }

    return ret;
}

Q_DECL_EXPORT QString cf_Right(const QString &string, int count)
{
    return string.right(count);
}

Q_DECL_EXPORT QString cf_RJustify(const QString &string, int length)
{
    QString ret = string;

    while(ret.length() < length)
    {
        ret = ret.prepend(' ');
    }

    return ret;
}

Q_DECL_EXPORT int cf_Round(double number)
{
    return round(number);
}

Q_DECL_EXPORT QString cf_RTrim(const QString &string)
{
    throw QMKFusionException("Not Implemented", "RTrim is not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_Second(const QDateTime &date)
{
    return date.time().second();
}

Q_DECL_EXPORT QString cf_SendGatewayMessage(const QString &gatewayID, const QWDDX &data)
{
    throw QMKFusionException("Not Implemented", "SendGatewayMessage is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_SerializeJSON(const QWDDX &var, bool serializeQueryByColumns)
{
    throw QMKFusionException("Not Implemented", "SerializeJSON is not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_SetEncoding(const QString &scope_name, const QString &charset)
{
    throw QMKFusionException("Not Implemented", "SetEncoding is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_SetLocale(const QString &new_locale)
{
    throw QMKFusionException("Not Implemented", "SetLocale is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_SetProfileString(const QString &iniPath, const QString &section, const QString &entry, const QString &value)
{
    throw QMKFusionException("Not Implemented", "SetProfileString is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_SetVariable(const QString &name, const QWDDX &value)
{
    throw QMKFusionException("Not Implemented", "SetVariable is not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_Sgn(double number)
{
    if (number > 0)
    {
        return 1;
    }
    else if (number < 0)
    {
        return -1;
    }

    return 0;
}

Q_DECL_EXPORT double cf_Sin(double number)
{
    return sin(number);
}

Q_DECL_EXPORT void cf_Sleep(int duration)
{
#ifdef Q_OS_WIN
#elif defined Q_OS_LINUX
    usleep(duration * 1000);
#else
    Sleep(duration);
#error Windows and Linux OSs are currently supported.
#endif
}

Q_DECL_EXPORT QString cf_SpanExcluding(const QString &string, const QWDDX &set)
{
    throw QMKFusionException("Not Implemented", "SpanExcluding is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_SpanIncluding(const QString &string, const QWDDX &set)
{
    throw QMKFusionException("Not Implemented", "SpanIncluding is not Implemented (yet:))");
}

Q_DECL_EXPORT double cf_Sqr(double number)
{
    return sqrt(number);
}

Q_DECL_EXPORT QString cf_StripCR(const QString &string)
{
    QString ret = string;

    ret = ret.remove('\r');

    return ret;
}

Q_DECL_EXPORT bool cf_StructAppend(QWDDX &struct1, const QWDDX &struct2, bool overwriteFlag)
{
    if (struct1.type() != QWDDX::Struct)
    {
        throw QMKFusionException("Not Struct", "struct1 is not a struct");
    }

    if (struct2.type() != QWDDX::Struct)
    {
        throw QMKFusionException("Not Struct", "struct2 is not a struct");
    }

    for(const QString& item : struct2.m_Struct->keys())
    {
        if ((overwriteFlag == false)&&(struct1.m_Struct->contains(item)))
        {
            continue;
        }

        struct1.m_Struct->insert(item, struct2.m_Struct->value(item));
    }

    return true;
}

Q_DECL_EXPORT bool cf_StructClear(QWDDX &structure)
{
    if (structure.type() != QWDDX::Struct)
    {
        throw QMKFusionException("Not Struct", "structure is not a struct");
    }

    structure.m_Struct->clear();

    return true;
}

Q_DECL_EXPORT QWDDX cf_StructCopy(QWDDX &structure)
{
    if (structure.type() != QWDDX::Struct)
    {
        throw QMKFusionException("Not Struct", "structure is not a struct");
    }

    return structure;
}

Q_DECL_EXPORT int cf_StructCount(const QWDDX &structure)
{
    if (structure.type() != QWDDX::Struct)
    {
        throw QMKFusionException("Not Struct", "structure is not a struct");
    }

    return structure.m_Struct->count();
}

Q_DECL_EXPORT bool cf_StructDelete(QWDDX &structure, const QString &key, bool indicatenotexisting)
{
    bool ret = true;

    if (structure.type() != QWDDX::Struct)
    {
        throw QMKFusionException("Not Struct", "structure is not a struct");
    }

    if (indicatenotexisting)
    {
        ret = structure.m_Struct->contains(key.toUpper());
    }

    structure.m_Struct->remove(key.toUpper());

    return ret;
}

Q_DECL_EXPORT QWDDX cf_StructFind(const QWDDX &structure, const QString &key)
{
    if (structure.type() != QWDDX::Struct)
    {
        throw QMKFusionException("Not Struct", "structure is not a struct");
    }

    if (!structure.m_Struct->contains(key.toUpper()))
    {
        throw QMKFusionException("Struct error", "key does not exist");
    }

    return structure.m_Struct->value(key.toUpper());
}

Q_DECL_EXPORT QWDDX cf_StructFindKey(const QWDDX &top, const QString &value, const QString &scope)
{
    Q_UNUSED(top);
    Q_UNUSED(value);
    Q_UNUSED(scope);

    throw QMKFusionException("Not Implemented", "StructFindKey is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_StructFindValue(const QWDDX &top, const QString &value, const QString &scope)
{
    Q_UNUSED(top);
    Q_UNUSED(value);
    Q_UNUSED(scope);

    throw QMKFusionException("Not Implemented", "StructFindValue is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_StructGet(const QString &pathDesired)
{
    Q_UNUSED(pathDesired);

    throw QMKFusionException("Not Implemented", "StructGet is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_StructInsert(QWDDX &structure, const QString &key, const QWDDX &value, bool allowoverwrite)
{
    if (structure.type() != QWDDX::Struct)
    {
        throw QMKFusionException("Not Struct", "structure is not a struct");
    }

    if ((allowoverwrite == false)&&(structure.m_Struct->contains(key.toUpper())))
    {
        return false;
    }

    structure.m_Struct->insert(key.toUpper(), value);

    return false;
}

Q_DECL_EXPORT bool cf_StructIsEmpty(const QWDDX &structure)
{
    if (structure.type() != QWDDX::Struct)
    {
        throw QMKFusionException("Not Struct", "structure is not a struct");
    }

    return structure.m_Struct->isEmpty();
}

Q_DECL_EXPORT QWDDX cf_StructKeyArray(const QWDDX &structure)
{
    QWDDX ret(QWDDX::Array);

    if (structure.type() != QWDDX::Struct)
    {
        throw QMKFusionException("Not Struct", "structure is not a struct");
    }

    for(const QString key : structure.m_Struct->keys())
    {
        ret.m_Array->append(key);
    }

    return ret;
}

Q_DECL_EXPORT bool cf_StructKeyExists(const QWDDX &structure, const QString &key)
{
    if (structure.type() != QWDDX::Struct)
    {
        throw QMKFusionException("Not Struct", "structure is not a struct");
    }

    return structure.m_Struct->contains(key);
}

Q_DECL_EXPORT QString cf_StructKeyList(const QWDDX &structure, const QString &delimiter)
{
    QStringList ret;

    if (structure.type() != QWDDX::Struct)
    {
        throw QMKFusionException("Not Struct", "structure is not a struct");
    }

    for(const QString key : structure.m_Struct->keys())
    {
        ret.append(key);
    }

    return ret.join(delimiter);
}

Q_DECL_EXPORT QWDDX cf_StructNew()
{
    return QWDDX(QWDDX::Struct);
}

Q_DECL_EXPORT QWDDX cf_StructSort(const QWDDX &base, const QString &sortType, const QString &sortOrder, const QString &pathToSubElement)
{
    Q_UNUSED(base);
    Q_UNUSED(sortType);
    Q_UNUSED(sortOrder);
    Q_UNUSED(pathToSubElement);

    throw QMKFusionException("Not Implemented", "StructSort is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_StructUpdate(QWDDX &structure, const QString &key, const QWDDX &value)
{
    if (structure.type() != QWDDX::Struct)
    {
        throw QMKFusionException("Not Struct", "structure is not a struct");
    }

    structure.m_Struct->insert(key.toUpper(), value);

    return true;
}

Q_DECL_EXPORT double cf_Tan(double number)
{
    return tan(number);
}

Q_DECL_EXPORT QString cf_TimeFormat(const QDateTime &time, const QString &mask)
{
    QMultiHash<QString, int> segments;
    QString ret = mask;
    int pos;

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("full", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 4, "h:mm:ss tt");
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("long", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 4, "h:mm:ss tt");
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("medium", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 6, "h:mm:ss tt");
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("short", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 5, "h:mm tt");
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("tt", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 2, "__");
        segments.insert("tt", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("t", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 1, "_");
        segments.insert("t", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("i", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 1, "_");
        segments.insert("i", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("l", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 1, "_");
        segments.insert("l", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("ss", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 2, "__");
        segments.insert("ss", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("s", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 1, "_");
        segments.insert("s", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("mm", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 2, "__");
        segments.insert("mm", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("m", pos, Qt::CaseInsensitive);
        if (i < 0) break;
        ret = ret.replace(i, 1, "_");
        segments.insert("m", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("HH", pos, Qt::CaseSensitive);
        if (i < 0) break;
        ret = ret.replace(i, 2, "__");
        segments.insert("HH", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("H", pos, Qt::CaseSensitive);
        if (i < 0) break;
        ret = ret.replace(i, 1, "_");
        segments.insert("H", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("hh", pos, Qt::CaseSensitive);
        if (i < 0) break;
        ret = ret.replace(i, 2, "__");
        segments.insert("hh", i);
        pos = i + 1;
    }

    pos = 0;
    while(1)
    {
        int i = ret.indexOf("h", pos, Qt::CaseSensitive);
        if (i < 0) break;
        ret = ret.replace(i, 1, "_");
        segments.insert("h", i);
        pos = i + 1;
    }

    for(int c = 0; c < segments.count(); c++)
    {
        const QString type = segments.keys().at(c);
        int pos = segments.values().at(c);

        if (type == "tt") ret.replace(pos, 2, time.toString("AP"));
        if (type == "t") ret.replace(pos, 1, time.toString("AP").left(1));
        if (type == "i") ret.replace(pos, 1, time.toString("z"));
        if (type == "l") ret.replace(pos, 1, time.toString("z"));
        if (type == "ss") ret.replace(pos, 2, time.toString("ss"));
        if (type == "s") ret.replace(pos, 1, time.toString("s"));
        if (type == "mm") ret.replace(pos, 2, time.toString("mm"));
        if (type == "m") ret.replace(pos, 1, time.toString("m"));
        if (type == "HH") ret.replace(pos, 2, time.toString("hh"));
        if (type == "H") ret.replace(pos, 1, time.toString("h"));
        if (type == "hh") ret.replace(pos, 2, time.toString("hh")); // TODO: 12h format is not implemented.
        if (type == "h") ret.replace(pos, 1, time.toString("h")); // TODO: 12h format is not implemented.
    }

    return ret;
}

Q_DECL_EXPORT QString cf_ToBase64(const QString &object, const QString &encoding)
{
    throw QMKFusionException("Not Implemented", "ToBase64 is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_ToBase64(const QByteArray &object, const QString &encoding)
{
    throw QMKFusionException("Not Implemented", "ToBase64 is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_ToBinary(const QString &string)
{
    throw QMKFusionException("Not Implemented", "ToBinary is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_ToBinary(const QByteArray &string)
{
    throw QMKFusionException("Not Implemented", "ToBinary is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_ToScript(const QString &cfvar, const QString &javascriptvar, bool outputformat, bool ASFormat)
{
    throw QMKFusionException("Not Implemented", "ToScript is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_ToString(const QWDDX &value, const QString &encoding)
{
    throw QMKFusionException("Not Implemented", "ToString is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_Trim(const QString &string)
{
    return string.trimmed();
}

Q_DECL_EXPORT QString cf_UCase(const QString &string)
{
    return string.toUpper();
}

Q_DECL_EXPORT QString cf_URLDecode(QString &urlEncodedString, const QString &charset)
{
    throw QMKFusionException("Not Implemented", "URLDecode is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_URLEncodedFormat(const QString &string, const QString &charset)
{
    throw QMKFusionException("Not Implemented", "URLEncodedFormat is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_URLSessionFormat(const QString &request_URL)
{
    throw QMKFusionException("Not Implemented", "URLSessionFormat is not Implemented (yet:))");
}

Q_DECL_EXPORT double cf_Val(const QString &string)
{
    QString tmp;
    double ret;
    bool ok;

    tmp = string;

    while (tmp.length() > 0)
    {
        ret = tmp.toDouble(&ok);

        if (ok == true)
        {
            return ret;
        }

        tmp = tmp.left(tmp.length() - 1);
    }

    return 0;
}

Q_DECL_EXPORT QString cf_ValueList(const QWDDX &query_column, const QString delimiter)
{
    if (query_column.type() != QWDDX::Array)
    {
        throw QMKFusionException("Parameter mismatch", "query_column is not column of a query.");
    }

    QStringList list;

    for(const QWDDX &item : *query_column.m_Array)
    {
        list << item.toString();
    }

    return list.join(delimiter);
}

Q_DECL_EXPORT void cf_VerifyClient()
{
    throw QMKFusionException("Not Implemented", "VerifyClient is not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_Week(const QDateTime &date)
{
    return date.date().weekNumber();
}

Q_DECL_EXPORT QString cf_Wrap(const QString &string, int limit, bool strip)
{
    throw QMKFusionException("Not Implemented", "Wrap is not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_XmlChildPos(const QWDDX &elem, const QWDDX &childName, int N)
{
    throw QMKFusionException("Not Implemented", "XmlChildPos is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_XmlElemNew(QWDDX &xmlObj, const QString &childName)
{
    throw QMKFusionException("Not Implemented", "XmlElemNew is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_XmlElemNew(QWDDX &xmlObj, const QString &_namespace, const QString &childName)
{
    throw QMKFusionException("Not Implemented", "XmlElemNew is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_XmlFormat(const QString &string)
{
    throw QMKFusionException("Not Implemented", "XmlFormat is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_XmlGetNodeType(const QWDDX &xmlNode)
{
    throw QMKFusionException("Not Implemented", "XmlGetNodeType is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_XmlNew(bool caseSensitive)
{
    throw QMKFusionException("Not Implemented", "XmlNew is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_XmlParse(const QString &xmlText, bool caseSensitive, const QString &validator)
{
    throw QMKFusionException("Not Implemented", "XmlParse is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_XmlSearch(const QWDDX &xmlDoc, const QString &xPathString)
{
    throw QMKFusionException("Not Implemented", "XmlSearch is not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_XmlTransform(QWDDX &xml, const QString &xsl, const QWDDX &parameters)
{
    throw QMKFusionException("Not Implemented", "XmlTransform is not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_XmlValidate(const QWDDX &xmlDoc, const QString &validator)
{
    throw QMKFusionException("Not Implemented", "XmlValidate is not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_Year(const QDateTime &date)
{
    return date.date().year();
}

Q_DECL_EXPORT bool cf_YesNoFormat(const QWDDX &value)
{
    throw QMKFusionException("Not Implemented", "YesNoFormat is not Implemented (yet:))");
}
