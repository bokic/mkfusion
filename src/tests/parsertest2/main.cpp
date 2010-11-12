#include <qcfparser.h>
#include <QTest>

class TestCases : public QObject
{
	Q_OBJECT
private slots:
	void initTestCase();
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
};

void TestCases::initTestCase()
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

	QVERIFY(tag.m_Arguments.m_ChildElements.count() == 5);


}


QTEST_MAIN(TestCases)
#include "main.moc"
