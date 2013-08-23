#include "qcftemplate.h"

QCFTemplate::QCFTemplate()
	: m_TemplateInstance(NULL)
{
}

QCFTemplate::~QCFTemplate()
{
}

void QCFTemplate::run(QCFRunningTemplate *p_TemplateInstance)
{
	m_TemplateInstance = p_TemplateInstance;
}

void QCFTemplate::f_WriteOutput(const QString &p_Text)
{
    if (m_TemplateInstance)
	{
        switch(m_TemplateInstance->m_OutputType)
        {
        case QCFRunningTemplate::OutputTypeContent:
            m_TemplateInstance->m_Output += p_Text;
            break;
        case QCFRunningTemplate::OutputTypeQuery:
            m_TemplateInstance->m_QueryOutput += p_Text;
            break;
        default:
            break;
        }
	}
}

void QCFTemplate::f_WriteOutput(const QWDDX &p_Wddx)
{
	QWDDX l_temp = p_Wddx;

    if (m_TemplateInstance)
	{
        switch(m_TemplateInstance->m_OutputType)
        {
        case QCFRunningTemplate::OutputTypeContent:
            m_TemplateInstance->m_Output += l_temp.toString();
            break;
        case QCFRunningTemplate::OutputTypeQuery:
            m_TemplateInstance->m_QueryOutput += l_temp.toString();
            break;
        default:
            break;
        }
	}
}

void QCFTemplate::startQuery()
{
    m_TemplateInstance->m_QueryOutput.clear();

    m_TemplateInstance->m_OutputType = QCFRunningTemplate::OutputTypeQuery;
}

QWDDX QCFTemplate::endQuery(const QString &p_DataSource)
{
    QWDDX ret(QWDDX::Query);

    //Get dbconnection object

    //Call prepare query

    //Send query parameters(if any)

    //call query exec.

    // copy

    m_TemplateInstance->m_QueryOutput.clear();

    m_TemplateInstance->m_OutputType = QCFRunningTemplate::OutputTypeContent;

    return ret;
}
