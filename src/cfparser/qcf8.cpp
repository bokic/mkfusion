#include "qcf8.h"

QHash<QString, QCFTag> QCF8::generateCFTags()
{
	QHash<QString, QCFTag> ret;
	QList<QCFTagArgument> args;

	ret.insert(QStringLiteral("cfabort"), QCFTag(QStringLiteral("cfabort"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("showError")));
    ret[QStringLiteral("cfabort")].m_ArgumentVariants.append(args);

    ret.insert(QStringLiteral("cfadmin"), QCFTag(QStringLiteral("cfadmin"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments, QCFTag::WithoutExpressionInside, true)); // Railo cftag

	ret.insert(QStringLiteral("cfajaximport"), QCFTag(QStringLiteral("cfajaximport"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("cssSrc")));
    args.append(QCFTagArgument(QStringLiteral("params")));
    args.append(QCFTagArgument(QStringLiteral("scriptSrc")));
    args.append(QCFTagArgument(QStringLiteral("tags")));
    ret[QStringLiteral("cfajaximport")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfajaxproxy"), QCFTag(QStringLiteral("cfajaxproxy"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("bind"), true));
    args.append(QCFTagArgument(QStringLiteral("jsclassname")));
    args.append(QCFTagArgument(QStringLiteral("onError")));
    args.append(QCFTagArgument(QStringLiteral("onSuccess")));
    ret[QStringLiteral("cfajaxproxy")].m_ArgumentVariants.append(args);
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("cfc"), true));
    args.append(QCFTagArgument(QStringLiteral("jsclassname")));
    args.append(QCFTagArgument(QStringLiteral("onError")));
    args.append(QCFTagArgument(QStringLiteral("onSuccess")));
    ret[QStringLiteral("cfajaxproxy")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfapplet"), QCFTag(QStringLiteral("cfapplet"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("appletSource"), true));
    args.append(QCFTagArgument(QStringLiteral("name"), true));
    args.append(QCFTagArgument(QStringLiteral("align")));
    args.append(QCFTagArgument(QStringLiteral("height")));
    args.append(QCFTagArgument(QStringLiteral("hSpace")));
    args.append(QCFTagArgument(QStringLiteral("notSupported")));
    args.append(QCFTagArgument(QStringLiteral("param_n")));
    args.append(QCFTagArgument(QStringLiteral("vSpace")));
    args.append(QCFTagArgument(QStringLiteral("width")));
    ret[QStringLiteral("cfapplet")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfapplication"), QCFTag(QStringLiteral("cfapplication"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("datasource")));
    args.append(QCFTagArgument(QStringLiteral("name")));
    args.append(QCFTagArgument(QStringLiteral("applicationTimeout")));
    args.append(QCFTagArgument(QStringLiteral("clientManagement")));
    args.append(QCFTagArgument(QStringLiteral("clientStorage")));
    args.append(QCFTagArgument(QStringLiteral("googleMapKey")));
    args.append(QCFTagArgument(QStringLiteral("loginStorage")));
    args.append(QCFTagArgument(QStringLiteral("scriptProtect")));
    args.append(QCFTagArgument(QStringLiteral("secureJSON")));
    args.append(QCFTagArgument(QStringLiteral("serverSideFormValidation")));
    args.append(QCFTagArgument(QStringLiteral("secureJSONPrefix")));
    args.append(QCFTagArgument(QStringLiteral("sessionManagement")));
    args.append(QCFTagArgument(QStringLiteral("sessionTimeout")));
    args.append(QCFTagArgument(QStringLiteral("setClientCookies")));
    args.append(QCFTagArgument(QStringLiteral("setDomainCookies")));
    ret[QStringLiteral("cfapplication")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfargument"), QCFTag(QStringLiteral("cfargument"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true));
    args.append(QCFTagArgument(QStringLiteral("default")));
    args.append(QCFTagArgument(QStringLiteral("displayname")));
    args.append(QCFTagArgument(QStringLiteral("hint")));
    args.append(QCFTagArgument(QStringLiteral("required")));
    args.append(QCFTagArgument(QStringLiteral("type")));
    ret[QStringLiteral("cfargument")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfassociate"), QCFTag(QStringLiteral("cfassociate"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("baseTag"), true));
    args.append(QCFTagArgument(QStringLiteral("dataCollection")));
    ret[QStringLiteral("cfassociate")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfbreak"), QCFTag(QStringLiteral("cfbreak"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfcache"), QCFTag(QStringLiteral("cfcache"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("action")));
    args.append(QCFTagArgument(QStringLiteral("directory")));
    args.append(QCFTagArgument(QStringLiteral("expireURL")));
    args.append(QCFTagArgument(QStringLiteral("password")));
    args.append(QCFTagArgument(QStringLiteral("port")));
    args.append(QCFTagArgument(QStringLiteral("protocol")));
    args.append(QCFTagArgument(QStringLiteral("timespan")));
    args.append(QCFTagArgument(QStringLiteral("username")));
    ret[QStringLiteral("cfcache")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfcalendar"), QCFTag(QStringLiteral("cfcalendar"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true));
    args.append(QCFTagArgument(QStringLiteral("dayNames")));
    args.append(QCFTagArgument(QStringLiteral("disabled")));
    args.append(QCFTagArgument(QStringLiteral("enabled")));
    args.append(QCFTagArgument(QStringLiteral("endRange")));
    args.append(QCFTagArgument(QStringLiteral("firstDayOfWeek")));
    args.append(QCFTagArgument(QStringLiteral("height")));
    args.append(QCFTagArgument(QStringLiteral("mask")));
    args.append(QCFTagArgument(QStringLiteral("monthNames")));
    args.append(QCFTagArgument(QStringLiteral("onBlur")));
    args.append(QCFTagArgument(QStringLiteral("onChange")));
    args.append(QCFTagArgument(QStringLiteral("onFocus")));
    args.append(QCFTagArgument(QStringLiteral("selectedDate")));
    args.append(QCFTagArgument(QStringLiteral("startRange")));
    args.append(QCFTagArgument(QStringLiteral("style")));
    args.append(QCFTagArgument(QStringLiteral("tooltip")));
    args.append(QCFTagArgument(QStringLiteral("visible")));
    args.append(QCFTagArgument(QStringLiteral("width")));
    ret[QStringLiteral("cfcalendar")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfcase"), QCFTag(QStringLiteral("cfcase"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("value"), true));
    args.append(QCFTagArgument(QStringLiteral("delimiters")));
    ret[QStringLiteral("cfcase")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfcatch"), QCFTag(QStringLiteral("cfcatch"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("type")));
    ret[QStringLiteral("cfcatch")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfchart"), QCFTag(QStringLiteral("cfchart"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("backgroundColor")));
    args.append(QCFTagArgument(QStringLiteral("chartHeight")));
    args.append(QCFTagArgument(QStringLiteral("chartWidth")));
    args.append(QCFTagArgument(QStringLiteral("dataBackgroundColor")));
    args.append(QCFTagArgument(QStringLiteral("font")));
    args.append(QCFTagArgument(QStringLiteral("fontBold")));
    args.append(QCFTagArgument(QStringLiteral("fontItalic")));
    args.append(QCFTagArgument(QStringLiteral("fontSize")));
    args.append(QCFTagArgument(QStringLiteral("foregroundColor")));
    args.append(QCFTagArgument(QStringLiteral("format")));
    args.append(QCFTagArgument(QStringLiteral("gridlines")));
    args.append(QCFTagArgument(QStringLiteral("labelFormat")));
    args.append(QCFTagArgument(QStringLiteral("markerSize")));
    args.append(QCFTagArgument(QStringLiteral("name")));
    args.append(QCFTagArgument(QStringLiteral("pieSliceStyle")));
    args.append(QCFTagArgument(QStringLiteral("scaleFrom")));
    args.append(QCFTagArgument(QStringLiteral("scaleTo")));
    args.append(QCFTagArgument(QStringLiteral("seriesPlacement")));
    args.append(QCFTagArgument(QStringLiteral("show3D")));
    args.append(QCFTagArgument(QStringLiteral("showBorder")));
    args.append(QCFTagArgument(QStringLiteral("showLegend")));
    args.append(QCFTagArgument(QStringLiteral("showMarkers")));
    args.append(QCFTagArgument(QStringLiteral("showXGridlines")));
    args.append(QCFTagArgument(QStringLiteral("showYGridlines")));
    args.append(QCFTagArgument(QStringLiteral("sortXAxis")));
    args.append(QCFTagArgument(QStringLiteral("style")));
    args.append(QCFTagArgument(QStringLiteral("title")));
    args.append(QCFTagArgument(QStringLiteral("tipbgcolor")));
    args.append(QCFTagArgument(QStringLiteral("tipStyle")));
    args.append(QCFTagArgument(QStringLiteral("url")));
    args.append(QCFTagArgument(QStringLiteral("xAxisTitle")));
    args.append(QCFTagArgument(QStringLiteral("xAxisType")));
    args.append(QCFTagArgument(QStringLiteral("xOffset")));
    args.append(QCFTagArgument(QStringLiteral("yAxisTitle")));
    args.append(QCFTagArgument(QStringLiteral("yAxisType")));
    args.append(QCFTagArgument(QStringLiteral("yOffset")));
    ret[QStringLiteral("cfchart")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfchartdata"), QCFTag(QStringLiteral("cfchartdata"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("item"), true));
    args.append(QCFTagArgument(QStringLiteral("value"), true));
    ret[QStringLiteral("cfchartdata")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfchartseries"), QCFTag(QStringLiteral("cfchartseries"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("type"), true));
    args.append(QCFTagArgument(QStringLiteral("itemColumn")));
    args.append(QCFTagArgument(QStringLiteral("valueColumn")));
    args.append(QCFTagArgument(QStringLiteral("colorlist")));
    args.append(QCFTagArgument(QStringLiteral("dataLabelStyle")));
    args.append(QCFTagArgument(QStringLiteral("markerStyle")));
    args.append(QCFTagArgument(QStringLiteral("paintStyle")));
    args.append(QCFTagArgument(QStringLiteral("query")));
    args.append(QCFTagArgument(QStringLiteral("seriesColor")));
    args.append(QCFTagArgument(QStringLiteral("seriesLabel")));
    ret[QStringLiteral("cfchartseries")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfcol"), QCFTag(QStringLiteral("cfcol"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfcollection"), QCFTag(QStringLiteral("cfcollection"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("action"), true));
    args.append(QCFTagArgument(QStringLiteral("categories")));
    args.append(QCFTagArgument(QStringLiteral("collection")));
    args.append(QCFTagArgument(QStringLiteral("language")));
    args.append(QCFTagArgument(QStringLiteral("name")));
    args.append(QCFTagArgument(QStringLiteral("path")));
    ret[QStringLiteral("cfcollection")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfcomponent"), QCFTag(QStringLiteral("cfcomponent"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("bindingname"), false));
    args.append(QCFTagArgument(QStringLiteral("displayname"), false));
    args.append(QCFTagArgument(QStringLiteral("extends"), false));
    args.append(QCFTagArgument(QStringLiteral("hint"), false));
    args.append(QCFTagArgument(QStringLiteral("implements"), false));
    args.append(QCFTagArgument(QStringLiteral("namespace"), false));
    args.append(QCFTagArgument(QStringLiteral("output"), false));
    args.append(QCFTagArgument(QStringLiteral("porttypename"), false));
    args.append(QCFTagArgument(QStringLiteral("serviceaddress"), false));
    args.append(QCFTagArgument(QStringLiteral("serviceportname"), false));
    args.append(QCFTagArgument(QStringLiteral("style"), false));
    args.append(QCFTagArgument(QStringLiteral("wsdlfile"), false));
    ret[QStringLiteral("cfcomponent")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfcontent"), QCFTag(QStringLiteral("cfcontent"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("deleteFile"), false));
    args.append(QCFTagArgument(QStringLiteral("file"), false));
    args.append(QCFTagArgument(QStringLiteral("reset"), false));
    args.append(QCFTagArgument(QStringLiteral("type"), false));
    args.append(QCFTagArgument(QStringLiteral("variable"), false));
    ret[QStringLiteral("cfcontent")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfcookie"), QCFTag(QStringLiteral("cfcookie"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true));
    args.append(QCFTagArgument(QStringLiteral("domain"), false));
    args.append(QCFTagArgument(QStringLiteral("expires"), false));
    args.append(QCFTagArgument(QStringLiteral("path"), false));
    args.append(QCFTagArgument(QStringLiteral("secure"), false));
    args.append(QCFTagArgument(QStringLiteral("value"), false));
    ret[QStringLiteral("cfcookie")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfdbinfo"), QCFTag(QStringLiteral("cfdbinfo"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfdefaultcase"), QCFTag(QStringLiteral("cfdefaultcase"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfdirectory"), QCFTag(QStringLiteral("cfdirectory"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("directory"), true));
    args.append(QCFTagArgument(QStringLiteral("action"), false, QCFTagArgument::TypeConstantString, QStringLiteral("list")));
    args.append(QCFTagArgument(QStringLiteral("filter"), false));
    args.append(QCFTagArgument(QStringLiteral("listinfo"), false, QCFTagArgument::TypeConstantString));
    ret[QStringLiteral("cfdirectory")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfdiv"), QCFTag(QStringLiteral("cfdiv"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfdocument"), QCFTag(QStringLiteral("cfdocument"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("format"), true));
    args.append(QCFTagArgument(QStringLiteral("authPassword")));
    args.append(QCFTagArgument(QStringLiteral("authUser")));
    args.append(QCFTagArgument(QStringLiteral("backgroundVisible")));
    args.append(QCFTagArgument(QStringLiteral("bookmark")));
    args.append(QCFTagArgument(QStringLiteral("encryption")));
    args.append(QCFTagArgument(QStringLiteral("filename")));
    args.append(QCFTagArgument(QStringLiteral("fontEmbed")));
    args.append(QCFTagArgument(QStringLiteral("localUrl")));
    args.append(QCFTagArgument(QStringLiteral("marginBottom")));
    args.append(QCFTagArgument(QStringLiteral("marginLeft")));
    args.append(QCFTagArgument(QStringLiteral("marginRight")));
    args.append(QCFTagArgument(QStringLiteral("marginTop")));
    args.append(QCFTagArgument(QStringLiteral("mimeType")));
    args.append(QCFTagArgument(QStringLiteral("name")));
    args.append(QCFTagArgument(QStringLiteral("orientation")));
    args.append(QCFTagArgument(QStringLiteral("overwrite")));
    args.append(QCFTagArgument(QStringLiteral("ownerPassword")));
    args.append(QCFTagArgument(QStringLiteral("pageHeight")));
    args.append(QCFTagArgument(QStringLiteral("pageType")));
    args.append(QCFTagArgument(QStringLiteral("pageWidth")));
    args.append(QCFTagArgument(QStringLiteral("permissions")));
    args.append(QCFTagArgument(QStringLiteral("proxyHost")));
    args.append(QCFTagArgument(QStringLiteral("proxyPassword")));
    args.append(QCFTagArgument(QStringLiteral("proxyPort")));
    args.append(QCFTagArgument(QStringLiteral("proxyUser")));
    args.append(QCFTagArgument(QStringLiteral("saveAsName")));
    args.append(QCFTagArgument(QStringLiteral("scale")));
    args.append(QCFTagArgument(QStringLiteral("src")));
    args.append(QCFTagArgument(QStringLiteral("srcfile")));
    args.append(QCFTagArgument(QStringLiteral("unit")));
    args.append(QCFTagArgument(QStringLiteral("userAgent")));
    args.append(QCFTagArgument(QStringLiteral("userPassword")));
    ret[QStringLiteral("cfdocument")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfdocumentitem"), QCFTag(QStringLiteral("cfdocumentitem"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("type"), true));
    ret[QStringLiteral("cfdocumentitem")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfdocumentsection"), QCFTag(QStringLiteral("cfdocumentsection"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("authPassword")));
    args.append(QCFTagArgument(QStringLiteral("authUser")));
    args.append(QCFTagArgument(QStringLiteral("marginBottom")));
    args.append(QCFTagArgument(QStringLiteral("marginLeft")));
    args.append(QCFTagArgument(QStringLiteral("marginRight")));
    args.append(QCFTagArgument(QStringLiteral("marginTop")));
    args.append(QCFTagArgument(QStringLiteral("mimeType")));
    args.append(QCFTagArgument(QStringLiteral("name")));
    args.append(QCFTagArgument(QStringLiteral("src")));
    args.append(QCFTagArgument(QStringLiteral("srcfile")));
    args.append(QCFTagArgument(QStringLiteral("userAgent")));
    ret[QStringLiteral("cfdocumentsection")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfdump"), QCFTag(QStringLiteral("cfdump"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("var"), true));
    ret[QStringLiteral("cfdump")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfelse"), QCFTag(QStringLiteral("cfelse"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeExpression));

	ret.insert(QStringLiteral("cfelseif"), QCFTag(QStringLiteral("cfelseif"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeExpression));

	ret.insert(QStringLiteral("cferror"), QCFTag(QStringLiteral("cferror"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("template"), true));
    args.append(QCFTagArgument(QStringLiteral("type"), true));
    args.append(QCFTagArgument(QStringLiteral("exception")));
    args.append(QCFTagArgument(QStringLiteral("mailTo")));
    ret[QStringLiteral("cferror")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfexchangecalendar"), QCFTag(QStringLiteral("cfexchangecalendar"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfexchangeconnection"), QCFTag(QStringLiteral("cfexchangeconnection"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfexchangecontact"), QCFTag(QStringLiteral("cfexchangecontact"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfexchangefilter"), QCFTag(QStringLiteral("cfexchangefilter"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfexchangemail"), QCFTag(QStringLiteral("cfexchangemail"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfexchangetask"), QCFTag(QStringLiteral("cfexchangetask"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfexecute"), QCFTag(QStringLiteral("cfexecute"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true));
    args.append(QCFTagArgument(QStringLiteral("arguments")));
    args.append(QCFTagArgument(QStringLiteral("outputFile")));
    args.append(QCFTagArgument(QStringLiteral("timeout")));
    args.append(QCFTagArgument(QStringLiteral("variable")));
    ret[QStringLiteral("cfexecute")].m_ArgumentVariants.append(args);


	ret.insert(QStringLiteral("cfexit"), QCFTag(QStringLiteral("cfexit"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("method"), false, QCFTagArgument::TypeConstantString));
    ret[QStringLiteral("cfexit")].m_ArgumentVariants.append(args);

	//ret.insert(QStringLiteral("cffeed"), QCFTag("cffeed"));

	ret.insert(QStringLiteral("cffile"), QCFTag(QStringLiteral("cffile"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("append")));
    args.append(QCFTagArgument(QStringLiteral("file"), true));
    args.append(QCFTagArgument(QStringLiteral("output"), true));
    args.append(QCFTagArgument(QStringLiteral("addNewLine")));
    args.append(QCFTagArgument(QStringLiteral("attributes")));
    args.append(QCFTagArgument(QStringLiteral("charset")));
    args.append(QCFTagArgument(QStringLiteral("fixnewline")));
    args.append(QCFTagArgument(QStringLiteral("mode")));
    ret[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("copy")));
    args.append(QCFTagArgument(QStringLiteral("destination"), true));
    args.append(QCFTagArgument(QStringLiteral("source"), true));
    args.append(QCFTagArgument(QStringLiteral("attributes")));
    args.append(QCFTagArgument(QStringLiteral("mode")));
    ret[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("delete")));
    args.append(QCFTagArgument(QStringLiteral("file"), true));
    ret[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("delete")));
    args.append(QCFTagArgument(QStringLiteral("file"), true));
    ret[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("move")));
    args.append(QCFTagArgument(QStringLiteral("destination"), true));
    args.append(QCFTagArgument(QStringLiteral("source"), true));
    args.append(QCFTagArgument(QStringLiteral("attributes")));
    args.append(QCFTagArgument(QStringLiteral("charset")));
    args.append(QCFTagArgument(QStringLiteral("mode")));
    ret[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("read")));
    args.append(QCFTagArgument(QStringLiteral("file"), true));
    args.append(QCFTagArgument(QStringLiteral("variable"), true));
    args.append(QCFTagArgument(QStringLiteral("charset")));
    ret[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("readBinary")));
    args.append(QCFTagArgument(QStringLiteral("file"), true));
    args.append(QCFTagArgument(QStringLiteral("variable"), true));
    ret[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("rename")));
    args.append(QCFTagArgument(QStringLiteral("destination"), true));
    args.append(QCFTagArgument(QStringLiteral("source"), true));
    args.append(QCFTagArgument(QStringLiteral("attributes")));
    args.append(QCFTagArgument(QStringLiteral("mode")));
    ret[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("upload")));
    args.append(QCFTagArgument(QStringLiteral("destination"), true));
    args.append(QCFTagArgument(QStringLiteral("fileField"), true));
    args.append(QCFTagArgument(QStringLiteral("accept")));
    args.append(QCFTagArgument(QStringLiteral("attributes")));
    args.append(QCFTagArgument(QStringLiteral("mode")));
    args.append(QCFTagArgument(QStringLiteral("nameConflict")));
    args.append(QCFTagArgument(QStringLiteral("result")));
    ret[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("uploadAll")));
    args.append(QCFTagArgument(QStringLiteral("destination"), true));
    args.append(QCFTagArgument(QStringLiteral("accept")));
    args.append(QCFTagArgument(QStringLiteral("attributes")));
    args.append(QCFTagArgument(QStringLiteral("mode")));
    args.append(QCFTagArgument(QStringLiteral("nameConflict")));
    args.append(QCFTagArgument(QStringLiteral("result")));
    ret[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("write")));
    args.append(QCFTagArgument(QStringLiteral("file"), true));
    args.append(QCFTagArgument(QStringLiteral("output"), true));
    args.append(QCFTagArgument(QStringLiteral("addNewLine")));
    args.append(QCFTagArgument(QStringLiteral("attributes")));
    args.append(QCFTagArgument(QStringLiteral("charset")));
    args.append(QCFTagArgument(QStringLiteral("result")));
    args.append(QCFTagArgument(QStringLiteral("mode")));
    ret[QStringLiteral("cffile")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cffinally"), QCFTag(QStringLiteral("cffinally"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfflush"), QCFTag(QStringLiteral("cfflush"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("interval")));
    ret[QStringLiteral("cfflush")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfform"), QCFTag(QStringLiteral("cfform"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("accessible")));
    args.append(QCFTagArgument(QStringLiteral("action")));
    args.append(QCFTagArgument(QStringLiteral("archive")));
    args.append(QCFTagArgument(QStringLiteral("codeBase")));
    args.append(QCFTagArgument(QStringLiteral("format")));
    args.append(QCFTagArgument(QStringLiteral("height")));
    args.append(QCFTagArgument(QStringLiteral("id")));
    args.append(QCFTagArgument(QStringLiteral("method")));
    args.append(QCFTagArgument(QStringLiteral("name")));
    args.append(QCFTagArgument(QStringLiteral("onError")));
    args.append(QCFTagArgument(QStringLiteral("onLoad")));
    args.append(QCFTagArgument(QStringLiteral("onReset")));
    args.append(QCFTagArgument(QStringLiteral("onSubmit")));
    args.append(QCFTagArgument(QStringLiteral("onSuccess")));
    args.append(QCFTagArgument(QStringLiteral("preloader")));
    args.append(QCFTagArgument(QStringLiteral("preserveData")));
    args.append(QCFTagArgument(QStringLiteral("scriptSrc")));
    args.append(QCFTagArgument(QStringLiteral("skin")));
    args.append(QCFTagArgument(QStringLiteral("style")));
    args.append(QCFTagArgument(QStringLiteral("timeout")));
    args.append(QCFTagArgument(QStringLiteral("width")));
    args.append(QCFTagArgument(QStringLiteral("wMode")));
    ret[QStringLiteral("cfform")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfformgroup"), QCFTag(QStringLiteral("cfformgroup"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("type"), true, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument(QStringLiteral("label")));
    args.append(QCFTagArgument(QStringLiteral("style")));
    args.append(QCFTagArgument(QStringLiteral("selectedIndex")));
    args.append(QCFTagArgument(QStringLiteral("width")));
    args.append(QCFTagArgument(QStringLiteral("height")));
    args.append(QCFTagArgument(QStringLiteral("enabled")));
    args.append(QCFTagArgument(QStringLiteral("visible")));
    args.append(QCFTagArgument(QStringLiteral("onChange")));
    args.append(QCFTagArgument(QStringLiteral("tooltip")));
    args.append(QCFTagArgument(QStringLiteral("id")));
    args.append(QCFTagArgument(QStringLiteral("query")));
    args.append(QCFTagArgument(QStringLiteral("maxrows")));
    args.append(QCFTagArgument(QStringLiteral("startrow")));
    ret[QStringLiteral("cfformgroup")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfformitem"), QCFTag(QStringLiteral("cfformitem"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfftp"), QCFTag(QStringLiteral("cfftp"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument(QStringLiteral("actionparam")));
    args.append(QCFTagArgument(QStringLiteral("buffersize")));
    args.append(QCFTagArgument(QStringLiteral("connection")));
    args.append(QCFTagArgument(QStringLiteral("passive")));
    args.append(QCFTagArgument(QStringLiteral("password")));
    args.append(QCFTagArgument(QStringLiteral("port")));
    args.append(QCFTagArgument(QStringLiteral("proxyServer")));
    args.append(QCFTagArgument(QStringLiteral("retryCount")));
    args.append(QCFTagArgument(QStringLiteral("server")));
    args.append(QCFTagArgument(QStringLiteral("stopOnError")));
    args.append(QCFTagArgument(QStringLiteral("timeout")));
    args.append(QCFTagArgument(QStringLiteral("username")));
    ret[QStringLiteral("cfftp")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cffunction"), QCFTag(QStringLiteral("cffunction"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument(QStringLiteral("access")));
    args.append(QCFTagArgument(QStringLiteral("description")));
    args.append(QCFTagArgument(QStringLiteral("displayName")));
    args.append(QCFTagArgument(QStringLiteral("hint")));
    args.append(QCFTagArgument(QStringLiteral("output")));
    args.append(QCFTagArgument(QStringLiteral("returnFormat")));
    args.append(QCFTagArgument(QStringLiteral("returnType")));
    args.append(QCFTagArgument(QStringLiteral("roles")));
    args.append(QCFTagArgument(QStringLiteral("secureJSON")));
    args.append(QCFTagArgument(QStringLiteral("verifyClient")));
    ret[QStringLiteral("cffunction")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfgraph"), QCFTag(QStringLiteral("cfgraph"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfgraphdata"), QCFTag(QStringLiteral("cfgraphdata"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

    ret.insert(QStringLiteral("cfgrid"), QCFTag(QStringLiteral("cfgrid"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true));
    args.append(QCFTagArgument(QStringLiteral("align")));
    args.append(QCFTagArgument(QStringLiteral("appendKey")));
    args.append(QCFTagArgument(QStringLiteral("autoWidth")));
    args.append(QCFTagArgument(QStringLiteral("bgColor")));
    args.append(QCFTagArgument(QStringLiteral("bind")));
    args.append(QCFTagArgument(QStringLiteral("bindOnLoad")));
    args.append(QCFTagArgument(QStringLiteral("bold")));
    args.append(QCFTagArgument(QStringLiteral("colHeaderAlign")));
    args.append(QCFTagArgument(QStringLiteral("colHeaderBold")));
    args.append(QCFTagArgument(QStringLiteral("colHeaderFont")));
    args.append(QCFTagArgument(QStringLiteral("colHeaderFontSize")));
    args.append(QCFTagArgument(QStringLiteral("colHeaderItalic")));
    args.append(QCFTagArgument(QStringLiteral("colHeaders")));
    args.append(QCFTagArgument(QStringLiteral("colHeaderTextColor")));
    args.append(QCFTagArgument(QStringLiteral("delete")));
    args.append(QCFTagArgument(QStringLiteral("deleteButton")));
    args.append(QCFTagArgument(QStringLiteral("enabled")));
    args.append(QCFTagArgument(QStringLiteral("font")));
    args.append(QCFTagArgument(QStringLiteral("fontSize")));
    args.append(QCFTagArgument(QStringLiteral("format")));
    args.append(QCFTagArgument(QStringLiteral("gridDataAlign")));
    args.append(QCFTagArgument(QStringLiteral("gridLines")));
    args.append(QCFTagArgument(QStringLiteral("height")));
    args.append(QCFTagArgument(QStringLiteral("highlightHref")));
    args.append(QCFTagArgument(QStringLiteral("href")));
    args.append(QCFTagArgument(QStringLiteral("hrefKey")));
    args.append(QCFTagArgument(QStringLiteral("hSpace")));
    args.append(QCFTagArgument(QStringLiteral("insert")));
    args.append(QCFTagArgument(QStringLiteral("insertButton")));
    args.append(QCFTagArgument(QStringLiteral("italic")));
    args.append(QCFTagArgument(QStringLiteral("maxRows")));
    args.append(QCFTagArgument(QStringLiteral("notSupported")));
    args.append(QCFTagArgument(QStringLiteral("onBlur")));
    args.append(QCFTagArgument(QStringLiteral("onChange")));
    args.append(QCFTagArgument(QStringLiteral("onError")));
    args.append(QCFTagArgument(QStringLiteral("onFocus")));
    args.append(QCFTagArgument(QStringLiteral("onValidate")));
    args.append(QCFTagArgument(QStringLiteral("pageSize")));
    args.append(QCFTagArgument(QStringLiteral("pictureBar")));
    args.append(QCFTagArgument(QStringLiteral("preservePageOnSort")));
    args.append(QCFTagArgument(QStringLiteral("query")));
    args.append(QCFTagArgument(QStringLiteral("rowHeaderAlign")));
    args.append(QCFTagArgument(QStringLiteral("rowHeaderBold")));
    args.append(QCFTagArgument(QStringLiteral("rowHeaderFont")));
    args.append(QCFTagArgument(QStringLiteral("rowHeaderFontSize")));
    args.append(QCFTagArgument(QStringLiteral("rowHeaderItalic")));
    args.append(QCFTagArgument(QStringLiteral("rowHeaders")));
    args.append(QCFTagArgument(QStringLiteral("rowHeaderTextColor")));
    args.append(QCFTagArgument(QStringLiteral("rowHeight")));
    args.append(QCFTagArgument(QStringLiteral("selectColor")));
    args.append(QCFTagArgument(QStringLiteral("selectMode")));
    args.append(QCFTagArgument(QStringLiteral("selectOnLoad")));
    args.append(QCFTagArgument(QStringLiteral("sort")));
    args.append(QCFTagArgument(QStringLiteral("sortAscendingButton")));
    args.append(QCFTagArgument(QStringLiteral("sortDescendingButton")));
    args.append(QCFTagArgument(QStringLiteral("stripeRowColor")));
    args.append(QCFTagArgument(QStringLiteral("stripeRows")));
    args.append(QCFTagArgument(QStringLiteral("style")));
    args.append(QCFTagArgument(QStringLiteral("target")));
    args.append(QCFTagArgument(QStringLiteral("textColor")));
    args.append(QCFTagArgument(QStringLiteral("tooltip")));
    args.append(QCFTagArgument(QStringLiteral("visible")));
    args.append(QCFTagArgument(QStringLiteral("vSpace")));
    args.append(QCFTagArgument(QStringLiteral("width")));
    ret[QStringLiteral("cfgrid")].m_ArgumentVariants.append(args);

    ret.insert(QStringLiteral("cfgridcolumn"), QCFTag(QStringLiteral("cfgridcolumn"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true));
    args.append(QCFTagArgument(QStringLiteral("bgColor")));
    args.append(QCFTagArgument(QStringLiteral("bold")));
    args.append(QCFTagArgument(QStringLiteral("dataAlign")));
    args.append(QCFTagArgument(QStringLiteral("display")));
    args.append(QCFTagArgument(QStringLiteral("font")));
    args.append(QCFTagArgument(QStringLiteral("fontSize")));
    args.append(QCFTagArgument(QStringLiteral("header")));
    args.append(QCFTagArgument(QStringLiteral("headerAlign")));
    args.append(QCFTagArgument(QStringLiteral("headerBold")));
    args.append(QCFTagArgument(QStringLiteral("headerFont")));
    args.append(QCFTagArgument(QStringLiteral("headerFontSize")));
    args.append(QCFTagArgument(QStringLiteral("headerItalic")));
    args.append(QCFTagArgument(QStringLiteral("headerTextColor")));
    args.append(QCFTagArgument(QStringLiteral("href")));
    args.append(QCFTagArgument(QStringLiteral("hrefKey")));
    args.append(QCFTagArgument(QStringLiteral("italic")));
    args.append(QCFTagArgument(QStringLiteral("mask")));
    args.append(QCFTagArgument(QStringLiteral("numberFormat")));
    args.append(QCFTagArgument(QStringLiteral("select")));
    args.append(QCFTagArgument(QStringLiteral("target")));
    args.append(QCFTagArgument(QStringLiteral("textColor")));
    args.append(QCFTagArgument(QStringLiteral("type")));
    args.append(QCFTagArgument(QStringLiteral("values")));
    args.append(QCFTagArgument(QStringLiteral("valuesDelimiter")));
    args.append(QCFTagArgument(QStringLiteral("valuesDisplay")));
    args.append(QCFTagArgument(QStringLiteral("width")));
    ret[QStringLiteral("cfgridcolumn")].m_ArgumentVariants.append(args);
    args.clear();

	ret.insert(QStringLiteral("cfgridrow"), QCFTag(QStringLiteral("cfgridrow"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("data"), true));
    ret[QStringLiteral("cfgridrow")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfgridupdate"), QCFTag(QStringLiteral("cfgridupdate"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfheader"), QCFTag(QStringLiteral("cfheader"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("charset"), false, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument(QStringLiteral("name"), true, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument(QStringLiteral("value")));
    ret[QStringLiteral("cfheader")].m_ArgumentVariants.append(args);
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("charset"), false, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument(QStringLiteral("statusCode"), true));
    args.append(QCFTagArgument(QStringLiteral("statusText")));
    args.append(QCFTagArgument(QStringLiteral("value")));
    ret[QStringLiteral("cfheader")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfhtmlhead"), QCFTag(QStringLiteral("cfhtmlhead"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.append(QCFTagArgument(QStringLiteral("text"), true));
    ret[QStringLiteral("cfhtmlhead")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfhttp"), QCFTag(QStringLiteral("cfhttp"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("url"), true));
    args.append(QCFTagArgument(QStringLiteral("charset")));
    args.append(QCFTagArgument(QStringLiteral("clientCert")));
    args.append(QCFTagArgument(QStringLiteral("clientCertPassword")));
    args.append(QCFTagArgument(QStringLiteral("columns")));
    args.append(QCFTagArgument(QStringLiteral("delimiter")));
    args.append(QCFTagArgument(QStringLiteral("file")));
    args.append(QCFTagArgument(QStringLiteral("firstrowasheaders")));
    args.append(QCFTagArgument(QStringLiteral("getAsBinary")));
    args.append(QCFTagArgument(QStringLiteral("method")));
    args.append(QCFTagArgument(QStringLiteral("multipart")));
    args.append(QCFTagArgument(QStringLiteral("name")));
    args.append(QCFTagArgument(QStringLiteral("password")));
    args.append(QCFTagArgument(QStringLiteral("path")));
    args.append(QCFTagArgument(QStringLiteral("port")));
    args.append(QCFTagArgument(QStringLiteral("proxyServer")));
    args.append(QCFTagArgument(QStringLiteral("proxyPort")));
    args.append(QCFTagArgument(QStringLiteral("proxyUser")));
    args.append(QCFTagArgument(QStringLiteral("proxyPassword")));
    args.append(QCFTagArgument(QStringLiteral("redirect")));
    args.append(QCFTagArgument(QStringLiteral("resolveURL")));
    args.append(QCFTagArgument(QStringLiteral("result")));
    args.append(QCFTagArgument(QStringLiteral("TextQualifier")));
    args.append(QCFTagArgument(QStringLiteral("throwOnError")));
    args.append(QCFTagArgument(QStringLiteral("timeout")));
    args.append(QCFTagArgument(QStringLiteral("username")));
    args.append(QCFTagArgument(QStringLiteral("userAgent")));
    ret[QStringLiteral("cfhttp")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfhttpparam"), QCFTag(QStringLiteral("cfhttpparam"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear(); // TODO: Make this argument as it should.
    args.append(QCFTagArgument(QStringLiteral("type"), true));
    args.append(QCFTagArgument(QStringLiteral("encoded")));
    args.append(QCFTagArgument(QStringLiteral("file")));
    args.append(QCFTagArgument(QStringLiteral("mimeType")));
    args.append(QCFTagArgument(QStringLiteral("name")));
    args.append(QCFTagArgument(QStringLiteral("value")));
    ret[QStringLiteral("cfhttpparam")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfif"), QCFTag(QStringLiteral("cfif"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeExpression));

	ret.insert(QStringLiteral("cfimage"), QCFTag(QStringLiteral("cfimage"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfimpersonate"), QCFTag(QStringLiteral("cfimpersonate"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfimport"), QCFTag(QStringLiteral("cfimport"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("taglib"), true, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument(QStringLiteral("prefix"), true, QCFTagArgument::TypeConstantString));
    ret[QStringLiteral("cfimport")].m_ArgumentVariants.append(args);
	
	ret.insert(QStringLiteral("cfinclude"), QCFTag(QStringLiteral("cfinclude"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("template"), true));
    ret[QStringLiteral("cfinclude")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfindex"), QCFTag(QStringLiteral("cfindex"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("action"), true));
    args.append(QCFTagArgument(QStringLiteral("collection"), true));
    args.append(QCFTagArgument(QStringLiteral("key"), true));
    args.append(QCFTagArgument(QStringLiteral("body")));
    args.append(QCFTagArgument(QStringLiteral("category")));
    args.append(QCFTagArgument(QStringLiteral("categoryTree")));
    args.append(QCFTagArgument(QStringLiteral("custom1")));
    args.append(QCFTagArgument(QStringLiteral("custom2")));
    args.append(QCFTagArgument(QStringLiteral("custom3")));
    args.append(QCFTagArgument(QStringLiteral("custom4")));
    args.append(QCFTagArgument(QStringLiteral("extensions")));
    args.append(QCFTagArgument(QStringLiteral("language")));
    args.append(QCFTagArgument(QStringLiteral("prefix")));
    args.append(QCFTagArgument(QStringLiteral("query")));
    args.append(QCFTagArgument(QStringLiteral("recurse")));
    args.append(QCFTagArgument(QStringLiteral("status")));
    args.append(QCFTagArgument(QStringLiteral("title")));
    args.append(QCFTagArgument(QStringLiteral("type")));
    args.append(QCFTagArgument(QStringLiteral("URLpath")));
    ret[QStringLiteral("cfindex")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfinput"), QCFTag(QStringLiteral("cfinput"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument(QStringLiteral("autosuggest")));
    args.append(QCFTagArgument(QStringLiteral("autosuggestBindDelay")));
    args.append(QCFTagArgument(QStringLiteral("autosuggestMinLength")));
    args.append(QCFTagArgument(QStringLiteral("bind")));
    args.append(QCFTagArgument(QStringLiteral("bindAttribute")));
    args.append(QCFTagArgument(QStringLiteral("bindOnLoad")));
    args.append(QCFTagArgument(QStringLiteral("checked")));
    args.append(QCFTagArgument(QStringLiteral("dayNames")));
    args.append(QCFTagArgument(QStringLiteral("delimiter")));
    args.append(QCFTagArgument(QStringLiteral("disabled")));
    args.append(QCFTagArgument(QStringLiteral("enabled")));
    args.append(QCFTagArgument(QStringLiteral("firstDayOfWeek")));
    args.append(QCFTagArgument(QStringLiteral("height")));
    args.append(QCFTagArgument(QStringLiteral("id")));
    args.append(QCFTagArgument(QStringLiteral("label")));
    args.append(QCFTagArgument(QStringLiteral("mask")));
    args.append(QCFTagArgument(QStringLiteral("maxLength")));
    args.append(QCFTagArgument(QStringLiteral("maxResultsDisplayed")));
    args.append(QCFTagArgument(QStringLiteral("message")));
    args.append(QCFTagArgument(QStringLiteral("monthNames")));
    args.append(QCFTagArgument(QStringLiteral("onBindError")));
    args.append(QCFTagArgument(QStringLiteral("onChange")));
    args.append(QCFTagArgument(QStringLiteral("onClick")));
    args.append(QCFTagArgument(QStringLiteral("onError")));
	// TODO: more
    ret[QStringLiteral("cfinput")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfinsert"), QCFTag(QStringLiteral("cfinsert"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfinterface"), QCFTag(QStringLiteral("cfinterface"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfinvoke"), QCFTag(QStringLiteral("cfinvoke"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("component"), true));
    args.append(QCFTagArgument(QStringLiteral("method"), true));
    args.append(QCFTagArgument(QStringLiteral("argumentCollection")));
    args.append(QCFTagArgument(QStringLiteral("password")));
    args.append(QCFTagArgument(QStringLiteral("returnVariable")));
    args.append(QCFTagArgument(QStringLiteral("username")));
    ret[QStringLiteral("cfinvoke")].m_ArgumentVariants.append(args);
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("method"), true));
    args.append(QCFTagArgument(QStringLiteral("argumentCollection")));
    args.append(QCFTagArgument(QStringLiteral("component")));
    args.append(QCFTagArgument(QStringLiteral("password")));
    args.append(QCFTagArgument(QStringLiteral("returnVariable")));
    args.append(QCFTagArgument(QStringLiteral("username")));
    ret[QStringLiteral("cfinvoke")].m_ArgumentVariants.append(args);
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("method"), true));
    args.append(QCFTagArgument(QStringLiteral("webservice"), true));
    args.append(QCFTagArgument(QStringLiteral("argumentCollection")));
    args.append(QCFTagArgument(QStringLiteral("component")));
    args.append(QCFTagArgument(QStringLiteral("password")));
    args.append(QCFTagArgument(QStringLiteral("proxyPassword")));
    args.append(QCFTagArgument(QStringLiteral("proxyPort")));
    args.append(QCFTagArgument(QStringLiteral("proxyServer")));
    args.append(QCFTagArgument(QStringLiteral("proxyUser")));
    args.append(QCFTagArgument(QStringLiteral("returnVariable")));
    args.append(QCFTagArgument(QStringLiteral("servicePort")));
    args.append(QCFTagArgument(QStringLiteral("timeout")));
    args.append(QCFTagArgument(QStringLiteral("username")));
    args.append(QCFTagArgument(QStringLiteral("wsdl2javaArgs")));
    ret[QStringLiteral("cfinvoke")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfinvokeargument"), QCFTag(QStringLiteral("cfinvokeargument"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true));
    args.append(QCFTagArgument(QStringLiteral("value"), true));
    args.append(QCFTagArgument(QStringLiteral("omit")));
    ret[QStringLiteral("cfinvokeargument")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cflayout"), QCFTag(QStringLiteral("cflayout"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cflayoutarea"), QCFTag(QStringLiteral("cflayoutarea"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfldap"), QCFTag(QStringLiteral("cfldap"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cflocation"), QCFTag(QStringLiteral("cflocation"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("url"), true));
    args.append(QCFTagArgument(QStringLiteral("addToken")));
    args.append(QCFTagArgument(QStringLiteral("statusCode")));
    ret[QStringLiteral("cflocation")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cflock"), QCFTag(QStringLiteral("cflock"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("timeout"), true));
    args.append(QCFTagArgument(QStringLiteral("name")));
    args.append(QCFTagArgument(QStringLiteral("scope")));
    args.append(QCFTagArgument(QStringLiteral("throwOnTimeout")));
    args.append(QCFTagArgument(QStringLiteral("type")));
    ret[QStringLiteral("cflock")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cflog"), QCFTag(QStringLiteral("cflog"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("text"), true));
    args.append(QCFTagArgument(QStringLiteral("application")));
    args.append(QCFTagArgument(QStringLiteral("file")));
    args.append(QCFTagArgument(QStringLiteral("log")));
    args.append(QCFTagArgument(QStringLiteral("type")));
    ret[QStringLiteral("cflog")].m_ArgumentVariants.append(args);

    ret.insert(QStringLiteral("cflogin"), QCFTag(QStringLiteral("cflogin"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

    ret.insert(QStringLiteral("cfloginuser"), QCFTag(QStringLiteral("cfloginuser"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true));
    args.append(QCFTagArgument(QStringLiteral("password"), true));
    args.append(QCFTagArgument(QStringLiteral("roles"), true));
    ret[QStringLiteral("cfloginuser")].m_ArgumentVariants.append(args);

    ret.insert(QStringLiteral("cflogout"), QCFTag(QStringLiteral("cflogout"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfloop"), QCFTag(QStringLiteral("cfloop"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("index"), true, QCFTagArgument::TypeVariable));
    args.append(QCFTagArgument(QStringLiteral("from"), true, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument(QStringLiteral("to"), true, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument(QStringLiteral("step"), false, QCFTagArgument::TypeConstantString));
    ret[QStringLiteral("cfloop")].m_ArgumentVariants.append(args);
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("condition"), true, QCFTagArgument::TypeExpression));
    ret[QStringLiteral("cfloop")].m_ArgumentVariants.append(args);
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("query"), true, QCFTagArgument::TypeVariable));
    args.append(QCFTagArgument(QStringLiteral("startRow"), false, QCFTagArgument::TypeAny));
    args.append(QCFTagArgument(QStringLiteral("endRow"), false, QCFTagArgument::TypeAny));
    ret[QStringLiteral("cfloop")].m_ArgumentVariants.append(args);
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("index"), true, QCFTagArgument::TypeVariable));
    args.append(QCFTagArgument(QStringLiteral("list"), true, QCFTagArgument::TypeVariable));
    args.append(QCFTagArgument(QStringLiteral("delimiters"), false, QCFTagArgument::TypeConstantString));
    ret[QStringLiteral("cfloop")].m_ArgumentVariants.append(args);
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("index"), true, QCFTagArgument::TypeVariable));
    args.append(QCFTagArgument(QStringLiteral("file"), true));
    args.append(QCFTagArgument(QStringLiteral("characters")));
    ret[QStringLiteral("cfloop")].m_ArgumentVariants.append(args);
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("index"), true, QCFTagArgument::TypeVariable));
    args.append(QCFTagArgument(QStringLiteral("array"), true));
    ret[QStringLiteral("cfloop")].m_ArgumentVariants.append(args);
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("collection"), true));
    args.append(QCFTagArgument(QStringLiteral("item"), true));
    ret[QStringLiteral("cfloop")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfmail"), QCFTag(QStringLiteral("cfmail"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments, QCFTag::WithExpressionInside));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("from"), true));
    args.append(QCFTagArgument(QStringLiteral("to"), true));
    args.append(QCFTagArgument(QStringLiteral("bcc")));
    args.append(QCFTagArgument(QStringLiteral("cc")));
    args.append(QCFTagArgument(QStringLiteral("charset")));
    args.append(QCFTagArgument(QStringLiteral("debug")));
    args.append(QCFTagArgument(QStringLiteral("failto")));
    args.append(QCFTagArgument(QStringLiteral("group")));
    args.append(QCFTagArgument(QStringLiteral("groupcasesensitive")));
    args.append(QCFTagArgument(QStringLiteral("mailerid")));
    args.append(QCFTagArgument(QStringLiteral("maxrows")));
    args.append(QCFTagArgument(QStringLiteral("mimeattach")));
    args.append(QCFTagArgument(QStringLiteral("password")));
    args.append(QCFTagArgument(QStringLiteral("port")));
    args.append(QCFTagArgument(QStringLiteral("priority")));
    args.append(QCFTagArgument(QStringLiteral("query")));
    args.append(QCFTagArgument(QStringLiteral("replyto")));
    args.append(QCFTagArgument(QStringLiteral("server")));
    args.append(QCFTagArgument(QStringLiteral("spoolenable")));
    args.append(QCFTagArgument(QStringLiteral("startrow")));
    args.append(QCFTagArgument(QStringLiteral("subject"), true));
    args.append(QCFTagArgument(QStringLiteral("timeout")));
    args.append(QCFTagArgument(QStringLiteral("type")));
    args.append(QCFTagArgument(QStringLiteral("username")));
    args.append(QCFTagArgument(QStringLiteral("useSSL")));
    args.append(QCFTagArgument(QStringLiteral("useTLS")));
    args.append(QCFTagArgument(QStringLiteral("wraptext")));
    ret[QStringLiteral("cfmail")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfmailparam"), QCFTag(QStringLiteral("cfmailparam"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfmailpart"), QCFTag(QStringLiteral("cfmailpart"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("type"), true));
    args.append(QCFTagArgument(QStringLiteral("charset")));
    args.append(QCFTagArgument(QStringLiteral("wraptext")));
    ret[QStringLiteral("cfmailpart")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfmenu"), QCFTag(QStringLiteral("cfmenu"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfmenuitem"), QCFTag(QStringLiteral("cfmenuitem"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

    ret.insert(QStringLiteral("cfmodule"), QCFTag(QStringLiteral("cfmodule"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments, QCFTag::WithoutExpressionInside, true));

	ret.insert(QStringLiteral("cfNTauthenticate"), QCFTag(QStringLiteral("cfNTauthenticate"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfobject"), QCFTag(QStringLiteral("cfobject"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("component"), true));
    args.append(QCFTagArgument(QStringLiteral("name"), true));
    args.append(QCFTagArgument(QStringLiteral("type"), false, QCFTagArgument::TypeConstantString, QStringLiteral("component")));
    ret[QStringLiteral("cfobject")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfobjectcache"), QCFTag(QStringLiteral("cfobjectcache"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfoutput"), QCFTag(QStringLiteral("cfoutput"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments, QCFTag::WithExpressionInside));
    args.clear();
    ret[QStringLiteral("cfoutput")].m_ArgumentVariants.append(args);
    args.append(QCFTagArgument(QStringLiteral("query"), true));
    ret[QStringLiteral("cfoutput")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfparam"), QCFTag(QStringLiteral("cfparam"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true));
    args.append(QCFTagArgument(QStringLiteral("default")));
    args.append(QCFTagArgument(QStringLiteral("max")));
    args.append(QCFTagArgument(QStringLiteral("min")));
    args.append(QCFTagArgument(QStringLiteral("pattern")));
    args.append(QCFTagArgument(QStringLiteral("type")));
    ret[QStringLiteral("cfparam")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfpdf"), QCFTag(QStringLiteral("cfpdf"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfpdfform"), QCFTag(QStringLiteral("cfpdfform"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfpdfformparam"), QCFTag(QStringLiteral("cfpdfformparam"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfpdfparam"), QCFTag(QStringLiteral("cfpdfparam"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfpdfsubform"), QCFTag(QStringLiteral("cfpdfsubform"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfpod"), QCFTag(QStringLiteral("cfpod"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfpop"), QCFTag(QStringLiteral("cfpop"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfpresentation"), QCFTag(QStringLiteral("cfpresentation"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfpresentationslide"), QCFTag(QStringLiteral("cfpresentationslide"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfpresenter"), QCFTag(QStringLiteral("cfpresenter"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfprint"), QCFTag(QStringLiteral("cfprint"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfprocessingdirective"), QCFTag(QStringLiteral("cfprocessingdirective"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("pageEncoding")));
    args.append(QCFTagArgument(QStringLiteral("suppressWhiteSpace")));
    ret[QStringLiteral("cfprocessingdirective")].m_ArgumentVariants.append(args);

    ret.insert(QStringLiteral("cfprocparam"), QCFTag(QStringLiteral("cfprocparam"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("CFSQLType"), true));
    args.append(QCFTagArgument(QStringLiteral("maxLength")));
    args.append(QCFTagArgument(QStringLiteral("null")));
    args.append(QCFTagArgument(QStringLiteral("scale")));
    args.append(QCFTagArgument(QStringLiteral("type")));
    args.append(QCFTagArgument(QStringLiteral("value")));
    args.append(QCFTagArgument(QStringLiteral("variable")));
    ret[QStringLiteral("cfprocparam")].m_ArgumentVariants.append(args);

    ret.insert(QStringLiteral("cfprocresult"), QCFTag(QStringLiteral("cfprocresult"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true));
    args.append(QCFTagArgument(QStringLiteral("maxRows")));
    args.append(QCFTagArgument(QStringLiteral("resultSet")));
    ret[QStringLiteral("cfprocresult")].m_ArgumentVariants.append(args);

    ret.insert(QStringLiteral("cfproperty"), QCFTag(QStringLiteral("cfproperty"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true));
    args.append(QCFTagArgument(QStringLiteral("default")));
    args.append(QCFTagArgument(QStringLiteral("displayname")));
    args.append(QCFTagArgument(QStringLiteral("hint")));
    args.append(QCFTagArgument(QStringLiteral("required")));
    args.append(QCFTagArgument(QStringLiteral("type")));
    ret[QStringLiteral("cfproperty")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfquery"), QCFTag(QStringLiteral("cfquery"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments, QCFTag::WithExpressionInside));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true));
    args.append(QCFTagArgument(QStringLiteral("blockFactor")));
    args.append(QCFTagArgument(QStringLiteral("cachedAfter")));
    args.append(QCFTagArgument(QStringLiteral("cachedWithin")));
    args.append(QCFTagArgument(QStringLiteral("dataSource")));
    args.append(QCFTagArgument(QStringLiteral("dbtype")));
    args.append(QCFTagArgument(QStringLiteral("debug")));
    args.append(QCFTagArgument(QStringLiteral("maxRows")));
    args.append(QCFTagArgument(QStringLiteral("password")));
    args.append(QCFTagArgument(QStringLiteral("result")));
    args.append(QCFTagArgument(QStringLiteral("timeout")));
    args.append(QCFTagArgument(QStringLiteral("username")));
    ret[QStringLiteral("cfquery")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfqueryparam"), QCFTag(QStringLiteral("cfqueryparam"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("value"), true));
    args.append(QCFTagArgument(QStringLiteral("CFSQLType")));
    args.append(QCFTagArgument(QStringLiteral("list")));
    args.append(QCFTagArgument(QStringLiteral("maxLength")));
    args.append(QCFTagArgument(QStringLiteral("null")));
    args.append(QCFTagArgument(QStringLiteral("scale")));
    args.append(QCFTagArgument(QStringLiteral("separator")));
    ret[QStringLiteral("cfqueryparam")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfregistry"), QCFTag(QStringLiteral("cfregistry"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfreport"), QCFTag(QStringLiteral("cfreport"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfreportparam"), QCFTag(QStringLiteral("cfreportparam"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfrethrow"), QCFTag(QStringLiteral("cfrethrow"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfreturn"), QCFTag(QStringLiteral("cfreturn"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeExpression));

	ret.insert(QStringLiteral("cfsavecontent"), QCFTag(QStringLiteral("cfsavecontent"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("variable")));
    ret[QStringLiteral("cfsavecontent")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfschedule"), QCFTag(QStringLiteral("cfschedule"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("action"), true));
    args.append(QCFTagArgument(QStringLiteral("task"), true));
    args.append(QCFTagArgument(QStringLiteral("endDate")));
    args.append(QCFTagArgument(QStringLiteral("endTime")));
    args.append(QCFTagArgument(QStringLiteral("file")));
    args.append(QCFTagArgument(QStringLiteral("interval")));
    args.append(QCFTagArgument(QStringLiteral("operation")));
    args.append(QCFTagArgument(QStringLiteral("password")));
    args.append(QCFTagArgument(QStringLiteral("path")));
    args.append(QCFTagArgument(QStringLiteral("port")));
    args.append(QCFTagArgument(QStringLiteral("proxyPassword")));
    args.append(QCFTagArgument(QStringLiteral("proxyPort")));
    args.append(QCFTagArgument(QStringLiteral("proxyServer")));
    args.append(QCFTagArgument(QStringLiteral("proxyUser")));
    args.append(QCFTagArgument(QStringLiteral("publish")));
    args.append(QCFTagArgument(QStringLiteral("requestTimeOut")));
    args.append(QCFTagArgument(QStringLiteral("resolveURL")));
    args.append(QCFTagArgument(QStringLiteral("startDate")));
    args.append(QCFTagArgument(QStringLiteral("startTime")));
    args.append(QCFTagArgument(QStringLiteral("url")));
    args.append(QCFTagArgument(QStringLiteral("username")));
    ret[QStringLiteral("cfschedule")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfscript"), QCFTag(QStringLiteral("cfscript"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    ret[QStringLiteral("cfscript")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfsearch"), QCFTag(QStringLiteral("cfsearch"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true));
    args.append(QCFTagArgument(QStringLiteral("collection"), true));
    args.append(QCFTagArgument(QStringLiteral("category")));
    args.append(QCFTagArgument(QStringLiteral("categoryTree")));
    args.append(QCFTagArgument(QStringLiteral("contextBytes")));
    args.append(QCFTagArgument(QStringLiteral("contextHighlightBegin")));
    args.append(QCFTagArgument(QStringLiteral("contextHighlightEnd")));
    args.append(QCFTagArgument(QStringLiteral("contextPassages")));
    args.append(QCFTagArgument(QStringLiteral("criteria")));
    args.append(QCFTagArgument(QStringLiteral("language")));
    args.append(QCFTagArgument(QStringLiteral("maxRows")));
    args.append(QCFTagArgument(QStringLiteral("previousCriteria")));
    args.append(QCFTagArgument(QStringLiteral("startRow")));
    args.append(QCFTagArgument(QStringLiteral("status")));
    args.append(QCFTagArgument(QStringLiteral("suggestions")));
    args.append(QCFTagArgument(QStringLiteral("type")));
    ret[QStringLiteral("cfsearch")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfselect"), QCFTag(QStringLiteral("cfselect"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	// TODO: more..
    ret[QStringLiteral("cfselect")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfservlet"), QCFTag(QStringLiteral("cfservlet"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfservletparam"), QCFTag(QStringLiteral("cfservletparam"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfset"), QCFTag(QStringLiteral("cfset"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeExpression));

	ret.insert(QStringLiteral("cfsetting"), QCFTag(QStringLiteral("cfsetting"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("enableCFoutputOnly")));
    args.append(QCFTagArgument(QStringLiteral("requestTimeout")));
    args.append(QCFTagArgument(QStringLiteral("showDebugOutput")));
    ret[QStringLiteral("cfsetting")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfsilent"), QCFTag(QStringLiteral("cfsilent"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfslider"), QCFTag(QStringLiteral("cfslider"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfsprydataset"), QCFTag(QStringLiteral("cfsprydataset"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

    ret.insert(QStringLiteral("cfstoredproc"), QCFTag(QStringLiteral("cfstoredproc"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("dataSource"), true));
    args.append(QCFTagArgument(QStringLiteral("procedure"), true));
    args.append(QCFTagArgument(QStringLiteral("blockFactor")));
    args.append(QCFTagArgument(QStringLiteral("debug")));
    args.append(QCFTagArgument(QStringLiteral("password")));
    args.append(QCFTagArgument(QStringLiteral("result")));
    args.append(QCFTagArgument(QStringLiteral("returnCode")));
    args.append(QCFTagArgument(QStringLiteral("username")));
    ret[QStringLiteral("cfstoredproc")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfswitch"), QCFTag(QStringLiteral("cfswitch"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("expression"), true));
    ret[QStringLiteral("cfswitch")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cftable"), QCFTag(QStringLiteral("cftable"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

    ret.insert(QStringLiteral("cftextarea"), QCFTag(QStringLiteral("cftextarea"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true));
    args.append(QCFTagArgument(QStringLiteral("basepath")));
    args.append(QCFTagArgument(QStringLiteral("bind")));
    args.append(QCFTagArgument(QStringLiteral("bindAttribute")));
    args.append(QCFTagArgument(QStringLiteral("bindOnLoad")));
    args.append(QCFTagArgument(QStringLiteral("disabled")));
    args.append(QCFTagArgument(QStringLiteral("enabled")));
    args.append(QCFTagArgument(QStringLiteral("fontFormats")));
    args.append(QCFTagArgument(QStringLiteral("fontNames")));
    args.append(QCFTagArgument(QStringLiteral("fontSizes")));
    args.append(QCFTagArgument(QStringLiteral("height")));
    args.append(QCFTagArgument(QStringLiteral("html")));
    args.append(QCFTagArgument(QStringLiteral("label")));
    args.append(QCFTagArgument(QStringLiteral("maxlength")));
    args.append(QCFTagArgument(QStringLiteral("message")));
    args.append(QCFTagArgument(QStringLiteral("onBindError")));
    args.append(QCFTagArgument(QStringLiteral("onChange")));
    args.append(QCFTagArgument(QStringLiteral("onClick")));
    args.append(QCFTagArgument(QStringLiteral("onError")));
    args.append(QCFTagArgument(QStringLiteral("onKeyDown")));
    args.append(QCFTagArgument(QStringLiteral("onKeyUp")));
    args.append(QCFTagArgument(QStringLiteral("onMouseDown")));
    args.append(QCFTagArgument(QStringLiteral("onMouseUp")));
    args.append(QCFTagArgument(QStringLiteral("onValidate")));
    args.append(QCFTagArgument(QStringLiteral("pattern")));
    args.append(QCFTagArgument(QStringLiteral("range")));
    args.append(QCFTagArgument(QStringLiteral("required")));
    args.append(QCFTagArgument(QStringLiteral("richtext")));
    args.append(QCFTagArgument(QStringLiteral("skin")));
    args.append(QCFTagArgument(QStringLiteral("sourceForToolTip")));
    args.append(QCFTagArgument(QStringLiteral("style")));
    args.append(QCFTagArgument(QStringLiteral("stylesXML")));
    args.append(QCFTagArgument(QStringLiteral("templatesXML")));
    args.append(QCFTagArgument(QStringLiteral("toolbar")));
    args.append(QCFTagArgument(QStringLiteral("toolbarOnFocus")));
    args.append(QCFTagArgument(QStringLiteral("tooltip")));
    args.append(QCFTagArgument(QStringLiteral("validate")));
    args.append(QCFTagArgument(QStringLiteral("validateAt")));
    args.append(QCFTagArgument(QStringLiteral("value")));
    args.append(QCFTagArgument(QStringLiteral("visible")));
    args.append(QCFTagArgument(QStringLiteral("width")));
    args.append(QCFTagArgument(QStringLiteral("wrap")));
    ret[QStringLiteral("cftextarea")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cftextinput"), QCFTag(QStringLiteral("cftextinput"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfthread"), QCFTag(QStringLiteral("cfthread"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("action")));
    args.append(QCFTagArgument(QStringLiteral("duration")));
    args.append(QCFTagArgument(QStringLiteral("name")));
    args.append(QCFTagArgument(QStringLiteral("priority")));
    args.append(QCFTagArgument(QStringLiteral("timeout")));
    ret[QStringLiteral("cfthread")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfthrow"), QCFTag(QStringLiteral("cfthrow"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("detail")));
    args.append(QCFTagArgument(QStringLiteral("errorCode")));
    args.append(QCFTagArgument(QStringLiteral("extendedInfo")));
    args.append(QCFTagArgument(QStringLiteral("message")));
    ret[QStringLiteral("cfthrow")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cftimer"), QCFTag(QStringLiteral("cftimer"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("label"), false, QCFTagArgument::TypeConstantString));
    ret[QStringLiteral("cftimer")].m_ArgumentVariants.append(args);
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("label"), false, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument(QStringLiteral("type"), false, QCFTagArgument::TypeConstantString, QStringLiteral("inline")));
    ret[QStringLiteral("cftimer")].m_ArgumentVariants.append(args);
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("label"), false, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument(QStringLiteral("type"), false, QCFTagArgument::TypeConstantString, QStringLiteral("outline")));
    ret[QStringLiteral("cftimer")].m_ArgumentVariants.append(args);
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("label"), false, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument(QStringLiteral("type"), false, QCFTagArgument::TypeConstantString, QStringLiteral("comment")));
    ret[QStringLiteral("cftimer")].m_ArgumentVariants.append(args);
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("label"), false, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument(QStringLiteral("type"), false, QCFTagArgument::TypeConstantString, QStringLiteral("debug")));
    ret[QStringLiteral("cftimer")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cftooltip"), QCFTag(QStringLiteral("cftooltip"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cftrace"), QCFTag(QStringLiteral("cftrace"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("abort")));
    args.append(QCFTagArgument(QStringLiteral("category")));
    args.append(QCFTagArgument(QStringLiteral("inline")));
    args.append(QCFTagArgument(QStringLiteral("text")));
    ret[QStringLiteral("cftrace")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cftransaction"), QCFTag(QStringLiteral("cftransaction"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cftree"), QCFTag(QStringLiteral("cftree"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cftreeitem"), QCFTag(QStringLiteral("cftreeitem"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cftry"), QCFTag(QStringLiteral("cftry"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfupdate"), QCFTag(QStringLiteral("cfupdate"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

    ret.insert(QStringLiteral("cfwddx"), QCFTag(QStringLiteral("cfwddx"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true, QCFTagArgument::TypeConstantString, QStringLiteral("cfml2wddx")));
    args.append(QCFTagArgument(QStringLiteral("input"), true));
    args.append(QCFTagArgument(QStringLiteral("output"), false));
    args.append(QCFTagArgument(QStringLiteral("useTimeZoneInfo"), false));
    ret[QStringLiteral("cfwddx")].m_ArgumentVariants.append(args);
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true, QCFTagArgument::TypeConstantString, QStringLiteral("wddx2cfml")));
    args.append(QCFTagArgument(QStringLiteral("input"), true));
    args.append(QCFTagArgument(QStringLiteral("output"), true));
    args.append(QCFTagArgument(QStringLiteral("validate"), false));
    ret[QStringLiteral("cfwddx")].m_ArgumentVariants.append(args);
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true, QCFTagArgument::TypeConstantString, QStringLiteral("cfml2js")));
    args.append(QCFTagArgument(QStringLiteral("input"), true));
    args.append(QCFTagArgument(QStringLiteral("output"), false));
    args.append(QCFTagArgument(QStringLiteral("topLevelVariable"), true));
    ret[QStringLiteral("cfwddx")].m_ArgumentVariants.append(args);
    args.clear();
    args.append(QCFTagArgument(QStringLiteral("name"), true, QCFTagArgument::TypeConstantString, QStringLiteral("wddx2js")));
    args.append(QCFTagArgument(QStringLiteral("input"), true));
    args.append(QCFTagArgument(QStringLiteral("output"), false));
    args.append(QCFTagArgument(QStringLiteral("topLevelVariable"), true));
    args.append(QCFTagArgument(QStringLiteral("validate"), false));
    ret[QStringLiteral("cfwddx")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfwindow"), QCFTag(QStringLiteral("cfwindow"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfxml"), QCFTag(QStringLiteral("cfxml"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
    args.append(QCFTagArgument(QStringLiteral("variable"), true));
    args.append(QCFTagArgument(QStringLiteral("caseSensitive")));
    ret[QStringLiteral("cfxml")].m_ArgumentVariants.append(args);

	ret.insert(QStringLiteral("cfzip"), QCFTag(QStringLiteral("cfzip"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert(QStringLiteral("cfzipparam"), QCFTag(QStringLiteral("cfzipparam"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	return ret;
}

QHash<QString, QCFFunction> QCF8::generateCFFunctions()
{
	QHash<QString, QCFFunction> ret;

	ret.insert(QStringLiteral("abs"), QCFFunction("Abs", QCFFunction::ReturnDouble));
    ret[QStringLiteral("abs")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDouble, true));

	ret.insert(QStringLiteral("acos"), QCFFunction("ACos", QCFFunction::ReturnDouble));
    ret[QStringLiteral("acos")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDouble, true));

    ret.insert(QStringLiteral("addsoaprequestheader"), QCFFunction("AddSOAPRequestHeader", QCFFunction::ReturnVoid));
    ret[QStringLiteral("addsoaprequestheader")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("addsoaprequestheader")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true));
    ret[QStringLiteral("addsoaprequestheader")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true));
    ret[QStringLiteral("addsoaprequestheader")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true));
    ret[QStringLiteral("addsoaprequestheader")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBool, false));

    ret.insert(QStringLiteral("addsoapresponseheader"), QCFFunction("AddSOAPResponseHeader", QCFFunction::ReturnVoid));
    ret[QStringLiteral("addsoapresponseheader")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true));
    ret[QStringLiteral("addsoapresponseheader")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true));
    ret[QStringLiteral("addsoapresponseheader")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true));
    ret[QStringLiteral("addsoapresponseheader")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBool, false));

    ret.insert(QStringLiteral("ajaxlink"), QCFFunction("AjaxLink", QCFFunction::ReturnString));
    ret[QStringLiteral("ajaxlink")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true));

    ret.insert(QStringLiteral("ajaxonload"), QCFFunction("AjaxOnLoad", QCFFunction::ReturnVoid));
    ret[QStringLiteral("ajaxonload")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true));

	ret.insert(QStringLiteral("arrayappend"), QCFFunction("ArrayAppend", QCFFunction::ReturnBool));
    ret[QStringLiteral("arrayappend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("arrayappend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeAny, true));

	ret.insert(QStringLiteral("arrayavg"), QCFFunction("ArrayAvg", QCFFunction::ReturnDouble));
    ret[QStringLiteral("arrayavg")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

	ret.insert(QStringLiteral("arrayclear"), QCFFunction("ArrayClear", QCFFunction::ReturnBool));
    ret[QStringLiteral("arrayclear")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

	ret.insert(QStringLiteral("arraydeleteat"), QCFFunction("ArrayDeleteAt", QCFFunction::ReturnBool));
    ret[QStringLiteral("arraydeleteat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("arraydeleteat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true));

    ret.insert(QStringLiteral("arrayinsertsat"), QCFFunction("ArrayInsertAt", QCFFunction::ReturnBool));
    ret[QStringLiteral("arrayinsertsat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("arrayinsertsat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("arrayinsertsat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeAny, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("arrayisdefined"), QCFFunction("ArrayIsDefined", QCFFunction::ReturnBool));
    ret[QStringLiteral("arrayisdefined")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("arrayisdefined")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("arrayisempty"), QCFFunction("ArrayIsEmpty", QCFFunction::ReturnBool));
    ret[QStringLiteral("arrayisempty")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    ret.insert(QStringLiteral("arraylen"), QCFFunction("ArrayLen", QCFFunction::ReturnBool));
    ret[QStringLiteral("arraylen")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    ret.insert(QStringLiteral("arraymax"), QCFFunction("ArrayMax", QCFFunction::ReturnDouble));
    ret[QStringLiteral("arraymax")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    ret.insert(QStringLiteral("arraymin"), QCFFunction("ArrayMin", QCFFunction::ReturnDouble));
    ret[QStringLiteral("arraymin")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    ret.insert(QStringLiteral("arraynew"), QCFFunction("ArrayNew", QCFFunction::ReturnQWDDX));
    ret[QStringLiteral("arraynew")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("arrayprepend"), QCFFunction("ArrayPrepend", QCFFunction::ReturnBool));
    ret[QStringLiteral("arrayprepend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("arrayprepend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeAny, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("arrayresize"), QCFFunction("ArrayResize", QCFFunction::ReturnBool));
    ret[QStringLiteral("arrayresize")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("arrayresize")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("arrayset"), QCFFunction("ArraySet", QCFFunction::ReturnBool));
    ret[QStringLiteral("arrayset")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("arrayset")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("arrayset")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("arrayset")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("arraysort"), QCFFunction("ArraySort", QCFFunction::ReturnBool));
    ret[QStringLiteral("arraysort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("arraysort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("arraysort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("arraysum"), QCFFunction("ArraySum", QCFFunction::ReturnDouble));
    ret[QStringLiteral("arraysum")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    ret.insert(QStringLiteral("arrayswap"), QCFFunction("ArraySwap", QCFFunction::ReturnBool));
    ret[QStringLiteral("arrayswap")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("arrayswap")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("arrayswap")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("arraytolist"), QCFFunction("ArrayToList", QCFFunction::ReturnString));
    ret[QStringLiteral("arraytolist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("arraytolist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("asc"), QCFFunction("Asc", QCFFunction::ReturnInt));
    ret[QStringLiteral("asc")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("asin"), QCFFunction("ASin", QCFFunction::ReturnDouble));
    ret[QStringLiteral("asin")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDouble, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("atn"), QCFFunction("Atn", QCFFunction::ReturnDouble));
    ret[QStringLiteral("atn")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDouble, true, QCFFunctionArgument::TypeAny));

    // AuthenticatedContext obsolete
    // AuthenticatedUser obsolete

    ret.insert(QStringLiteral("binarydecode"), QCFFunction("BinaryDecode", QCFFunction::ReturnBinary));
    ret[QStringLiteral("binarydecode")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("binarydecode")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("binaryencode"), QCFFunction("BinaryEncode", QCFFunction::ReturnString));
    ret[QStringLiteral("binaryencode")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBinary, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("binaryencode")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("bitand"), QCFFunction("BitAnd", QCFFunction::ReturnInt));
    ret[QStringLiteral("bitand")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("bitand")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("bitmaskclear"), QCFFunction("BitMaskClear", QCFFunction::ReturnInt));
    ret[QStringLiteral("bitmaskclear")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("bitmaskclear")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("bitmaskclear")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("bitmaskread"), QCFFunction("BitMaskRead", QCFFunction::ReturnInt));
    ret[QStringLiteral("bitmaskread")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("bitmaskread")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("bitmaskread")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("bitmaskset"), QCFFunction("BitMaskSet", QCFFunction::ReturnInt));
    ret[QStringLiteral("bitmaskset")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("bitmaskset")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("bitmaskset")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("bitmaskset")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("bitnot"), QCFFunction("BitNot", QCFFunction::ReturnInt));
    ret[QStringLiteral("bitnot")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("bitor"), QCFFunction("BitOr", QCFFunction::ReturnInt));
    ret[QStringLiteral("bitor")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("bitshln"), QCFFunction("BitSHLN", QCFFunction::ReturnInt));
    ret[QStringLiteral("bitshln")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("bitshln")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("bitshrn"), QCFFunction("BitSHRN", QCFFunction::ReturnInt));
    ret[QStringLiteral("bitshrn")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("bitshrn")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("bitxor"), QCFFunction("BitXor", QCFFunction::ReturnInt));
    ret[QStringLiteral("bitxor")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("bitxor")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("ceiling"), QCFFunction("Ceiling", QCFFunction::ReturnInt));
    ret[QStringLiteral("ceiling")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("charsetdecode"), QCFFunction("CharsetDecode", QCFFunction::ReturnBinary));
    ret[QStringLiteral("charsetdecode")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("charsetdecode")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("charsetencode"), QCFFunction("CharsetEncode", QCFFunction::ReturnString));
    ret[QStringLiteral("charsetdecode")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBinary, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("charsetdecode")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

	ret.insert(QStringLiteral("chr"), QCFFunction("Chr", QCFFunction::ReturnString));
    ret[QStringLiteral("chr")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("cjustify"), QCFFunction("CJustify", QCFFunction::ReturnString));
    ret[QStringLiteral("cjustify")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("cjustify")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("compare"), QCFFunction("Compare", QCFFunction::ReturnInt));
    ret[QStringLiteral("compare")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("compare")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("comparenocase"), QCFFunction("CompareNoCase", QCFFunction::ReturnInt));
    ret[QStringLiteral("comparenocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("comparenocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("cos"), QCFFunction("Cos", QCFFunction::ReturnDouble));
    ret[QStringLiteral("cos")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDouble, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("createdate"), QCFFunction("CreateDate", QCFFunction::ReturnDateTime));
    ret[QStringLiteral("createdate")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("createdate")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("createdate")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("createdatetime"), QCFFunction("CreateDateTime", QCFFunction::ReturnDateTime));
    ret[QStringLiteral("createdatetime")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("createdatetime")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("createdatetime")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("createdatetime")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("createdatetime")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("createdatetime")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("createobject"), QCFFunction("CreateObject", QCFFunction::ReturnQWDDX, true));
    ret[QStringLiteral("createobject")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeConstant));
    ret[QStringLiteral("createobject")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeConstant));

    ret.insert(QStringLiteral("createodbcdatetime"), QCFFunction("CreateODBCDateTime", QCFFunction::ReturnDateTime));
    ret[QStringLiteral("createodbcdatetime")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDateTime, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("createuuid"), QCFFunction("CreateUUID", QCFFunction::ReturnString));

    ret.insert(QStringLiteral("datecompare"), QCFFunction("DateCompare", QCFFunction::ReturnInt));
    ret[QStringLiteral("datecompare")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDateTime, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("datecompare")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDateTime, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("datecompare")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("dateformat"), QCFFunction("DateFormat", QCFFunction::ReturnString));
    ret[QStringLiteral("dateformat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("dateformat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("dateformat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("decrypt"), QCFFunction("Decrypt", QCFFunction::ReturnString));
    ret[QStringLiteral("decrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("decrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("decrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("decrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("decrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, false, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("decrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("duplicate"), QCFFunction("Duplicate", QCFFunction::ReturnQWDDX));
    ret[QStringLiteral("duplicate")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("encrypt"), QCFFunction("Encrypt", QCFFunction::ReturnString));
    ret[QStringLiteral("encrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("encrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("decrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("encrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("encrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, false, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("encrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("fileexists"), QCFFunction("FileExists", QCFFunction::ReturnBool));
    ret[QStringLiteral("fileexists")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("find"), QCFFunction("Find", QCFFunction::ReturnInt));
    ret[QStringLiteral("find")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("find")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("find")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("findnocase"), QCFFunction("FindNoCase", QCFFunction::ReturnInt));
    ret[QStringLiteral("findnocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("findnocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("findnocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("findoneof"), QCFFunction("FindOneOf", QCFFunction::ReturnInt));
    ret[QStringLiteral("findoneof")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("findoneof")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("findoneof")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("formatbasen"), QCFFunction("FormatBaseN", QCFFunction::ReturnString));
    ret[QStringLiteral("formatbasen")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("formatbasen")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("getclientvariableslist"), QCFFunction("GetClientVariablesList", QCFFunction::ReturnString));

	ret.insert(QStringLiteral("fix"), QCFFunction("Fix", QCFFunction::ReturnInt));
    ret[QStringLiteral("fix")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDouble, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("getbasetagdata"), QCFFunction("GetBaseTagData", QCFFunction::ReturnQWDDX, true));
    ret[QStringLiteral("getbasetagdata")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("getbasetagdata")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("getbasetaglist"), QCFFunction("GetBaseTagList", QCFFunction::ReturnString, true));

    ret.insert(QStringLiteral("int"), QCFFunction("Int", QCFFunction::ReturnString));
    ret[QStringLiteral("int")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDouble, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("isarray"), QCFFunction("IsArray", QCFFunction::ReturnBool));
    ret[QStringLiteral("isarray")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("isarray")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("isdefined"), QCFFunction("IsDefined", QCFFunction::ReturnBool, true));
    ret[QStringLiteral("isdefined")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("isstruct"), QCFFunction("IsStruct", QCFFunction::ReturnBool));
    ret[QStringLiteral("isstruct")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    ret.insert(QStringLiteral("isquery"), QCFFunction("IsQuery", QCFFunction::ReturnBool));
    ret[QStringLiteral("isquery")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

	ret.insert(QStringLiteral("lcase"), QCFFunction("LCase", QCFFunction::ReturnString));
    ret[QStringLiteral("lcase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

	ret.insert(QStringLiteral("left"), QCFFunction("Left", QCFFunction::ReturnString));
    ret[QStringLiteral("left")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("left")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

	ret.insert(QStringLiteral("len"), QCFFunction("Len", QCFFunction::ReturnInt));
    ret[QStringLiteral("len")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listappend"), QCFFunction("ListAppend", QCFFunction::ReturnString));
    ret[QStringLiteral("listappend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listappend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listappend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listchangedelims"), QCFFunction("ListChangeDelims", QCFFunction::ReturnString));
    ret[QStringLiteral("listchangedelims")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listchangedelims")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listchangedelims")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listcontains"), QCFFunction("ListContains", QCFFunction::ReturnString));
    ret[QStringLiteral("listcontains")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listcontains")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listcontains")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listcontainsnocase"), QCFFunction("ListContainsNoCase", QCFFunction::ReturnString));
    ret[QStringLiteral("listcontainsnocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listcontainsnocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listcontainsnocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listdeleteat"), QCFFunction("ListDeleteAt", QCFFunction::ReturnString));
    ret[QStringLiteral("listdeleteat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listdeleteat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listdeleteat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listfind"), QCFFunction("ListFind", QCFFunction::ReturnInt));
    ret[QStringLiteral("listfind")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listfind")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listfind")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listfindnocase"), QCFFunction("ListFindNoCase", QCFFunction::ReturnInt));
    ret[QStringLiteral("listfindnocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listfindnocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listfindnocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listfirst"), QCFFunction("ListFirst", QCFFunction::ReturnString));
    ret[QStringLiteral("listfirst")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listfirst")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listgetat"), QCFFunction("ListGetAt", QCFFunction::ReturnString));
    ret[QStringLiteral("listgetat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listgetat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listgetat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listinsertat"), QCFFunction("ListInsertAt", QCFFunction::ReturnString));
    ret[QStringLiteral("listinsertat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listinsertat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listinsertat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listinsertat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listlast"), QCFFunction("ListLast", QCFFunction::ReturnString));
    ret[QStringLiteral("listlast")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listlast")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listlen"), QCFFunction("ListLen", QCFFunction::ReturnInt));
    ret[QStringLiteral("listlen")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listlen")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listprepend"), QCFFunction("ListPrepend", QCFFunction::ReturnString));
    ret[QStringLiteral("listprepend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listprepend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listprepend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listqualify"), QCFFunction("ListQualify", QCFFunction::ReturnString));
    ret[QStringLiteral("listqualify")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listqualify")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listqualify")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listqualify")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listrest"), QCFFunction("ListRest", QCFFunction::ReturnString));
    ret[QStringLiteral("listrest")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listrest")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listsetat"), QCFFunction("ListSetAt", QCFFunction::ReturnString));
    ret[QStringLiteral("listsetat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listsetat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listsetat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listsetat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listsort"), QCFFunction("ListSort", QCFFunction::ReturnString));
    ret[QStringLiteral("listsort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listsort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listsort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listsort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listvaluecount"), QCFFunction("ListValueCount", QCFFunction::ReturnInt));
    ret[QStringLiteral("listvaluecount")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listvaluecount")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listvaluecount")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listvaluecountnocount"), QCFFunction("ListValueCountNoCase", QCFFunction::ReturnInt));
    ret[QStringLiteral("listvaluecountnocount")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listvaluecountnocount")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listvaluecountnocount")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("listtoarray"), QCFFunction("ListToArray", QCFFunction::ReturnQWDDX));
    ret[QStringLiteral("listtoarray")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listtoarray")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("listtoarray")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBool, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("now"), QCFFunction("Now", QCFFunction::ReturnDateTime));

    ret.insert(QStringLiteral("queryaddrow"), QCFFunction("QueryAddRow", QCFFunction::ReturnInt));
    ret[QStringLiteral("queryaddrow")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("queryaddrow")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("querynew"), QCFFunction("QueryNew", QCFFunction::ReturnQWDDX));
    ret[QStringLiteral("querynew")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("querynew")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("quotedvaluelist"), QCFFunction("QuotedValueList", QCFFunction::ReturnString));
    ret[QStringLiteral("quotedvaluelist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("quotedvaluelist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("queryaddcolumn"), QCFFunction("QueryAddColumn", QCFFunction::ReturnInt));
    ret[QStringLiteral("queryaddcolumn")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("queryaddcolumn")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("queryaddcolumn")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("queryaddcolumn")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("queryconvertforgrid"), QCFFunction("QueryConvertForGrid", QCFFunction::ReturnQWDDX));
    ret[QStringLiteral("queryconvertforgrid")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("queryconvertforgrid")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("queryconvertforgrid")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("querysetcell"), QCFFunction("QuerySetCell", QCFFunction::ReturnBool));
    ret[QStringLiteral("querysetcell")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("querysetcell")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("querysetcell")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("querysetcell")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("quotedvalue"), QCFFunction("QuotedValue", QCFFunction::ReturnString));
    ret[QStringLiteral("quotedvalue")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("quotedvalue")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("replace"), QCFFunction("Replace", QCFFunction::ReturnString));
    ret[QStringLiteral("replace")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("replace")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("replace")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("replace")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("replacelist"), QCFFunction("ReplaceList", QCFFunction::ReturnString));
    ret[QStringLiteral("replacelist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("replacelist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("replacelist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("reverse"), QCFFunction("Reverse", QCFFunction::ReturnString));
    ret[QStringLiteral("reverse")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("right"), QCFFunction("Right", QCFFunction::ReturnString));
    ret[QStringLiteral("right")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("right")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("structappend"), QCFFunction("StructAppend", QCFFunction::ReturnBool));
    ret[QStringLiteral("structappend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("structappend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("structappend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBool, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("structclear"), QCFFunction("StructClear", QCFFunction::ReturnBool));
    ret[QStringLiteral("structappend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    ret.insert(QStringLiteral("structcopy"), QCFFunction("StructCopy", QCFFunction::ReturnQWDDX));
    ret[QStringLiteral("structcopy")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    ret.insert(QStringLiteral("structcount"), QCFFunction("StructCount", QCFFunction::ReturnInt));
    ret[QStringLiteral("structcount")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    ret.insert(QStringLiteral("structdelete"), QCFFunction("StructDelete", QCFFunction::ReturnBool));
    ret[QStringLiteral("structdelete")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("structdelete")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("structdelete")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBool, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("structfind"), QCFFunction("StructFind", QCFFunction::ReturnQWDDX));
    ret[QStringLiteral("structfind")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("structfind")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("structfindkey"), QCFFunction("StructFindKey", QCFFunction::ReturnQWDDX));
    ret[QStringLiteral("structfind")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("structfind")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("structfind")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("structfindvalue"), QCFFunction("StructFindValue", QCFFunction::ReturnQWDDX));
    ret[QStringLiteral("structfindvalue")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("structfindvalue")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("structfindvalue")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("structget"), QCFFunction("StructGet", QCFFunction::ReturnQWDDX));
    ret[QStringLiteral("structget")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("structinsert"), QCFFunction("StructInsert", QCFFunction::ReturnBool));
    ret[QStringLiteral("structinsert")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("structinsert")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("structinsert")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("structdelete")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBool, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("structisempty"), QCFFunction("StructIsEmpty", QCFFunction::ReturnBool));
    ret[QStringLiteral("structisempty")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    ret.insert(QStringLiteral("structkeyarray"), QCFFunction("StructKeyArray", QCFFunction::ReturnQWDDX));
    ret[QStringLiteral("structkeyarray")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    ret.insert(QStringLiteral("structkeyexists"), QCFFunction("StructKeyExists", QCFFunction::ReturnBool));
    ret[QStringLiteral("structkeyexists")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("structkeyexists")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("structkeylist"), QCFFunction("StructKeyList", QCFFunction::ReturnBool));
    ret[QStringLiteral("structkeylist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("structkeylist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("structnew"), QCFFunction("StructNew", QCFFunction::ReturnQWDDX));

    ret.insert(QStringLiteral("structsort"), QCFFunction("StructSort", QCFFunction::ReturnQWDDX));
    ret[QStringLiteral("structsort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("structsort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("structsort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("structsort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("structupdate"), QCFFunction("StructUpdate", QCFFunction::ReturnBool));
    ret[QStringLiteral("structupdate")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("structupdate")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeVariable));
    ret[QStringLiteral("structupdate")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    ret.insert(QStringLiteral("timeformat"), QCFFunction("TimeFormat", QCFFunction::ReturnString));
    ret[QStringLiteral("timeformat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDateTime, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("timeformat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("trim"), QCFFunction("Trim", QCFFunction::ReturnString));
    ret[QStringLiteral("trim")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("ucase"), QCFFunction("UCase", QCFFunction::ReturnString));
    ret[QStringLiteral("ucase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("val"), QCFFunction("Val", QCFFunction::ReturnDouble));
    ret[QStringLiteral("val")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("valuelist"), QCFFunction("ValueList", QCFFunction::ReturnString));
    ret[QStringLiteral("valuelist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeAny));
    ret[QStringLiteral("valuelist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert(QStringLiteral("writeoutput"), QCFFunction("WriteOutput", QCFFunction::ReturnVoid, true));
    ret[QStringLiteral("writeoutput")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    return ret;
}
