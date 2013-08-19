#include "qcf8.h"

QHash<QString, QCFTag> QCF8::generateCFTags()
{
	QHash<QString, QCFTag> ret;
	QList<QCFTagArgument> args;

	ret.insert("cfabort", QCFTag("cfabort", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("showError"));
	ret["cfabort"].m_ArgumentVariants.append(args);

    ret.insert("cfadmin", QCFTag("cfadmin", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments, QCFTag::WithoutExpressionInside, true)); // Railo cftag

	ret.insert("cfajaximport", QCFTag("cfajaximport", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("cssSrc"));
	args.append(QCFTagArgument("params"));
	args.append(QCFTagArgument("scriptSrc"));
	args.append(QCFTagArgument("tags"));
	ret["cfajaximport"].m_ArgumentVariants.append(args);

	ret.insert("cfajaxproxy", QCFTag("cfajaxproxy", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("bind", true));
	args.append(QCFTagArgument("jsclassname"));
	args.append(QCFTagArgument("onError"));
	args.append(QCFTagArgument("onSuccess"));
	ret["cfajaxproxy"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("cfc", true));
	args.append(QCFTagArgument("jsclassname"));
	args.append(QCFTagArgument("onError"));
	args.append(QCFTagArgument("onSuccess"));
	ret["cfajaxproxy"].m_ArgumentVariants.append(args);

	ret.insert("cfapplet", QCFTag("cfapplet", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("appletSource", true));
	args.append(QCFTagArgument("name", true));
	args.append(QCFTagArgument("align"));
	args.append(QCFTagArgument("height"));
	args.append(QCFTagArgument("hSpace"));
	args.append(QCFTagArgument("notSupported"));
	args.append(QCFTagArgument("param_n"));
	args.append(QCFTagArgument("vSpace"));
	args.append(QCFTagArgument("width"));
	ret["cfapplet"].m_ArgumentVariants.append(args);

	ret.insert("cfapplication", QCFTag("cfapplication", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("datasource"));
	args.append(QCFTagArgument("name"));
	args.append(QCFTagArgument("applicationTimeout"));
	args.append(QCFTagArgument("clientManagement"));
	args.append(QCFTagArgument("clientStorage"));
	args.append(QCFTagArgument("googleMapKey"));
	args.append(QCFTagArgument("loginStorage"));
	args.append(QCFTagArgument("scriptProtect"));
	args.append(QCFTagArgument("secureJSON"));
	args.append(QCFTagArgument("serverSideFormValidation"));
	args.append(QCFTagArgument("secureJSONPrefix"));
	args.append(QCFTagArgument("sessionManagement"));
	args.append(QCFTagArgument("sessionTimeout"));
	args.append(QCFTagArgument("setClientCookies"));
	args.append(QCFTagArgument("setDomainCookies"));
	ret["cfapplication"].m_ArgumentVariants.append(args);

	ret.insert("cfargument", QCFTag("cfargument", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("name", true));
	args.append(QCFTagArgument("default"));
	args.append(QCFTagArgument("displayname"));
	args.append(QCFTagArgument("hint"));
	args.append(QCFTagArgument("required"));
	args.append(QCFTagArgument("type"));
	ret["cfargument"].m_ArgumentVariants.append(args);

	ret.insert("cfassociate", QCFTag("cfassociate", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("baseTag", true));
	args.append(QCFTagArgument("dataCollection"));
	ret["cfassociate"].m_ArgumentVariants.append(args);

	ret.insert("cfbreak", QCFTag("cfbreak", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfcache", QCFTag("cfcache", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("action"));
	args.append(QCFTagArgument("directory"));
	args.append(QCFTagArgument("expireURL"));
	args.append(QCFTagArgument("password"));
	args.append(QCFTagArgument("port"));
	args.append(QCFTagArgument("protocol"));
	args.append(QCFTagArgument("timespan"));
	args.append(QCFTagArgument("username"));
	ret["cfcache"].m_ArgumentVariants.append(args);

	ret.insert("cfcalendar", QCFTag("cfcalendar", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("name", true));
	args.append(QCFTagArgument("dayNames"));
	args.append(QCFTagArgument("disabled"));
	args.append(QCFTagArgument("enabled"));
	args.append(QCFTagArgument("endRange"));
	args.append(QCFTagArgument("firstDayOfWeek"));
	args.append(QCFTagArgument("height"));
	args.append(QCFTagArgument("mask"));
	args.append(QCFTagArgument("monthNames"));
	args.append(QCFTagArgument("onBlur"));
	args.append(QCFTagArgument("onChange"));
	args.append(QCFTagArgument("onFocus"));
	args.append(QCFTagArgument("selectedDate"));
	args.append(QCFTagArgument("startRange"));
	args.append(QCFTagArgument("style"));
	args.append(QCFTagArgument("tooltip"));
	args.append(QCFTagArgument("visible"));
	args.append(QCFTagArgument("width"));
	ret["cfcalendar"].m_ArgumentVariants.append(args);

	ret.insert("cfcase", QCFTag("cfcase", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("value", true));
	args.append(QCFTagArgument("delimiters"));
	ret["cfcase"].m_ArgumentVariants.append(args);

	ret.insert("cfcatch", QCFTag("cfcatch", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("type"));
	ret["cfcatch"].m_ArgumentVariants.append(args);

	ret.insert("cfchart", QCFTag("cfchart", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("backgroundColor"));
	args.append(QCFTagArgument("chartHeight"));
	args.append(QCFTagArgument("chartWidth"));
	args.append(QCFTagArgument("dataBackgroundColor"));
	args.append(QCFTagArgument("font"));
	args.append(QCFTagArgument("fontBold"));
	args.append(QCFTagArgument("fontItalic"));
	args.append(QCFTagArgument("fontSize"));
	args.append(QCFTagArgument("foregroundColor"));
	args.append(QCFTagArgument("format"));
	args.append(QCFTagArgument("gridlines"));
	args.append(QCFTagArgument("labelFormat"));
	args.append(QCFTagArgument("markerSize"));
	args.append(QCFTagArgument("name"));
	args.append(QCFTagArgument("pieSliceStyle"));
	args.append(QCFTagArgument("scaleFrom"));
	args.append(QCFTagArgument("scaleTo"));
	args.append(QCFTagArgument("seriesPlacement"));
	args.append(QCFTagArgument("show3D"));
	args.append(QCFTagArgument("showBorder"));
	args.append(QCFTagArgument("showLegend"));
	args.append(QCFTagArgument("showMarkers"));
	args.append(QCFTagArgument("showXGridlines"));
	args.append(QCFTagArgument("showYGridlines"));
	args.append(QCFTagArgument("sortXAxis"));
	args.append(QCFTagArgument("style"));
	args.append(QCFTagArgument("title"));
	args.append(QCFTagArgument("tipbgcolor"));
	args.append(QCFTagArgument("tipStyle"));
	args.append(QCFTagArgument("url"));
	args.append(QCFTagArgument("xAxisTitle"));
	args.append(QCFTagArgument("xAxisType"));
	args.append(QCFTagArgument("xOffset"));
	args.append(QCFTagArgument("yAxisTitle"));
	args.append(QCFTagArgument("yAxisType"));
	args.append(QCFTagArgument("yOffset"));
	ret["cfchart"].m_ArgumentVariants.append(args);

	ret.insert("cfchartdata", QCFTag("cfchartdata", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("item", true));
	args.append(QCFTagArgument("value", true));
	ret["cfchartdata"].m_ArgumentVariants.append(args);

	ret.insert("cfchartseries", QCFTag("cfchartseries", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("type", true));
    args.append(QCFTagArgument("itemColumn"));
    args.append(QCFTagArgument("valueColumn"));
    args.append(QCFTagArgument("colorlist"));
    args.append(QCFTagArgument("dataLabelStyle"));
    args.append(QCFTagArgument("markerStyle"));
    args.append(QCFTagArgument("paintStyle"));
    args.append(QCFTagArgument("query"));
    args.append(QCFTagArgument("seriesColor"));
    args.append(QCFTagArgument("seriesLabel"));
    ret["cfchartseries"].m_ArgumentVariants.append(args);

	ret.insert("cfcol", QCFTag("cfcol", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfcollection", QCFTag("cfcollection", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("action", true));
    args.append(QCFTagArgument("categories"));
    args.append(QCFTagArgument("collection"));
    args.append(QCFTagArgument("language"));
    args.append(QCFTagArgument("name"));
    args.append(QCFTagArgument("path"));
    ret["cfcollection"].m_ArgumentVariants.append(args);

	ret.insert("cfcomponent", QCFTag("cfcomponent", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("bindingname", false));
    args.append(QCFTagArgument("displayname", false));
    args.append(QCFTagArgument("extends", false));
    args.append(QCFTagArgument("hint", false));
    args.append(QCFTagArgument("implements", false));
    args.append(QCFTagArgument("namespace", false));
    args.append(QCFTagArgument("output", false));
    args.append(QCFTagArgument("porttypename", false));
    args.append(QCFTagArgument("serviceaddress", false));
    args.append(QCFTagArgument("serviceportname", false));
    args.append(QCFTagArgument("style", false));
    args.append(QCFTagArgument("wsdlfile", false));
    ret["cfcomponent"].m_ArgumentVariants.append(args);

	ret.insert("cfcontent", QCFTag("cfcontent", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("deleteFile", false));
    args.append(QCFTagArgument("file", false));
    args.append(QCFTagArgument("reset", false));
    args.append(QCFTagArgument("type", false));
    args.append(QCFTagArgument("variable", false));
    ret["cfcontent"].m_ArgumentVariants.append(args);

	ret.insert("cfcookie", QCFTag("cfcookie", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("name", true));
    args.append(QCFTagArgument("domain", false));
    args.append(QCFTagArgument("expires", false));
    args.append(QCFTagArgument("path", false));
    args.append(QCFTagArgument("secure", false));
    args.append(QCFTagArgument("value", false));
    ret["cfcookie"].m_ArgumentVariants.append(args);

	ret.insert("cfdbinfo", QCFTag("cfdbinfo", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfdefaultcase", QCFTag("cfdefaultcase", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfdirectory", QCFTag("cfdirectory", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("directory", true));
	args.append(QCFTagArgument("action", false, QCFTagArgument::TypeConstantString, "list"));
	args.append(QCFTagArgument("filter", false));
	args.append(QCFTagArgument("listinfo", false, QCFTagArgument::TypeConstantString));
	ret["cfdirectory"].m_ArgumentVariants.append(args);

	ret.insert("cfdiv", QCFTag("cfdiv", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfdocument", QCFTag("cfdocument", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("format", true));
    args.append(QCFTagArgument("authPassword"));
    args.append(QCFTagArgument("authUser"));
    args.append(QCFTagArgument("backgroundVisible"));
    args.append(QCFTagArgument("bookmark"));
    args.append(QCFTagArgument("encryption"));
    args.append(QCFTagArgument("filename"));
    args.append(QCFTagArgument("fontEmbed"));
    args.append(QCFTagArgument("localUrl"));
    args.append(QCFTagArgument("marginBottom"));
    args.append(QCFTagArgument("marginLeft"));
    args.append(QCFTagArgument("marginRight"));
    args.append(QCFTagArgument("marginTop"));
    args.append(QCFTagArgument("mimeType"));
    args.append(QCFTagArgument("name"));
    args.append(QCFTagArgument("orientation"));
    args.append(QCFTagArgument("overwrite"));
    args.append(QCFTagArgument("ownerPassword"));
    args.append(QCFTagArgument("pageHeight"));
    args.append(QCFTagArgument("pageType"));
    args.append(QCFTagArgument("pageWidth"));
    args.append(QCFTagArgument("permissions"));
    args.append(QCFTagArgument("proxyHost"));
    args.append(QCFTagArgument("proxyPassword"));
    args.append(QCFTagArgument("proxyPort"));
    args.append(QCFTagArgument("proxyUser"));
    args.append(QCFTagArgument("saveAsName"));
    args.append(QCFTagArgument("scale"));
    args.append(QCFTagArgument("src"));
    args.append(QCFTagArgument("srcfile"));
    args.append(QCFTagArgument("unit"));
    args.append(QCFTagArgument("userAgent"));
    args.append(QCFTagArgument("userPassword"));
    ret["cfdocument"].m_ArgumentVariants.append(args);

	ret.insert("cfdocumentitem", QCFTag("cfdocumentitem", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("type", true));
    ret["cfdocumentitem"].m_ArgumentVariants.append(args);

	ret.insert("cfdocumentsection", QCFTag("cfdocumentsection", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("authPassword"));
    args.append(QCFTagArgument("authUser"));
    args.append(QCFTagArgument("marginBottom"));
    args.append(QCFTagArgument("marginLeft"));
    args.append(QCFTagArgument("marginRight"));
    args.append(QCFTagArgument("marginTop"));
    args.append(QCFTagArgument("mimeType"));
    args.append(QCFTagArgument("name"));
    args.append(QCFTagArgument("src"));
    args.append(QCFTagArgument("srcfile"));
    args.append(QCFTagArgument("userAgent"));
    ret["cfdocumentsection"].m_ArgumentVariants.append(args);

	ret.insert("cfdump", QCFTag("cfdump", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("var", true));
	ret["cfdump"].m_ArgumentVariants.append(args);

	ret.insert("cfelse", QCFTag("cfelse", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeExpression));

	ret.insert("cfelseif", QCFTag("cfelseif", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeExpression));

	ret.insert("cferror", QCFTag("cferror", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("template", true));
	args.append(QCFTagArgument("type", true));
	args.append(QCFTagArgument("exception"));
	args.append(QCFTagArgument("mailTo"));
	ret["cferror"].m_ArgumentVariants.append(args);

	ret.insert("cfexchangecalendar", QCFTag("cfexchangecalendar", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfexchangeconnection", QCFTag("cfexchangeconnection", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfexchangecontact", QCFTag("cfexchangecontact", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfexchangefilter", QCFTag("cfexchangefilter", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfexchangemail", QCFTag("cfexchangemail", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfexchangetask", QCFTag("cfexchangetask", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfexecute", QCFTag("cfexecute", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("name", true));
	args.append(QCFTagArgument("arguments"));
	args.append(QCFTagArgument("outputFile"));
	args.append(QCFTagArgument("timeout"));
	args.append(QCFTagArgument("variable"));
	ret["cfexecute"].m_ArgumentVariants.append(args);


	ret.insert("cfexit", QCFTag("cfexit", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("method", false, QCFTagArgument::TypeConstantString));
	ret["cfexit"].m_ArgumentVariants.append(args);

	//ret.insert("cffeed", QCFTag("cffeed"));

	ret.insert("cffile", QCFTag("cffile", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("action", true, QCFTagArgument::TypeConstantString, "append"));
	args.append(QCFTagArgument("file", true));
	args.append(QCFTagArgument("output", true));
	args.append(QCFTagArgument("addNewLine"));
	args.append(QCFTagArgument("attributes"));
	args.append(QCFTagArgument("charset"));
	args.append(QCFTagArgument("fixnewline"));
	args.append(QCFTagArgument("mode"));
	ret["cffile"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("action", true, QCFTagArgument::TypeConstantString, "copy"));
	args.append(QCFTagArgument("destination", true));
	args.append(QCFTagArgument("source", true));
	args.append(QCFTagArgument("attributes"));
	args.append(QCFTagArgument("mode"));
	ret["cffile"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("action", true, QCFTagArgument::TypeConstantString, "delete"));
	args.append(QCFTagArgument("file", true));
	ret["cffile"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("action", true, QCFTagArgument::TypeConstantString, "delete"));
	args.append(QCFTagArgument("file", true));
	ret["cffile"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("action", true, QCFTagArgument::TypeConstantString, "move"));
	args.append(QCFTagArgument("destination", true));
	args.append(QCFTagArgument("source", true));
	args.append(QCFTagArgument("attributes"));
	args.append(QCFTagArgument("charset"));
	args.append(QCFTagArgument("mode"));
	ret["cffile"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("action", true, QCFTagArgument::TypeConstantString, "read"));
	args.append(QCFTagArgument("file", true));
	args.append(QCFTagArgument("variable", true));
	args.append(QCFTagArgument("charset"));
	ret["cffile"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("action", true, QCFTagArgument::TypeConstantString, "readBinary"));
	args.append(QCFTagArgument("file", true));
	args.append(QCFTagArgument("variable", true));
	ret["cffile"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("action", true, QCFTagArgument::TypeConstantString, "rename"));
	args.append(QCFTagArgument("destination", true));
	args.append(QCFTagArgument("source", true));
	args.append(QCFTagArgument("attributes"));
	args.append(QCFTagArgument("mode"));
	ret["cffile"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("action", true, QCFTagArgument::TypeConstantString, "upload"));
	args.append(QCFTagArgument("destination", true));
	args.append(QCFTagArgument("fileField", true));
	args.append(QCFTagArgument("accept"));
	args.append(QCFTagArgument("attributes"));
	args.append(QCFTagArgument("mode"));
	args.append(QCFTagArgument("nameConflict"));
	args.append(QCFTagArgument("result"));
	ret["cffile"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("action", true, QCFTagArgument::TypeConstantString, "uploadAll"));
	args.append(QCFTagArgument("destination", true));
	args.append(QCFTagArgument("accept"));
	args.append(QCFTagArgument("attributes"));
	args.append(QCFTagArgument("mode"));
	args.append(QCFTagArgument("nameConflict"));
	args.append(QCFTagArgument("result"));
	ret["cffile"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("action", true, QCFTagArgument::TypeConstantString, "write"));
	args.append(QCFTagArgument("file", true));
	args.append(QCFTagArgument("output", true));
	args.append(QCFTagArgument("addNewLine"));
	args.append(QCFTagArgument("attributes"));
	args.append(QCFTagArgument("charset"));
	args.append(QCFTagArgument("result"));
	args.append(QCFTagArgument("mode"));
	ret["cffile"].m_ArgumentVariants.append(args);

	ret.insert("cffinally", QCFTag("cffinally", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfflush", QCFTag("cfflush", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("interval"));
	ret["cfflush"].m_ArgumentVariants.append(args);

	ret.insert("cfform", QCFTag("cfform", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("accessible"));
    args.append(QCFTagArgument("action"));
    args.append(QCFTagArgument("archive"));
    args.append(QCFTagArgument("codeBase"));
    args.append(QCFTagArgument("format"));
    args.append(QCFTagArgument("height"));
    args.append(QCFTagArgument("id"));
    args.append(QCFTagArgument("method"));
    args.append(QCFTagArgument("name"));
    args.append(QCFTagArgument("onError"));
    args.append(QCFTagArgument("onLoad"));
    args.append(QCFTagArgument("onReset"));
    args.append(QCFTagArgument("onSubmit"));
    args.append(QCFTagArgument("onSuccess"));
    args.append(QCFTagArgument("preloader"));
    args.append(QCFTagArgument("preserveData"));
    args.append(QCFTagArgument("scriptSrc"));
    args.append(QCFTagArgument("skin"));
    args.append(QCFTagArgument("style"));
    args.append(QCFTagArgument("timeout"));
    args.append(QCFTagArgument("width"));
    args.append(QCFTagArgument("wMode"));
    ret["cfform"].m_ArgumentVariants.append(args);

	ret.insert("cfformgroup", QCFTag("cfformgroup", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("type", true, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument("label"));
    args.append(QCFTagArgument("style"));
    args.append(QCFTagArgument("selectedIndex"));
    args.append(QCFTagArgument("width"));
    args.append(QCFTagArgument("height"));
    args.append(QCFTagArgument("enabled"));
    args.append(QCFTagArgument("visible"));
    args.append(QCFTagArgument("onChange"));
    args.append(QCFTagArgument("tooltip"));
    args.append(QCFTagArgument("id"));
    args.append(QCFTagArgument("query"));
    args.append(QCFTagArgument("maxrows"));
    args.append(QCFTagArgument("startrow"));
    ret["cfformgroup"].m_ArgumentVariants.append(args);

	ret.insert("cfformitem", QCFTag("cfformitem", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfftp", QCFTag("cfftp", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("action", true, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument("actionparam"));
    args.append(QCFTagArgument("buffersize"));
    args.append(QCFTagArgument("connection"));
    args.append(QCFTagArgument("passive"));
    args.append(QCFTagArgument("password"));
    args.append(QCFTagArgument("port"));
    args.append(QCFTagArgument("proxyServer"));
    args.append(QCFTagArgument("retryCount"));
    args.append(QCFTagArgument("server"));
    args.append(QCFTagArgument("stopOnError"));
    args.append(QCFTagArgument("timeout"));
    args.append(QCFTagArgument("username"));
    ret["cfftp"].m_ArgumentVariants.append(args);

	ret.insert("cffunction", QCFTag("cffunction", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("name", true, QCFTagArgument::TypeConstantString));
	args.append(QCFTagArgument("access"));
	args.append(QCFTagArgument("description"));
	args.append(QCFTagArgument("displayName"));
	args.append(QCFTagArgument("hint"));
	args.append(QCFTagArgument("output"));
	args.append(QCFTagArgument("returnFormat"));
	args.append(QCFTagArgument("returnType"));
	args.append(QCFTagArgument("roles"));
	args.append(QCFTagArgument("secureJSON"));
	args.append(QCFTagArgument("verifyClient"));
	ret["cffunction"].m_ArgumentVariants.append(args);

	ret.insert("cfgraph", QCFTag("cfgraph", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfgraphdata", QCFTag("cfgraphdata", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

    ret.insert("cfgrid", QCFTag("cfgrid", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("name", true));
    args.append(QCFTagArgument("align"));
    args.append(QCFTagArgument("appendKey"));
    args.append(QCFTagArgument("autoWidth"));
    args.append(QCFTagArgument("bgColor"));
    args.append(QCFTagArgument("bind"));
    args.append(QCFTagArgument("bindOnLoad"));
    args.append(QCFTagArgument("bold"));
    args.append(QCFTagArgument("colHeaderAlign"));
    args.append(QCFTagArgument("colHeaderBold"));
    args.append(QCFTagArgument("colHeaderFont"));
    args.append(QCFTagArgument("colHeaderFontSize"));
    args.append(QCFTagArgument("colHeaderItalic"));
    args.append(QCFTagArgument("colHeaders"));
    args.append(QCFTagArgument("colHeaderTextColor"));
    args.append(QCFTagArgument("delete"));
    args.append(QCFTagArgument("deleteButton"));
    args.append(QCFTagArgument("enabled"));
    args.append(QCFTagArgument("font"));
    args.append(QCFTagArgument("fontSize"));
    args.append(QCFTagArgument("format"));
    args.append(QCFTagArgument("gridDataAlign"));
    args.append(QCFTagArgument("gridLines"));
    args.append(QCFTagArgument("height"));
    args.append(QCFTagArgument("highlightHref"));
    args.append(QCFTagArgument("href"));
    args.append(QCFTagArgument("hrefKey"));
    args.append(QCFTagArgument("hSpace"));
    args.append(QCFTagArgument("insert"));
    args.append(QCFTagArgument("insertButton"));
    args.append(QCFTagArgument("italic"));
    args.append(QCFTagArgument("maxRows"));
    args.append(QCFTagArgument("notSupported"));
    args.append(QCFTagArgument("onBlur"));
    args.append(QCFTagArgument("onChange"));
    args.append(QCFTagArgument("onError"));
    args.append(QCFTagArgument("onFocus"));
    args.append(QCFTagArgument("onValidate"));
    args.append(QCFTagArgument("pageSize"));
    args.append(QCFTagArgument("pictureBar"));
    args.append(QCFTagArgument("preservePageOnSort"));
    args.append(QCFTagArgument("query"));
    args.append(QCFTagArgument("rowHeaderAlign"));
    args.append(QCFTagArgument("rowHeaderBold"));
    args.append(QCFTagArgument("rowHeaderFont"));
    args.append(QCFTagArgument("rowHeaderFontSize"));
    args.append(QCFTagArgument("rowHeaderItalic"));
    args.append(QCFTagArgument("rowHeaders"));
    args.append(QCFTagArgument("rowHeaderTextColor"));
    args.append(QCFTagArgument("rowHeight"));
    args.append(QCFTagArgument("selectColor"));
    args.append(QCFTagArgument("selectMode"));
    args.append(QCFTagArgument("selectOnLoad"));
    args.append(QCFTagArgument("sort"));
    args.append(QCFTagArgument("sortAscendingButton"));
    args.append(QCFTagArgument("sortDescendingButton"));
    args.append(QCFTagArgument("stripeRowColor"));
    args.append(QCFTagArgument("stripeRows"));
    args.append(QCFTagArgument("style"));
    args.append(QCFTagArgument("target"));
    args.append(QCFTagArgument("textColor"));
    args.append(QCFTagArgument("tooltip"));
    args.append(QCFTagArgument("visible"));
    args.append(QCFTagArgument("vSpace"));
    args.append(QCFTagArgument("width"));
    ret["cfgrid"].m_ArgumentVariants.append(args);

    ret.insert("cfgridcolumn", QCFTag("cfgridcolumn", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("name", true));
    args.append(QCFTagArgument("bgColor"));
    args.append(QCFTagArgument("bold"));
    args.append(QCFTagArgument("dataAlign"));
    args.append(QCFTagArgument("display"));
    args.append(QCFTagArgument("font"));
    args.append(QCFTagArgument("fontSize"));
    args.append(QCFTagArgument("header"));
    args.append(QCFTagArgument("headerAlign"));
    args.append(QCFTagArgument("headerBold"));
    args.append(QCFTagArgument("headerFont"));
    args.append(QCFTagArgument("headerFontSize"));
    args.append(QCFTagArgument("headerItalic"));
    args.append(QCFTagArgument("headerTextColor"));
    args.append(QCFTagArgument("href"));
    args.append(QCFTagArgument("hrefKey"));
    args.append(QCFTagArgument("italic"));
    args.append(QCFTagArgument("mask"));
    args.append(QCFTagArgument("numberFormat"));
    args.append(QCFTagArgument("select"));
    args.append(QCFTagArgument("target"));
    args.append(QCFTagArgument("textColor"));
    args.append(QCFTagArgument("type"));
    args.append(QCFTagArgument("values"));
    args.append(QCFTagArgument("valuesDelimiter"));
    args.append(QCFTagArgument("valuesDisplay"));
    args.append(QCFTagArgument("width"));
    ret["cfgridcolumn"].m_ArgumentVariants.append(args);
    args.clear();

	ret.insert("cfgridrow", QCFTag("cfgridrow", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("data", true));
    ret["cfgridrow"].m_ArgumentVariants.append(args);

	ret.insert("cfgridupdate", QCFTag("cfgridupdate", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfheader", QCFTag("cfheader", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("charset", false, QCFTagArgument::TypeConstantString));
	args.append(QCFTagArgument("name", true, QCFTagArgument::TypeConstantString));
	args.append(QCFTagArgument("value"));
	ret["cfheader"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("charset", false, QCFTagArgument::TypeConstantString));
	args.append(QCFTagArgument("statusCode", true));
	args.append(QCFTagArgument("statusText"));
	args.append(QCFTagArgument("value"));
	ret["cfheader"].m_ArgumentVariants.append(args);

	ret.insert("cfhtmlhead", QCFTag("cfhtmlhead", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.append(QCFTagArgument("text", true));
    ret["cfhtmlhead"].m_ArgumentVariants.append(args);

	ret.insert("cfhttp", QCFTag("cfhttp", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("url", true));
    args.append(QCFTagArgument("charset"));
    args.append(QCFTagArgument("clientCert"));
    args.append(QCFTagArgument("clientCertPassword"));
    args.append(QCFTagArgument("columns"));
    args.append(QCFTagArgument("delimiter"));
    args.append(QCFTagArgument("file"));
    args.append(QCFTagArgument("firstrowasheaders"));
    args.append(QCFTagArgument("getAsBinary"));
    args.append(QCFTagArgument("method"));
    args.append(QCFTagArgument("multipart"));
    args.append(QCFTagArgument("name"));
    args.append(QCFTagArgument("password"));
    args.append(QCFTagArgument("path"));
    args.append(QCFTagArgument("port"));
    args.append(QCFTagArgument("proxyServer"));
    args.append(QCFTagArgument("proxyPort"));
    args.append(QCFTagArgument("proxyUser"));
    args.append(QCFTagArgument("proxyPassword"));
    args.append(QCFTagArgument("redirect"));
    args.append(QCFTagArgument("resolveURL"));
    args.append(QCFTagArgument("result"));
    args.append(QCFTagArgument("TextQualifier"));
    args.append(QCFTagArgument("throwOnError"));
    args.append(QCFTagArgument("timeout"));
    args.append(QCFTagArgument("username"));
    args.append(QCFTagArgument("userAgent"));
    ret["cfhttp"].m_ArgumentVariants.append(args);

	ret.insert("cfhttpparam", QCFTag("cfhttpparam", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear(); // TODO: Make this argument as it should.
    args.append(QCFTagArgument("type", true));
    args.append(QCFTagArgument("encoded"));
    args.append(QCFTagArgument("file"));
    args.append(QCFTagArgument("mimeType"));
    args.append(QCFTagArgument("name"));
    args.append(QCFTagArgument("value"));
    ret["cfhttpparam"].m_ArgumentVariants.append(args);

	ret.insert("cfif", QCFTag("cfif", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeExpression));

	ret.insert("cfimage", QCFTag("cfimage", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfimpersonate", QCFTag("cfimpersonate", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfimport", QCFTag("cfimport", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("taglib", true));
	args.append(QCFTagArgument("prefix", true));
	ret["cfimport"].m_ArgumentVariants.append(args);
	
	ret.insert("cfinclude", QCFTag("cfinclude", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("template", true));
	ret["cfinclude"].m_ArgumentVariants.append(args);

	ret.insert("cfindex", QCFTag("cfindex", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("action", true));
    args.append(QCFTagArgument("collection", true));
    args.append(QCFTagArgument("key", true));
    args.append(QCFTagArgument("body"));
    args.append(QCFTagArgument("category"));
    args.append(QCFTagArgument("categoryTree"));
    args.append(QCFTagArgument("custom1"));
    args.append(QCFTagArgument("custom2"));
    args.append(QCFTagArgument("custom3"));
    args.append(QCFTagArgument("custom4"));
    args.append(QCFTagArgument("extensions"));
    args.append(QCFTagArgument("language"));
    args.append(QCFTagArgument("prefix"));
    args.append(QCFTagArgument("query"));
    args.append(QCFTagArgument("recurse"));
    args.append(QCFTagArgument("status"));
    args.append(QCFTagArgument("title"));
    args.append(QCFTagArgument("type"));
    args.append(QCFTagArgument("URLpath"));
    ret["cfindex"].m_ArgumentVariants.append(args);

	ret.insert("cfinput", QCFTag("cfinput", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("name", true, QCFTagArgument::TypeConstantString));
	args.append(QCFTagArgument("autosuggest"));
	args.append(QCFTagArgument("autosuggestBindDelay"));
	args.append(QCFTagArgument("autosuggestMinLength"));
	args.append(QCFTagArgument("bind"));
	args.append(QCFTagArgument("bindAttribute"));
	args.append(QCFTagArgument("bindOnLoad"));
	args.append(QCFTagArgument("checked"));
	args.append(QCFTagArgument("dayNames"));
	args.append(QCFTagArgument("delimiter"));
	args.append(QCFTagArgument("disabled"));
	args.append(QCFTagArgument("enabled"));
	args.append(QCFTagArgument("firstDayOfWeek"));
	args.append(QCFTagArgument("height"));
	args.append(QCFTagArgument("id"));
	args.append(QCFTagArgument("label"));
	args.append(QCFTagArgument("mask"));
	args.append(QCFTagArgument("maxLength"));
	args.append(QCFTagArgument("maxResultsDisplayed"));
	args.append(QCFTagArgument("message"));
	args.append(QCFTagArgument("monthNames"));
	args.append(QCFTagArgument("onBindError"));
	args.append(QCFTagArgument("onChange"));
	args.append(QCFTagArgument("onClick"));
	args.append(QCFTagArgument("onError"));
	// TODO: more
	ret["cfinput"].m_ArgumentVariants.append(args);

	ret.insert("cfinsert", QCFTag("cfinsert", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfinterface", QCFTag("cfinterface", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfinvoke", QCFTag("cfinvoke", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("component", true));
    args.append(QCFTagArgument("method", true));
    args.append(QCFTagArgument("argumentCollection"));
    args.append(QCFTagArgument("password"));
    args.append(QCFTagArgument("returnVariable"));
    args.append(QCFTagArgument("username"));
    ret["cfinvoke"].m_ArgumentVariants.append(args);
    args.clear();
    args.append(QCFTagArgument("method", true));
    args.append(QCFTagArgument("argumentCollection"));
    args.append(QCFTagArgument("component"));
    args.append(QCFTagArgument("password"));
    args.append(QCFTagArgument("returnVariable"));
    args.append(QCFTagArgument("username"));
    ret["cfinvoke"].m_ArgumentVariants.append(args);
    args.clear();
    args.append(QCFTagArgument("method", true));
    args.append(QCFTagArgument("webservice", true));
    args.append(QCFTagArgument("argumentCollection"));
    args.append(QCFTagArgument("component"));
    args.append(QCFTagArgument("password"));
    args.append(QCFTagArgument("proxyPassword"));
    args.append(QCFTagArgument("proxyPort"));
    args.append(QCFTagArgument("proxyServer"));
    args.append(QCFTagArgument("proxyUser"));
    args.append(QCFTagArgument("returnVariable"));
    args.append(QCFTagArgument("servicePort"));
    args.append(QCFTagArgument("timeout"));
    args.append(QCFTagArgument("username"));
    args.append(QCFTagArgument("wsdl2javaArgs"));
    ret["cfinvoke"].m_ArgumentVariants.append(args);

	ret.insert("cfinvokeargument", QCFTag("cfinvokeargument", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("name", true));
    args.append(QCFTagArgument("value", true));
    args.append(QCFTagArgument("omit"));
    ret["cfinvokeargument"].m_ArgumentVariants.append(args);

	ret.insert("cflayout", QCFTag("cflayout", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cflayoutarea", QCFTag("cflayoutarea", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfldap", QCFTag("cfldap", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cflocation", QCFTag("cflocation", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("url", true));
	args.append(QCFTagArgument("addToken"));
	args.append(QCFTagArgument("statusCode"));
	ret["cflocation"].m_ArgumentVariants.append(args);

	ret.insert("cflock", QCFTag("cflock", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("timeout", true));
	args.append(QCFTagArgument("name"));
	args.append(QCFTagArgument("scope"));
	args.append(QCFTagArgument("throwOnTimeout"));
	args.append(QCFTagArgument("type"));
	ret["cflock"].m_ArgumentVariants.append(args);

	ret.insert("cflog", QCFTag("cflog", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("text", true));
	args.append(QCFTagArgument("application"));
	args.append(QCFTagArgument("file"));
	args.append(QCFTagArgument("log"));
	args.append(QCFTagArgument("type"));
	ret["cflog"].m_ArgumentVariants.append(args);

    ret.insert("cflogin", QCFTag("cflogin", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

    ret.insert("cfloginuser", QCFTag("cfloginuser", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("name", true));
    args.append(QCFTagArgument("password", true));
    args.append(QCFTagArgument("roles", true));
    ret["cfloginuser"].m_ArgumentVariants.append(args);

    ret.insert("cflogout", QCFTag("cflogout", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfloop", QCFTag("cfloop", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("index", true, QCFTagArgument::TypeVariable));
	args.append(QCFTagArgument("from", true, QCFTagArgument::TypeConstantString));
	args.append(QCFTagArgument("to", true, QCFTagArgument::TypeConstantString));
	args.append(QCFTagArgument("step", false, QCFTagArgument::TypeConstantString));
	ret["cfloop"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("condition", true, QCFTagArgument::TypeExpression));
	ret["cfloop"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("query", true, QCFTagArgument::TypeVariable));
	args.append(QCFTagArgument("startRow", false, QCFTagArgument::TypeExpression));
	args.append(QCFTagArgument("endRow", false, QCFTagArgument::TypeExpression));
	ret["cfloop"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("index", true, QCFTagArgument::TypeVariable));
	args.append(QCFTagArgument("list", true, QCFTagArgument::TypeVariable));
	args.append(QCFTagArgument("delimiters", false, QCFTagArgument::TypeConstantString));
	ret["cfloop"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("index", true, QCFTagArgument::TypeVariable));
	args.append(QCFTagArgument("file", true));
	args.append(QCFTagArgument("characters"));
	ret["cfloop"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("index", true, QCFTagArgument::TypeVariable));
	args.append(QCFTagArgument("array", true));
	ret["cfloop"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("collection", true));
	args.append(QCFTagArgument("item", true));
	ret["cfloop"].m_ArgumentVariants.append(args);

	ret.insert("cfmail", QCFTag("cfmail", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments, QCFTag::WithExpressionInside));
    args.clear();
    args.append(QCFTagArgument("from", true));
    args.append(QCFTagArgument("to", true));
    args.append(QCFTagArgument("bcc"));
    args.append(QCFTagArgument("cc"));
    args.append(QCFTagArgument("charset"));
    args.append(QCFTagArgument("debug"));
    args.append(QCFTagArgument("failto"));
    args.append(QCFTagArgument("group"));
    args.append(QCFTagArgument("groupcasesensitive"));
    args.append(QCFTagArgument("mailerid"));
    args.append(QCFTagArgument("maxrows"));
    args.append(QCFTagArgument("mimeattach"));
    args.append(QCFTagArgument("password"));
    args.append(QCFTagArgument("port"));
    args.append(QCFTagArgument("priority"));
    args.append(QCFTagArgument("query"));
    args.append(QCFTagArgument("replyto"));
    args.append(QCFTagArgument("server"));
    args.append(QCFTagArgument("spoolenable"));
    args.append(QCFTagArgument("startrow"));
    args.append(QCFTagArgument("subject", true));
    args.append(QCFTagArgument("timeout"));
    args.append(QCFTagArgument("type"));
    args.append(QCFTagArgument("username"));
    args.append(QCFTagArgument("useSSL"));
    args.append(QCFTagArgument("useTLS"));
    args.append(QCFTagArgument("wraptext"));
    ret["cfmail"].m_ArgumentVariants.append(args);

	ret.insert("cfmailparam", QCFTag("cfmailparam", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfmailpart", QCFTag("cfmailpart", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("type", true));
    args.append(QCFTagArgument("charset"));
    args.append(QCFTagArgument("wraptext"));
    ret["cfmailpart"].m_ArgumentVariants.append(args);

	ret.insert("cfmenu", QCFTag("cfmenu", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfmenuitem", QCFTag("cfmenuitem", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

    ret.insert("cfmodule", QCFTag("cfmodule", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments, QCFTag::WithoutExpressionInside, true));

	ret.insert("cfNTauthenticate", QCFTag("cfNTauthenticate", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfobject", QCFTag("cfobject", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("component", true));
	args.append(QCFTagArgument("name", true));
	args.append(QCFTagArgument("type", false, QCFTagArgument::TypeConstantString, "component"));
	ret["cfobject"].m_ArgumentVariants.append(args);

	ret.insert("cfobjectcache", QCFTag("cfobjectcache", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfoutput", QCFTag("cfoutput", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments, QCFTag::WithExpressionInside));
    args.clear();
    ret["cfoutput"].m_ArgumentVariants.append(args);
    args.append(QCFTagArgument("query", true));
    ret["cfoutput"].m_ArgumentVariants.append(args);

	ret.insert("cfparam", QCFTag("cfparam", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("name", true));
	args.append(QCFTagArgument("default"));
	args.append(QCFTagArgument("max"));
	args.append(QCFTagArgument("min"));
	args.append(QCFTagArgument("pattern"));
	args.append(QCFTagArgument("type"));
	ret["cfparam"].m_ArgumentVariants.append(args);

	ret.insert("cfpdf", QCFTag("cfpdf", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfpdfform", QCFTag("cfpdfform", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfpdfformparam", QCFTag("cfpdfformparam", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfpdfparam", QCFTag("cfpdfparam", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfpdfsubform", QCFTag("cfpdfsubform", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfpod", QCFTag("cfpod", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfpop", QCFTag("cfpop", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfpresentation", QCFTag("cfpresentation", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfpresentationslide", QCFTag("cfpresentationslide", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfpresenter", QCFTag("cfpresenter", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfprint", QCFTag("cfprint", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfprocessingdirective", QCFTag("cfprocessingdirective", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("pageEncoding"));
	args.append(QCFTagArgument("suppressWhiteSpace"));
	ret["cfprocessingdirective"].m_ArgumentVariants.append(args);

    ret.insert("cfprocparam", QCFTag("cfprocparam", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("CFSQLType", true));
    args.append(QCFTagArgument("maxLength"));
    args.append(QCFTagArgument("null"));
    args.append(QCFTagArgument("scale"));
    args.append(QCFTagArgument("type"));
    args.append(QCFTagArgument("value"));
    args.append(QCFTagArgument("variable"));
    ret["cfprocparam"].m_ArgumentVariants.append(args);

    ret.insert("cfprocresult", QCFTag("cfprocresult", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("name", true));
    args.append(QCFTagArgument("maxRows"));
    args.append(QCFTagArgument("resultSet"));
    ret["cfprocresult"].m_ArgumentVariants.append(args);

    ret.insert("cfproperty", QCFTag("cfproperty", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("name", true));
    args.append(QCFTagArgument("default"));
    args.append(QCFTagArgument("displayname"));
    args.append(QCFTagArgument("hint"));
    args.append(QCFTagArgument("required"));
    args.append(QCFTagArgument("type"));
    ret["cfproperty"].m_ArgumentVariants.append(args);

	ret.insert("cfquery", QCFTag("cfquery", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments, QCFTag::WithExpressionInside));
	args.clear();
	args.append(QCFTagArgument("name"));
	args.append(QCFTagArgument("blockFactor"));
	args.append(QCFTagArgument("cachedAfter"));
	args.append(QCFTagArgument("cachedWithin"));
	args.append(QCFTagArgument("dataSource"));
	args.append(QCFTagArgument("dbtype"));
	args.append(QCFTagArgument("debug"));
	args.append(QCFTagArgument("maxRows"));
	args.append(QCFTagArgument("password"));
	args.append(QCFTagArgument("result"));
	args.append(QCFTagArgument("timeout"));
	args.append(QCFTagArgument("username"));
	ret["cfquery"].m_ArgumentVariants.append(args);

	ret.insert("cfqueryparam", QCFTag("cfqueryparam", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("value", true));
	args.append(QCFTagArgument("CFSQLType"));
	args.append(QCFTagArgument("list"));
	args.append(QCFTagArgument("maxLength"));
	args.append(QCFTagArgument("null"));
	args.append(QCFTagArgument("scale"));
	args.append(QCFTagArgument("separator"));
	ret["cfqueryparam"].m_ArgumentVariants.append(args);

	ret.insert("cfregistry", QCFTag("cfregistry", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfreport", QCFTag("cfreport", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfreportparam", QCFTag("cfreportparam", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfrethrow", QCFTag("cfrethrow", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfreturn", QCFTag("cfreturn", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeExpression));

	ret.insert("cfsavecontent", QCFTag("cfsavecontent", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("variable"));
    ret["cfsavecontent"].m_ArgumentVariants.append(args);

	ret.insert("cfschedule", QCFTag("cfschedule", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("action", true));
    args.append(QCFTagArgument("task", true));
    args.append(QCFTagArgument("endDate"));
    args.append(QCFTagArgument("endTime"));
    args.append(QCFTagArgument("file"));
    args.append(QCFTagArgument("interval"));
    args.append(QCFTagArgument("operation"));
    args.append(QCFTagArgument("password"));
    args.append(QCFTagArgument("path"));
    args.append(QCFTagArgument("port"));
    args.append(QCFTagArgument("proxyPassword"));
    args.append(QCFTagArgument("proxyPort"));
    args.append(QCFTagArgument("proxyServer"));
    args.append(QCFTagArgument("proxyUser"));
    args.append(QCFTagArgument("publish"));
    args.append(QCFTagArgument("requestTimeOut"));
    args.append(QCFTagArgument("resolveURL"));
    args.append(QCFTagArgument("startDate"));
    args.append(QCFTagArgument("startTime"));
    args.append(QCFTagArgument("url"));
    args.append(QCFTagArgument("username"));
    ret["cfschedule"].m_ArgumentVariants.append(args);

	ret.insert("cfscript", QCFTag("cfscript", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    ret["cfscript"].m_ArgumentVariants.append(args);

	ret.insert("cfsearch", QCFTag("cfsearch", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("name", true));
    args.append(QCFTagArgument("collection", true));
    args.append(QCFTagArgument("category"));
    args.append(QCFTagArgument("categoryTree"));
    args.append(QCFTagArgument("contextBytes"));
    args.append(QCFTagArgument("contextHighlightBegin"));
    args.append(QCFTagArgument("contextHighlightEnd"));
    args.append(QCFTagArgument("contextPassages"));
    args.append(QCFTagArgument("criteria"));
    args.append(QCFTagArgument("language"));
    args.append(QCFTagArgument("maxRows"));
    args.append(QCFTagArgument("previousCriteria"));
    args.append(QCFTagArgument("startRow"));
    args.append(QCFTagArgument("status"));
    args.append(QCFTagArgument("suggestions"));
    args.append(QCFTagArgument("type"));
    ret["cfsearch"].m_ArgumentVariants.append(args);

	ret.insert("cfselect", QCFTag("cfselect", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	// TODO: more..
	ret["cfselect"].m_ArgumentVariants.append(args);

	ret.insert("cfservlet", QCFTag("cfservlet", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfservletparam", QCFTag("cfservletparam", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfset", QCFTag("cfset", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeExpression));

	ret.insert("cfsetting", QCFTag("cfsetting", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("enableCFoutputOnly"));
	args.append(QCFTagArgument("requestTimeout"));
	args.append(QCFTagArgument("showDebugOutput"));
	ret["cfsetting"].m_ArgumentVariants.append(args);

	ret.insert("cfsilent", QCFTag("cfsilent", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfslider", QCFTag("cfslider", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfsprydataset", QCFTag("cfsprydataset", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

    ret.insert("cfstoredproc", QCFTag("cfstoredproc", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("dataSource", true));
    args.append(QCFTagArgument("procedure", true));
    args.append(QCFTagArgument("blockFactor"));
    args.append(QCFTagArgument("debug"));
    args.append(QCFTagArgument("password"));
    args.append(QCFTagArgument("result"));
    args.append(QCFTagArgument("returnCode"));
    args.append(QCFTagArgument("username"));
    ret["cfstoredproc"].m_ArgumentVariants.append(args);

	ret.insert("cfswitch", QCFTag("cfswitch", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("expression", true));
	ret["cfswitch"].m_ArgumentVariants.append(args);

	ret.insert("cftable", QCFTag("cftable", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

    ret.insert("cftextarea", QCFTag("cftextarea", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("name", true));
    args.append(QCFTagArgument("basepath"));
    args.append(QCFTagArgument("bind"));
    args.append(QCFTagArgument("bindAttribute"));
    args.append(QCFTagArgument("bindOnLoad"));
    args.append(QCFTagArgument("disabled"));
    args.append(QCFTagArgument("enabled"));
    args.append(QCFTagArgument("fontFormats"));
    args.append(QCFTagArgument("fontNames"));
    args.append(QCFTagArgument("fontSizes"));
    args.append(QCFTagArgument("height"));
    args.append(QCFTagArgument("html"));
    args.append(QCFTagArgument("label"));
    args.append(QCFTagArgument("maxlength"));
    args.append(QCFTagArgument("message"));
    args.append(QCFTagArgument("onBindError"));
    args.append(QCFTagArgument("onChange"));
    args.append(QCFTagArgument("onClick"));
    args.append(QCFTagArgument("onError"));
    args.append(QCFTagArgument("onKeyDown"));
    args.append(QCFTagArgument("onKeyUp"));
    args.append(QCFTagArgument("onMouseDown"));
    args.append(QCFTagArgument("onMouseUp"));
    args.append(QCFTagArgument("onValidate"));
    args.append(QCFTagArgument("pattern"));
    args.append(QCFTagArgument("range"));
    args.append(QCFTagArgument("required"));
    args.append(QCFTagArgument("richtext"));
    args.append(QCFTagArgument("skin"));
    args.append(QCFTagArgument("sourceForToolTip"));
    args.append(QCFTagArgument("style"));
    args.append(QCFTagArgument("stylesXML"));
    args.append(QCFTagArgument("templatesXML"));
    args.append(QCFTagArgument("toolbar"));
    args.append(QCFTagArgument("toolbarOnFocus"));
    args.append(QCFTagArgument("tooltip"));
    args.append(QCFTagArgument("validate"));
    args.append(QCFTagArgument("validateAt"));
    args.append(QCFTagArgument("value"));
    args.append(QCFTagArgument("visible"));
    args.append(QCFTagArgument("width"));
    args.append(QCFTagArgument("wrap"));
    ret["cftextarea"].m_ArgumentVariants.append(args);

	ret.insert("cftextinput", QCFTag("cftextinput", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfthread", QCFTag("cfthread", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("action"));
    args.append(QCFTagArgument("duration"));
    args.append(QCFTagArgument("name"));
    args.append(QCFTagArgument("priority"));
    args.append(QCFTagArgument("timeout"));
    ret["cfthread"].m_ArgumentVariants.append(args);

	ret.insert("cfthrow", QCFTag("cfthrow", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("detail"));
    args.append(QCFTagArgument("errorCode"));
    args.append(QCFTagArgument("extendedInfo"));
    args.append(QCFTagArgument("message"));
    ret["cfthrow"].m_ArgumentVariants.append(args);

	ret.insert("cftimer", QCFTag("cftimer", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("label", false, QCFTagArgument::TypeConstantString));
    ret["cftimer"].m_ArgumentVariants.append(args);
    args.clear();
    args.append(QCFTagArgument("label", false, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument("type", false, QCFTagArgument::TypeConstantString, "inline"));
    ret["cftimer"].m_ArgumentVariants.append(args);
    args.clear();
    args.append(QCFTagArgument("label", false, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument("type", false, QCFTagArgument::TypeConstantString, "outline"));
    ret["cftimer"].m_ArgumentVariants.append(args);
    args.clear();
    args.append(QCFTagArgument("label", false, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument("type", false, QCFTagArgument::TypeConstantString, "comment"));
    ret["cftimer"].m_ArgumentVariants.append(args);
    args.clear();
    args.append(QCFTagArgument("label", false, QCFTagArgument::TypeConstantString));
    args.append(QCFTagArgument("type", false, QCFTagArgument::TypeConstantString, "debug"));
    ret["cftimer"].m_ArgumentVariants.append(args);

	ret.insert("cftooltip", QCFTag("cftooltip", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cftrace", QCFTag("cftrace", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("abort"));
	args.append(QCFTagArgument("category"));
	args.append(QCFTagArgument("inline"));
	args.append(QCFTagArgument("text"));
	ret["cftrace"].m_ArgumentVariants.append(args);

	ret.insert("cftransaction", QCFTag("cftransaction", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert("cftree", QCFTag("cftree", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cftreeitem", QCFTag("cftreeitem", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cftry", QCFTag("cftry", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfupdate", QCFTag("cfupdate", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

    ret.insert("cfwddx", QCFTag("cfwddx", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
    args.clear();
    args.append(QCFTagArgument("name", true, QCFTagArgument::TypeConstantString, "cfml2wddx"));
    args.append(QCFTagArgument("input", true));
    args.append(QCFTagArgument("output", false));
    args.append(QCFTagArgument("useTimeZoneInfo", false));
    ret["cfwddx"].m_ArgumentVariants.append(args);
    args.clear();
    args.append(QCFTagArgument("name", true, QCFTagArgument::TypeConstantString, "wddx2cfml"));
    args.append(QCFTagArgument("input", true));
    args.append(QCFTagArgument("output", true));
    args.append(QCFTagArgument("validate", false));
    ret["cfwddx"].m_ArgumentVariants.append(args);
    args.clear();
    args.append(QCFTagArgument("name", true, QCFTagArgument::TypeConstantString, "cfml2js"));
    args.append(QCFTagArgument("input", true));
    args.append(QCFTagArgument("output", false));
    args.append(QCFTagArgument("topLevelVariable", true));
    ret["cfwddx"].m_ArgumentVariants.append(args);
    args.clear();
    args.append(QCFTagArgument("name", true, QCFTagArgument::TypeConstantString, "wddx2js"));
    args.append(QCFTagArgument("input", true));
    args.append(QCFTagArgument("output", false));
    args.append(QCFTagArgument("topLevelVariable", true));
    args.append(QCFTagArgument("validate", false));
    ret["cfwddx"].m_ArgumentVariants.append(args);

	ret.insert("cfwindow", QCFTag("cfwindow", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfxml", QCFTag("cfxml", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("variable", true));
	args.append(QCFTagArgument("caseSensitive"));
	ret["cfxml"].m_ArgumentVariants.append(args);

	ret.insert("cfzip", QCFTag("cfzip", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfzipparam", QCFTag("cfzipparam", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	return ret;
}

QHash<QString, QCFFunction> QCF8::generateCFFunctions()
{
	QHash<QString, QCFFunction> ret;

	ret.insert("abs", QCFFunction("Abs", QCFFunction::ReturnDouble));
	ret["abs"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDouble, true));

	ret.insert("acos", QCFFunction("ACos", QCFFunction::ReturnDouble));
	ret["acos"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDouble, true));

	//ret.insert("addsoaprequestheader", QCFFunction("AddSOAPRequestHeader", QCFFunction::ReturnVoid));
	//ret["addsoaprequestheader"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeVariable));
	//ret["addsoaprequestheader"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true));
	//ret["addsoaprequestheader"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true));
	//ret["addsoaprequestheader"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true));
	//ret["addsoaprequestheader"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBool, false));

	//ret.insert("addsoapresponseheader", QCFFunction("AddSOAPResponseHeader", QCFFunction::ReturnVoid));
	//ret["addsoapresponseheader"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true));
	//ret["addsoapresponseheader"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true));
	//ret["addsoapresponseheader"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true));
	//ret["addsoapresponseheader"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBool, false));

	//ret.insert("ajaxlink", QCFFunction("AjaxLink", QCFFunction::ReturnString));
	//ret["ajaxlink"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true));

	//ret.insert("ajaxonload", QCFFunction("AjaxOnLoad", QCFFunction::ReturnVoid));
	//ret["ajaxonload"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true));

    // ColdFusion 9
	//ret.insert("applicationstop", QCFFunction("ApplicationStop", QCFFunction::ReturnVoid));

	ret.insert("arrayappend", QCFFunction("ArrayAppend", QCFFunction::ReturnBool));
	ret["arrayappend"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
	ret["arrayappend"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeAny, true));

	ret.insert("arrayavg", QCFFunction("ArrayAvg", QCFFunction::ReturnDouble));
	ret["arrayavg"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

	ret.insert("arrayclear", QCFFunction("ArrayClear", QCFFunction::ReturnBool));
	ret["arrayclear"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    // ColdFusion 9
    //ret.insert("arraycontains", QCFFunction("ArrayContains", QCFFunction::ReturnBool));
    //ret["arraycontains"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    // ColdFusion 9
    //ret.insert("arraydelete", QCFFunction("ArrayDelete", QCFFunction::ReturnBool));
    //ret["arraydelete"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    //ret["arraydelete"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

	ret.insert("arraydeleteat", QCFFunction("ArrayDeleteAt", QCFFunction::ReturnBool));
	ret["arraydeleteat"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
	ret["arraydeleteat"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true));

    // ColdFusion 9
    //ret.insert("arrayfind", QCFFunction("ArrayFind", QCFFunction::ReturnInt));
    //ret["arrayfind"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    //ret["arrayfind"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true));

    // ColdFusion 9
	// ArrayFindNoCase;

    ret.insert("arrayinsertsat", QCFFunction("ArrayInsertAt", QCFFunction::ReturnBool));
    ret["arrayinsertsat"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret["arrayinsertsat"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret["arrayinsertsat"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeAny, true, QCFFunctionArgument::TypeAny));

    ret.insert("arrayisdefined", QCFFunction("ArrayIsDefined", QCFFunction::ReturnBool));
    ret["arrayisdefined"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret["arrayisdefined"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert("arrayisempty", QCFFunction("ArrayIsEmpty", QCFFunction::ReturnBool));
    ret["arrayisempty"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    ret.insert("arraylen", QCFFunction("ArrayLen", QCFFunction::ReturnBool));
    ret["arraylen"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    ret.insert("arraymax", QCFFunction("ArrayMax", QCFFunction::ReturnDouble));
    ret["arraymax"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    ret.insert("arraymin", QCFFunction("ArrayMin", QCFFunction::ReturnDouble));
    ret["arraymin"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    ret.insert("arraynew", QCFFunction("ArrayNew", QCFFunction::ReturnQWDDX));
    ret["arraynew"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert("arrayprepend", QCFFunction("ArrayPrepend", QCFFunction::ReturnBool));
    ret["arrayprepend"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret["arrayprepend"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeAny, true, QCFFunctionArgument::TypeAny));

    ret.insert("arrayresize", QCFFunction("ArrayResize", QCFFunction::ReturnBool));
    ret["arrayresize"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret["arrayresize"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert("arrayset", QCFFunction("ArraySet", QCFFunction::ReturnBool));
    ret["arrayset"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret["arrayset"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret["arrayset"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret["arrayset"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeAny));

    ret.insert("arraysort", QCFFunction("ArraySort", QCFFunction::ReturnBool));
    ret["arraysort"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret["arraysort"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret["arraysort"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));

    ret.insert("arraysum", QCFFunction("ArraySum", QCFFunction::ReturnDouble));
    ret["arraysum"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

    ret.insert("arrayswap", QCFFunction("ArraySwap", QCFFunction::ReturnBool));
    ret["arrayswap"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret["arrayswap"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
    ret["arrayswap"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

    ret.insert("arraytolist", QCFFunction("ArrayToList", QCFFunction::ReturnString));
    ret["arraytolist"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret["arraytolist"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));


	//ret.insert("Asc", QCFFunction("Asc"));
	//ret.insert("ASin", QCFFunction("ASin"));
	//ret.insert("Atn", QCFFunction("Atn"));
	//ret.insert("BinaryDecode", QCFFunction("BinaryDecode"));
	//ret.insert("BinaryEncode", QCFFunction("BinaryEncode"));
	//ret.insert("BitAnd", QCFFunction("BitAnd"));
	//ret.insert("BitMaskClear", QCFFunction("BitMaskClear"));
	//ret.insert("BitMaskRead", QCFFunction("BitMaskRead"));
	//ret.insert("BitMaskSet", QCFFunction("BitMaskSet"));
	//ret.insert("BitNot", QCFFunction("BitNot"));
	//ret.insert("BitOr", QCFFunction("BitOr"));
	//ret.insert("BitSHLN", QCFFunction("BitSHLN"));
	//ret.insert("BitSHRN", QCFFunction("BitSHRN"));
	//ret.insert("BitXor", QCFFunction("BitXor"));
	//ret.insert("Ceiling", QCFFunction("Ceiling"));
	//ret.insert("CharsetDecode", QCFFunction("CharsetDecode"));
	//ret.insert("CharsetEncode", QCFFunction("CharsetEncode"));
	ret.insert("chr", QCFFunction("Chr", QCFFunction::ReturnString));
	ret["chr"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

	//ret.insert("CJustify", QCFFunction("CJustify"));
	//ret.insert("Compare", QCFFunction("Compare"));
	//ret.insert("CompareNoCase", QCFFunction("CompareNoCase"));

	//ret.insert("Cos", QCFFunction("Cos"));
	//ret.insert("CreateDate", QCFFunction("CreateDate"));
	//ret.insert("CreateDateTime", QCFFunction("CreateDateTime"));

	//ret.insert("CreateObject", QCFFunction("CreateObject"));
	//ret.insert("BitNot", QCFFunction("BitNot"));
	//ret.insert("BitNot", QCFFunction("BitNot"));

	ret.insert("fix", QCFFunction("Fix", QCFFunction::ReturnInt));
	ret["fix"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeDouble, true, QCFFunctionArgument::TypeAny));

    ret.insert("isarray", QCFFunction("IsArray", QCFFunction::ReturnBool));
    ret["isarray"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
    ret["isarray"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, false, QCFFunctionArgument::TypeAny));

	ret.insert("lcase", QCFFunction("LCase", QCFFunction::ReturnString));
	ret["lcase"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

	ret.insert("left", QCFFunction("Left", QCFFunction::ReturnString));
	ret["left"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
	ret["left"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));

	ret.insert("len", QCFFunction("Len", QCFFunction::ReturnInt));
	ret["len"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));

    ret.insert("listtoarray", QCFFunction("ListToArray", QCFFunction::ReturnQWDDX));
    ret["listtoarray"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, true, QCFFunctionArgument::TypeAny));
    ret["listtoarray"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeString, false, QCFFunctionArgument::TypeAny));
    ret["listtoarray"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeBool, false, QCFFunctionArgument::TypeAny));

    ret.insert("structnew", QCFFunction("StructNew", QCFFunction::ReturnQWDDX));

    return ret;
}
