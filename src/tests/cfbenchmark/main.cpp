#include <pi_orig.h>
#include <pi_opt.h>
#include <pi_opt2.h>

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
    void optPI2();
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
}*/

void TestCases::optPI2()
{
    QBENCHMARK {
        QCFGeneratedWorkerThreadOpt2 optTemplate;

        optTemplate.executePage();
    }
}

QTEST_MAIN(TestCases)
#include "main.moc"
