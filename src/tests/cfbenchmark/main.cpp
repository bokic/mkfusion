#include <pi_orig.h>
#include <pi_opt.h>
#include <pi_opt2.h>

#include "qtextparser.h"
#include <qcfvariant.h>
#include <qcfparser.h>
#include <qcfserver.h>
#include <QTest>
#include <QFile>

#include <string>
#include <map>

class TestCases : public QObject
{
    Q_OBJECT
private slots:
    //void origPI();
    //void optPI();
    //void optPI2();
    void benchOldParser();
    void benchNewParser();
};

/*void TestCases::origPI()
{
    QBENCHMARK {
        QCFGeneratedTemplateOrig origTemplate;

        QCFRunningTemplate *m_TemplateInstance = new QCFRunningTemplate();

        m_TemplateInstance->m_VARIABLES.setType(QCFVariant::Struct);

        origTemplate.run(m_TemplateInstance);
    }
}

void TestCases::optPI()
{
    QBENCHMARK {
        QCFGeneratedTemplateOpt optTemplate;

        QCFRunningTemplate *m_TemplateInstance = new QCFRunningTemplate();

        m_TemplateInstance->m_VARIABLES.setType(QCFVariant::Struct);

        optTemplate.run(m_TemplateInstance);

        delete m_TemplateInstance;
        m_TemplateInstance = nullptr;
    }
}

void TestCases::optPI2()
{
    QBENCHMARK
    {
        QCFGeneratedWorkerThreadOpt2 optTemplate;

        optTemplate.executePage();
    }
}*/

void TestCases::benchOldParser()
{
    QCFParser parser(CompilerMode, QCFParserTemplateFile);

    QBENCHMARK
    {
        QCFParserErrorType err = parser.parse(QFileInfo("site/pi.cfm"));

        if (err == NoError)
        {
            const QList<QCFParserTag> &tags = parser.getTags();

            //qDebug() << tags.count();
        }
        else
        {
            qDebug() << "Parsing error!";
        }
    }
}

void TestCases::benchNewParser()
{
    QTextParser::loadParserDefinitionsFromDir("../src/textparser");
    QTextParser parser;

    parser.setTextTypeByFileExtension("cfm");

    QBENCHMARK
    {
        QTextParserElements elements = parser.parseFile("site/pi.cfm");

        //qDebug() << elements.count();
    }
}

QTEST_MAIN(TestCases)
#include "main.moc"
