#ifndef CFFUNCTIONS_H
#define CFFUNCTIONS_H

#include "qmkfusionexception.h"
#include "qcfrunningtemplate.h"
#include "common.h"

#include <QString>


Q_DECL_EXPORT double cf_Abs(double);
Q_DECL_EXPORT int cf_Abs(int);
Q_DECL_EXPORT QWDDX cf_Abs(const QWDDX&);
Q_DECL_EXPORT double cf_ACos(double);
Q_DECL_EXPORT QWDDX cf_ACos(const QWDDX&);
Q_DECL_EXPORT void cf_AddSOAPRequestHeader(QWDDX&, const QString&, const QString&, const QWDDX&, bool);
Q_DECL_EXPORT void cf_AddSOAPResponseHeader(const QString&, const QString&, const QWDDX&, bool);
Q_DECL_EXPORT QString cf_AjaxLink(const QString&);
Q_DECL_EXPORT void cf_AjaxOnLoad(const QString&);
//Q_DECL_EXPORT void cf_ApplicationStop(); // ColdFusion 9
Q_DECL_EXPORT bool cf_ArrayAppend(QWDDX&, const QWDDX&);
Q_DECL_EXPORT double cf_ArrayAvg(const QWDDX&);
Q_DECL_EXPORT bool cf_ArrayClear(QWDDX&);
//Q_DECL_EXPORT bool cf_ArrayContains(const QWDDX&, const QWDDX&); // ColdFusion 9
//Q_DECL_EXPORT bool cf_ArrayDelete(QWDDX&, const QWDDX&); // ColdFusion 9
Q_DECL_EXPORT bool cf_ArrayDeleteAt(QWDDX&, int);
//Q_DECL_EXPORT int cf_ArrayFind(const QWDDX&, const QWDDX&); // ColdFusion 9
//Q_DECL_EXPORT int cf_ArrayFindNoCase(const QWDDX&, const QWDDX&); // ColdFusion 9
Q_DECL_EXPORT bool cf_ArrayInsertAt(QWDDX&, int, const QWDDX&);
Q_DECL_EXPORT bool cf_ArrayIsEmpty(const QWDDX&);
Q_DECL_EXPORT int cf_ArrayLen(const QWDDX&);
Q_DECL_EXPORT double cf_ArrayMin(const QWDDX&);
Q_DECL_EXPORT double cf_ArrayMax(const QWDDX&);
Q_DECL_EXPORT QWDDX cf_ArrayNew(int);
Q_DECL_EXPORT bool cf_ArrayPrepend(QWDDX&, const QWDDX&);
Q_DECL_EXPORT bool cf_ArrayResize(QWDDX&, int);
Q_DECL_EXPORT bool cf_ArraySet(QWDDX&, int, int, const QWDDX&);
Q_DECL_EXPORT bool cf_ArraySort(QWDDX&, const QString&, const QString&);
Q_DECL_EXPORT double cf_ArraySum(const QWDDX&);
Q_DECL_EXPORT bool cf_ArraySwap(QWDDX&, int, int);
Q_DECL_EXPORT QString cf_ArrayToList(const QWDDX&, const QString&);
Q_DECL_EXPORT int cf_Asc(const QString&);
Q_DECL_EXPORT double cf_ASin(double);
Q_DECL_EXPORT double cf_Atn(double);
// AuthenticatedContext
// AuthenticatedUser
Q_DECL_EXPORT QString cf_BinaryDecode(const QString&, const QString&);
Q_DECL_EXPORT QString cf_BinaryEncode(const QString&, const QString&);
Q_DECL_EXPORT int cf_BitAnd(int, int);
Q_DECL_EXPORT int cf_BitMaskClear(int, int, int);
Q_DECL_EXPORT int cf_BitMaskRead(int, int, int);
Q_DECL_EXPORT int cf_BitMaskSet(int, int, int, int);
Q_DECL_EXPORT int cf_BitNot(int);
Q_DECL_EXPORT int cf_BitOr(int, int);
Q_DECL_EXPORT int cf_BitSHLN(int, int);
Q_DECL_EXPORT int cf_BitSHRN(int, int);
Q_DECL_EXPORT int cf_BitXor(int, int);
Q_DECL_EXPORT QWDDX cf_CacheGet(const QString&);
Q_DECL_EXPORT QWDDX cf_CacheGetAllIds();
Q_DECL_EXPORT QWDDX cf_CacheGetMetadata(const QString&);
Q_DECL_EXPORT QWDDX cf_CacheGetProperties(const QString&);
Q_DECL_EXPORT void cf_CachePut(const QString&, const QWDDX&, int, int);
Q_DECL_EXPORT void cf_CacheRemove(const QString&, bool);
Q_DECL_EXPORT void cf_CacheSetProperties(const QWDDX&);
Q_DECL_EXPORT double cf_Ceiling(double);
Q_DECL_EXPORT QString cf_CharsetDecode(const QString&, const QString&);
Q_DECL_EXPORT QString cf_CharsetEncode(const QString&, const QString&);
Q_DECL_EXPORT QString cf_Chr(int);
Q_DECL_EXPORT QString cf_CJustify(const QString&, int);
Q_DECL_EXPORT int cf_Compare(const QString&, const QString&);
Q_DECL_EXPORT int cf_CompareNoCase(const QString&, const QString&);
Q_DECL_EXPORT double cf_Cos(double);
Q_DECL_EXPORT QWDDX cf_CreateDate(int, int, int);
Q_DECL_EXPORT QWDDX cf_CreateDateTime(int, int, int, int, int, int);
Q_DECL_EXPORT QWDDX cf_CreateDotNETObject(const QString&, const QString&, const QString&, int, const QString&, bool);
Q_DECL_EXPORT QWDDX cf_CreateCOMObject(const QString&, const QString&, const QString&);
Q_DECL_EXPORT QWDDX cf_CreateComponentObject(const QString&);
Q_DECL_EXPORT QWDDX cf_CreateCobraObject(const QString&, const QString&, const QString&);
Q_DECL_EXPORT QWDDX cf_CreateJavaObject(const QString&);
Q_DECL_EXPORT QWDDX cf_CreateWebServiceObject(const QString&, const QString&, const QString&, const QWDDX&);
Q_DECL_EXPORT QWDDX cf_CreateODBCDate(const QDateTime&);
Q_DECL_EXPORT QWDDX cf_CreateODBCDateTime(const QDateTime&);
Q_DECL_EXPORT QWDDX cf_CreateTime(int, int, int);
Q_DECL_EXPORT QWDDX cf_CreateTimeSpan(int, int, int, int);
Q_DECL_EXPORT QString cf_CreateUUID();
Q_DECL_EXPORT QWDDX cf_DateAdd(const QString&, int, const QDateTime&);
Q_DECL_EXPORT int cf_DateCompare(const QWDDX&, const QWDDX&, const QString& = "s");
Q_DECL_EXPORT int cf_DateDiff(const QString&, const QDateTime&, const QDateTime&);
Q_DECL_EXPORT QString cf_DateFormat(const QDateTime&, const QString&);
Q_DECL_EXPORT int cf_DatePart(const QString&, const QDateTime&);
Q_DECL_EXPORT int cf_Day(const QDateTime&);
Q_DECL_EXPORT int cf_DayOfWeek(const QDateTime&);
Q_DECL_EXPORT QString cf_DayOfWeekAsString(int, const QString& = "");
Q_DECL_EXPORT int cf_DayOfYear(const QDateTime&);
Q_DECL_EXPORT int cf_DaysInMonth(const QDateTime&);
Q_DECL_EXPORT int cf_DaysInYear(const QDateTime&);
Q_DECL_EXPORT QString cf_DE(const QString&);
Q_DECL_EXPORT QString cf_DecimalFormat(double);
Q_DECL_EXPORT double cf_DecrementValue(double);
Q_DECL_EXPORT QString cf_Decrypt(const QString&, const QString&, const QString& = "CFMX_COMPAT", const QString& = "UU", const QString& = "", int = 1);
Q_DECL_EXPORT QString cf_DecryptBinary(const QString&, const QString&, const QString& = "CFMX_COMPAT", const QString& = "UU", const QString& = "", int = 1);
Q_DECL_EXPORT bool cf_DeleteClientVariable(const QString&);
Q_DECL_EXPORT QString cf_DeserializeJSON(const QString&, bool = true);
Q_DECL_EXPORT void cf_DirectoryCreate(const QString&);
Q_DECL_EXPORT void cf_DirectoryDelete(const QString&, bool = false);
Q_DECL_EXPORT bool cf_DirectoryExists(const QString&);
Q_DECL_EXPORT QWDDX cf_DirectoryList(const QString&, bool, const QString&, const QString&, const QString&);
Q_DECL_EXPORT void cf_DirectoryRename(const QString&, const QString&);
Q_DECL_EXPORT QString cf_DollarFormat(double);
Q_DECL_EXPORT QWDDX cf_DotNetToCFType(const QWDDX&);
Q_DECL_EXPORT QWDDX cf_Duplicate(const QWDDX&);

//Encrypt
//EncryptBinary
//EntityDelete
//EntityLoad
//EntityLoadByExample
//EntityLoadByPK
//EntityMerge
//EntityNew
//EntityReload
//EntitySave
//EntitytoQuery
//Evaluate
Q_DECL_EXPORT double cf_Exp(double);
Q_DECL_EXPORT int cf_Exp(int);
//ExpandPath
//FileClose
//FileCopy
//FileDelete
//FileExists
//FileIsEOF
//FileMove
//FileOpen
//FileRead
//FileReadBinary
//FileReadLine
//FileSeek
//FileSetAccessMode
//FileSetAttribute
//FileSetLastModified
//FileSkipBytes
//FileWrite
//FileWriteLine
Q_DECL_EXPORT int cf_Find(const QString&, const QString&, int = 1);
Q_DECL_EXPORT int cf_FindNoCase(const QString&, const QString&, int = 1);
Q_DECL_EXPORT int cf_FindOneOf(const QString&, const QString&, int = 1);
Q_DECL_EXPORT int cf_FirstDayOfMonth(const QDateTime&);
Q_DECL_EXPORT int cf_Fix(double);
Q_DECL_EXPORT int cf_FormatBaseN(int, int);
/*GenerateSecretKey
GetAuthUser
GetBaseTagData
GetBaseTagList
GetBaseTemplatePath
GetClientVariablesList
GetComponentMetaData
GetContextRoot
GetCurrentTemplatePath
GetDirectoryFromPath
GetEncoding
GetException
GetFileFromPath
GetFileInfo
GetFunctionCalledName
GetFunctionList
GetGatewayHelper
GetHttpRequestData
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
GetPrinterList
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
GetVFSMetaData
GetWriteableImageFormats
Hash
HQL Methods
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
ImageGetEXIFMetadata
ImageGetEXIFTag
ImageGetHeight
ImageGetIPTCMetadata
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
/*IsAuthenticated
IsAuthorized
IsBinary
IsBoolean
IsCustomFunction
IsDate
IsDDX
IsDebugMode
IsDefined
IsImage
IsImageFile
IsInstanceOf
IsIPv6
IsJSON
IsK2ServerABroker
IsK2ServerDocCountExceeded
IsK2ServerOnline
IsLeapYear
IsLocalHost
IsNull
IsNumeric
IsNumericDate
IsObject
IsPDFFile
IsPDFObject
IsProtected
IsQuery
IsSimpleValue
IsSOAPRequest
IsSpreadsheetFile
IsSpreadsheetObject*/
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
JSStringFormat
*/
Q_DECL_EXPORT QString cf_LCase(const QString&);
Q_DECL_EXPORT QString cf_Left(const QString&, int);
Q_DECL_EXPORT int cf_Len(const QString&);
/*
ListAppend
ListChangeDelims
ListContains
ListContainsNoCase
ListDeleteAt
ListFind
ListFindNoCase
ListFirst
ListGetAt
ListInsertAt
ListLast
ListLen
ListPrepend
ListQualify
ListRest
ListSetAt
ListSort*/
Q_DECL_EXPORT QWDDX cf_ListToArray(const QString &list, const QString &delimiters = ",", bool includeEmptyFields = false);
/*ListValueCount
ListValueCountNoCase
LJustify
Location
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
ObjectEquals
ObjectLoad
ObjectSave
ORMClearSession
ORMCloseSession
ORMEvictCollection
ORMEvictEntity
ORMEvictQueries
ORMExecuteQuery
ORMFlush
ORMGetSession
ORMGetSessionFactory
ORMReload
ParagraphFormat
ParameterExists
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
REMatch
REMatchNoCase
ReleaseComObject
RemoveChars
RepeatString
Replace
ReplaceList
ReplaceNoCase
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
SpreadsheetAddColumn
SpreadsheetAddImage
SpreadsheetAddFreezePane
SpreadsheetAddInfo
SpreadsheetAddRow
SpreadsheetAddRows
SpreadsheetAddSplitPane
SpreadsheetCreateSheet
SpreadsheetDeleteColumn
SpreadsheetDeleteColumns
SpreadsheetDeleteRow
SpreadsheetDeleteRows
SpreadsheetFormatCell
SpreadsheetFormatColumn
SpreadsheetFormatColumns
SpreadsheetFormatRow
SpreadsheetFormatRows
SpreadsheetGetCellComment
SpreadsheetGetCellFormula
SpreadsheetGetCellValue
SpreadsheetInfo
SpreadsheetMergeCells
SpreadsheetNew
SpreadsheetRead
SpreadsheetReadBinary
SpreadsheetSetActiveSheet
SpreadsheetSetActiveSheetNumber
SpreadsheetSetCellComment
SpreadsheetSetCellFormula
SpreadsheetSetCellValue
SpreadsheetSetColumnWidth
SpreadsheetSetFooter
SpreadsheetSetHeader
SpreadsheetSetRowHeight
SpreadsheetShiftColumns
SpreadsheetShiftRows
SpreadsheetWrite
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
ThreadJoin
ThreadTerminate
Throw
TimeFormat
ToBase64
ToBinary
ToScript
ToString
Trace
Trim
UCase
URLDecode
URLEncodedFormat
URLSessionFormat
Val
ValueList
VerifyClient
Week
Wrap
Writedump
Writelog
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
YesNoFormat
*/

QString WriteException(const QMKFusionException &, const QCFRunningTemplate_Request &);

#endif // CFFUNCTIONS_H
