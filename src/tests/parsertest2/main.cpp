#include <qcfgenerator.h>
#include <qcfparser.h>
#include <QtDebug>

int main(int /*argc*/, char ** /*argv*/)
{
	QString l_CFCode;

	l_CFCode = "<cfset a = 12 />";
	//l_CFCode = "<cfset a = \"ako #1 + 2 + 3 + 4 + 5#\" />";
	//l_CFCode = "<cfdump var=\"# 1 + 2 + (3 + 4) + 5#\"/>";
	//l_CFCode = "<cfset a = \"#b * 4#\" />";
	//l_CFCode = "<cfoutput>b=#b(12)#</cfoutput>";
	//l_CFCode = "<cfset a = 12 /><cfoutput>a =</cfoutput>#a#";
	//l_CFCode = "<cfif a eq 12>";
	//l_CFCode = "<cfabort showError=\"Greska be zaeban.\" />";
	//l_CFCode = "<cfloop from=\"1\" to=\"10\" index=\"i\">";
	//l_CFCode = "<cfif (mode EQ \"new\")>a</cfif>";

	QCFParser parser;
	QCFParserErrorType parsingError = parser.Parse(l_CFCode);

	if (parsingError != NoError)
	{
		qDebug() << parser.getError();
		return -1;
	}

	QList<QCFParserTag> l_tags;
	l_tags = parser.getTags();
	QString ret;

	QCFGenerator l_CFGenerator;

	foreach(QCFParserTag l_tag, l_tags)
	{
		QString tt =  l_CFGenerator.GenerateCCodeFromCFTag(l_tag);
		ret += tt + "\n";
	}

	qDebug() << ret;

	return 0;
}
