#include "qcf8.h"
#include "qcftag.h"
#include "qcffunction.h"

#include <QString>
#include <QHash>


QHash<QString, QCFTag> QCF8::m_generateCFTags;
QHash<QString, QCFFunction> QCF8::m_generateCFFunctions;

const QHash<QString, QCFTag> & QCF8::generateCFTags()
{
    if (m_generateCFTags.count() == 0)
    {
        QList<QCFTagArgument> args;

        m_generateCFTags.reserve(300);

        m_generateCFTags.insert(QStringLiteral("cfabort"), QCFTag(QStringLiteral("cfabort"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("showError")));
        m_generateCFTags[QStringLiteral("cfabort")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfadmin"), QCFTag(QStringLiteral("cfadmin"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments, QCFTag::WithoutExpressionInside, true)); // Railo cftag

        m_generateCFTags.insert(QStringLiteral("cfajaximport"), QCFTag(QStringLiteral("cfajaximport"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("cssSrc")));
        args.append(QCFTagArgument(QStringLiteral("params")));
        args.append(QCFTagArgument(QStringLiteral("scriptSrc")));
        args.append(QCFTagArgument(QStringLiteral("tags")));
        m_generateCFTags[QStringLiteral("cfajaximport")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfajaxproxy"), QCFTag(QStringLiteral("cfajaxproxy"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("bind"), true));
        args.append(QCFTagArgument(QStringLiteral("jsclassname")));
        args.append(QCFTagArgument(QStringLiteral("onError")));
        args.append(QCFTagArgument(QStringLiteral("onSuccess")));
        m_generateCFTags[QStringLiteral("cfajaxproxy")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("cfc"), true));
        args.append(QCFTagArgument(QStringLiteral("jsclassname")));
        args.append(QCFTagArgument(QStringLiteral("onError")));
        args.append(QCFTagArgument(QStringLiteral("onSuccess")));
        m_generateCFTags[QStringLiteral("cfajaxproxy")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfapplet"), QCFTag(QStringLiteral("cfapplet"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cfapplet")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfapplication"), QCFTag(QStringLiteral("cfapplication"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cfapplication")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfargument"), QCFTag(QStringLiteral("cfargument"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("name"), true));
        args.append(QCFTagArgument(QStringLiteral("default")));
        args.append(QCFTagArgument(QStringLiteral("displayname")));
        args.append(QCFTagArgument(QStringLiteral("hint")));
        args.append(QCFTagArgument(QStringLiteral("required")));
        args.append(QCFTagArgument(QStringLiteral("type")));
        m_generateCFTags[QStringLiteral("cfargument")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfassociate"), QCFTag(QStringLiteral("cfassociate"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("baseTag"), true));
        args.append(QCFTagArgument(QStringLiteral("dataCollection")));
        m_generateCFTags[QStringLiteral("cfassociate")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfbreak"), QCFTag(QStringLiteral("cfbreak"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfcache"), QCFTag(QStringLiteral("cfcache"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("action")));
        args.append(QCFTagArgument(QStringLiteral("directory")));
        args.append(QCFTagArgument(QStringLiteral("expireURL")));
        args.append(QCFTagArgument(QStringLiteral("password")));
        args.append(QCFTagArgument(QStringLiteral("port")));
        args.append(QCFTagArgument(QStringLiteral("protocol")));
        args.append(QCFTagArgument(QStringLiteral("timespan")));
        args.append(QCFTagArgument(QStringLiteral("username")));
        m_generateCFTags[QStringLiteral("cfcache")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfcalendar"), QCFTag(QStringLiteral("cfcalendar"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cfcalendar")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfcase"), QCFTag(QStringLiteral("cfcase"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("value"), true));
        args.append(QCFTagArgument(QStringLiteral("delimiters")));
        m_generateCFTags[QStringLiteral("cfcase")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfcatch"), QCFTag(QStringLiteral("cfcatch"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("type")));
        m_generateCFTags[QStringLiteral("cfcatch")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfchart"), QCFTag(QStringLiteral("cfchart"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cfchart")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfchartdata"), QCFTag(QStringLiteral("cfchartdata"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("item"), true));
        args.append(QCFTagArgument(QStringLiteral("value"), true));
        m_generateCFTags[QStringLiteral("cfchartdata")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfchartseries"), QCFTag(QStringLiteral("cfchartseries"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cfchartseries")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfcol"), QCFTag(QStringLiteral("cfcol"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfcollection"), QCFTag(QStringLiteral("cfcollection"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("action"), true));
        args.append(QCFTagArgument(QStringLiteral("categories")));
        args.append(QCFTagArgument(QStringLiteral("collection")));
        args.append(QCFTagArgument(QStringLiteral("language")));
        args.append(QCFTagArgument(QStringLiteral("name")));
        args.append(QCFTagArgument(QStringLiteral("path")));
        m_generateCFTags[QStringLiteral("cfcollection")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfcomponent"), QCFTag(QStringLiteral("cfcomponent"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cfcomponent")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfcontent"), QCFTag(QStringLiteral("cfcontent"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("deleteFile"), false));
        args.append(QCFTagArgument(QStringLiteral("file"), false));
        args.append(QCFTagArgument(QStringLiteral("reset"), false));
        args.append(QCFTagArgument(QStringLiteral("type"), false));
        args.append(QCFTagArgument(QStringLiteral("variable"), false));
        m_generateCFTags[QStringLiteral("cfcontent")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfcookie"), QCFTag(QStringLiteral("cfcookie"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("name"), true));
        args.append(QCFTagArgument(QStringLiteral("domain"), false));
        args.append(QCFTagArgument(QStringLiteral("expires"), false));
        args.append(QCFTagArgument(QStringLiteral("path"), false));
        args.append(QCFTagArgument(QStringLiteral("secure"), false));
        args.append(QCFTagArgument(QStringLiteral("value"), false));
        m_generateCFTags[QStringLiteral("cfcookie")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfdbinfo"), QCFTag(QStringLiteral("cfdbinfo"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfdefaultcase"), QCFTag(QStringLiteral("cfdefaultcase"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfdirectory"), QCFTag(QStringLiteral("cfdirectory"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("directory"), true));
        args.append(QCFTagArgument(QStringLiteral("action"), false, QCFTagArgument::TypeConstantString, QStringLiteral("list")));
        args.append(QCFTagArgument(QStringLiteral("filter"), false));
        args.append(QCFTagArgument(QStringLiteral("listinfo"), false, QCFTagArgument::TypeConstantString));
        m_generateCFTags[QStringLiteral("cfdirectory")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfdiv"), QCFTag(QStringLiteral("cfdiv"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfdocument"), QCFTag(QStringLiteral("cfdocument"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cfdocument")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfdocumentitem"), QCFTag(QStringLiteral("cfdocumentitem"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("type"), true));
        m_generateCFTags[QStringLiteral("cfdocumentitem")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfdocumentsection"), QCFTag(QStringLiteral("cfdocumentsection"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cfdocumentsection")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfdump"), QCFTag(QStringLiteral("cfdump"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("var"), true));
        m_generateCFTags[QStringLiteral("cfdump")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfelse"), QCFTag(QStringLiteral("cfelse"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeExpression));

        m_generateCFTags.insert(QStringLiteral("cfelseif"), QCFTag(QStringLiteral("cfelseif"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeExpression));

        m_generateCFTags.insert(QStringLiteral("cferror"), QCFTag(QStringLiteral("cferror"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("template"), true));
        args.append(QCFTagArgument(QStringLiteral("type"), true));
        args.append(QCFTagArgument(QStringLiteral("exception")));
        args.append(QCFTagArgument(QStringLiteral("mailTo")));
        m_generateCFTags[QStringLiteral("cferror")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfexchangecalendar"), QCFTag(QStringLiteral("cfexchangecalendar"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfexchangeconnection"), QCFTag(QStringLiteral("cfexchangeconnection"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfexchangecontact"), QCFTag(QStringLiteral("cfexchangecontact"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfexchangefilter"), QCFTag(QStringLiteral("cfexchangefilter"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfexchangemail"), QCFTag(QStringLiteral("cfexchangemail"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfexchangetask"), QCFTag(QStringLiteral("cfexchangetask"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfexecute"), QCFTag(QStringLiteral("cfexecute"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("name"), true));
        args.append(QCFTagArgument(QStringLiteral("arguments")));
        args.append(QCFTagArgument(QStringLiteral("outputFile")));
        args.append(QCFTagArgument(QStringLiteral("timeout")));
        args.append(QCFTagArgument(QStringLiteral("variable")));
        m_generateCFTags[QStringLiteral("cfexecute")].m_ArgumentVariants.append(args);


        m_generateCFTags.insert(QStringLiteral("cfexit"), QCFTag(QStringLiteral("cfexit"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("method"), false, QCFTagArgument::TypeConstantString));
        m_generateCFTags[QStringLiteral("cfexit")].m_ArgumentVariants.append(args);

        //ret.insert(QStringLiteral("cffeed"), QCFTag("cffeed"));

        m_generateCFTags.insert(QStringLiteral("cffile"), QCFTag(QStringLiteral("cffile"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("append")));
        args.append(QCFTagArgument(QStringLiteral("file"), true));
        args.append(QCFTagArgument(QStringLiteral("output"), true));
        args.append(QCFTagArgument(QStringLiteral("addNewLine")));
        args.append(QCFTagArgument(QStringLiteral("attributes")));
        args.append(QCFTagArgument(QStringLiteral("charset")));
        args.append(QCFTagArgument(QStringLiteral("fixnewline")));
        args.append(QCFTagArgument(QStringLiteral("mode")));
        m_generateCFTags[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("copy")));
        args.append(QCFTagArgument(QStringLiteral("destination"), true));
        args.append(QCFTagArgument(QStringLiteral("source"), true));
        args.append(QCFTagArgument(QStringLiteral("attributes")));
        args.append(QCFTagArgument(QStringLiteral("mode")));
        m_generateCFTags[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("delete")));
        args.append(QCFTagArgument(QStringLiteral("file"), true));
        m_generateCFTags[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("delete")));
        args.append(QCFTagArgument(QStringLiteral("file"), true));
        m_generateCFTags[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("move")));
        args.append(QCFTagArgument(QStringLiteral("destination"), true));
        args.append(QCFTagArgument(QStringLiteral("source"), true));
        args.append(QCFTagArgument(QStringLiteral("attributes")));
        args.append(QCFTagArgument(QStringLiteral("charset")));
        args.append(QCFTagArgument(QStringLiteral("mode")));
        m_generateCFTags[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("read")));
        args.append(QCFTagArgument(QStringLiteral("file"), true));
        args.append(QCFTagArgument(QStringLiteral("variable"), true));
        args.append(QCFTagArgument(QStringLiteral("charset")));
        m_generateCFTags[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("readBinary")));
        args.append(QCFTagArgument(QStringLiteral("file"), true));
        args.append(QCFTagArgument(QStringLiteral("variable"), true));
        m_generateCFTags[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("rename")));
        args.append(QCFTagArgument(QStringLiteral("destination"), true));
        args.append(QCFTagArgument(QStringLiteral("source"), true));
        args.append(QCFTagArgument(QStringLiteral("attributes")));
        args.append(QCFTagArgument(QStringLiteral("mode")));
        m_generateCFTags[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("upload")));
        args.append(QCFTagArgument(QStringLiteral("destination"), true));
        args.append(QCFTagArgument(QStringLiteral("fileField"), true));
        args.append(QCFTagArgument(QStringLiteral("accept")));
        args.append(QCFTagArgument(QStringLiteral("attributes")));
        args.append(QCFTagArgument(QStringLiteral("mode")));
        args.append(QCFTagArgument(QStringLiteral("nameConflict")));
        args.append(QCFTagArgument(QStringLiteral("result")));
        m_generateCFTags[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("uploadAll")));
        args.append(QCFTagArgument(QStringLiteral("destination"), true));
        args.append(QCFTagArgument(QStringLiteral("accept")));
        args.append(QCFTagArgument(QStringLiteral("attributes")));
        args.append(QCFTagArgument(QStringLiteral("mode")));
        args.append(QCFTagArgument(QStringLiteral("nameConflict")));
        args.append(QCFTagArgument(QStringLiteral("result")));
        m_generateCFTags[QStringLiteral("cffile")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("action"), true, QCFTagArgument::TypeConstantString, QStringLiteral("write")));
        args.append(QCFTagArgument(QStringLiteral("file"), true));
        args.append(QCFTagArgument(QStringLiteral("output"), true));
        args.append(QCFTagArgument(QStringLiteral("addNewLine")));
        args.append(QCFTagArgument(QStringLiteral("attributes")));
        args.append(QCFTagArgument(QStringLiteral("charset")));
        args.append(QCFTagArgument(QStringLiteral("result")));
        args.append(QCFTagArgument(QStringLiteral("mode")));
        m_generateCFTags[QStringLiteral("cffile")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cffinally"), QCFTag(QStringLiteral("cffinally"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfflush"), QCFTag(QStringLiteral("cfflush"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("interval")));
        m_generateCFTags[QStringLiteral("cfflush")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfform"), QCFTag(QStringLiteral("cfform"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cfform")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfformgroup"), QCFTag(QStringLiteral("cfformgroup"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cfformgroup")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfformitem"), QCFTag(QStringLiteral("cfformitem"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfftp"), QCFTag(QStringLiteral("cfftp"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cfftp")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cffunction"), QCFTag(QStringLiteral("cffunction"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cffunction")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfgraph"), QCFTag(QStringLiteral("cfgraph"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfgraphdata"), QCFTag(QStringLiteral("cfgraphdata"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfgrid"), QCFTag(QStringLiteral("cfgrid"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cfgrid")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfgridcolumn"), QCFTag(QStringLiteral("cfgridcolumn"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cfgridcolumn")].m_ArgumentVariants.append(args);
        args.clear();

        m_generateCFTags.insert(QStringLiteral("cfgridrow"), QCFTag(QStringLiteral("cfgridrow"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("data"), true));
        m_generateCFTags[QStringLiteral("cfgridrow")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfgridupdate"), QCFTag(QStringLiteral("cfgridupdate"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfheader"), QCFTag(QStringLiteral("cfheader"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("charset"), false, QCFTagArgument::TypeConstantString));
        args.append(QCFTagArgument(QStringLiteral("name"), true, QCFTagArgument::TypeConstantString));
        args.append(QCFTagArgument(QStringLiteral("value")));
        m_generateCFTags[QStringLiteral("cfheader")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("charset"), false, QCFTagArgument::TypeConstantString));
        args.append(QCFTagArgument(QStringLiteral("statusCode"), true));
        args.append(QCFTagArgument(QStringLiteral("statusText")));
        args.append(QCFTagArgument(QStringLiteral("value")));
        m_generateCFTags[QStringLiteral("cfheader")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfhtmlhead"), QCFTag(QStringLiteral("cfhtmlhead"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.append(QCFTagArgument(QStringLiteral("text"), true));
        m_generateCFTags[QStringLiteral("cfhtmlhead")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfhttp"), QCFTag(QStringLiteral("cfhttp"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cfhttp")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfhttpparam"), QCFTag(QStringLiteral("cfhttpparam"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear(); // TODO: Make this argument as it should.
        args.append(QCFTagArgument(QStringLiteral("type"), true));
        args.append(QCFTagArgument(QStringLiteral("encoded")));
        args.append(QCFTagArgument(QStringLiteral("file")));
        args.append(QCFTagArgument(QStringLiteral("mimeType")));
        args.append(QCFTagArgument(QStringLiteral("name")));
        args.append(QCFTagArgument(QStringLiteral("value")));
        m_generateCFTags[QStringLiteral("cfhttpparam")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfif"), QCFTag(QStringLiteral("cfif"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeExpression));

        m_generateCFTags.insert(QStringLiteral("cfimage"), QCFTag(QStringLiteral("cfimage"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfimpersonate"), QCFTag(QStringLiteral("cfimpersonate"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfimport"), QCFTag(QStringLiteral("cfimport"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("taglib"), true, QCFTagArgument::TypeConstantString));
        args.append(QCFTagArgument(QStringLiteral("prefix"), true, QCFTagArgument::TypeConstantString));
        m_generateCFTags[QStringLiteral("cfimport")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfinclude"), QCFTag(QStringLiteral("cfinclude"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("template"), true));
        m_generateCFTags[QStringLiteral("cfinclude")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfindex"), QCFTag(QStringLiteral("cfindex"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cfindex")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfinput"), QCFTag(QStringLiteral("cfinput"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cfinput")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfinsert"), QCFTag(QStringLiteral("cfinsert"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfinterface"), QCFTag(QStringLiteral("cfinterface"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfinvoke"), QCFTag(QStringLiteral("cfinvoke"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("component"), true));
        args.append(QCFTagArgument(QStringLiteral("method"), true));
        args.append(QCFTagArgument(QStringLiteral("argumentCollection")));
        args.append(QCFTagArgument(QStringLiteral("password")));
        args.append(QCFTagArgument(QStringLiteral("returnVariable")));
        args.append(QCFTagArgument(QStringLiteral("username")));
        m_generateCFTags[QStringLiteral("cfinvoke")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("method"), true));
        args.append(QCFTagArgument(QStringLiteral("argumentCollection")));
        args.append(QCFTagArgument(QStringLiteral("component")));
        args.append(QCFTagArgument(QStringLiteral("password")));
        args.append(QCFTagArgument(QStringLiteral("returnVariable")));
        args.append(QCFTagArgument(QStringLiteral("username")));
        m_generateCFTags[QStringLiteral("cfinvoke")].m_ArgumentVariants.append(args);
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
        m_generateCFTags[QStringLiteral("cfinvoke")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfinvokeargument"), QCFTag(QStringLiteral("cfinvokeargument"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("name"), true));
        args.append(QCFTagArgument(QStringLiteral("value"), true));
        args.append(QCFTagArgument(QStringLiteral("omit")));
        m_generateCFTags[QStringLiteral("cfinvokeargument")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cflayout"), QCFTag(QStringLiteral("cflayout"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cflayoutarea"), QCFTag(QStringLiteral("cflayoutarea"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfldap"), QCFTag(QStringLiteral("cfldap"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cflocation"), QCFTag(QStringLiteral("cflocation"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("url"), true));
        args.append(QCFTagArgument(QStringLiteral("addToken")));
        args.append(QCFTagArgument(QStringLiteral("statusCode")));
        m_generateCFTags[QStringLiteral("cflocation")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cflock"), QCFTag(QStringLiteral("cflock"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("timeout"), true));
        args.append(QCFTagArgument(QStringLiteral("name")));
        args.append(QCFTagArgument(QStringLiteral("scope")));
        args.append(QCFTagArgument(QStringLiteral("throwOnTimeout")));
        args.append(QCFTagArgument(QStringLiteral("type")));
        m_generateCFTags[QStringLiteral("cflock")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cflog"), QCFTag(QStringLiteral("cflog"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("text"), true));
        args.append(QCFTagArgument(QStringLiteral("application")));
        args.append(QCFTagArgument(QStringLiteral("file")));
        args.append(QCFTagArgument(QStringLiteral("log")));
        args.append(QCFTagArgument(QStringLiteral("type")));
        m_generateCFTags[QStringLiteral("cflog")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cflogin"), QCFTag(QStringLiteral("cflogin"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfloginuser"), QCFTag(QStringLiteral("cfloginuser"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("name"), true));
        args.append(QCFTagArgument(QStringLiteral("password"), true));
        args.append(QCFTagArgument(QStringLiteral("roles"), true));
        m_generateCFTags[QStringLiteral("cfloginuser")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cflogout"), QCFTag(QStringLiteral("cflogout"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfloop"), QCFTag(QStringLiteral("cfloop"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("index"), true, QCFTagArgument::TypeVariable));
        args.append(QCFTagArgument(QStringLiteral("from"), true, QCFTagArgument::TypeConstantString));
        args.append(QCFTagArgument(QStringLiteral("to"), true, QCFTagArgument::TypeConstantString));
        args.append(QCFTagArgument(QStringLiteral("step"), false, QCFTagArgument::TypeConstantString));
        m_generateCFTags[QStringLiteral("cfloop")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("condition"), true, QCFTagArgument::TypeExpression));
        m_generateCFTags[QStringLiteral("cfloop")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("query"), true, QCFTagArgument::TypeVariable));
        args.append(QCFTagArgument(QStringLiteral("startRow"), false, QCFTagArgument::TypeAny));
        args.append(QCFTagArgument(QStringLiteral("endRow"), false, QCFTagArgument::TypeAny));
        m_generateCFTags[QStringLiteral("cfloop")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("index"), true, QCFTagArgument::TypeVariable));
        args.append(QCFTagArgument(QStringLiteral("list"), true, QCFTagArgument::TypeVariable));
        args.append(QCFTagArgument(QStringLiteral("delimiters"), false, QCFTagArgument::TypeConstantString));
        m_generateCFTags[QStringLiteral("cfloop")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("index"), true, QCFTagArgument::TypeVariable));
        args.append(QCFTagArgument(QStringLiteral("file"), true));
        args.append(QCFTagArgument(QStringLiteral("characters")));
        m_generateCFTags[QStringLiteral("cfloop")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("index"), true, QCFTagArgument::TypeVariable));
        args.append(QCFTagArgument(QStringLiteral("array"), true));
        m_generateCFTags[QStringLiteral("cfloop")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("collection"), true));
        args.append(QCFTagArgument(QStringLiteral("item"), true));
        m_generateCFTags[QStringLiteral("cfloop")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfmail"), QCFTag(QStringLiteral("cfmail"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments, QCFTag::WithExpressionInside));
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
        m_generateCFTags[QStringLiteral("cfmail")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfmailparam"), QCFTag(QStringLiteral("cfmailparam"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfmailpart"), QCFTag(QStringLiteral("cfmailpart"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("type"), true));
        args.append(QCFTagArgument(QStringLiteral("charset")));
        args.append(QCFTagArgument(QStringLiteral("wraptext")));
        m_generateCFTags[QStringLiteral("cfmailpart")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfmenu"), QCFTag(QStringLiteral("cfmenu"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfmenuitem"), QCFTag(QStringLiteral("cfmenuitem"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfmodule"), QCFTag(QStringLiteral("cfmodule"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments, QCFTag::WithoutExpressionInside, true));

        m_generateCFTags.insert(QStringLiteral("cfNTauthenticate"), QCFTag(QStringLiteral("cfNTauthenticate"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfobject"), QCFTag(QStringLiteral("cfobject"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("component"), true));
        args.append(QCFTagArgument(QStringLiteral("name"), true));
        args.append(QCFTagArgument(QStringLiteral("type"), false, QCFTagArgument::TypeConstantString, QStringLiteral("component")));
        m_generateCFTags[QStringLiteral("cfobject")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfobjectcache"), QCFTag(QStringLiteral("cfobjectcache"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfoutput"), QCFTag(QStringLiteral("cfoutput"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments, QCFTag::WithExpressionInside));
        args.clear();
        m_generateCFTags[QStringLiteral("cfoutput")].m_ArgumentVariants.append(args);
        args.append(QCFTagArgument(QStringLiteral("query"), true));
        m_generateCFTags[QStringLiteral("cfoutput")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfparam"), QCFTag(QStringLiteral("cfparam"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("name"), true));
        args.append(QCFTagArgument(QStringLiteral("default")));
        args.append(QCFTagArgument(QStringLiteral("max")));
        args.append(QCFTagArgument(QStringLiteral("min")));
        args.append(QCFTagArgument(QStringLiteral("pattern")));
        args.append(QCFTagArgument(QStringLiteral("type")));
        m_generateCFTags[QStringLiteral("cfparam")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfpdf"), QCFTag(QStringLiteral("cfpdf"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfpdfform"), QCFTag(QStringLiteral("cfpdfform"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfpdfformparam"), QCFTag(QStringLiteral("cfpdfformparam"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfpdfparam"), QCFTag(QStringLiteral("cfpdfparam"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfpdfsubform"), QCFTag(QStringLiteral("cfpdfsubform"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfpod"), QCFTag(QStringLiteral("cfpod"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfpop"), QCFTag(QStringLiteral("cfpop"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfpresentation"), QCFTag(QStringLiteral("cfpresentation"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfpresentationslide"), QCFTag(QStringLiteral("cfpresentationslide"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfpresenter"), QCFTag(QStringLiteral("cfpresenter"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfprint"), QCFTag(QStringLiteral("cfprint"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfprocessingdirective"), QCFTag(QStringLiteral("cfprocessingdirective"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("pageEncoding")));
        args.append(QCFTagArgument(QStringLiteral("suppressWhiteSpace")));
        m_generateCFTags[QStringLiteral("cfprocessingdirective")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfprocparam"), QCFTag(QStringLiteral("cfprocparam"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("CFSQLType"), true));
        args.append(QCFTagArgument(QStringLiteral("maxLength")));
        args.append(QCFTagArgument(QStringLiteral("null")));
        args.append(QCFTagArgument(QStringLiteral("scale")));
        args.append(QCFTagArgument(QStringLiteral("type")));
        args.append(QCFTagArgument(QStringLiteral("value")));
        args.append(QCFTagArgument(QStringLiteral("variable")));
        m_generateCFTags[QStringLiteral("cfprocparam")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfprocresult"), QCFTag(QStringLiteral("cfprocresult"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("name"), true));
        args.append(QCFTagArgument(QStringLiteral("maxRows")));
        args.append(QCFTagArgument(QStringLiteral("resultSet")));
        m_generateCFTags[QStringLiteral("cfprocresult")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfproperty"), QCFTag(QStringLiteral("cfproperty"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("name"), true));
        args.append(QCFTagArgument(QStringLiteral("default")));
        args.append(QCFTagArgument(QStringLiteral("displayname")));
        args.append(QCFTagArgument(QStringLiteral("hint")));
        args.append(QCFTagArgument(QStringLiteral("required")));
        args.append(QCFTagArgument(QStringLiteral("type")));
        m_generateCFTags[QStringLiteral("cfproperty")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfquery"), QCFTag(QStringLiteral("cfquery"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments, QCFTag::WithExpressionInside));
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
        m_generateCFTags[QStringLiteral("cfquery")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfqueryparam"), QCFTag(QStringLiteral("cfqueryparam"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("value"), true));
        args.append(QCFTagArgument(QStringLiteral("CFSQLType")));
        args.append(QCFTagArgument(QStringLiteral("list")));
        args.append(QCFTagArgument(QStringLiteral("maxLength")));
        args.append(QCFTagArgument(QStringLiteral("null")));
        args.append(QCFTagArgument(QStringLiteral("scale")));
        args.append(QCFTagArgument(QStringLiteral("separator")));
        m_generateCFTags[QStringLiteral("cfqueryparam")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfregistry"), QCFTag(QStringLiteral("cfregistry"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfreport"), QCFTag(QStringLiteral("cfreport"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfreportparam"), QCFTag(QStringLiteral("cfreportparam"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfrethrow"), QCFTag(QStringLiteral("cfrethrow"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfreturn"), QCFTag(QStringLiteral("cfreturn"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeExpression));

        m_generateCFTags.insert(QStringLiteral("cfsavecontent"), QCFTag(QStringLiteral("cfsavecontent"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("variable")));
        m_generateCFTags[QStringLiteral("cfsavecontent")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfschedule"), QCFTag(QStringLiteral("cfschedule"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cfschedule")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfscript"), QCFTag(QStringLiteral("cfscript"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        m_generateCFTags[QStringLiteral("cfscript")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfsearch"), QCFTag(QStringLiteral("cfsearch"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cfsearch")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfselect"), QCFTag(QStringLiteral("cfselect"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        // TODO: more..
        m_generateCFTags[QStringLiteral("cfselect")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfservlet"), QCFTag(QStringLiteral("cfservlet"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfservletparam"), QCFTag(QStringLiteral("cfservletparam"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfset"), QCFTag(QStringLiteral("cfset"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeExpression));

        m_generateCFTags.insert(QStringLiteral("cfsetting"), QCFTag(QStringLiteral("cfsetting"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("enableCFoutputOnly")));
        args.append(QCFTagArgument(QStringLiteral("requestTimeout")));
        args.append(QCFTagArgument(QStringLiteral("showDebugOutput")));
        m_generateCFTags[QStringLiteral("cfsetting")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfsilent"), QCFTag(QStringLiteral("cfsilent"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfslider"), QCFTag(QStringLiteral("cfslider"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfsprydataset"), QCFTag(QStringLiteral("cfsprydataset"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfstoredproc"), QCFTag(QStringLiteral("cfstoredproc"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("dataSource"), true));
        args.append(QCFTagArgument(QStringLiteral("procedure"), true));
        args.append(QCFTagArgument(QStringLiteral("blockFactor")));
        args.append(QCFTagArgument(QStringLiteral("debug")));
        args.append(QCFTagArgument(QStringLiteral("password")));
        args.append(QCFTagArgument(QStringLiteral("result")));
        args.append(QCFTagArgument(QStringLiteral("returnCode")));
        args.append(QCFTagArgument(QStringLiteral("username")));
        m_generateCFTags[QStringLiteral("cfstoredproc")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfswitch"), QCFTag(QStringLiteral("cfswitch"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("expression"), true));
        m_generateCFTags[QStringLiteral("cfswitch")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cftable"), QCFTag(QStringLiteral("cftable"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cftextarea"), QCFTag(QStringLiteral("cftextarea"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
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
        m_generateCFTags[QStringLiteral("cftextarea")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cftextinput"), QCFTag(QStringLiteral("cftextinput"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfthread"), QCFTag(QStringLiteral("cfthread"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("action")));
        args.append(QCFTagArgument(QStringLiteral("duration")));
        args.append(QCFTagArgument(QStringLiteral("name")));
        args.append(QCFTagArgument(QStringLiteral("priority")));
        args.append(QCFTagArgument(QStringLiteral("timeout")));
        m_generateCFTags[QStringLiteral("cfthread")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfthrow"), QCFTag(QStringLiteral("cfthrow"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("detail")));
        args.append(QCFTagArgument(QStringLiteral("errorCode")));
        args.append(QCFTagArgument(QStringLiteral("extendedInfo")));
        args.append(QCFTagArgument(QStringLiteral("message")));
        m_generateCFTags[QStringLiteral("cfthrow")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cftimer"), QCFTag(QStringLiteral("cftimer"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("label"), false, QCFTagArgument::TypeConstantString));
        m_generateCFTags[QStringLiteral("cftimer")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("label"), false, QCFTagArgument::TypeConstantString));
        args.append(QCFTagArgument(QStringLiteral("type"), false, QCFTagArgument::TypeConstantString, QStringLiteral("inline")));
        m_generateCFTags[QStringLiteral("cftimer")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("label"), false, QCFTagArgument::TypeConstantString));
        args.append(QCFTagArgument(QStringLiteral("type"), false, QCFTagArgument::TypeConstantString, QStringLiteral("outline")));
        m_generateCFTags[QStringLiteral("cftimer")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("label"), false, QCFTagArgument::TypeConstantString));
        args.append(QCFTagArgument(QStringLiteral("type"), false, QCFTagArgument::TypeConstantString, QStringLiteral("comment")));
        m_generateCFTags[QStringLiteral("cftimer")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("label"), false, QCFTagArgument::TypeConstantString));
        args.append(QCFTagArgument(QStringLiteral("type"), false, QCFTagArgument::TypeConstantString, QStringLiteral("debug")));
        m_generateCFTags[QStringLiteral("cftimer")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cftooltip"), QCFTag(QStringLiteral("cftooltip"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cftrace"), QCFTag(QStringLiteral("cftrace"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("abort")));
        args.append(QCFTagArgument(QStringLiteral("category")));
        args.append(QCFTagArgument(QStringLiteral("inline")));
        args.append(QCFTagArgument(QStringLiteral("text")));
        m_generateCFTags[QStringLiteral("cftrace")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cftransaction"), QCFTag(QStringLiteral("cftransaction"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cftree"), QCFTag(QStringLiteral("cftree"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cftreeitem"), QCFTag(QStringLiteral("cftreeitem"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cftry"), QCFTag(QStringLiteral("cftry"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfupdate"), QCFTag(QStringLiteral("cfupdate"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfwddx"), QCFTag(QStringLiteral("cfwddx"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("name"), true, QCFTagArgument::TypeConstantString, QStringLiteral("cfml2wddx")));
        args.append(QCFTagArgument(QStringLiteral("input"), true));
        args.append(QCFTagArgument(QStringLiteral("output"), false));
        args.append(QCFTagArgument(QStringLiteral("useTimeZoneInfo"), false));
        m_generateCFTags[QStringLiteral("cfwddx")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("name"), true, QCFTagArgument::TypeConstantString, QStringLiteral("wddx2cfml")));
        args.append(QCFTagArgument(QStringLiteral("input"), true));
        args.append(QCFTagArgument(QStringLiteral("output"), true));
        args.append(QCFTagArgument(QStringLiteral("validate"), false));
        m_generateCFTags[QStringLiteral("cfwddx")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("name"), true, QCFTagArgument::TypeConstantString, QStringLiteral("cfml2js")));
        args.append(QCFTagArgument(QStringLiteral("input"), true));
        args.append(QCFTagArgument(QStringLiteral("output"), false));
        args.append(QCFTagArgument(QStringLiteral("topLevelVariable"), true));
        m_generateCFTags[QStringLiteral("cfwddx")].m_ArgumentVariants.append(args);
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("name"), true, QCFTagArgument::TypeConstantString, QStringLiteral("wddx2js")));
        args.append(QCFTagArgument(QStringLiteral("input"), true));
        args.append(QCFTagArgument(QStringLiteral("output"), false));
        args.append(QCFTagArgument(QStringLiteral("topLevelVariable"), true));
        args.append(QCFTagArgument(QStringLiteral("validate"), false));
        m_generateCFTags[QStringLiteral("cfwddx")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfwindow"), QCFTag(QStringLiteral("cfwindow"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfxml"), QCFTag(QStringLiteral("cfxml"), QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
        args.clear();
        args.append(QCFTagArgument(QStringLiteral("variable"), true));
        args.append(QCFTagArgument(QStringLiteral("caseSensitive")));
        m_generateCFTags[QStringLiteral("cfxml")].m_ArgumentVariants.append(args);

        m_generateCFTags.insert(QStringLiteral("cfzip"), QCFTag(QStringLiteral("cfzip"), QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.insert(QStringLiteral("cfzipparam"), QCFTag(QStringLiteral("cfzipparam"), QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

        m_generateCFTags.squeeze();
    }

    return m_generateCFTags;
}

const QHash<QString, QCFFunction> & QCF8::generateCFFunctions()
{
    if (m_generateCFFunctions.count() == 0)
    {
        m_generateCFFunctions.reserve(500);

        m_generateCFFunctions.insert(QStringLiteral("abs"), QCFFunction("Abs", QCFFunction::ReturnDouble));
        m_generateCFFunctions[QStringLiteral("abs")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDouble, true));

        m_generateCFFunctions.insert(QStringLiteral("acos"), QCFFunction("ACos", QCFFunction::ReturnDouble));
        m_generateCFFunctions[QStringLiteral("acos")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDouble, true));

        m_generateCFFunctions.insert(QStringLiteral("addsoaprequestheader"), QCFFunction("AddSOAPRequestHeader", QCFFunction::ReturnVoid));
        m_generateCFFunctions[QStringLiteral("addsoaprequestheader")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("addsoaprequestheader")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true));
        m_generateCFFunctions[QStringLiteral("addsoaprequestheader")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true));
        m_generateCFFunctions[QStringLiteral("addsoaprequestheader")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true));
        m_generateCFFunctions[QStringLiteral("addsoaprequestheader")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBool, false));

        m_generateCFFunctions.insert(QStringLiteral("addsoapresponseheader"), QCFFunction("AddSOAPResponseHeader", QCFFunction::ReturnVoid));
        m_generateCFFunctions[QStringLiteral("addsoapresponseheader")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true));
        m_generateCFFunctions[QStringLiteral("addsoapresponseheader")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true));
        m_generateCFFunctions[QStringLiteral("addsoapresponseheader")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true));
        m_generateCFFunctions[QStringLiteral("addsoapresponseheader")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBool, false));

        m_generateCFFunctions.insert(QStringLiteral("ajaxlink"), QCFFunction("AjaxLink", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("ajaxlink")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true));

        m_generateCFFunctions.insert(QStringLiteral("ajaxonload"), QCFFunction("AjaxOnLoad", QCFFunction::ReturnVoid));
        m_generateCFFunctions[QStringLiteral("ajaxonload")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true));

        m_generateCFFunctions.insert(QStringLiteral("arrayappend"), QCFFunction("ArrayAppend", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("arrayappend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("arrayappend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeAny, true));

        m_generateCFFunctions.insert(QStringLiteral("arrayavg"), QCFFunction("ArrayAvg", QCFFunction::ReturnDouble));
        m_generateCFFunctions[QStringLiteral("arrayavg")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));

        m_generateCFFunctions.insert(QStringLiteral("arrayclear"), QCFFunction("ArrayClear", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("arrayclear")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));

        m_generateCFFunctions.insert(QStringLiteral("arraydeleteat"), QCFFunction("ArrayDeleteAt", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("arraydeleteat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("arraydeleteat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true));

        m_generateCFFunctions.insert(QStringLiteral("arrayinsertsat"), QCFFunction("ArrayInsertAt", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("arrayinsertsat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("arrayinsertsat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("arrayinsertsat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeAny, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("arrayisdefined"), QCFFunction("ArrayIsDefined", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("arrayisdefined")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("arrayisdefined")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("arrayisempty"), QCFFunction("ArrayIsEmpty", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("arrayisempty")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));

        m_generateCFFunctions.insert(QStringLiteral("arraylen"), QCFFunction("ArrayLen", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("arraylen")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));

        m_generateCFFunctions.insert(QStringLiteral("arraymax"), QCFFunction("ArrayMax", QCFFunction::ReturnDouble));
        m_generateCFFunctions[QStringLiteral("arraymax")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));

        m_generateCFFunctions.insert(QStringLiteral("arraymin"), QCFFunction("ArrayMin", QCFFunction::ReturnDouble));
        m_generateCFFunctions[QStringLiteral("arraymin")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));

        m_generateCFFunctions.insert(QStringLiteral("arraynew"), QCFFunction("ArrayNew", QCFFunction::ReturnQCFVariant));
        m_generateCFFunctions[QStringLiteral("arraynew")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("arrayprepend"), QCFFunction("ArrayPrepend", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("arrayprepend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("arrayprepend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeAny, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("arrayresize"), QCFFunction("ArrayResize", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("arrayresize")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("arrayresize")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("arrayset"), QCFFunction("ArraySet", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("arrayset")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("arrayset")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("arrayset")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("arrayset")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("arraysort"), QCFFunction("ArraySort", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("arraysort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("arraysort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("arraysort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("arraysum"), QCFFunction("ArraySum", QCFFunction::ReturnDouble));
        m_generateCFFunctions[QStringLiteral("arraysum")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));

        m_generateCFFunctions.insert(QStringLiteral("arrayswap"), QCFFunction("ArraySwap", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("arrayswap")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("arrayswap")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("arrayswap")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("arraytolist"), QCFFunction("ArrayToList", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("arraytolist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("arraytolist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("asc"), QCFFunction("Asc", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("asc")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("asin"), QCFFunction("ASin", QCFFunction::ReturnDouble));
        m_generateCFFunctions[QStringLiteral("asin")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDouble, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("atn"), QCFFunction("Atn", QCFFunction::ReturnDouble));
        m_generateCFFunctions[QStringLiteral("atn")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDouble, true, QCFFunctionArgument::TypeAny));

        // AuthenticatedContext obsolete
        // AuthenticatedUser obsolete

        m_generateCFFunctions.insert(QStringLiteral("binarydecode"), QCFFunction("BinaryDecode", QCFFunction::ReturnBinary));
        m_generateCFFunctions[QStringLiteral("binarydecode")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("binarydecode")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("binaryencode"), QCFFunction("BinaryEncode", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("binaryencode")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBinary, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("binaryencode")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("bitand"), QCFFunction("BitAnd", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("bitand")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("bitand")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("bitmaskclear"), QCFFunction("BitMaskClear", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("bitmaskclear")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("bitmaskclear")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("bitmaskclear")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("bitmaskread"), QCFFunction("BitMaskRead", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("bitmaskread")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("bitmaskread")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("bitmaskread")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("bitmaskset"), QCFFunction("BitMaskSet", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("bitmaskset")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("bitmaskset")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("bitmaskset")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("bitmaskset")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("bitnot"), QCFFunction("BitNot", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("bitnot")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("bitor"), QCFFunction("BitOr", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("bitor")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("bitshln"), QCFFunction("BitSHLN", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("bitshln")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("bitshln")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("bitshrn"), QCFFunction("BitSHRN", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("bitshrn")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("bitshrn")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("bitxor"), QCFFunction("BitXor", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("bitxor")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("bitxor")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("ceiling"), QCFFunction("Ceiling", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("ceiling")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("charsetdecode"), QCFFunction("CharsetDecode", QCFFunction::ReturnBinary));
        m_generateCFFunctions[QStringLiteral("charsetdecode")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("charsetdecode")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("charsetencode"), QCFFunction("CharsetEncode", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("charsetdecode")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBinary, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("charsetdecode")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("chr"), QCFFunction("Chr", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("chr")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("cjustify"), QCFFunction("CJustify", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("cjustify")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("cjustify")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("compare"), QCFFunction("Compare", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("compare")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("compare")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("comparenocase"), QCFFunction("CompareNoCase", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("comparenocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("comparenocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("cos"), QCFFunction("Cos", QCFFunction::ReturnDouble));
        m_generateCFFunctions[QStringLiteral("cos")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDouble, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("createdate"), QCFFunction("CreateDate", QCFFunction::ReturnDateTime));
        m_generateCFFunctions[QStringLiteral("createdate")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("createdate")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("createdate")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("createdatetime"), QCFFunction("CreateDateTime", QCFFunction::ReturnDateTime));
        m_generateCFFunctions[QStringLiteral("createdatetime")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("createdatetime")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("createdatetime")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("createdatetime")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("createdatetime")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("createdatetime")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("createobject"), QCFFunction("CreateObject", QCFFunction::ReturnQCFVariant, true));
        m_generateCFFunctions[QStringLiteral("createobject")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeConstant));
        m_generateCFFunctions[QStringLiteral("createobject")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeConstant));

        m_generateCFFunctions.insert(QStringLiteral("createodbcdatetime"), QCFFunction("CreateODBCDateTime", QCFFunction::ReturnDateTime));
        m_generateCFFunctions[QStringLiteral("createodbcdatetime")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDateTime, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("createuuid"), QCFFunction("CreateUUID", QCFFunction::ReturnString));

        m_generateCFFunctions.insert(QStringLiteral("datecompare"), QCFFunction("DateCompare", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("datecompare")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDateTime, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("datecompare")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDateTime, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("datecompare")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("dateformat"), QCFFunction("DateFormat", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("dateformat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("dateformat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("dateformat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("decrypt"), QCFFunction("Decrypt", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("decrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("decrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("decrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("decrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("decrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, false, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("decrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("duplicate"), QCFFunction("Duplicate", QCFFunction::ReturnQCFVariant));
        m_generateCFFunctions[QStringLiteral("duplicate")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("encrypt"), QCFFunction("Encrypt", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("encrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("encrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("decrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("encrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("encrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, false, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("encrypt")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("fileexists"), QCFFunction("FileExists", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("fileexists")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("find"), QCFFunction("Find", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("find")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("find")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("find")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("findnocase"), QCFFunction("FindNoCase", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("findnocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("findnocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("findnocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("findoneof"), QCFFunction("FindOneOf", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("findoneof")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("findoneof")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("findoneof")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("formatbasen"), QCFFunction("FormatBaseN", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("formatbasen")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("formatbasen")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("getclientvariableslist"), QCFFunction("GetClientVariablesList", QCFFunction::ReturnString));

        m_generateCFFunctions.insert(QStringLiteral("fix"), QCFFunction("Fix", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("fix")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDouble, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("getbasetagdata"), QCFFunction("GetBaseTagData", QCFFunction::ReturnQCFVariant, true));
        m_generateCFFunctions[QStringLiteral("getbasetagdata")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("getbasetagdata")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("getbasetaglist"), QCFFunction("GetBaseTagList", QCFFunction::ReturnString, true));

        m_generateCFFunctions.insert(QStringLiteral("int"), QCFFunction("Int", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("int")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDouble, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("isarray"), QCFFunction("IsArray", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("isarray")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("isarray")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("isdefined"), QCFFunction("IsDefined", QCFFunction::ReturnBool, true));
        m_generateCFFunctions[QStringLiteral("isdefined")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("isstruct"), QCFFunction("IsStruct", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("isstruct")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));

        m_generateCFFunctions.insert(QStringLiteral("isquery"), QCFFunction("IsQuery", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("isquery")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));

        m_generateCFFunctions.insert(QStringLiteral("lcase"), QCFFunction("LCase", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("lcase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("left"), QCFFunction("Left", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("left")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("left")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("len"), QCFFunction("Len", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("len")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listappend"), QCFFunction("ListAppend", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("listappend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listappend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listappend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listchangedelims"), QCFFunction("ListChangeDelims", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("listchangedelims")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listchangedelims")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listchangedelims")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listcontains"), QCFFunction("ListContains", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("listcontains")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listcontains")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listcontains")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listcontainsnocase"), QCFFunction("ListContainsNoCase", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("listcontainsnocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listcontainsnocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listcontainsnocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listdeleteat"), QCFFunction("ListDeleteAt", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("listdeleteat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listdeleteat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listdeleteat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listfind"), QCFFunction("ListFind", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("listfind")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listfind")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listfind")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listfindnocase"), QCFFunction("ListFindNoCase", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("listfindnocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listfindnocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listfindnocase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listfirst"), QCFFunction("ListFirst", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("listfirst")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listfirst")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listgetat"), QCFFunction("ListGetAt", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("listgetat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listgetat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listgetat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listinsertat"), QCFFunction("ListInsertAt", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("listinsertat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listinsertat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listinsertat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listinsertat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listlast"), QCFFunction("ListLast", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("listlast")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listlast")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listlen"), QCFFunction("ListLen", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("listlen")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listlen")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listprepend"), QCFFunction("ListPrepend", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("listprepend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listprepend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listprepend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listqualify"), QCFFunction("ListQualify", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("listqualify")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listqualify")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listqualify")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listqualify")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listrest"), QCFFunction("ListRest", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("listrest")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listrest")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listsetat"), QCFFunction("ListSetAt", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("listsetat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listsetat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listsetat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listsetat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listsort"), QCFFunction("ListSort", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("listsort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listsort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listsort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listsort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listvaluecount"), QCFFunction("ListValueCount", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("listvaluecount")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listvaluecount")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listvaluecount")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listvaluecountnocount"), QCFFunction("ListValueCountNoCase", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("listvaluecountnocount")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listvaluecountnocount")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listvaluecountnocount")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("listtoarray"), QCFFunction("ListToArray", QCFFunction::ReturnQCFVariant));
        m_generateCFFunctions[QStringLiteral("listtoarray")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listtoarray")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("listtoarray")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBool, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("now"), QCFFunction("Now", QCFFunction::ReturnDateTime));

        m_generateCFFunctions.insert(QStringLiteral("queryaddrow"), QCFFunction("QueryAddRow", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("queryaddrow")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("queryaddrow")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("querynew"), QCFFunction("QueryNew", QCFFunction::ReturnQCFVariant));
        m_generateCFFunctions[QStringLiteral("querynew")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("querynew")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("quotedvaluelist"), QCFFunction("QuotedValueList", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("quotedvaluelist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("quotedvaluelist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("queryaddcolumn"), QCFFunction("QueryAddColumn", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("queryaddcolumn")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("queryaddcolumn")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("queryaddcolumn")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("queryaddcolumn")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("queryconvertforgrid"), QCFFunction("QueryConvertForGrid", QCFFunction::ReturnQCFVariant));
        m_generateCFFunctions[QStringLiteral("queryconvertforgrid")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("queryconvertforgrid")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("queryconvertforgrid")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("querysetcell"), QCFFunction("QuerySetCell", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("querysetcell")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("querysetcell")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("querysetcell")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("querysetcell")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("quotedvalue"), QCFFunction("QuotedValue", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("quotedvalue")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("quotedvalue")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("replace"), QCFFunction("Replace", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("replace")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("replace")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("replace")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("replace")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("replacelist"), QCFFunction("ReplaceList", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("replacelist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("replacelist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("replacelist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("reverse"), QCFFunction("Reverse", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("reverse")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("right"), QCFFunction("Right", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("right")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("right")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("structappend"), QCFFunction("StructAppend", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("structappend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("structappend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("structappend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBool, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("structclear"), QCFFunction("StructClear", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("structappend")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));

        m_generateCFFunctions.insert(QStringLiteral("structcopy"), QCFFunction("StructCopy", QCFFunction::ReturnQCFVariant));
        m_generateCFFunctions[QStringLiteral("structcopy")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));

        m_generateCFFunctions.insert(QStringLiteral("structcount"), QCFFunction("StructCount", QCFFunction::ReturnInt));
        m_generateCFFunctions[QStringLiteral("structcount")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));

        m_generateCFFunctions.insert(QStringLiteral("structdelete"), QCFFunction("StructDelete", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("structdelete")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("structdelete")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("structdelete")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBool, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("structfind"), QCFFunction("StructFind", QCFFunction::ReturnQCFVariant));
        m_generateCFFunctions[QStringLiteral("structfind")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("structfind")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("structfindkey"), QCFFunction("StructFindKey", QCFFunction::ReturnQCFVariant));
        m_generateCFFunctions[QStringLiteral("structfind")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("structfind")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("structfind")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("structfindvalue"), QCFFunction("StructFindValue", QCFFunction::ReturnQCFVariant));
        m_generateCFFunctions[QStringLiteral("structfindvalue")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("structfindvalue")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("structfindvalue")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("structget"), QCFFunction("StructGet", QCFFunction::ReturnQCFVariant));
        m_generateCFFunctions[QStringLiteral("structget")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("structinsert"), QCFFunction("StructInsert", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("structinsert")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("structinsert")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("structinsert")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("structdelete")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBool, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("structisempty"), QCFFunction("StructIsEmpty", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("structisempty")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));

        m_generateCFFunctions.insert(QStringLiteral("structkeyarray"), QCFFunction("StructKeyArray", QCFFunction::ReturnQCFVariant));
        m_generateCFFunctions[QStringLiteral("structkeyarray")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));

        m_generateCFFunctions.insert(QStringLiteral("structkeyexists"), QCFFunction("StructKeyExists", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("structkeyexists")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("structkeyexists")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("structkeylist"), QCFFunction("StructKeyList", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("structkeylist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("structkeylist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("structnew"), QCFFunction("StructNew", QCFFunction::ReturnQCFVariant));

        m_generateCFFunctions.insert(QStringLiteral("structsort"), QCFFunction("StructSort", QCFFunction::ReturnQCFVariant));
        m_generateCFFunctions[QStringLiteral("structsort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("structsort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("structsort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("structsort")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("structupdate"), QCFFunction("StructUpdate", QCFFunction::ReturnBool));
        m_generateCFFunctions[QStringLiteral("structupdate")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("structupdate")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeVariable));
        m_generateCFFunctions[QStringLiteral("structupdate")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeVariable));

        m_generateCFFunctions.insert(QStringLiteral("timeformat"), QCFFunction("TimeFormat", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("timeformat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDateTime, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("timeformat")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("trim"), QCFFunction("Trim", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("trim")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("ucase"), QCFFunction("UCase", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("ucase")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("val"), QCFFunction("Val", QCFFunction::ReturnDouble));
        m_generateCFFunctions[QStringLiteral("val")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("valuelist"), QCFFunction("ValueList", QCFFunction::ReturnString));
        m_generateCFFunctions[QStringLiteral("valuelist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQCFVariant, true, QCFFunctionArgument::TypeAny));
        m_generateCFFunctions[QStringLiteral("valuelist")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.insert(QStringLiteral("writeoutput"), QCFFunction("WriteOutput", QCFFunction::ReturnVoid, true));
        m_generateCFFunctions[QStringLiteral("writeoutput")].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

        m_generateCFFunctions.squeeze();
    }

    return m_generateCFFunctions;
}
