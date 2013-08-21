#ifndef CFFUNCTIONS_H
#define CFFUNCTIONS_H

#include "qmkfusionexception.h"
#include "qcfrunningtemplate.h"
#include "common.h"
#include "qwddx.h"

#include <QStringList>
#include <QDateTime>
#include <QString>


Q_DECL_EXPORT double cf_Abs(double number);
Q_DECL_EXPORT double cf_ACos(double number);
Q_DECL_EXPORT void cf_AddSOAPRequestHeader(QWDDX &webservice, const QString &_namespace, const QString &name, const QWDDX &value, bool mustunderstand);
Q_DECL_EXPORT void cf_AddSOAPResponseHeader(const QString &_namespace, const QString &name, const QWDDX &value, bool mustunderstand);
Q_DECL_EXPORT QString cf_AjaxLink(const QString &URL);
Q_DECL_EXPORT void cf_AjaxOnLoad(const QString &functionName);
Q_DECL_EXPORT bool cf_ArrayAppend(QWDDX &array, const QWDDX &value);
Q_DECL_EXPORT double cf_ArrayAvg(const QWDDX &array);
Q_DECL_EXPORT bool cf_ArrayClear(QWDDX &array);
Q_DECL_EXPORT bool cf_ArrayDeleteAt(QWDDX &array, int position);
Q_DECL_EXPORT bool cf_ArrayInsertAt(QWDDX &array, int position, const QWDDX &value);
Q_DECL_EXPORT bool cf_ArrayIsDefined(const QWDDX &array, int elementIndex);
Q_DECL_EXPORT bool cf_ArrayIsEmpty(const QWDDX &array);
Q_DECL_EXPORT int cf_ArrayLen(const QWDDX &array);
Q_DECL_EXPORT double cf_ArrayMax(const QWDDX &array);
Q_DECL_EXPORT double cf_ArrayMin(const QWDDX &array);
Q_DECL_EXPORT QWDDX cf_ArrayNew(int dimension);
Q_DECL_EXPORT bool cf_ArrayPrepend(QWDDX &array, const QWDDX &value);
Q_DECL_EXPORT bool cf_ArrayResize(QWDDX &array, int minSize);
Q_DECL_EXPORT bool cf_ArraySet(QWDDX &array, int start, int end, const QWDDX &value);
Q_DECL_EXPORT bool cf_ArraySort(QWDDX &array, const QString &sort_type, const QString &sort_order);
Q_DECL_EXPORT double cf_ArraySum(const QWDDX&);
Q_DECL_EXPORT bool cf_ArraySwap(QWDDX&, int, int);
Q_DECL_EXPORT QString cf_ArrayToList(const QWDDX&, const QString&);
Q_DECL_EXPORT int cf_Asc(const QString &array);
Q_DECL_EXPORT double cf_ASin(double number);
Q_DECL_EXPORT double cf_Atn(double number);
Q_DECL_EXPORT QString cf_BinaryDecode(const QString &string, const QString &binaryencoding);
Q_DECL_EXPORT QString cf_BinaryEncode(const QString &binarydata, const QString &encoding);
Q_DECL_EXPORT int cf_BitAnd(int number1, int number2);
Q_DECL_EXPORT int cf_BitMaskClear(int number, int start, int length);
Q_DECL_EXPORT int cf_BitMaskRead(int number, int start, int length);
Q_DECL_EXPORT int cf_BitMaskSet(int number, int mask, int start, int length);
Q_DECL_EXPORT int cf_BitNot(int number);
Q_DECL_EXPORT int cf_BitOr(int number1, int number2);
Q_DECL_EXPORT int cf_BitSHLN(int number, int count);
Q_DECL_EXPORT int cf_BitSHRN(int number, int count);
Q_DECL_EXPORT int cf_BitXor(int number1, int number2);
Q_DECL_EXPORT double cf_Ceiling(double number);
Q_DECL_EXPORT QString cf_CharsetDecode(const QString &string, const QString &encoding);
Q_DECL_EXPORT QString cf_CharsetEncode(const QString &binaryobject, const QString &encoding);
Q_DECL_EXPORT QString cf_Chr(int number);
Q_DECL_EXPORT QString cf_CJustify(const QString &string, int length);
Q_DECL_EXPORT int cf_Compare(const QString &string1, const QString &string2);
Q_DECL_EXPORT int cf_CompareNoCase(const QString &string1, const QString &string2);
Q_DECL_EXPORT double cf_Cos(double number);
Q_DECL_EXPORT QWDDX cf_CreateDate(int year, int month, int day);
Q_DECL_EXPORT QWDDX cf_CreateDateTime(int year, int month, int day, int hour, int minute, int second);
Q_DECL_EXPORT QWDDX cf_CreateObject(const QString &type); // TODO: Unfinished.
Q_DECL_EXPORT QWDDX cf_CreateODBCDate(const QDateTime &date);
Q_DECL_EXPORT QWDDX cf_CreateODBCDateTime(const QDateTime &date);
Q_DECL_EXPORT QWDDX cf_CreateODBCTime(const QDateTime &date);
Q_DECL_EXPORT QWDDX cf_CreateTime(int hour, int minute, int second);
Q_DECL_EXPORT QWDDX cf_CreateTimeSpan(int days, int hours, int minutes, int seconds);
Q_DECL_EXPORT QString cf_CreateUUID();
Q_DECL_EXPORT QWDDX cf_DateAdd(const QString &datepart, int number, const QDateTime &date);
Q_DECL_EXPORT int cf_DateCompare(const QDateTime &date1, const QDateTime &date2, const QString &datePart = "s");
Q_DECL_EXPORT QString cf_DateConvert(const QString &conversion_type, const QDateTime &date);
Q_DECL_EXPORT int cf_DateDiff(const QString &datepart, const QDateTime &date1, const QDateTime &date2);
Q_DECL_EXPORT QString cf_DateFormat(const QDateTime &date, const QString &mask);
Q_DECL_EXPORT int cf_DatePart(const QString &datepart, const QDateTime &date);
Q_DECL_EXPORT int cf_Day(const QDateTime &date);
Q_DECL_EXPORT int cf_DayOfWeek(const QDateTime &date);
Q_DECL_EXPORT QString cf_DayOfWeekAsString(int day_of_week, const QString &locale = "");
Q_DECL_EXPORT int cf_DayOfYear(const QDateTime &date);
Q_DECL_EXPORT int cf_DaysInMonth(const QDateTime &date);
Q_DECL_EXPORT int cf_DaysInYear(const QDateTime &date);
Q_DECL_EXPORT QString cf_DE(const QString &string);
Q_DECL_EXPORT QString cf_DecimalFormat(double number);
Q_DECL_EXPORT double cf_DecrementValue(double number);
Q_DECL_EXPORT QString cf_Decrypt(const QString &encrypted_string, const QString &key, const QString &algorithm = "CFMX_COMPAT", const QString &encoding = "UU", const QString &IVorSalt = "", int iterations = 1);
Q_DECL_EXPORT QString cf_DecryptBinary(const QString &bytes, const QString &key, const QString &algorithm = "CFMX_COMPAT", const QString &IVorSalt = "UU", const QString& = "", int iterations = 1);
Q_DECL_EXPORT bool cf_DeleteClientVariable(const QString &name);
Q_DECL_EXPORT QString cf_DeserializeJSON(const QString &JSONVar, bool strictMapping = true);
Q_DECL_EXPORT bool cf_DirectoryExists(const QString &absolute_path);
Q_DECL_EXPORT QString cf_DollarFormat(double number);
Q_DECL_EXPORT QWDDX cf_DotNetToCFType(const QWDDX &variable_name);
Q_DECL_EXPORT QWDDX cf_Duplicate(const QWDDX &variable_name);
Q_DECL_EXPORT QString cf_Encrypt(const QString &string, const QString &key, const QString &algorithm = "CFMX_COMPAT", const QString &encoding = "UU", const QString &IVorSalt = "", int iterations = 1);
Q_DECL_EXPORT QString cf_EncryptBinary(const QString &bytes, const QString &key, const QString &algorithm = "CFMX_COMPAT", const QString &IVorSalt = "UU", const QString& = "", int iterations = 1);
Q_DECL_EXPORT QWDDX cf_Evaluate(const QStringList &string_expressions);
Q_DECL_EXPORT double cf_Exp(double number);
Q_DECL_EXPORT QString cf_ExpandPath(const QString &relative_path);
Q_DECL_EXPORT void cf_FileClose(QWDDX &fileObj);
Q_DECL_EXPORT void cf_FileCopy(const QString &source, const QString &destination);
Q_DECL_EXPORT void cf_FileDelete(const QString &filepath);
Q_DECL_EXPORT bool cf_FileExists(const QString &absolute_path);
Q_DECL_EXPORT bool cf_FileIsEOF(QWDDX &fileObj);
Q_DECL_EXPORT void cf_FileMove(const QString &source, const QString &destination);
Q_DECL_EXPORT QWDDX cf_FileOpen(const QString &filepath, const QString mode = "read", const QString charset = "");
Q_DECL_EXPORT QString cf_FileRead(const QString &filepath, const QString charset = "");
Q_DECL_EXPORT QString cf_FileRead(QWDDX &fileObj, int buffersize = -1);
Q_DECL_EXPORT QWDDX cf_FileReadBinary(const QString &filepath);
Q_DECL_EXPORT QString cf_FileReadLine(QWDDX &fileObj);
Q_DECL_EXPORT void cf_FileSetAccessMode(const QString &filepath, const QString mode); // TODO: Make this available only under Linux
Q_DECL_EXPORT void cf_FileSetAttribute(const QString &filepath, const QString mode); // TODO: Make this available only under Windows
Q_DECL_EXPORT void cf_FileSetLastModified(const QString &filepath, const QDateTime &date);
Q_DECL_EXPORT void cf_FileWrite(const QString &filepath, const QString &data, const QString &charset = "");
Q_DECL_EXPORT void cf_FileWrite(QWDDX &fileObj, const QString &data);
Q_DECL_EXPORT int cf_Find(const QString &substring, const QString &string, int start = 1);
Q_DECL_EXPORT int cf_FindNoCase(const QString &substring, const QString &string, int start = 1);
Q_DECL_EXPORT int cf_FindOneOf(const QString &set, const QString &string, int start = 1);
Q_DECL_EXPORT int cf_FirstDayOfMonth(const QDateTime &date);
Q_DECL_EXPORT int cf_Fix(double);
Q_DECL_EXPORT QString cf_FormatBaseN(int number, int radix);
Q_DECL_EXPORT QString cf_GenerateSecretKey(const QString &algorithm, int keysize = -1);
Q_DECL_EXPORT QString cf_GetAuthUser();
Q_DECL_EXPORT QWDDX cf_GetBaseTagData(const QString &tagname, int instancenumber = 1);
Q_DECL_EXPORT QString cf_GetBaseTagList();
Q_DECL_EXPORT QString cf_GetBaseTemplatePath();
Q_DECL_EXPORT QString cf_GetClientVariablesList();
Q_DECL_EXPORT QWDDX cf_GetComponentMetaData(const QString &path);
Q_DECL_EXPORT QString cf_GetContextRoot();
Q_DECL_EXPORT QString cf_GetCurrentTemplatePath();
Q_DECL_EXPORT QString cf_GetDirectoryFromPath(const QString &path);
Q_DECL_EXPORT QString cf_GetEncoding(const QString &scope_name);
Q_DECL_EXPORT QWDDX cf_GetException(const QWDDX &object);
Q_DECL_EXPORT QString cf_GetFileFromPath(const QString &path);
Q_DECL_EXPORT QWDDX cf_GetFileInfo(const QString &path);
Q_DECL_EXPORT QString cf_GetFunctionList();
Q_DECL_EXPORT QWDDX cf_GetGatewayHelper(const QString &gatewayID);
/*GetHttpRequestData
GetHttpTimeString
GetK2ServerDocCount
GetK2ServerDocCountLimit
GetLocale
GetLocaleDisplayName
GetLocalHostIP
GetMetaData
GetMetricData
GetPageContext
GetPrinterInfo
GetProfileSections
GetProfileString
GetReadableImageFormats
GetSOAPRequest
GetSOAPRequestHeader
GetSOAPResponse
GetSOAPResponseHeader
GetTempDirectory
GetTempFile
GetTemplatePath
GetTickCount
GetTimeZoneInfo
GetToken
GetUserRoles
GetWriteableImageFormats
Hash
Hour
HTMLCodeFormat
HTMLEditFormat
IIf
ImageAddBorder
ImageBlur
ImageClearRect
ImageCopy
ImageCrop
ImageDrawArc
ImageDrawBeveledRect
ImageDrawCubicCurve
ImageDrawLine
ImageDrawLines
ImageDrawOval
ImageDrawPoint
ImageDrawQuadraticCurve
ImageDrawRect
ImageDrawRoundRect
ImageDrawText
ImageFlip
ImageGetBlob
ImageGetBufferedImage
ImageGetEXIFTag
ImageGetHeight
ImageGetIPTCTag
ImageGetWidth
ImageGrayscale
ImageInfo
ImageNegative
ImageNew
ImageOverlay
ImagePaste
ImageRead
ImageReadBase64
ImageResize
ImageRotate
ImageRotateDrawingAxis
ImageScaleToFit
ImageSetAntialiasing
ImageSetBackgroundColor
ImageSetDrawingColor
ImageSetDrawingStroke
ImageSetDrawingTransparency
ImageSharpen
ImageShear
ImageShearDrawingAxis
ImageTranslate
ImageTranslateDrawingAxis
ImageWrite
ImageWriteBase64
ImageXORDrawingMode
IncrementValue
InputBaseN
Insert
Int*/
Q_DECL_EXPORT bool cf_IsArray(const QWDDX &var, int level = 0);
/*IsBinary
IsBoolean
IsCustomFunction
IsDate
IsDDX
IsDebugMode
IsDefined
IsImage
IsImageFile
IsInstanceOf
IsJSON
IsLeapYear
IsLocalHost
IsNumeric
IsNumericDate
IsObject
IsPDFFile
IsPDFObject
IsQuery
IsSimpleValue
IsSOAPRequest*/
Q_DECL_EXPORT bool cf_IsStruct(const QWDDX &variable);
/*IsUserInAnyRole
IsUserInRole
IsUserLoggedIn
IsValid
IsWDDX
IsXML
IsXmlAttribute
IsXmlDoc
IsXmlElem
IsXmlNode
IsXmlRoot
JavaCast
JSStringFormat*/
Q_DECL_EXPORT QString cf_LCase(const QString &string);
Q_DECL_EXPORT QString cf_Left(const QString &string, int count);
Q_DECL_EXPORT int cf_Len(const QString &string);
Q_DECL_EXPORT QString cf_ListAppend(QString &list, const QString &value, const QString &delimiters = ",");
Q_DECL_EXPORT QString cf_ListChangeDelims(QString &list, const QString &new_delimiter, const QString &delimiters = ",");
Q_DECL_EXPORT int cf_ListContains(const QString &list, const QString &substring, const QString &delimiters = ",");
Q_DECL_EXPORT int cf_ListContainsNoCase(const QString &list, const QString &substring, const QString &delimiters = ",");
Q_DECL_EXPORT QString cf_ListDeleteAt(QString &list, int position, const QString &delimiters = ",");
Q_DECL_EXPORT int cf_ListFind(const QString &list, const QString &value, const QString &delimiters = ",");
Q_DECL_EXPORT int cf_ListFindNoCase(const QString &list, const QString &value, const QString &delimiters = ",");
Q_DECL_EXPORT QString cf_ListFirst(const QString &list, const QString &delimiters = ",");
Q_DECL_EXPORT QString cf_ListGetAt(const QString &list, int position, const QString &delimiters = ",");
Q_DECL_EXPORT QString cf_ListInsertAt(QString &list, int position, const QString value, const QString &delimiters = ",");
Q_DECL_EXPORT QString cf_ListLast(const QString &list, const QString &delimiters = ",");
Q_DECL_EXPORT int cf_ListLen(const QString &list, const QString &delimiters = ",");
Q_DECL_EXPORT QString cf_ListPrepend(QString &list, const QString &value, const QString &delimiters = ",");
Q_DECL_EXPORT QString cf_ListQualify(QString &list, const QString &quallifier, const QString &delimiters = ",", const QString elements = "all"); // TODO: Check if all is default. Missing from the docs.
Q_DECL_EXPORT QString cf_ListRest(const QString &list, const QString &delimiters = ",");
Q_DECL_EXPORT QString cf_ListSetAt(QString &list, int position, const QString value, const QString &delimiters = ",");
Q_DECL_EXPORT QString cf_ListSort(QString &list, const QString sort_type, const QString sort_order = "asc", const QString &delimiters = ",");
Q_DECL_EXPORT QWDDX cf_ListToArray(const QString &list, const QString &delimiters = ",", bool includeEmptyFields = false);
Q_DECL_EXPORT int cf_ListValueCount(const QString &list, const QString value, const QString &delimiters = ",");
Q_DECL_EXPORT int cf_ListValueCountNoCase(const QString &list, const QString value, const QString &delimiters = ",");
/*LJustify
Log
Log10
LSCurrencyFormat
LSDateFormat
LSEuroCurrencyFormat
LSIsCurrency
LSIsDate
LSIsNumeric
LSNumberFormat
LSParseCurrency
LSParseDateTime
LSParseEuroCurrency
LSParseNumber
LSTimeFormat
LTrim
Max
Mid
Min
Minute
Month
MonthAsString
Now
NumberFormat
ParagraphFormat
ParseDateTime
Pi
PrecisionEvaluate
PreserveSingleQuotes
Quarter
QueryAddColumn
QueryAddRow
QueryConvertForGrid
QueryNew
QuerySetCell
QuotedValueList
Rand
Randomize
RandRange
REFind
REFindNoCase
ReleaseComObject
REMatch
REMatchNoCase
RemoveChars
RepeatString
Replace*/
Q_DECL_EXPORT QString cf_ReplaceList(QString &list, const QString &list1, const QString &list2);
/*ReplaceNoCase
REReplace
REReplaceNoCase
Reverse
Right
RJustify
Round
RTrim
Second
SendGatewayMessage
SerializeJSON
SetEncoding
SetLocale
SetProfileString
SetVariable
Sgn
Sin
Sleep
SpanExcluding
SpanIncluding
Sqr
StripCR*/
Q_DECL_EXPORT bool cf_StructAppend(QWDDX &struct1, const QWDDX &struct2, bool overwriteFlag = true);
Q_DECL_EXPORT bool cf_StructClear(QWDDX &structure);
Q_DECL_EXPORT QWDDX cf_StructCopy(QWDDX &structure);
Q_DECL_EXPORT int cf_StructCount(const QWDDX &structure);
Q_DECL_EXPORT bool cf_StructDelete(QWDDX &structure, const QString &key, bool indicatenotexisting = false);
Q_DECL_EXPORT QWDDX cf_StructFind(const QWDDX &structure, const QString &key);
Q_DECL_EXPORT QWDDX cf_StructFindKey(const QWDDX &top, const QString &value, const QString &scope = "one");
Q_DECL_EXPORT QWDDX cf_StructFindValue(const QWDDX &top, const QString &value, const QString &scope = "one");
Q_DECL_EXPORT QWDDX cf_StructGet(const QString &pathDesired);
Q_DECL_EXPORT bool cf_StructInsert(QWDDX &structure, const QString &key, const QWDDX &value, bool allowoverwrite = false);
Q_DECL_EXPORT bool cf_StructIsEmpty(const QWDDX &structure);
Q_DECL_EXPORT QWDDX cf_StructKeyArray(const QWDDX &structure);
Q_DECL_EXPORT bool cf_StructKeyExists(const QWDDX &structure, const QString &key);
Q_DECL_EXPORT QString cf_StructKeyList(const QWDDX &structure, const QString &delimiter = ",");
Q_DECL_EXPORT QWDDX cf_StructNew();
Q_DECL_EXPORT QWDDX cf_StructSort(const QWDDX &base, const QString &sortType = "text", const QString &sortOrder = "asc", const QString &pathToSubElement = "");
Q_DECL_EXPORT bool cf_StructUpdate(QWDDX &structure, const QString &key, const QWDDX &value);
/*Tan
TimeFormat
ToBase64
ToBinary
ToScript
ToString
Trim
UCase
URLDecode
URLEncodedFormat
URLSessionFormat
Val*/
Q_DECL_EXPORT QString cf_ValueList(const QWDDX &query_column, const QString delimiter = ",");
/*VerifyClient
Week
Wrap
WriteOutput
XmlChildPos
XmlElemNew
XmlFormat
XmlGetNodeType
XmlNew
XmlParse
XmlSearch
XmlTransform
XmlValidate
Year
YesNoFormat*/

QString WriteException(const QMKFusionException &, const QCFRunningTemplate_Request &);

#endif // CFFUNCTIONS_H
