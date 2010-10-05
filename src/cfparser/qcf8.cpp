#include "qcf8.h"

QHash<QString, QCFTag> QCF8::generateCFTags()
{
	QHash<QString, QCFTag> ret;
	QList<QCFTagArgument> args;

	ret.insert("cfabort", QCFTag("cfabort", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("showError"));
	ret["cfabort"].m_ArgumentVariants.append(args);

	ret.insert("cfadmin", QCFTag("cfadmin", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments)); // Railo cftag

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

	ret.insert("cfcol", QCFTag("cfcol", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfcollection", QCFTag("cfcollection", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfcomponent", QCFTag("cfcomponent", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfcontent", QCFTag("cfcontent", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfcookie", QCFTag("cfcookie", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

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

	ret.insert("cfdocumentitem", QCFTag("cfdocumentitem", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfdocumentsection", QCFTag("cfdocumentsection", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

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

	ret.insert("cfformgroup", QCFTag("cfformgroup", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfformitem", QCFTag("cfformitem", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfftp", QCFTag("cfftp", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

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

	//ret.insert("cfgraph", QCFTag("cfgraph"));
	//ret.insert("cfgraphdata", QCFTag("cfgraphdata"));
	//ret.insert("cfgrid", QCFTag("cfgrid"));
	//ret.insert("cfgridcolumn", QCFTag("cfgridcolumn"));
	//ret.insert("cfgridrow", QCFTag("cfgridrow"));
	//ret.insert("cfgridupdate", QCFTag("cfgridupdate"));
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

	ret.insert("cfhttp", QCFTag("cfhttp", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
	ret.insert("cfhttpparam", QCFTag("cfhttpparam", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfif", QCFTag("cfif", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeExpression));

	//ret.insert("cfimage", QCFTag("cfimage"));
	//ret.insert("cfimpersonate", QCFTag("cfimpersonate"));

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
	//ret.insert("cfinput", QCFTag("cfinput"));
	//ret.insert("cfinsert", QCFTag("cfinsert"));
	//ret.insert("cfinterface", QCFTag("cfinterface"));
	ret.insert("cfinvoke", QCFTag("cfinvoke", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
	ret.insert("cfinvokeargument", QCFTag("cfinvokeargument", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	//ret.insert("cflayout", QCFTag("cflayout"));
	//ret.insert("cflayoutarea", QCFTag("cflayoutarea"));
	//ret.insert("cfldap", QCFTag("cfldap"));

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

	//ret.insert("cflogin", QCFTag("cflogin"));
	//ret.insert("cfloginuser", QCFTag("cfloginuser"));
	//ret.insert("cflogout", QCFTag("cflogout"));

	ret.insert("cfloop", QCFTag("cfloop", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("index", true, QCFTagArgument::TypeVariable));
	args.append(QCFTagArgument("from", true));
	args.append(QCFTagArgument("to", true));
	args.append(QCFTagArgument("step"));
	ret["cfloop"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("condition", true, QCFTagArgument::TypeVariable));
	ret["cfloop"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("query", true));
	args.append(QCFTagArgument("startRow"));
	args.append(QCFTagArgument("endRow"));
	ret["cfloop"].m_ArgumentVariants.append(args);
	args.clear();
	args.append(QCFTagArgument("index", true, QCFTagArgument::TypeVariable));
	args.append(QCFTagArgument("list", true));
	args.append(QCFTagArgument("delimiters"));
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
	//ret.insert("cfmailparam", QCFTag("cfmailparam"));
	ret.insert("cfmailpart", QCFTag("cfmailpart", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	//ret.insert("cfmenu", QCFTag("cfmenu"));
	//ret.insert("cfmenuitem", QCFTag("cfmenuitem"));
	ret.insert("cfmodule", QCFTag("cfmodule", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	//ret.insert("cfNTauthenticate", QCFTag("cfNTauthenticate"));

	ret.insert("cfobject", QCFTag("cfobject", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("component", true));
	args.append(QCFTagArgument("name", true));
	args.append(QCFTagArgument("type", false, QCFTagArgument::TypeConstantString, "component"));
	ret["cfobject"].m_ArgumentVariants.append(args);

	//ret.insert("cfobjectcache", QCFTag("cfobjectcache"));

	ret.insert("cfoutput", QCFTag("cfoutput", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments, QCFTag::WithExpressionInside));

	ret.insert("cfparam", QCFTag("cfparam", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("name", true));
	args.append(QCFTagArgument("default"));
	args.append(QCFTagArgument("max"));
	args.append(QCFTagArgument("min"));
	args.append(QCFTagArgument("pattern"));
	args.append(QCFTagArgument("type"));
	ret["cfparam"].m_ArgumentVariants.append(args);

	//ret.insert("cfpdf", QCFTag("cfpdf"));
	//ret.insert("cfpdfform", QCFTag("cfpdfform"));
	//ret.insert("cfpdfformparam", QCFTag("cfpdfformparam"));
	//ret.insert("cfpdfparam", QCFTag("cfpdfparam"));
	//ret.insert("cfpdfsubform", QCFTag("cfpdfsubform"));
	//ret.insert("cfpod", QCFTag("cfpod"));
	//ret.insert("cfpop", QCFTag("cfpop"));
	//ret.insert("cfpresentation", QCFTag("cfpresentation"));
	//ret.insert("cfpresentationslide", QCFTag("cfpresentationslide"));
	//ret.insert("cfpresenter", QCFTag("cfpresenter"));
	//ret.insert("cfprint", QCFTag("cfprint"));

	ret.insert("cfprocessingdirective", QCFTag("cfprocessingdirective", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("pageEncoding"));
	args.append(QCFTagArgument("suppressWhiteSpace"));
	ret["cfprocessingdirective"].m_ArgumentVariants.append(args);

	//ret.insert("cfprocparam", QCFTag("cfprocparam"));
	//ret.insert("cfprocresult", QCFTag("cfprocresult"));
	ret.insert("cfproperty", QCFTag("cfproperty", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

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

	//ret.insert("cfregistry", QCFTag("cfregistry"));
	//ret.insert("cfreport", QCFTag("cfreport"));
	//ret.insert("cfreportparam", QCFTag("cfreportparam"));
	//ret.insert("cfrethrow", QCFTag("cfrethrow"));
	ret.insert("cfreturn", QCFTag("cfreturn", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeExpression));

	ret.insert("cfsavecontent", QCFTag("cfsavecontent", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfschedule", QCFTag("cfschedule", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfscript", QCFTag("cfscript", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	ret.insert("cfsearch", QCFTag("cfsearch", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	//ret.insert("cfselect", QCFTag("cfselect"));
	//ret.insert("cfservlet", QCFTag("cfservlet"));
	//ret.insert("cfservletparam", QCFTag("cfservletparam"));

	ret.insert("cfset", QCFTag("cfset", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeExpression));

	ret.insert("cfsetting", QCFTag("cfsetting", QCFTag::TagTypeWithoutCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("enableCFoutputOnly"));
	args.append(QCFTagArgument("requestTimeout"));
	args.append(QCFTagArgument("showDebugOutput"));
	ret["cfsetting"].m_ArgumentVariants.append(args);

	ret.insert("cfsilent", QCFTag("cfsilent", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));

	//ret.insert("cfslider", QCFTag("cfslider"));
	//ret.insert("cfsprydataset", QCFTag("cfsprydataset"));
	//ret.insert("cfstoredproc", QCFTag("cfstoredproc"));

	ret.insert("cfswitch", QCFTag("cfswitch", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("expression", true));
	ret["cfswitch"].m_ArgumentVariants.append(args);

	//ret.insert("cftable", QCFTag("cftable"));
	//ret.insert("cftextarea", QCFTag("cftextarea"));
	//ret.insert("cftextinput", QCFTag("cftextinput"));
	ret.insert("cfthread", QCFTag("cfthread", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
	ret.insert("cfthrow", QCFTag("cfthrow", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
	//ret.insert("cftimer", QCFTag("cftimer"));
	//ret.insert("cftooltip", QCFTag("cftooltip"));
	//ret.insert("cftrace", QCFTag("cftrace"));
	ret.insert("cftransaction", QCFTag("cftransaction", QCFTag::TagTypeNoRestriction, QCFTag::ArgumentsTypeArguments));
	//ret.insert("cftree", QCFTag("cftree"));
	//ret.insert("cftreeitem", QCFTag("cftreeitem"));
	ret.insert("cftry", QCFTag("cftry", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
	//ret.insert("cfupdate", QCFTag("cfupdate"));
	//ret.insert("cfwddx", QCFTag("cfwddx"));
	//ret.insert("cfwindow", QCFTag("cfwindow"));

	ret.insert("cfxml", QCFTag("cfxml", QCFTag::TagTypeWithCloseTag, QCFTag::ArgumentsTypeArguments));
	args.clear();
	args.append(QCFTagArgument("variable", true));
	args.append(QCFTagArgument("caseSensitive"));
	ret["cfxml"].m_ArgumentVariants.append(args);

	//ret.insert("cfzip", QCFTag("cfzip"));
	//ret.insert("cfzipparam", QCFTag("cfzipparam"));

	return ret;
}

QHash<QString, QCFFunction> QCF8::generateCFFunctions()
{
	QHash<QString, QCFFunction> ret;


	// Page 1 a-b

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

	//ret.insert("applicationstop", QCFFunction("ApplicationStop", QCFFunction::ReturnVoid));

	ret.insert("arrayappend", QCFFunction("ArrayAppend", QCFFunction::ReturnBool));
	ret["arrayappend"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
	ret["arrayappend"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeAny, true));

	ret.insert("arrayavg", QCFFunction("ArrayAvg", QCFFunction::ReturnDouble));
	ret["arrayavg"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

	ret.insert("arrayclear", QCFFunction("ArrayClear", QCFFunction::ReturnBool));
	ret["arrayclear"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

	ret.insert("arraycontains", QCFFunction("ArrayContains", QCFFunction::ReturnBool));
	ret["arraycontains"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

	ret.insert("arraydelete", QCFFunction("ArrayDeleteAt", QCFFunction::ReturnBool));
	ret["arraydelete"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
	ret["arraydelete"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));

	ret.insert("arraydeleteat", QCFFunction("ArrayDeleteAt", QCFFunction::ReturnBool));
	ret["arraydeleteat"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true, QCFFunctionArgument::TypeVariable));
	ret["arraydeleteat"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeQWDDX, true));

	// ArrayFind;
	// ArrayFindNoCase;
	//ret.insert("ArrayInsertAt", QCFFunction("ArrayInsertAt"));
	//ret.insert("ArrayIsDefined", QCFFunction("ArrayIsDefined"));
	//ret.insert("ArrayIsEmpty", QCFFunction("ArrayIsEmpty"));
	//ret.insert("ArrayLen", QCFFunction("ArrayLen"));
	//ret.insert("ArrayMax", QCFFunction("ArrayMax"));
	//ret.insert("ArrayMin", QCFFunction("ArrayMin"));
	ret.insert("arraynew", QCFFunction("ArrayNew", QCFFunction::ReturnQWDDX));
	ret["arraynew"].m_Arguments.append(QCFFunctionArgument(QCFFunctionArgument::ArgumentDataTypeInt, true, QCFFunctionArgument::TypeAny));
	//ret.insert("ArrayPrepend", QCFFunction("ArrayPrepend"));
	//ret.insert("ArrayResize", QCFFunction("ArrayResize"));
	//ret.insert("ArraySet", QCFFunction("ArraySet"));
	//ret.insert("ArraySort", QCFFunction("ArraySort"));
	//ret.insert("ArraySum", QCFFunction("ArraySum"));
	//ret.insert("ArraySwap", QCFFunction("ArraySwap"));
	//ret.insert("ArrayToList", QCFFunction("ArrayToList"));
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

	// Page 2 c-d

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

	return ret;
}
