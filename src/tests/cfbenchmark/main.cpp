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

        QCFServer m_Server;
        QCFRunningTemplate *m_TemplateInstance = new QCFRunningTemplate();

        m_TemplateInstance->m_CFServer = &m_Server;

        m_Server.m_RunnuingTemplatesByThreadId.insert(QThread::currentThreadId(), m_TemplateInstance);

        m_TemplateInstance->m_VARIABLES.setType(QWDDX::Struct);

        optTemplate.run(m_TemplateInstance);

        delete m_TemplateInstance;
        m_TemplateInstance = nullptr;
    }
}

QTEST_MAIN(TestCases)
#include "main.moc"
