#include <qcfrunningtemplate.h>
#include <qcfparser.h>
#include <qwddx.h>
#include <QTest>
#include <QFile>

#include <string>
#include <map>

class TestCases : public QObject
{
	Q_OBJECT
private slots:
/*	void initTestCase();
	void cleanupTestCase();
	void testcase1();
	void testcase2();
	void testcase3();
	void testcase4();
	void testcase5();
	void testcase6();
	void testcase7();
	void testcase8();
	void testcase9();
	void testcase10();
	void testcase11();
	void testcase12();
	void testcase13();
	void testcase14();
    void testcase15();
	void testcase16();
	void testcase17();
	void testcase18();
	void testcase19();
	void BenchUnoptimisedCode();
	void BenchOptimisedCode();
	void BenchOptimisedCode2();
	void bench1_stl();
	void bench1_qt();
    void bench_parser();
    void verificator_improove_test();*/
    void parseBigFile();
    void benchPI();
    void compareIssue();
};

/*void TestCases::initTestCase()
{
}

void TestCases::cleanupTestCase()
{

}

void TestCases::testcase1()
{
	QCFParser parser;
	QList<QCFParserTag> tags;

	QBENCHMARK {
		QVERIFY(parser.Parse("<cfset '# #'>") == NoError);
	}

	tags = parser.getTags();

	QVERIFY(tags.count() == 1);
	QVERIFY(tags.at(0).m_Name == "cfset");
	QVERIFY(tags.at(0).m_Start == 0);
	QVERIFY(tags.at(0).m_Length == 13);
	QVERIFY(tags.at(0).m_EndTag == 0);
	QVERIFY(tags.at(0).m_InlineClosedTag == false);
	QVERIFY(tags.at(0).m_TagType == CFTagType);

	QVERIFY(tags.at(0).m_Arguments.m_Position == 7);
	QVERIFY(tags.at(0).m_Arguments.m_Size == 5);
	QVERIFY(tags.at(0).m_Arguments.m_Type == Expression);
	QVERIFY(tags.at(0).m_Arguments.m_ChildElements.count() == 1);
}

void TestCases::testcase2()
{
	QCFParser parser;

	QBENCHMARK {
		//QVERIFY(parser.Parse("<cfset a =") == ParsingError);
	}
}

void TestCases::testcase3()
{
	QCFParser parser;

	QBENCHMARK {
		QVERIFY(parser.Parse("<cfset a = 12 />") == NoError);
	}
}

void TestCases::testcase4()
{
	QCFParser parser;

	QBENCHMARK {
		QVERIFY(parser.Parse("<cfset a = \"ako #1 + 2 + 3 + 4 + 5#\" />") == NoError);
	}
}

void TestCases::testcase5()
{
	QCFParser parser;

	QBENCHMARK {
		QVERIFY(parser.Parse("<cfdump var=\"# 1 + 2 + (3 + 4) + 5#\"/>") == NoError);
	}
}

void TestCases::testcase6()
{
	QCFParser parser;

	QBENCHMARK {
		QVERIFY(parser.Parse("<cfset a = \"#b * 4#\" />") == NoError);
	}
}

void TestCases::testcase7()
{
	QCFParser parser;

	QBENCHMARK {
		QVERIFY(parser.Parse("<cfoutput>b=#b(12)#</cfoutput>") == NoError);
	}
}

void TestCases::testcase8()
{
	QCFParser parser;

	QBENCHMARK {
		QVERIFY(parser.Parse("<cfset a = 12 /><cfoutput>a =</cfoutput>#a#") == NoError);
	}
}

void TestCases::testcase9()
{
	QCFParser parser;

	QBENCHMARK {
		QVERIFY(parser.Parse("<cfif a eq 12>") == NoError);
	}
}

void TestCases::testcase10()
{
	QCFParser parser;

	QBENCHMARK {
		QVERIFY(parser.Parse("<cfloop from=\"1\" to=\"10\" index=\"i\">") == NoError);
	}
}

void TestCases::testcase11()
{
	//QCFParser parser;

	//QBENCHMARK {
	//	QVERIFY(parser.Parse("<cfif (mode EQ \"new\")>a</cfif>") == NoError);
	//}
}

void TestCases::testcase12()
{
	QCFParser parser;
	QCFParserErrorType error(NoError);

	QBENCHMARK {
		error = parser.Parse("<cfset tmp_val = (final[i] * 4) + transfer />");
	}

	QVERIFY(error == NoError);

	QList<QCFParserTag> l_tags = parser.getTags();
	QVERIFY(l_tags.count() == 1);

	QCFParserTag tag = l_tags.at(0);

	QVERIFY(tag.m_Name == "cfset");

	QBENCHMARK {
		error = parser.Parse("<cfset final[i] = tmp_val Mod 10 />");
	}

	QVERIFY(error == NoError);

	l_tags = parser.getTags();
	QVERIFY(l_tags.count() == 1);

	tag = l_tags.at(0);

	QVERIFY(tag.m_Name == "cfset");
}

void TestCases::testcase13()
{
	QCFParser parser;
	QCFParserErrorType error = parser.Parse("<cfset a = 1 +1 />");

	QVERIFY(error == NoError);

	QList<QCFParserTag> l_tags = parser.getTags();
	QVERIFY(l_tags.count() == 1);

	QCFParserTag tag = l_tags.at(0);

	QVERIFY(tag.m_Name == "cfset");
	QVERIFY(tag.m_Arguments.m_ChildElements.count() == 5);
}

void TestCases::testcase14()
{
	QCFParser parser;
	QCFParserErrorType error = parser.Parse("<cfset a = \"12\" />");

	QVERIFY(error == NoError);

	QList<QCFParserTag> l_tags = parser.getTags();
	QVERIFY(l_tags.count() == 1);

	QCFParserTag tag = l_tags.at(0);

	QVERIFY(tag.m_Name == "cfset");
	QVERIFY(tag.m_Start == 0);
	QVERIFY(tag.m_Length == 18);
	QVERIFY(tag.m_Arguments.m_ChildElements.count() == 3);

	QCFParserElement el;

	el = tag.m_Arguments.m_ChildElements.at(0);
	QVERIFY(el.m_Position == 7);
	QVERIFY(el.m_Size == 1);
	QVERIFY(el.m_Type == Variable);
	QVERIFY(el.m_Text == "a");

	el = tag.m_Arguments.m_ChildElements.at(1);
	QVERIFY(el.m_Position == 9);
	QVERIFY(el.m_Size == 1);
	QVERIFY(el.m_Type == Operator);
	QVERIFY(el.m_Text == "=");

	el = tag.m_Arguments.m_ChildElements.at(2);
	QVERIFY(el.m_Position == 11);
	QVERIFY(el.m_Size == 4);
	QVERIFY(el.m_Type == String);
	QVERIFY(el.m_Text == "12");

	QVERIFY(el.m_ChildElements.count() == 1);

	el = el.m_ChildElements.at(0);
	QVERIFY(el.m_Position == 12);
	QVERIFY(el.m_Size == 2);
	QVERIFY(el.m_Type == Number);
	QVERIFY(el.m_Text == "12");
}

void TestCases::testcase15()
{
	QCFParser parser;
	QCFParserErrorType error = parser.Parse("<cfset a = \"#boro#\" />");

	QVERIFY(error == NoError);

	QList<QCFParserTag> l_tags = parser.getTags();
	QVERIFY(l_tags.count() == 1);

	QCFParserTag tag = l_tags.at(0);

	QVERIFY(tag.m_Name == "cfset");
	QVERIFY(tag.m_Start == 0);
	QVERIFY(tag.m_Length == 22);
	QVERIFY(tag.m_Arguments.m_ChildElements.count() == 3);

	QCFParserElement el;

	el = tag.m_Arguments.m_ChildElements.at(0);
	QVERIFY(el.m_Position == 7);
	QVERIFY(el.m_Size == 1);
	QVERIFY(el.m_Type == Variable);
	QVERIFY(el.m_Text == "a");

	el = tag.m_Arguments.m_ChildElements.at(1);
	QVERIFY(el.m_Position == 9);
	QVERIFY(el.m_Size == 1);
	QVERIFY(el.m_Type == Operator);
	QVERIFY(el.m_Text == "=");

	el = tag.m_Arguments.m_ChildElements.at(2);
	QVERIFY(el.m_Position == 11);
	QVERIFY(el.m_Size == 8);
	QVERIFY(el.m_Type == String);

	QVERIFY(el.m_ChildElements.count() == 1);

	el = el.m_ChildElements.at(0);
	QVERIFY(el.m_Position == 12);
	QVERIFY(el.m_Size == 6);
	QVERIFY(el.m_Type == SharpExpression);

	QVERIFY(el.m_ChildElements.count() == 1);

	el = el.m_ChildElements.at(0);
	QVERIFY(el.m_Position == 13);
	QVERIFY(el.m_Size == 4);
	QVERIFY(el.m_Type == Expression);

	QVERIFY(el.m_ChildElements.count() == 1);

	el = el.m_ChildElements.at(0);
	QVERIFY(el.m_Position == 13);
	QVERIFY(el.m_Size == 4);
	QVERIFY(el.m_Type == Variable);
	QVERIFY(el.m_Text == "boro");
}

void TestCases::testcase16()
{
    QCFParser parser;
    QCFParserErrorType error = parser.Parse("<cfscript>a = Abs(-12);</cfscript>");

    QVERIFY(error == NoError);

    QList<QCFParserTag> l_tags = parser.getTags();
    QVERIFY(l_tags.count() == 2);

    QCFParserTag tag = l_tags.at(0);

    QCFParserElement expession = tag.m_Arguments;
    QVERIFY(expession.m_Type = Expression);
}

void TestCases::testcase17()
{
    QCFParser parser;
    QCFParserErrorType error = parser.Parse("<CFSCRIPT>funct1(\"<!---\");</CFSCRIPT>");

    QVERIFY(error == NoError);

    QList<QCFParserTag> l_tags = parser.getTags();
    QVERIFY(l_tags.count() == 2);

    QCFParserTag tag = l_tags.at(0);

    QCFParserElement expession = tag.m_Arguments;
    QVERIFY(expession.m_Type = Expression);
}

void TestCases::testcase18()
{
	QCFParser parser;
	QCFParserErrorType error = parser.Parse("<cfset a[1][2] = 12 />");

	Q_UNUSED(error);
}

void TestCases::testcase19()
{
	QCFParser parser;
	QCFParserErrorType error = parser.Parse("<cfset destination=\"#ExpandPath('pods/images')#/img_#Val(id)#.#extFile#\" />");

	Q_UNUSED(error);
}

void TestCases::BenchUnoptimisedCode()
{
	// <cfset a = 1 /><cfloop from="1" to="1000000" index="c"><cfset a = a + 1 /></cfloop><cfoutput>#a#</cfoutput>
	// ColdFusion9: 338ms
	// Railo: 377ms
	// BlueDragon: 956ms
	// MKFusion: 21ms ???, 100ms


    QCFRunningTemplate *m_TemplateInstance = new QCFRunningTemplate();

	m_TemplateInstance->m_VARIABLES.m_Type = QWDDX::Struct;

	QBENCHMARK
	{
        m_TemplateInstance->m_VARIABLES[QStringLiteral("A")] = QWDDX(1);

        for (m_TemplateInstance->m_VARIABLES[QStringLiteral("C")] = QWDDX(1); m_TemplateInstance->m_VARIABLES[QStringLiteral("C")] <= QWDDX(1000000); m_TemplateInstance->m_VARIABLES[QStringLiteral("C")] = m_TemplateInstance->m_VARIABLES[QStringLiteral("C")] + QWDDX(1))
		{
            m_TemplateInstance->m_VARIABLES[QStringLiteral("A")] = m_TemplateInstance->m_VARIABLES[QStringLiteral("A")] + QWDDX(1);
		}
	}

	delete m_TemplateInstance;
}

void TestCases::BenchOptimisedCode()
{
    QCFRunningTemplate *m_TemplateInstance = new QCFRunningTemplate();

	m_TemplateInstance->m_VARIABLES.m_Type = QWDDX::Struct;

	QBENCHMARK
	{
		{
			//QWDDX *opt_m_VARIABLES_A = &m_TemplateInstance->m_VARIABLES["A"]; *opt_m_VARIABLES_A = 1;
            m_TemplateInstance->m_VARIABLES[QStringLiteral("A")] = 1;

            //QWDDX *opt_m_VARIABLES_A = nullptr;
            QWDDX *opt_m_VARIABLES_C = &m_TemplateInstance->m_VARIABLES[QStringLiteral("C")]; *opt_m_VARIABLES_C = 1;
			for(; ; )
			{
                //if (opt_m_VARIABLES_A == nullptr) opt_m_VARIABLES_A = &m_TemplateInstance->m_VARIABLES[QStringLiteral("A")];

				// *opt_m_VARIABLES_A = *opt_m_VARIABLES_A + 1;

				if (*opt_m_VARIABLES_C >= 1000000)
				{
					break;
				}

				*opt_m_VARIABLES_C += 1;
			}
		}
	}

	delete m_TemplateInstance;
}

void TestCases::BenchOptimisedCode2()
{
    QCFRunningTemplate *m_TemplateInstance = new QCFRunningTemplate();

	m_TemplateInstance->m_VARIABLES.m_Type = QWDDX::Struct;

	QBENCHMARK
	{
		{
			//QWDDX *opt_m_VARIABLES_A = &m_TemplateInstance->m_VARIABLES["A"]; *opt_m_VARIABLES_A = 1;
            m_TemplateInstance->m_VARIABLES[QStringLiteral("A")] = 1;

            QWDDX *opt_m_VARIABLES_A = nullptr;
			quint32 l_loopCounter = 1;
			for(; ; )
			{
                if (opt_m_VARIABLES_A == nullptr) opt_m_VARIABLES_A = &m_TemplateInstance->m_VARIABLES[QStringLiteral("A")];

				// *opt_m_VARIABLES_A = *opt_m_VARIABLES_A + 1;

				if (l_loopCounter >= 1000000)
				{
					break;
				}

				l_loopCounter += 1;
			}
		}
	}

	delete m_TemplateInstance;
}

void TestCases::bench1_stl()
{

	using namespace std;

	QBENCHMARK
	{
		map<wstring, int> m_VARIABLES;

        for(m_VARIABLES[QStringLiteral("C")] = 1; m_VARIABLES[QStringLiteral("C")] < 1000000; m_VARIABLES[QStringLiteral("C")] = m_VARIABLES[QStringLiteral("C")] + 1)
		{
            m_VARIABLES[QStringLiteral("A")] = m_VARIABLES[QStringLiteral("A")] + 1;
		}
	}
}

void TestCases::bench1_qt()
{
	QBENCHMARK
	{
		QMap<QString, int> m_VARIABLES;

		for(m_VARIABLES["C"] = 1; m_VARIABLES["C"] < 1000000; m_VARIABLES["C"] = m_VARIABLES["C"] + 1)
		{
			m_VARIABLES["A"] = m_VARIABLES["A"] + 1;
		}
	}
}

void TestCases::bench_parser()
{
	QFile file("site/bigones/frontend.cfm");
	QString l_fileContent;

	if (file.open(QIODevice::ReadOnly))
	{
		QByteArray l_content = file.readAll();

		l_fileContent = QString::fromUtf8(l_content.constData(), l_content.length());

		file.close();
	}


	QBENCHMARK {
		QCFParser parser;
		QList<QCFParserTag> tags;

		parser.Parse(l_fileContent);

		tags = parser.getTags();
	}
}

void TestCases::verificator_improove_test()
{
	QFile file("site/pi.cfm");
	QString l_fileContent;

	if (file.open(QIODevice::ReadOnly))
	{
		QByteArray l_content = file.readAll();

		l_fileContent = QString::fromUtf8(l_content.constData(), l_content.length());

		file.close();
	}

	QCFParser parser;
	QCFParserErrorType error = parser.Parse(l_fileContent);

	QVERIFY(error == NoError);
}
*/
void TestCases::parseBigFile()
{
	QCFParser parser;

	QFile file("index.cfm");

	file.open(QIODevice::ReadOnly);

	QString str = file.readAll();

	QBENCHMARK {
		parser.parse(str);

		//int c = parser.getTags().count();

		//qDebug("Parser element count is %u\n", c);
	}
}

void TestCases::benchPI()
{
    QBENCHMARK {

    }
}

void TestCases::compareIssue()
{
    QCFRunningTemplate *m_TemplateInstance = new QCFRunningTemplate();

    m_TemplateInstance->m_VARIABLES.setType(QWDDX::Struct);

    m_TemplateInstance->m_VARIABLES[L"SETTING"] = QString("Style");

    QVERIFY(m_TemplateInstance->m_VARIABLES[L"SETTING"] == QWDDX(L"Style"));

    delete m_TemplateInstance;
}


QTEST_MAIN(TestCases)
#include "main.moc"
