#include <pi_orig.h>
#include <pi_opt.h>
#include <pi_opt2.h>

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
    //void origPI();
    //void optPI();
    void optPI2();
};

/*void TestCases::origPI()
{
    QBENCHMARK {
        QCFGeneratedTemplateOrig origTemplate;

        QCFRunningTemplate *m_TemplateInstance = new QCFRunningTemplate();

        m_TemplateInstance->m_VARIABLES.setType(QWDDX::Struct);

        origTemplate.run(m_TemplateInstance);
    }
}

void TestCases::optPI()
{
    QBENCHMARK {
        QCFGeneratedTemplateOpt optTemplate;

        QCFRunningTemplate *m_TemplateInstance = new QCFRunningTemplate();

        m_TemplateInstance->m_VARIABLES.setType(QWDDX::Struct);

        optTemplate.run(m_TemplateInstance);

        delete m_TemplateInstance;
        m_TemplateInstance = NULL;
    }
}*/

void TestCases::optPI2()
{
    QBENCHMARK {
        QCFGeneratedTemplateOpt2 optTemplate;
        QCFTemplate stdTemplate;

        QCFRunningTemplate *m_TemplateInstance = new QCFRunningTemplate();

        m_TemplateInstance->m_VARIABLES.setType(QWDDX::Struct);

        optTemplate.run(m_TemplateInstance);

        stdTemplate.addCustomFunction("guidtostring", [](QCFRunningTemplate *m_TemplateInstance, const QList<QWDDX> &arguments) -> QWDDX {
            QWDDX ARGUMENTS(QWDDX::Struct);
            QWDDX LOCAL(QWDDX::Struct);

            if(arguments.count() > 0 ) {
                ARGUMENTS["GUIDBYTEARRAY"] = arguments.at(0);
            } else {;
                ARGUMENTS["GUIDBYTEARRAY"] = "";
            };

            LOCAL["HEXSTRING"] = QWDDX(L"");
            if (cf_IsArray(ARGUMENTS["GUIDBYTEARRAY"]) && cf_ArrayLen(ARGUMENTS["GUIDBYTEARRAY"]) >= QWDDX(16)) {
                LOCAL["HEXSTRING"] = LOCAL["HEXSTRING"] & callCustomFunction("guidbytetohex", QList<QWDDX>() << ARGUMENTS["GUIDBYTEARRAY"][QWDDX(4)]) ;
            }

            return 0;
        });

        delete m_TemplateInstance;
        m_TemplateInstance = NULL;
    }
}

QTEST_MAIN(TestCases)
#include "main.moc"
