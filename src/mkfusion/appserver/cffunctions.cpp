#include "cffunctions.h"
#include "qmkfusionexception.h"
#include <QDateTime>

#include <math.h>

// Page1
double cf_Abs(double val)
{
	return fabs(val);
}

int cf_Abs(int val)
{
	return abs(val);
}

double cf_ACos(double val)
{
	if ((val < -1)||(val > 1))
	{
		throw QMKFusionInvalidArgumentException("ACos", 1, val, -1, 1);
	}

	return acos(val);
}

void cf_AddSOAPRequestHeader(QWDDX *p_WebService, const QString& p_Namespace, const QString& p_Name, const QWDDX& p_Value, bool p_MustUnderstand)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

void cf_AddSOAPResponseHeader(const QString& p_Namespace, const QString& p_Name, const QWDDX& p_Value, bool p_MustUnderstand)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QString cf_AjaxLink(const QString& p_URL)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

void cf_AjaxOnLoad(const QString& p_FunctionName)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

void cf_ApplicationStop()
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

bool cf_ArrayAppend(QWDDX *p_Array, const QWDDX& p_Value)
{
	if (p_Array->m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	if (p_Array->m_ArrayDimension > 1)
	{
		if (p_Value.m_Type != QWDDX::Array)
		{
			throw QMKFusionArrayGenericMultiDimException();
		}
		if (p_Array->m_ArrayDimension != p_Value.m_ArrayDimension + 1)
		{
			throw QMKFusionArrayGenericMultiDimException();
		}
	}

	p_Array->m_Array.append(p_Value);

	return true;
}

double cf_ArrayAvg(const QWDDX& p_Array)
{
	if (p_Array.m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	if (p_Array.m_ArrayDimension != 1)
	{
		throw new QMKFusionArrayNotOneDimensionException();
	}

	if (p_Array.m_Array.size() == 0)
	{
		return 0;
	}

	double sum = 0;
	QWDDX temp = p_Array;

	for (int c = 0; c < temp.m_Array.size(); c++)
	{
		sum += temp.m_Array[c].toNumber();
	}

	return sum / temp.m_Array.size();
}

bool cf_ArrayClear(QWDDX *p_Value)
{
	if (p_Value->m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	p_Value->m_Array.clear();

	return true;
}

bool cf_ArrayContains(const QWDDX& p_Array, const QWDDX& p_Search)
{
	if (p_Array.m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	QWDDX temp2 = p_Search;

	for(int c = 0; c < p_Array.m_Array.size(); c++)
	{
		QWDDX temp1 = p_Array.m_Array[c];
		if (temp1.toString() == temp2.toString())
		{
			return true;
		}
	}

	return false;
}

bool cf_ArrayDelete(QWDDX *p_Array, const QWDDX& p_Value)
{
	if (p_Array->m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	QWDDX temp = p_Value;

	for(int c = 0; c < p_Array->m_Array.size(); c++)
	{
		if (p_Array[c] == temp)
		{
			p_Array->m_Array.remove(c);
			return true;
		}
	}

	return false;
}

bool cf_ArrayDeleteAt(QWDDX *p_Array, int p_Index)
{
	if (p_Array->m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	if ((p_Index < 1)||(p_Index > p_Array->m_Array.size()))
	{
		throw QMKFusionInvalidArrayIndexException(p_Index, p_Array->m_Array.size());
	}

	p_Array->m_Array.remove(p_Index - 1);

	return true;
}

int cf_ArrayFind(const QWDDX& p_Array, const QWDDX& p_Search)
{
	if (p_Array.m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	QWDDX temp2 = p_Search;

	for(int c = 0; c < p_Array.m_Array.size(); c++)
	{
		QWDDX temp1 = p_Array.m_Array[c];
		if (temp1.toString() == temp2.toString())
		{
			return c + 1;
		}
	}

	return 0;
}

int cf_ArrayFindNoCase(const QWDDX& p_Array, const QWDDX& p_Search)
{
	if (p_Array.m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	QWDDX temp2 = p_Search;

	for(int c = 0; c < p_Array.m_Array.size(); c++)
	{
		QWDDX temp1 = p_Array.m_Array[c];
		if (temp1.toString().compare(temp2.toString(), Qt::CaseInsensitive) == 0)
		{
			return c + 1;
		}
	}

	return 0;
}

bool cf_ArrayInsertAt(QWDDX* p_Array, int p_Index, const QWDDX& p_Value)
{
	if (p_Array->m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	if (p_Array->m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	if (p_Array->m_ArrayDimension > 1)
	{
		if (p_Value.m_Type != QWDDX::Array)
		{
			throw QMKFusionArrayGenericMultiDimException();
		}
		if (p_Array->m_ArrayDimension != p_Value.m_ArrayDimension + 1)
		{
			throw QMKFusionArrayGenericMultiDimException();
		}
	}

	if ((p_Index < 1)||(p_Index > p_Array->m_Array.size()))
	{
		throw QMKFusionInvalidArrayIndexException(p_Index, p_Array->m_Array.size());
	}

	QWDDX temp = p_Value;

	p_Array->m_Array.insert(p_Index - 1, temp);

	return true;
}

bool cf_ArrayIsDefined(const QWDDX& p_Array, int p_Index)
{
	if (p_Array.m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	if ((p_Index < 1)||(p_Index > p_Array.m_Array.size()))
	{
		throw QMKFusionInvalidArrayIndexException(p_Index, p_Array.m_Array.size());
	}

	if (p_Array.m_Array[p_Index - 1].m_Type == QWDDX::Null)
	{
		return false;
	}

	return true;
}

bool cf_ArrayIsEmpty(const QWDDX& p_Array)
{
	if (p_Array.m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	if (p_Array.m_Array.size() == 0)
	{
		return true;
	}

	return false;
}

int cf_ArrayLen(const QWDDX& p_Array)
{
	if (p_Array.m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	return p_Array.m_Array.size();
}

double cf_ArrayMax(const QWDDX& p_Array)
{
	if (p_Array.m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	if (p_Array.m_ArrayDimension != 1)
	{
		throw new QMKFusionArrayNotOneDimensionException();
	}

	double ret = 0;

	for(int c = 0; c < p_Array.m_Array.size(); c++)
	{
		QWDDX temp = p_Array.m_Array[c];

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

double cf_ArrayMin(const QWDDX& p_Array)
{
	if (p_Array.m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	if (p_Array.m_ArrayDimension != 1)
	{
		throw new QMKFusionArrayNotOneDimensionException();
	}

	double ret = 0;

	for(int c = 0; c < p_Array.m_Array.size(); c++)
	{
		QWDDX temp = p_Array.m_Array[c];

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


QWDDX cf_ArrayNew(int p_Dimension)
{
	if ((p_Dimension < 1)||(p_Dimension > 3))
	{
		throw QMKFusionBadArrayDimensionException(p_Dimension);
	}

	QWDDX ret(QWDDX::Array);

	ret.m_ArrayDimension = p_Dimension;

	return ret;
}

bool cf_ArrayPrepend(QWDDX *p_Array, const QWDDX &p_Value)
{
	if (p_Array->m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	if (p_Array->m_ArrayDimension > 1)
	{
		if (p_Value.m_Type != QWDDX::Array)
		{
			throw QMKFusionArrayGenericMultiDimException();
		}
		if (p_Array->m_ArrayDimension != p_Value.m_ArrayDimension + 1)
		{
			throw QMKFusionArrayGenericMultiDimException();
		}
	}

	QWDDX temp = p_Value;

	p_Array->m_Array.insert(0, temp);

	return true;
}


bool cf_ArrayResize(QWDDX *p_Array, int p_MinSize)
{
	if (p_Array->m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	if (p_Array->m_Array.size() < p_MinSize)
	{
		p_Array->m_Array.reserve(p_MinSize);
	}

	return true;
}

bool cf_ArraySet(QWDDX *p_Array, int p_Start, int p_End, const QWDDX &p_Value)
{
	if (p_Array->m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	if((p_Start > p_End)||(p_Start <= 0))
	{
		throw QMKFusionArraySetRangeException(p_Start, p_End);
	}

	if (p_Array->m_ArrayDimension > 1)
	{
		if (p_Value.m_Type != QWDDX::Array)
		{
			throw QMKFusionArrayGenericMultiDimException();
		}
		if (p_Array->m_ArrayDimension != p_Value.m_ArrayDimension + 1)
		{
			throw QMKFusionArrayGenericMultiDimException();
		}
	}

	QWDDX temp = p_Value;

	for(int c = p_Start - 1; c < p_End; c++)
	{
		p_Array->m_Array[c] = temp;
	}

	return true;
}

bool cf_ArraySort(QWDDX *p_Array, const QString &p_SortType, const QString &p_SortOrder)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

double cf_ArraySum(const QWDDX& p_Array)
{
	if (p_Array.m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	if (p_Array.m_ArrayDimension != 1)
	{
		throw new QMKFusionArrayNotOneDimensionException();
	}

	if (p_Array.m_Array.size() == 0)
	{
		return 0;
	}

	double sum = 0;
	QWDDX temp = p_Array;

	for (int c = 0; c < temp.m_Array.size(); c++)
	{
		sum += temp.m_Array[c].toNumber();
	}

	return sum;
}

bool cf_ArraySwap(QWDDX *p_Array, int p_Pos1, int p_Pos2)
{
	if (p_Array->m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	p_Pos1--;
	p_Pos2--;

	if((p_Pos1 < 0)||(p_Pos1 >= p_Array->m_Array.size()))
	{
		throw QMKFusionArraySwapRangeException(p_Pos1 + 1, p_Array->m_Array.size());
	}
	if((p_Pos2 < 0)||(p_Pos2 >= p_Array->m_Array.size()))
	{
		throw QMKFusionArraySwapRangeException(p_Pos2 + 1, p_Array->m_Array.size());
	}

	QWDDX temp = p_Array->m_Array[p_Pos1];
	p_Array->m_Array[p_Pos1] = p_Array->m_Array[p_Pos2];
	p_Array->m_Array[p_Pos2] = temp;

	return true;
}

QString cf_ArrayToList(const QWDDX& p_Array, const QString& p_Delimiter)
{
	QString ret;

	if (p_Array.m_Type != QWDDX::Array)
	{
		throw QMKFusionException("Not Array", "Not Array");
	}

	if (p_Array.m_ArrayDimension != 1)
	{
		throw new QMKFusionArrayNotOneDimensionException();
	}

	for(int c = 0; c < p_Array.m_Array.size(); c++)
	{
		if (c > 0)
		{
			ret += p_Delimiter;
		}

		QWDDX temp = p_Array.m_Array[c];

		ret += temp.toString();
	}

	return ret;
}

int cf_Asc(const QString& p_String)
{
	if (p_String.isEmpty())
	{
		return 0;
	}

	return p_String[0].unicode();
}

double cf_ASin(double val)
{
	return asin(val);
}

double cf_Atn(double val)
{
	return atan(val);
}

QString cf_BinaryDecode(const QString& p_String, const QString& p_Type)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QString cf_BinaryEncode(const QString& p_String, const QString& p_Type)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

int cf_BitAnd(int p_num1, int p_num2)
{
	return p_num1 & p_num2;
}

int cf_BitMaskClear(int p_num, int p_start, int p_end)
{
	if((p_start < 0)||(p_start > 31))
	{
		throw QMKFusionInvalidArgumentException("BitMaskClear", 2, p_start, 0, 31);
	}

	if((p_end < 0)||(p_end > 31))
	{
		throw QMKFusionInvalidArgumentException("BitMaskClear", 3, p_end, 0, 31);
	}

	return p_num & ~(((1 << p_end) - 1) << p_start);
}

int cf_BitMaskRead(int p_num, int p_start, int p_end)
{

	if((p_start < 0)||(p_start > 31))
	{
		throw QMKFusionInvalidArgumentException("BitMaskRead", 2, p_start, 0, 31);
	}

	if((p_end < 0)||(p_end > 31))
	{
		throw QMKFusionInvalidArgumentException("BitMaskRead", 3, p_end, 0, 31);
	}

	return (p_num >> p_start) & ((1 << p_end) - 1);
}

int cf_BitMaskSet(int p_num, int p_mask, int p_start, int p_end)
{
	if((p_start < 0)||(p_start > 31))
	{
		throw QMKFusionInvalidArgumentException("BitMaskSet", 2, p_start, 0, 31);
	}

	if((p_end < 0)||(p_end > 31))
	{
		throw QMKFusionInvalidArgumentException("BitMaskSet", 3, p_end, 0, 31);
	}

	p_mask &= (1 << p_end) - 1;
	return p_num & ~((((1 << p_end) - 1) << p_start) | p_mask) << p_start;
}

int cf_BitNot(int p_number)
{
	return ~p_number;
}

int cf_BitOr(int p_number1, int p_number2)
{
	return p_number1 | p_number2;
}

int cf_BitSHLN(int p_number, int p_count)
{
	if ((p_count < 0)||(p_count > 31))
	{
		throw new QMKFusionInvalidArgumentException("BitSHLN", 2, p_count, 0, 31);
	}

	return p_number << p_count;
}

int cf_BitSHRN(int p_number, int p_count)
{
	if ((p_count < 0)||(p_count > 31))
	{
		throw new QMKFusionInvalidArgumentException("BitSHRN", 2, p_count, 0, 31);
	}

	return p_number >> p_count;
}

int cf_BitXor(int p_number1, int p_number2)
{
	return p_number1 ^ p_number2;
}

QWDDX cf_CacheGet(const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QWDDX cf_CacheGetAllIds()
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QWDDX cf_CacheGetMetadata(const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QWDDX cf_CacheGetProperties(const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

void cf_CachePut(const QString&, const QWDDX&, int, int)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

void cf_CacheRemove(const QString&, bool)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

void cf_CacheSetProperties(const QWDDX&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

double cf_Ceiling(double p_number)
{
	return ceil(p_number);
}

QString cf_CharsetDecode(const QString&, const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QString cf_CharsetEncode(const QString&, const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QString cf_Chr(int p_number)
{
	return QChar(p_number);
}

QString cf_CJustify(const QString& p_Value, int p_lenght)
{
	QString ret;

	if (p_lenght < 0)
	{
		throw QMKFusionInvalidArgumentException("CJustify", 2, p_lenght, "positive integer");
	}

	if (p_lenght <= p_Value.length())
	{
		return p_Value;
	}

	ret = p_Value;

	int start = (p_lenght - p_Value.length()) / 2;

	for(int c = 0; c < start; c++)
	{
		ret = ' ' + ret;
	}

	return ret;
}

int cf_Compare(const QString& p_Value1, const QString& p_Value2)
{
	QWDDX l_Value1 = p_Value1;
	QWDDX l_Value2 = p_Value2;

	return l_Value1.toString().compare(l_Value2.toString(), Qt::CaseSensitive);
}

int cf_CompareNoCase(const QString& p_Value1, const QString& p_Value2)
{
	QWDDX l_Value1 = p_Value1;
	QWDDX l_Value2 = p_Value2;

	return l_Value1.toString().compare(l_Value2.toString(), Qt::CaseInsensitive);
}

double cf_Cos(double val)
{
	return cos(val);
}

QWDDX cf_CreateDate(int p_Year, int p_Month, int p_Day)
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

QWDDX cf_CreateDateTime(int p_Year, int p_Month, int p_Day, int p_Hour, int p_Minute, int p_Second)
{
	return QDateTime(QDate(p_Year, p_Month, p_Day), QTime(p_Hour, p_Minute, p_Second));
}

QWDDX cf_CreateDotNETObject(const QString&, const QString&, const QString&, int, const QString&, bool)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QWDDX cf_CreateCOMObject(const QString&, const QString&, const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QWDDX cf_CreateComponentObject(const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QWDDX cf_CreateCobraObject(const QString&, const QString&, const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QWDDX cf_CreateJavaObject(const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QWDDX cf_CreateWebServiceObject(const QString&, const QString&, const QString&, const QWDDX&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QWDDX cf_CreateODBCDate(const QDateTime& p_Date)
{
	return QDateTime(QDate(p_Date.date().year(), p_Date.date().month(), p_Date.date().day()));
}

QWDDX cf_CreateODBCDateTime(const QDateTime& p_Date)
{
	return p_Date;
}

QWDDX cf_CreateODBCTime(const QDateTime& p_Date)
{
	return QDateTime(QDate(1899, 12, 30), QTime(p_Date.time().hour(), p_Date.time().minute(), p_Date.time().second()));
}

QWDDX cf_CreateTime(int p_Hour, int p_Minute, int p_Second)
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

QWDDX cf_CreateTimeSpan(int p_Days, int p_Hours, int p_Minutes, int p_Seconds)
{
	QDateTime ret = QDateTime(QDate(1899, 12, 30));

	ret.addDays(p_Days);
	ret.addSecs((p_Hours * 60 * 60) + (p_Minutes * 60) + p_Seconds);

	return ret;
}

QString cf_CreateUUID()
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QDateTime cf_DateAdd(const QString& p_DatePart, int p_Value, const QWDDX& p_Date)
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

int cf_DateCompare(const QWDDX& p_Date1, const QWDDX& p_Date2, const QString& p_DatePart)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

int cf_DateDiff(const QString&, const QDateTime&, const QDateTime&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QString cf_DateFormat(const QDateTime&, const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

int cf_DatePart(const QString&, const QDateTime&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

int cf_Day(const QDateTime&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

int cf_DayOfWeek(const QDateTime&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QString cf_DayOfWeekAsString(int, const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

int cf_DayOfYear(const QDateTime&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

int cf_DaysInMonth(const QDateTime&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

int cf_DaysInYear(const QDateTime&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QString cf_DE(const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QString cf_DecimalFormat(double)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

double cf_DecrementValue(double)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QString cf_Decrypt(const QString&, const QString&, const QString&, const QString&, const QString&, int)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QString cf_DecryptBinary(const QString&, const QString&, const QString&, const QString&, const QString&, int)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

bool cf_DeleteClientVariable(const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QString cf_DeserializeJSON(const QString&, bool)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

void cf_DirectoryCreate(const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

void cf_DirectoryDelete(const QString&, bool)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

bool cf_DirectoryExists(const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QWDDX cf_DirectoryList(const QString&, bool, const QString&, const QString&, const QString&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

void cf_DirectoryRename(const QString&, const QString&)

{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QString cf_DollarFormat(double)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QWDDX cf_DotNetToCFType(const QWDDX&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}

QWDDX cf_Duplicate(const QWDDX&)
{
	throw QMKFusionException("Not Implemented", "Not Implemented (yet:))");
}
// Page3




QString WriteException(QMKFusionException &ex, const QCFRunningTemplate_Request& r)
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
