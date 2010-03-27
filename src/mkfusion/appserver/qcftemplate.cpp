#include "qcftemplate.h"

QCFTemplate::QCFTemplate()
{ // TODO: please verify in the following 3 lines are nessesary.
	m_isModified.m_Filename = "";
	m_isModified.m_Size = 0;
	m_isModified.m_Modified = 0;
}

void QCFTemplate::run(QCFRunningTemplate* p_TemplateInstance)
{
	m_TemplateInstance = p_TemplateInstance;
}

void QCFTemplate::f_WriteOutput(const QString& p_Text)
{
	if (m_TemplateInstance != NULL)
	{
		m_TemplateInstance->m_Output += p_Text;
	}
}

void QCFTemplate::f_WriteOutput(const QWDDX& p_Wddx)
{
	QWDDX l_temp = p_Wddx;

	if (m_TemplateInstance != NULL)
	{
		m_TemplateInstance->m_Output += l_temp.toString();
	}
}
