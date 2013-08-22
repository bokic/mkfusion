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

Q_DECL_EXPORT int cf_Compare(const QString &p_Value1, const QString &p_Value2)
{
	QWDDX l_Value1 = p_Value1;
	QWDDX l_Value2 = p_Value2;

	return l_Value1.toString().compare(l_Value2.toString(), Qt::CaseSensitive);
}

Q_DECL_EXPORT int cf_CompareNoCase(const QString &p_Value1, const QString &p_Value2)
{
	QWDDX l_Value1 = p_Value1;
	QWDDX l_Value2 = p_Value2;

	return l_Value1.toString().compare(l_Value2.toString(), Qt::CaseInsensitive);
}

Q_DECL_EXPORT double cf_Cos(double val)
{
	return cos(val);
}

Q_DECL_EXPORT QWDDX cf_CreateDate(int p_Year, int p_Month, int p_Day)
{
	if ((p_Month < 1)||(p_Month > 12))
	{
		throw QMKFusionInvalidArgumentException("CreateDate", 2, p_Month, 1, 12);
	}

	if ((p_Day < 1)||(p_Day > 31))
	{
		throw QMKFusionInvalidArgumentException("CreateDate", 3, p_Day, 1, 31);
	}

	return QDateTime(QDate(p_Year, p_Month, p_Day));
}

Q_DECL_EXPORT QWDDX cf_CreateDateTime(int p_Year, int p_Month, int p_Day, int p_Hour, int p_Minute, int p_Second)
{
	return QDateTime(QDate(p_Year, p_Month, p_Day), QTime(p_Hour, p_Minute, p_Second));
}

Q_DECL_EXPORT QWDDX cf_CreateObject(const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_CreateODBCDate(const QDateTime &p_Date)
{
	return QDateTime(QDate(p_Date.date().year(), p_Date.date().month(), p_Date.date().day()));
}

Q_DECL_EXPORT QWDDX cf_CreateODBCDateTime(const QDateTime &p_Date)
{
	return p_Date;
}

Q_DECL_EXPORT QWDDX cf_CreateODBCTime(const QDateTime &p_Date)
{
	return QDateTime(QDate(1899, 12, 30), QTime(p_Date.time().hour(), p_Date.time().minute(), p_Date.time().second()));
}

Q_DECL_EXPORT QWDDX cf_CreateTime(int p_Hour, int p_Minute, int p_Second)
{
	if ((p_Hour < 0)||(p_Hour > 23))
	{
		throw QMKFusionInvalidArgumentException("CreateTime", 1, p_Hour, 0, 23);
	}

	if ((p_Minute < 0)||(p_Minute > 59))
	{
		throw QMKFusionInvalidArgumentException("CreateTime", 2, p_Minute, 0, 59);
	}

	if ((p_Second < 0)||(p_Second > 59))
	{
		throw QMKFusionInvalidArgumentException("CreateTime", 3, p_Second, 0, 59);
	}

	return QDateTime(QDate(1899, 12, 30), QTime(p_Hour, p_Minute, p_Second));
}

Q_DECL_EXPORT QWDDX cf_CreateTimeSpan(int p_Days, int p_Hours, int p_Minutes, int p_Seconds)
{
	QDateTime ret = QDateTime(QDate(1899, 12, 30));

	ret.addDays(p_Days);
	ret.addSecs((p_Hours * 60 * 60) + (p_Minutes * 60) + p_Seconds);

	return ret;
}

Q_DECL_EXPORT QString cf_CreateUUID()
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QDateTime cf_DateAdd(const QString &p_DatePart, int p_Value, const QWDDX &p_Date)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");

	QWDDX temp = p_Date;
	QDateTime ret = temp.toDateTime();

	if(p_DatePart.compare("yyyy", Qt::CaseInsensitive) == 0)
	{
		ret.addYears(p_Value);
	}
	else if(p_DatePart.compare("q", Qt::CaseInsensitive) == 0)
	{

	}
	else if(p_DatePart.compare("m", Qt::CaseInsensitive) == 0)
	{

	}
	else if(p_DatePart.compare("y", Qt::CaseInsensitive) == 0)
	{

	}
	else if(p_DatePart.compare("d", Qt::CaseInsensitive) == 0)
	{

	}
	else if(p_DatePart.compare("w", Qt::CaseInsensitive) == 0)
	{

	}
	else if(p_DatePart.compare("ww", Qt::CaseInsensitive) == 0)
	{

	}
	else if(p_DatePart.compare("h", Qt::CaseInsensitive) == 0)
	{

	}
	else if(p_DatePart.compare("n", Qt::CaseInsensitive) == 0)
	{

	}
	else if(p_DatePart.compare("s", Qt::CaseInsensitive) == 0)
	{

	}
	else if(p_DatePart.compare("l", Qt::CaseInsensitive) == 0)
	{

	}
	else
	{

	}

	return ret;
}

Q_DECL_EXPORT int cf_DateCompare(const QWDDX &p_Date1, const QWDDX &p_Date2, const QString &p_DatePart)
{
    Q_UNUSED(p_Date1);
    Q_UNUSED(p_Date2);
    Q_UNUSED(p_DatePart);

	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_DateDiff(const QString&, const QDateTime&, const QDateTime&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DateFormat(const QDateTime&, const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_DatePart(const QString&, const QDateTime&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_Day(const QDateTime&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_DayOfWeek(const QDateTime&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DayOfWeekAsString(int, const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_DayOfYear(const QDateTime&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_DaysInMonth(const QDateTime&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT int cf_DaysInYear(const QDateTime&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DE(const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DecimalFormat(double)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT double cf_DecrementValue(double)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_Decrypt(const QString&, const QString&, const QString&, const QString&, const QString&, int)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DecryptBinary(const QString&, const QString&, const QString&, const QString&, const QString&, int)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_DeleteClientVariable(const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DeserializeJSON(const QString&, bool)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT bool cf_DirectoryExists(const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QString cf_DollarFormat(double)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_DotNetToCFType(const QWDDX&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

Q_DECL_EXPORT QWDDX cf_Duplicate(const QWDDX &variable_name)
{
    return variable_name;
}

Q_DECL_EXPORT double cf_Exp(double number)
{
    return exp(number);
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

Q_DECL_EXPORT QString cf_GetClientVariablesList()
{
    throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
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

Q_DECL_EXPORT bool cf_IsStruct(const QWDDX &variable)
{
    if (variable.type() == QWDDX::Struct)
    {
        return true;
    }

    return false;
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
