#include "qcftemplate.h"
#include "cffunctions.h"
#include "qcfserver.h"

#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>

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
    m_TemplateInstance->m_QueryParams.clear();

    m_TemplateInstance->m_OutputType = QCFRunningTemplate::OutputTypeQuery;
}

QWDDX QCFTemplate::endQuery(const QString &p_DataSource)
{
    QWDDX ret(QWDDX::Query);

    //Get dbconnection object
    QSqlDatabase conn = ((QCFServer*)m_TemplateInstance->m_CFServer)->getDBConnection(p_DataSource);

    if (conn.open() == false)
    {
        throw QMKFusionException("Database connection failed.");
    }

    //Call prepare query
    QSqlQuery query(conn);

    if (query.prepare(m_TemplateInstance->m_QueryOutput) == false)
    {
        throw QMKFusionException("Invalid query syntax.");
    }

    //Send query parameters(if any)
    for(int c = 0; c < m_TemplateInstance->m_QueryParams.count(); c++)
    {
        query.bindValue(c, m_TemplateInstance->m_QueryParams.at(c).toString());
    }

    //call query exec.
    if (query.exec() == false)
    {
        throw QMKFusionException("query execute failed.");
    }

    // copy
    for(int f = 0; f < query.record().count(); f++)
    {
        cf_QueryAddColumn(ret, query.record().fieldName(f));
    }

    int row = 1;

    while(query.next())
    {
        cf_QueryAddRow(ret);

        for(int f = 0; f < query.record().count(); f++)
        {
            cf_QuerySetCell(ret, query.record().fieldName(f), query.record().value(f).toString(), row);
        }

        row++;
    }

    m_TemplateInstance->m_QueryOutput.clear();
    m_TemplateInstance->m_QueryParams.clear();

    m_TemplateInstance->m_OutputType = QCFRunningTemplate::OutputTypeContent;

    return ret;
}
