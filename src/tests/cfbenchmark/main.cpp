#include <pi_orig.h>
#include <pi_opt.h>

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
    void optPI();
};

/*void TestCases::origPI()
{
    QBENCHMARK {
        QCFGeneratedTemplateOrig origTemplate;

        QCFRunningTemplate* m_TemplateInstance = new QCFRunningTemplate();

        m_TemplateInstance->m_VARIABLES.m_Type = QWDDX::Struct;

        origTemplate.run(m_TemplateInstance);
    }
}*/

void TestCases::optPI()
{
    QBENCHMARK {
        QCFGeneratedTemplateOpt optTemplate;

        QCFRunningTemplate* m_TemplateInstance = new QCFRunningTemplate();

        m_TemplateInstance->m_VARIABLES.setType(QWDDX::Struct);

        optTemplate.run(m_TemplateInstance);

        delete m_TemplateInstance;
        m_TemplateInstance = NULL;
    }
}

QTEST_MAIN(TestCases)
#include "main.moc"
