#include <qcfparser.h>
#include <QTest>

class TestCases : public QObject
{
	Q_OBJECT
private slots:
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
};

void TestCases::testcase1()
{
	QCFParser parser;
	QList<QCFParserTag> tags;

	QBENCHMARK {
		QVERIFY(parser.Parse("<cfset '# #' />") == NoError);
	}

	tags = parser.getTags();

	QVERIFY(tags.count() == 1);
	QVERIFY(tags.at(0).m_Name == "cfset");
	QVERIFY(tags.at(0).m_Start == 0);
	QVERIFY(tags.at(0).m_Length == 15);
	QVERIFY(tags.at(0).m_EndTag == 0);
	QVERIFY(tags.at(0).m_InlineClosedTag == true);
	QVERIFY(tags.at(0).m_TagType == CFTagType);

	QVERIFY(tags.at(0).m_Arguments.m_Position == 7);
	QVERIFY(tags.at(0).m_Arguments.m_Size == 6);
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
	QCFParser parser;

	QBENCHMARK {
		QVERIFY(parser.Parse("<cfif (mode EQ \"new\")>a</cfif>") == NoError);
	}
}

QTEST_MAIN(TestCases)
#include "main.moc"
