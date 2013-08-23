#include "cffunctions.h"
#include "qmkfusionexception.h"
#include <QStringList>
#include <QDateTime>

#include <math.h>


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

	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_AddSOAPResponseHeader(const QString &_namespace, const QString &name, const QWDDX &value, bool mustunderstand)
{
    Q_UNUSED(_namespace);
    Q_UNUSED(name);
    Q_UNUSED(value);
    Q_UNUSED(mustunderstand);

	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_AjaxLink(const QString &URL)
{
    Q_UNUSED(URL);

	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT void cf_AjaxOnLoad(const QString &functionName)
{
    Q_UNUSED(functionName);

	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
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
        QWDDX temp = array.m_Array->at(c);

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
        QWDDX temp = array.m_Array->at(c);

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

	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_BinaryEncode(const QString &binarydata, const QString &encoding)
{
    Q_UNUSED(binarydata);
    Q_UNUSED(encoding);

    throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
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

	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_CharsetEncode(const QString &binaryobject, const QString &encoding)
{
    Q_UNUSED(binaryobject);
    Q_UNUSED(encoding);

    throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
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

	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
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
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QDateTime cf_DateAdd(const QString &datepart, int number, QDateTime &date)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");

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
    Q_UNUSED(date1);
    Q_UNUSED(date2);
    Q_UNUSED(datePart);

	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DateConvert(const QString &conversion_type, const QDateTime &date)
{
    Q_UNUSED(conversion_type);
    Q_UNUSED(date);

	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_DateDiff(const QString &datepart, const QDateTime &date1, const QDateTime &date2)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DateFormat(const QDateTime &date, const QString &mask)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_DatePart(const QString &datepart, const QDateTime &date)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_Day(const QDateTime &date)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_DayOfWeek(const QDateTime &date)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DayOfWeekAsString(int day_of_week, const QString &locale)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_DayOfYear(const QDateTime &date)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_DaysInMonth(const QDateTime &date)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_DaysInYear(const QDateTime &date)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DE(const QString &string)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DecimalFormat(double number)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT double cf_DecrementValue(double number)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_Decrypt(const QString &encrypted_string, const QString &key, const QString &algorithm, const QString &encoding, const QString &IVorSalt, int iterations)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DecryptBinary(const QString &bytes, const QString &key, const QString &algorithm, const QString &IVorSalt, int iterations)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_DeleteClientVariable(const QString &name)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DeserializeJSON(const QString &JSONVar, bool strictMapping)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_DirectoryExists(const QString &absolute_path)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DollarFormat(double number)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_DotNetToCFType(const QWDDX &variable_name)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_Duplicate(const QWDDX &variable_name)
{
    return variable_name;
}

Q_DECL_EXPORT QString cf_Encrypt(const QString &string, const QString &key, const QString &algorithm, const QString &encoding, const QString &IVorSalt, int iterations)
{
}

Q_DECL_EXPORT QString cf_EncryptBinary(const QString &bytes, const QString &key, const QString &algorithm, const QString &IVorSalt, int iterations)
{
}

Q_DECL_EXPORT QWDDX cf_Evaluate(const QStringList &string_expressions)
{
}

Q_DECL_EXPORT double cf_Exp(double number)
{
    return exp(number);
}

Q_DECL_EXPORT QString cf_ExpandPath(const QString &relative_path)
{
}

Q_DECL_EXPORT void cf_FileClose(QWDDX &fileObj)
{
}

Q_DECL_EXPORT void cf_FileCopy(const QString &source, const QString &destination)
{
}

Q_DECL_EXPORT void cf_FileDelete(const QString &filepath)
{
}

Q_DECL_EXPORT bool cf_FileExists(const QString &absolute_path)
{
}

Q_DECL_EXPORT bool cf_FileIsEOF(QWDDX &fileObj)
{
}

Q_DECL_EXPORT void cf_FileMove(const QString &source, const QString &destination)
{
}

Q_DECL_EXPORT QWDDX cf_FileOpen(const QString &filepath, const QString mode, const QString charset)
{
}

Q_DECL_EXPORT QString cf_FileRead(const QString &filepath, const QString charset)
{
}

Q_DECL_EXPORT QString cf_FileRead(QWDDX &fileObj, int buffersize)
{
}

Q_DECL_EXPORT QWDDX cf_FileReadBinary(const QString &filepath)
{
}

Q_DECL_EXPORT QString cf_FileReadLine(QWDDX &fileObj)
{
}

Q_DECL_EXPORT void cf_FileSetAccessMode(const QString &filepath, const QString mode) // TODO: Make this available only under Linux
{
}

Q_DECL_EXPORT void cf_FileSetAttribute(const QString &filepath, const QString mode) // TODO: Make this available only under Windows
{
}

Q_DECL_EXPORT void cf_FileSetLastModified(const QString &filepath, const QDateTime &date)
{
}

Q_DECL_EXPORT void cf_FileWrite(const QString &filepath, const QString &data, const QString &charset)
{
}

Q_DECL_EXPORT void cf_FileWrite(QWDDX &fileObj, const QString &data)
{
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

    throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_FirstDayOfMonth(const QDateTime &date)
{
    Q_UNUSED(date);

    throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
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
    Q_UNUSED(number);
    Q_UNUSED(radix);

    throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_GenerateSecretKey(const QString &algorithm, int keysize)
{
}

Q_DECL_EXPORT QString cf_GetAuthUser()
{
}

Q_DECL_EXPORT QWDDX cf_GetBaseTagData(const QString &tagname, int instancenumber)
{
}

Q_DECL_EXPORT QString cf_GetBaseTagList()
{
}

Q_DECL_EXPORT QString cf_GetBaseTemplatePath()
{
}

Q_DECL_EXPORT QString cf_GetClientVariablesList()
{
    throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_GetComponentMetaData(const QString &path)
{
}

Q_DECL_EXPORT QString cf_GetContextRoot()
{
}

Q_DECL_EXPORT QString cf_GetCurrentTemplatePath()
{
}

Q_DECL_EXPORT QString cf_GetDirectoryFromPath(const QString &path)
{
}

Q_DECL_EXPORT QString cf_GetEncoding(const QString &scope_name)
{
}

Q_DECL_EXPORT QWDDX cf_GetException(const QWDDX &object)
{
}

Q_DECL_EXPORT QString cf_GetFileFromPath(const QString &path)
{
}

Q_DECL_EXPORT QWDDX cf_GetFileInfo(const QString &path)
{
}

Q_DECL_EXPORT QString cf_GetFunctionList()
{
}

Q_DECL_EXPORT QWDDX cf_GetGatewayHelper(const QString &gatewayID)
{
}

Q_DECL_EXPORT QWDDX cf_GetHttpRequestData()
{
}

Q_DECL_EXPORT QString cf_GetHttpTimeString(const QDateTime &date_time_object)
{
}

Q_DECL_EXPORT int cf_GetK2ServerDocCount()
{
}

Q_DECL_EXPORT int cf_GetK2ServerDocCountLimit()
{
}

Q_DECL_EXPORT QString cf_GetLocale()
{
}

Q_DECL_EXPORT QString cf_GetLocaleDisplayName(const QString &locale, const QString &inlocale)
{
}

Q_DECL_EXPORT QString cf_GetLocalHostIP()
{
}

Q_DECL_EXPORT QWDDX cf_GetMetaData(const QWDDX &object)
{
}

Q_DECL_EXPORT QWDDX cf_GetMetricData(const QString &mode)
{
}

Q_DECL_EXPORT QWDDX cf_GetPageContext()
{
}

Q_DECL_EXPORT QWDDX cf_GetPrinterInfo(const QString &printer)
{
}

Q_DECL_EXPORT QWDDX cf_GetProfileSections(const QString &iniFile)
{
}

Q_DECL_EXPORT QWDDX cf_GetProfileString(const QString &iniFile, const QString &section, const QString &entry)
{
}

Q_DECL_EXPORT QString cf_GetReadableImageFormats()
{
}


Q_DECL_EXPORT QWDDX cf_GetSOAPRequest()
{
}

Q_DECL_EXPORT QWDDX cf_GetSOAPRequestHeader(const QString &_namespace, const QString &name, bool asXML)
{
}

Q_DECL_EXPORT QWDDX cf_GetSOAPResponse(QWDDX &webservice)
{
}

Q_DECL_EXPORT QWDDX cf_GetSOAPResponseHeader(const QString &_namespace, const QString &name, bool asXML)
{
}

Q_DECL_EXPORT QString cf_GetTempDirectory()
{
}

Q_DECL_EXPORT QString cf_GetTempFile(const QString &dir, const QString &prefix)
{
}

Q_DECL_EXPORT QString cf_GetTemplatePath()
{
}

Q_DECL_EXPORT QString cf_GetTickCount()
{
}

Q_DECL_EXPORT QWDDX cf_GetTimeZoneInfo()
{
}

Q_DECL_EXPORT QString cf_GetToken(const QString &string, int index, const QString &delimiters)
{
}

Q_DECL_EXPORT QString cf_GetUserRoles()
{
}

Q_DECL_EXPORT QString cf_GetWriteableImageFormats()
{
}

Q_DECL_EXPORT QString cf_Hash(const QString &string, const QString &algorithm, const QString &encoding)
{
}

Q_DECL_EXPORT int cf_Hour(const QDateTime &date)
{
}

Q_DECL_EXPORT QString cf_HTMLCodeFormat(const QString &string, const QString &version)
{
}

Q_DECL_EXPORT QString cf_HTMLEditFormat(const QString &string, const QString &version)
{
}

Q_DECL_EXPORT bool cf_IIf(bool condition, const QString &string_expression1, const QString &string_expression2)
{
}

Q_DECL_EXPORT void cf_ImageAddBorder(QWDDX &name, int thickness, const QString &color, const QString &borderType)
{
}

Q_DECL_EXPORT void cf_ImageBlur(QWDDX &name, int blurRadius)
{
}

Q_DECL_EXPORT void cf_ImageClearRect(QWDDX &name, int x, int y, int width, int height)
{
}

Q_DECL_EXPORT QWDDX cf_ImageCopy(QWDDX &name, int x, int y, int width, int height, int dx, int dy)
{
}

Q_DECL_EXPORT void cf_ImageCrop(QWDDX &name, int x, int y, int width, int height)
{
}

Q_DECL_EXPORT void cf_ImageDrawArc(QWDDX &name, int x, int y, int width, int height, int startAngle, double arcAngle, bool filled)
{
}

Q_DECL_EXPORT void cf_ImageDrawBeveledRect(QWDDX &name, int x, int y, int width, int height, bool raised, bool filled)
{
}

Q_DECL_EXPORT void cf_ImageDrawCubicCurve(QWDDX &name, int ctrlx1, int ctrly1, int ctrlx2, int ctrly2, int x1, int y1, int x2, int y2)
{
}

Q_DECL_EXPORT void cf_ImageDrawLine(QWDDX &name, int x1, int y1, int x2, int y2)
{
}

Q_DECL_EXPORT void cf_ImageDrawLines(QWDDX &name, const QWDDX &xcoords, const QWDDX &ycoords, bool isPolygon, bool filled)
{
}

Q_DECL_EXPORT void cf_ImageDrawOval(QWDDX &name, int x, int y, int width, int height, bool filled)
{
}

Q_DECL_EXPORT void cf_ImageDrawPoint(QWDDX &name, int x, int y)
{
}

Q_DECL_EXPORT void cf_ImageDrawQuadraticCurve(QWDDX &name, int ctrlx1, int ctrly1, int ctrlx2, int ctrly2, int x1, int y1, int x2, int y2)
{
}

Q_DECL_EXPORT void cf_ImageDrawRect(QWDDX &name, int x, int y, int width, int height, bool filled)
{
}

Q_DECL_EXPORT void cf_ImageDrawRoundRect(QWDDX &name, int x, int y, int width, int height, int arcWidth, int arcHeight, bool filled)
{
}

Q_DECL_EXPORT void cf_ImageDrawText(QWDDX &name, const QString &str, int x, int y, const QWDDX &attributeCollection)
{
}

Q_DECL_EXPORT void cf_ImageFlip(QWDDX &name, const QString &transpose)
{
}

Q_DECL_EXPORT QWDDX cf_ImageGetBlob(const QWDDX &source)
{
}

Q_DECL_EXPORT QWDDX cf_ImageGetBufferedImage(const QWDDX &name)
{
}

Q_DECL_EXPORT QString cf_ImageGetEXIFTag(const QWDDX &name, const QString &tagName)
{
}

Q_DECL_EXPORT int cf_ImageGetHeight(const QWDDX &name)
{
}

Q_DECL_EXPORT QString cf_ImageGetIPTCTag(const QWDDX &name, const QString &tagName)
{
}

Q_DECL_EXPORT int cf_ImageGetWidth(const QWDDX &name)
{
}

Q_DECL_EXPORT void cf_ImageGrayscale(QWDDX &name)
{
}

Q_DECL_EXPORT QWDDX cf_ImageInfo(const QWDDX &name)
{
}

Q_DECL_EXPORT void cf_ImageNegative(QWDDX &name)
{
}

Q_DECL_EXPORT QWDDX cf_ImageNew(const QString &source, int width, int height, const QString &imageType, const QString canvasColor)
{
}

Q_DECL_EXPORT void cf_ImageOverlay(QWDDX &source1, const QWDDX &source2)
{
}

Q_DECL_EXPORT QWDDX cf_ImagePaste(QWDDX &image1, const QWDDX &image2, int x, int y)
{
}

Q_DECL_EXPORT QWDDX cf_ImageRead(const QString &path)
{
}

Q_DECL_EXPORT QWDDX cf_ImageReadBase64(const QString &string)
{
}

Q_DECL_EXPORT void cf_ImageResize(QWDDX &name, int width, int height, const QString &interpolation, int blurFactor)
{
}

Q_DECL_EXPORT void cf_ImageRotate(QWDDX &name, double angle, int x, int y, const QString &interpolation)
{
}

Q_DECL_EXPORT QWDDX cf_ImageRotateDrawingAxis(QWDDX &name, double angle, int x, int y)
{
}

Q_DECL_EXPORT void cf_ImageScaleToFit(QWDDX &name, const QString &fitWidth, const QString &fitHeight, const QString &interpolation, int blurFactor)
{
}

Q_DECL_EXPORT void cf_ImageSetAntialiasing(QWDDX &name, bool antialias)
{
}

Q_DECL_EXPORT void cf_ImageSetBackgroundColor(QWDDX &name, const QString &color)
{
}

Q_DECL_EXPORT void cf_ImageSetDrawingColor(QWDDX &name, const QString &color)
{
}

Q_DECL_EXPORT void cf_ImageSetDrawingStroke(QWDDX &name, const QWDDX &attributeCollection)
{
}

Q_DECL_EXPORT void cf_ImageSetDrawingTransparency(QWDDX &name, double percent)
{
}

Q_DECL_EXPORT void cf_ImageSharpen(QWDDX &name, double gain)
{
}

Q_DECL_EXPORT void cf_ImageShear(QWDDX &name, double shear, const QString &direction, const QString &interpolation)
{
}

Q_DECL_EXPORT void cf_ImageShearDrawingAxis(QWDDX &name, double shx, double shy)
{
}

Q_DECL_EXPORT void cf_ImageTranslate(QWDDX &name, int xTrans, int yTrans, const QString &interpolation)
{
}

Q_DECL_EXPORT void cf_ImageTranslateDrawingAxis(QWDDX &name, int x, int y)
{
}

Q_DECL_EXPORT void cf_ImageWrite(const QWDDX &name, const QString &destination, double quality)
{
}

Q_DECL_EXPORT QString cf_ImageWriteBase64(const QWDDX &name, const QString &destination, const QString &format, bool inHTMLFormat)
{
}

Q_DECL_EXPORT void cf_ImageXORDrawingMode(QWDDX &name, const QString &c1)
{
}

Q_DECL_EXPORT int cf_IncrementValue(int number)
{
}

Q_DECL_EXPORT QString cf_InputBaseN(const QString &string, int radix)
{
}

Q_DECL_EXPORT QString cf_Insert(const QString &substring, QString &string, int position)
{
}

Q_DECL_EXPORT QString cf_Int(double number)
{
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
}

Q_DECL_EXPORT bool cf_IsBoolean(const QWDDX &value)
{
}

Q_DECL_EXPORT bool cf_IsCustomFunction(const QWDDX &name)
{
}

Q_DECL_EXPORT bool cf_IsDate(const QWDDX &string)
{
}

Q_DECL_EXPORT bool cf_IsDDX(const QString &path_or_string)
{
}

Q_DECL_EXPORT bool cf_IsDebugMode()
{
}

Q_DECL_EXPORT bool cf_IsDefined(const QWDDX &variable_name)
{
}

Q_DECL_EXPORT bool cf_IsImage(const QWDDX &name)
{
}

Q_DECL_EXPORT bool cf_IsImageFile(const QWDDX &path)
{
}

Q_DECL_EXPORT bool cf_IsInstanceOf(const QWDDX &object, const QString &typeName)
{
}

Q_DECL_EXPORT bool cf_IsJSON(const QWDDX &var)
{
}

Q_DECL_EXPORT bool cf_IsLeapYear(int year)
{
}

Q_DECL_EXPORT bool cf_IsLocalHost(const QString &ipaddress)
{
}

Q_DECL_EXPORT bool cf_IsNumeric(const QString &string)
{
}

Q_DECL_EXPORT bool cf_IsNumericDate(double number)
{
}

Q_DECL_EXPORT bool cf_IsObject(const QWDDX &value)
{
}

Q_DECL_EXPORT bool cf_IsPDFFile(const QString &path)
{
}

Q_DECL_EXPORT bool cf_IsPDFObject(const QWDDX &value)
{
}

Q_DECL_EXPORT bool cf_IsQuery(const QWDDX &value)
{
}

Q_DECL_EXPORT bool cf_IsSimpleValue(const QWDDX &value)
{
}

Q_DECL_EXPORT bool cf_IsSOAPRequest()
{
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
}

Q_DECL_EXPORT bool cf_IsUserInRole(const QString &role_name)
{
}

Q_DECL_EXPORT bool cf_IsUserLoggedIn()
{
}

Q_DECL_EXPORT bool cf_IsValid(const QString &type, const QWDDX &value)
{
}

Q_DECL_EXPORT bool cf_IsValid(const QString &type, const QWDDX &value, int min, int max)
{
}

Q_DECL_EXPORT bool cf_IsValid(const QString &type, const QWDDX &value, const QString &pattern)
{
}

Q_DECL_EXPORT bool cf_IsWDDX(const QWDDX &value)
{
}

Q_DECL_EXPORT bool cf_IsXML(const QWDDX &value)
{
}

Q_DECL_EXPORT bool cf_IsXmlAttribute(const QWDDX &value)
{
}

Q_DECL_EXPORT bool cf_IsXmlDoc(const QWDDX &value)
{
}

Q_DECL_EXPORT bool cf_IsXmlElem(const QWDDX &value)
{
}

Q_DECL_EXPORT bool cf_IsXmlNode(const QWDDX &value)
{
}

Q_DECL_EXPORT bool cf_IsXmlRoot(const QWDDX &value)
{
}

Q_DECL_EXPORT QWDDX JavaCast(const QString &type, const QWDDX &value)
{
}

Q_DECL_EXPORT QString JSStringFormat(const QString &string)
{
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
}

Q_DECL_EXPORT QString cf_ListChangeDelims(QString &list, const QString &new_delimiter, const QString &delimiters)
{
}

Q_DECL_EXPORT int cf_ListContains(const QString &list, const QString &substring, const QString &delimiters)
{
}

Q_DECL_EXPORT int cf_ListContainsNoCase(const QString &list, const QString &substring, const QString &delimiters)
{
}

Q_DECL_EXPORT QString cf_ListDeleteAt(QString &list, int position, const QString &delimiters)
{
}

Q_DECL_EXPORT int cf_ListFind(const QString &list, const QString &value, const QString &delimiters)
{
}

Q_DECL_EXPORT int cf_ListFindNoCase(const QString &list, const QString &value, const QString &delimiters)
{
}

Q_DECL_EXPORT QString cf_ListFirst(const QString &list, const QString &delimiters)
{
}

Q_DECL_EXPORT QString cf_ListGetAt(const QString &list, int position, const QString &delimiters)
{
}

Q_DECL_EXPORT QString cf_ListInsertAt(QString &list, int position, const QString value, const QString &delimiters)
{
}

Q_DECL_EXPORT QString cf_ListLast(const QString &list, const QString &delimiters)
{
}

Q_DECL_EXPORT int cf_ListLen(const QString &list, const QString &delimiters)
{
}

Q_DECL_EXPORT QString cf_ListPrepend(QString &list, const QString &value, const QString &delimiters)
{
}

Q_DECL_EXPORT QString cf_ListQualify(QString &list, const QString &quallifier, const QString &delimiters, const QString elements)
{
}

Q_DECL_EXPORT QString cf_ListRest(const QString &list, const QString &delimiters)
{
}

Q_DECL_EXPORT QString cf_ListSetAt(QString &list, int position, const QString value, const QString &delimiters)
{
}

Q_DECL_EXPORT QString cf_ListSort(QString &list, const QString sort_type, const QString sort_order, const QString &delimiters)
{
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
}

Q_DECL_EXPORT int cf_ListValueCountNoCase(const QString &list, const QString value, const QString &delimiters)
{
}

Q_DECL_EXPORT QString cf_LJustify(const QString &string, int length)
{
}

Q_DECL_EXPORT double cf_Log(double number)
{
}

Q_DECL_EXPORT double cf_Log10(double number)
{
}

Q_DECL_EXPORT QString cf_LSCurrencyFormat(double number, const QString &type, const QString locale)
{
}

Q_DECL_EXPORT QString cf_LSDateFormat(const QDateTime &date, const QString &mask, const QString &locale)
{
}

Q_DECL_EXPORT QString cf_LSEuroCurrencyFormat(double currency_number, const QString &locale, const QString &type)
{
}

Q_DECL_EXPORT bool cf_LSIsCurrency(const QString &string, const QString &locale)
{
}

Q_DECL_EXPORT bool cf_LSIsDate(const QString &string, const QString &locale)
{
}

Q_DECL_EXPORT bool cf_LSIsNumeric(const QString &string, const QString &locale)
{
}

Q_DECL_EXPORT QString cf_LSNumberFormat(double number, const QString &mask, const QString &locale)
{
}

Q_DECL_EXPORT QString cf_LSParseCurrency(const QString &string, const QString &locale)
{
}

Q_DECL_EXPORT QDateTime cf_LSParseDateTime(const QString &string, const QString &locale)
{
}

Q_DECL_EXPORT QString cf_LSParseEuroCurrency(const QString &currency_string, const QString &locale)
{
}

Q_DECL_EXPORT QString cf_LSParseNumber(const QString &string, const QString &locale)
{
}

Q_DECL_EXPORT QString cf_LSTimeFormat(const QDateTime &time, const QString &locale)
{
}

Q_DECL_EXPORT QString cf_LSTimeFormat(const QString &time, const QString &locale)
{
}

Q_DECL_EXPORT QString cf_LTrim(QString &string)
{
}

Q_DECL_EXPORT double cf_Max(double number1, double number2)
{
}

Q_DECL_EXPORT QString cf_Mid(const QString &string, int start, int count)
{
}

Q_DECL_EXPORT double cf_Min(double number1, double number2)
{
}

Q_DECL_EXPORT int cf_Minute(const QDateTime &date)
{
}

Q_DECL_EXPORT int cf_Month(const QDateTime &date)
{
}

Q_DECL_EXPORT QString cf_MonthAsString(const QDateTime &date, const QString &locale)
{
}

Q_DECL_EXPORT QDateTime cf_Now()
{
}

Q_DECL_EXPORT QString cf_NumberFormat(double number, const QString &mask)
{
}

Q_DECL_EXPORT QString cf_ParagraphFormat(const QString &string)
{
}

Q_DECL_EXPORT QDateTime cf_ParseDateTime(const QString &datetime_string, const QString &pop_conversion)
{
}

Q_DECL_EXPORT double cf_Pi()
{
}

Q_DECL_EXPORT QWDDX cf_PrecisionEvaluate(const QStringList &string_expressions)
{
}

Q_DECL_EXPORT QString cf_PreserveSingleQuotes(const QString &variable)
{
}

Q_DECL_EXPORT int cf_Quarter(const QDateTime &date)
{
}

Q_DECL_EXPORT int cf_QueryAddColumn(QWDDX &query, const QString &column_name, const QString &datatype, const QString &array_name)
{
}

Q_DECL_EXPORT int cf_QueryAddRow(QWDDX &query, int number)
{
}

Q_DECL_EXPORT QWDDX cf_QueryConvertForGrid(const QWDDX &query, int page, int pageSize)
{
}

Q_DECL_EXPORT QWDDX cf_QueryNew(const QString &columnlist, const QString &columntypelist)
{
}

Q_DECL_EXPORT bool cf_QuerySetCell(QWDDX &query, const QString &column_name, const QWDDX &value, int row_number)
{
}

Q_DECL_EXPORT QString cf_QuotedValueList(const QWDDX &query_column, const QString &delimiter)
{
}

Q_DECL_EXPORT double cf_Rand(const QString &algorithm)
{
}

Q_DECL_EXPORT double cf_Randomize(int number, const QString &algorithm)
{
}

Q_DECL_EXPORT int cf_RandRange(int number1, int number2, const QString &algorithm)
{
}

Q_DECL_EXPORT QWDDX cf_REFind(const QString &reg_expression, const QString &string, int start, bool returnsubexpressions)
{
}

Q_DECL_EXPORT QWDDX cf_REFindNoCase(const QString &reg_expression, const QString &string, int start, bool returnsubexpressions)
{
}

Q_DECL_EXPORT void cf_ReleaseComObject(QWDDX &objectName)
{
}

Q_DECL_EXPORT QWDDX cf_REMatch(const QString &reg_expression, const QString &string)
{
}

Q_DECL_EXPORT QWDDX cf_REMatchNoCase(const QString &reg_expression, const QString &string)
{
}

Q_DECL_EXPORT QString cf_RemoveChars(QString &string, int start, int count)
{
}

Q_DECL_EXPORT QString cf_RepeatString(QString &string, int count)
{
}

Q_DECL_EXPORT QString cf_Replace(QString &string, const QString &substring1, const QString &substring2, const QString &scope)
{
}

Q_DECL_EXPORT QString cf_ReplaceList(QString &list, const QString &list1, const QString &list2)
{
}

Q_DECL_EXPORT QString cf_ReplaceNoCase(QString &string, const QString &substring1, const QString &substring2, const QString &scope)
{
}

Q_DECL_EXPORT QString cf_REReplace(const QString &string, const QString &reg_expression, const QString &substring, const QString &scope)
{
}

Q_DECL_EXPORT QString cf_REReplaceNoCase(const QString &string, const QString &reg_expression, const QString &substring, const QString &scope)
{
}

Q_DECL_EXPORT QString cf_Reverse(const QString &string)
{
}

Q_DECL_EXPORT QString cf_Right(const QString &string, int count)
{
}

Q_DECL_EXPORT QString cf_RJustify(QString &string, int length)
{
}

Q_DECL_EXPORT int cf_Round(double number)
{
}

Q_DECL_EXPORT QString cf_RTrim(QString &string)
{
}

Q_DECL_EXPORT int cf_Second(const QDateTime &date)
{
}

Q_DECL_EXPORT QString cf_SendGatewayMessage(const QString &gatewayID, const QWDDX &data)
{
}

Q_DECL_EXPORT QString cf_SerializeJSON(const QWDDX &var, bool serializeQueryByColumns)
{
}

Q_DECL_EXPORT void cf_SetEncoding(const QString &scope_name, const QString &charset)
{
}

Q_DECL_EXPORT QString cf_SetLocale(const QString &new_locale)
{
}

Q_DECL_EXPORT QString cf_SetProfileString(const QString &iniPath, const QString &section, const QString &entry, const QString &value)
{
}

Q_DECL_EXPORT QWDDX cf_SetVariable(const QString &name, const QWDDX &value)
{
}

Q_DECL_EXPORT int cf_Sgn(double number)
{
}

Q_DECL_EXPORT double cf_Sin(double number)
{
}

Q_DECL_EXPORT void cf_Sleep(int duration)
{
}

Q_DECL_EXPORT QString cf_SpanExcluding(const QString &string, const QWDDX &set)
{
}

Q_DECL_EXPORT QString cf_SpanIncluding(const QString &string, const QWDDX &set)
{
}

Q_DECL_EXPORT double cf_Sqr(double number)
{
}

Q_DECL_EXPORT QString cf_StripCR(QString &string)
{
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
        ret = structure.m_Struct->contains(key);
    }

    structure.m_Struct->remove(key);

    return ret;
}

Q_DECL_EXPORT QWDDX cf_StructFind(const QWDDX &structure, const QString &key)
{
    if (structure.type() != QWDDX::Struct)
    {
        throw QMKFusionException("Not Struct", "structure is not a struct");
    }

    if (!structure.m_Struct->contains(key))
    {
        throw QMKFusionException("Struct error", "key does not exist");
    }

    return structure.m_Struct->value(key);
}

Q_DECL_EXPORT QWDDX cf_StructFindKey(const QWDDX &top, const QString &value, const QString &scope)
{
    Q_UNUSED(top);
    Q_UNUSED(value);
    Q_UNUSED(scope);

    throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_StructFindValue(const QWDDX &top, const QString &value, const QString &scope)
{
    Q_UNUSED(top);
    Q_UNUSED(value);
    Q_UNUSED(scope);

    throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_StructGet(const QString &pathDesired)
{
    Q_UNUSED(pathDesired);

    throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_StructInsert(QWDDX &structure, const QString &key, const QWDDX &value, bool allowoverwrite)
{
    if (structure.type() != QWDDX::Struct)
    {
        throw QMKFusionException("Not Struct", "structure is not a struct");
    }

    if ((allowoverwrite == false)&&(structure.m_Struct->contains(key)))
    {
        return false;
    }

    structure.m_Struct->insert(key, value);

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

    throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_StructUpdate(QWDDX &structure, const QString &key, const QWDDX &value)
{
    if (structure.type() != QWDDX::Struct)
    {
        throw QMKFusionException("Not Struct", "structure is not a struct");
    }

    structure.m_Struct->insert(key, value);

    return true;
}

Q_DECL_EXPORT double cf_Tan(double number)
{
}

Q_DECL_EXPORT QString cf_TimeFormat(const QDateTime &time, const QString &mask)
{
}

Q_DECL_EXPORT QString cf_ToBase64(const QString &object, const QString &encoding)
{
}

Q_DECL_EXPORT QString cf_ToBase64(const QByteArray &object, const QString &encoding)
{
}

Q_DECL_EXPORT QWDDX cf_ToBinary(const QString &string)
{
}

Q_DECL_EXPORT QWDDX cf_ToBinary(const QByteArray &string)
{
}

Q_DECL_EXPORT QString cf_ToScript(const QString &cfvar, const QString &javascriptvar, bool outputformat, bool ASFormat)
{
}

Q_DECL_EXPORT QString cf_ToString(const QWDDX &value, const QString &encoding)
{
}

Q_DECL_EXPORT QString cf_Trim(QString &string)
{
}

Q_DECL_EXPORT QString cf_UCase(QString &string)
{
}

Q_DECL_EXPORT QString cf_URLDecode(QString &urlEncodedString, const QString &charset)
{
}

Q_DECL_EXPORT QString cf_URLEncodedFormat(QString &string, const QString &charset)
{
}

Q_DECL_EXPORT QString cf_URLSessionFormat(const QString &request_URL)
{
}

Q_DECL_EXPORT double cf_Val(const QString &string)
{
}

Q_DECL_EXPORT QString cf_ValueList(const QWDDX &query_column, const QString delimiter)
{
}

Q_DECL_EXPORT void cf_VerifyClient()
{
}

Q_DECL_EXPORT int cf_Week(const QDateTime &date)
{
}

Q_DECL_EXPORT QString cf_Wrap(const QString &string, int limit, bool strip)
{
}

Q_DECL_EXPORT void cf_WriteOutput(const QString &string)
{
}

Q_DECL_EXPORT bool cf_XmlChildPos(const QWDDX &elem, const QWDDX &childName, int N)
{
}

Q_DECL_EXPORT QWDDX cf_XmlElemNew(QWDDX &xmlObj, const QString &childName)
{
}

Q_DECL_EXPORT QWDDX cf_XmlElemNew(QWDDX &xmlObj, const QString &_namespace, const QString &childName)
{
}

Q_DECL_EXPORT QString cf_XmlFormat(QString &string)
{
}

Q_DECL_EXPORT QString cf_XmlGetNodeType(const QWDDX &xmlNode)
{
}

Q_DECL_EXPORT QWDDX cf_XmlNew(bool caseSensitive)
{
}

Q_DECL_EXPORT QWDDX cf_XmlParse(const QString &xmlText, bool caseSensitive, const QString &validator)
{
}

Q_DECL_EXPORT QWDDX cf_XmlSearch(const QWDDX &xmlDoc, const QString &xPathString)
{
}

Q_DECL_EXPORT QString cf_XmlTransform(QWDDX &xml, const QString &xsl, const QWDDX &parameters)
{
}

Q_DECL_EXPORT QWDDX cf_XmlValidate(const QWDDX &xmlDoc, const QString &validator)
{
}

Q_DECL_EXPORT int cf_Year(const QDateTime &date)
{
}

Q_DECL_EXPORT bool cf_YesNoFormat(const QWDDX &value)
{
}

QString WriteException(const QMKFusionException &ex, const QCFRunningTemplate_Request &r)
{
	QString ret;

	ret  = "<font style=\"COLOR: black; FONT: 16pt/18pt verdana\">The web site you are accessing has experienced an unexpected error.<br>Please contact the website administrator.</font>\n";
	ret += "<br>\n";
	ret += "<br>\n";
	ret += "<table border=\"1\" cellpadding=\"3\" bordercolor=\"#000808\" bgcolor=\"#e7e7e7\">\n";
	ret += "\t<tr>\n";
	ret += "\t\t<td bgcolor=\"#000066\">\n";
	ret += "\t\t\t<font style=\"COLOR: white; FONT: 11pt/13pt verdana\" color=\"white\">The following information is meant for the website developer for debugging purposes.</font>\n";
	ret += "\t\t</td>\n";
	ret += "\t<tr>\n";
	ret += "\t<tr>\n";
	ret += "\t\t<td bgcolor=\"#4646EE\">\n";
	ret += "\t\t\t<font style=\"COLOR: white; FONT: 11pt/13pt verdana\" color=\"white\">Error Occurred While Processing Request</font>\n";
	ret += "\t\t</td>\n";
	ret += "\t</tr>\n";
	ret += "\t<tr>\n";
	ret += "\t\t<td>\n";
	ret += "\t\t\t<font style=\"COLOR: black; FONT: 8pt/11pt verdana\">\n";
	ret += "\t\t\t\t<table width=\"500\" cellpadding=\"0\" cellspacing=\"0\" border=\"0\">\n";
	ret += "\t\t\t\t\t<tr>\n";
	ret += "\t\t\t\t\t\t<td id=\"tableProps2\" align=\"left\" valign=\"middle\" width=\"500\">\n";
	ret += "\t\t\t\t\t\t\t<h1 id=\"textSection1\" style=\"COLOR: black; FONT: 13pt/15pt verdana\">" + *ex.m_message + "</h1>\n";
	ret += "\t\t\t\t\t\t</td>\n";
	ret += "\t\t\t\t\t</tr>\n";
	ret += "\t\t\t\t\t<tr>\n";
	ret += "\t\t\t\t\t\t<td id=\"tablePropsWidth\" width=\"400\" colspan=\"2\">\n";
	ret += "\t\t\t\t\t\t\t<font style=\"COLOR: black; FONT: 8pt/11pt verdana\"></font>\n";
	ret += "\t\t\t\t\t\t</td>\n";
	ret += "\t\t\t\t\t</tr>\n";
	ret += "\t\t\t\t\t<tr>\n";
	ret += "\t\t\t\t\t\t<td height>&nbsp;</td>\n";
	ret += "\t\t\t\t\t</tr>\n";
	ret += "\t\t\t\t\t<tr>\n";
	ret += "\t\t\t\t\t\t<td colspan=\"2\">\n";
	ret += "\t\t\t\t\t\t\t<font style=\"COLOR: black; FONT: 8pt/11pt verdana\">\n";
	ret += "\t\t\t\t\t\t\t\tResources:\n";
	ret += "\t\t\t\t\t\t\t\t<ul>\n";
	ret += "\t\t\t\t\t\t\t\t\t<li>Enable Robust Exception Information to provide greater detail about the source of errors.  In the Administrator, click Debugging & Logging > Debug Output Settings, and select the Robust Exception Information option.</li>\n";
	ret += "\t\t\t\t\t\t\t\t\t<li>Check the <a href='http://www.bokicsoft.com/mkfusion/docs/' target=\"new\">ColdFusion documentation</a> to verify that you are using the correct syntax.</li>\n";
	ret += "\t\t\t\t\t\t\t\t\t<li>Search the <a href='http://www.bokicsoft.com/mkfusion/kb/' target=\"new\">Knowledge Base</a> to find a solution to your problem.</li>\n";
	ret += "\t\t\t\t\t\t\t\t</ul>\n";
	ret += "\t\t\t\t\t\t\t</font>\n";
	ret += "\t\t\t\t\t\t</td>\n";
	ret += "\t\t\t\t\t</tr>\n";
	ret += "\t\t\t\t\t<tr>\n";
	ret += "\t\t\t\t\t\t<td colspan=\"2\">\n";
	ret += "\t\t\t\t\t\t\t<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\">\n";
	ret += "\t\t\t\t\t\t\t\t<tr>\n";
	ret += "\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">Browser&nbsp;&nbsp;</td>\n";
	ret += "\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">" + r.m_UserAgent + "</td>\n";
	ret += "\t\t\t\t\t\t\t\t</tr>\n";
	ret += "\t\t\t\t\t\t\t\t<tr>\n";
	ret += "\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">Remote Address&nbsp;&nbsp;</td>\n";
	ret += "\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">" + r.m_Host + "</td>\n";
	ret += "\t\t\t\t\t\t\t\t</tr>\n";
	ret += "\t\t\t\t\t\t\t\t<tr>\n";
	ret += "\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">Referrer&nbsp;&nbsp;</td>\n";
	ret += "\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">" + r.m_Referer + "</td>\n";
	ret += "\t\t\t\t\t\t\t\t</tr>\n";
	ret += "\t\t\t\t\t\t\t\t<tr>\n";
	ret += "\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">Date/Time&nbsp;&nbsp;</td>\n";
	ret += "\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">" + QDateTime::currentDateTime().toString("dd-MMM-yy hh:mm AP") + "</td>\n";
	ret += "\t\t\t\t\t\t\t\t</tr>\n";
	ret += "\t\t\t\t\t\t\t</table>\n";
	ret += "\t\t\t\t\t\t</td>\n";
	ret += "\t\t\t\t\t</tr>\n";
	ret += "\t\t\t\t</table>\n";
	ret += "\t\t\t</font>\n";
	ret += "\t\t</td>\n";
	ret += "\t</tr>\n";
	ret += "</table>\n";

	return  ret;
}
