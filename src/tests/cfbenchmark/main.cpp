#include <pi_orig.h>
#include <pi_opt.h>
#include <pi_opt2.h>

#include <qcfrunningtemplate.h>
#include <qcfparser.h>
#include <qcfserver.h>
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
        m_TemplateInstance = nullptr;
    }
}*/

void TestCases::optPI2()
{
    QBENCHMARK {
        QCFGeneratedTemplateOpt2 optTemplate;
        QCFTemplate stdTemplate;

        QCFServer m_Server;
        QCFRunningTemplate *m_TemplateInstance = new QCFRunningTemplate();

        m_TemplateInstance->m_CFServer = &m_Server;

        m_Server.m_RunnuingTemplatesByThreadId.insert(QThread::currentThreadId(), m_TemplateInstance);

        m_TemplateInstance->m_VARIABLES.setType(QWDDX::Struct);

        optTemplate.run(m_TemplateInstance);

        stdTemplate.addCustomFunction("guidtostring", [](QCFRunningTemplate *m_TemplateInstance, const QList<QWDDX> &arguments) -> QWDDX {
            QWDDX ARGUMENTS(QWDDX::Struct);
            QWDDX LOCAL(QWDDX::Struct);

            if(arguments.count() > 0 ) {
                updateVariable(ARGUMENTS, "GUIDBYTEARRAY", arguments.at(0));
            } else {
                updateVariable(ARGUMENTS, "GUIDBYTEARRAY", "");
            };

            LOCAL[L"HEXSTRING"] = QWDDX(L"");
            if (cf_IsArray(ARGUMENTS[L"GUIDBYTEARRAY"]) && cf_ArrayLen(ARGUMENTS[L"GUIDBYTEARRAY"]) >= QWDDX(16)) {
                LOCAL[L"HEXSTRING"] = LOCAL[L"HEXSTRING"] & callCustomFunction("guidbytetohex", QList<QWDDX>() << ARGUMENTS[L"GUIDBYTEARRAY"][QWDDX(4)]) ;
            }

            return 0;
        });

        delete m_TemplateInstance;
        m_TemplateInstance = nullptr;
    }
}

QTEST_MAIN(TestCases)
#include "main.moc"
