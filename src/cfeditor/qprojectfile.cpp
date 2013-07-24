#include "qprojectfile.h"

bool operator<(const QProjectFile &p_Value1, const QProjectFile &p_Value2)
{
	if ((p_Value1.m_IsFolder == true)&&(p_Value2.m_IsFolder == false))
	{
		return true;
	}

	if ((p_Value2.m_IsFolder == true)&&(p_Value1.m_IsFolder == false))
	{
		return false;
	}

	return p_Value1.m_FileName < p_Value2.m_FileName;
}
