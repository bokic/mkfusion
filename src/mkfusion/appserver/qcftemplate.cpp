#include "qcftemplate.h"
#include "qmkfusionservice.h"
#include "qtservice.h"
#include "cffunctions.h"
#include "qcfserver.h"

#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>


QCFTemplate::QCFTemplate()
    : m_TemplateInstance(nullptr)
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

void QCFTemplate::f_Location(const QString &p_URL, int p_StatusCode)
{
    if ((p_StatusCode < 300)||(p_StatusCode > 307))
    {
        throw QMKFusionInvalidArgumentException("f_Location", 2, p_StatusCode, 300, 307);
    }

    m_TemplateInstance->m_StatusCode = p_StatusCode;

    m_TemplateInstance->m_Header.insert("location", p_URL);

    m_TemplateInstance->m_Output.clear();

    // TODO: Add url redirect
    throw QMKFusionCFAbortException();
}

void QCFTemplate::f_Location(const QString &p_URL, bool p_AddToken, int p_StatusCode)
{

}

void QCFTemplate::f_Include(const QString &p_template)
{
    createCFMTemplateDef createCFMTemplate = 0;

    if (p_template.isEmpty())
    {
        throw QMKFusionException(tr("Attribute validation error for CFINCLUDE."));
    }

    QFileInfo fi(this->m_isModified.m_Filename);
    QDir dir = fi.dir();
    QString target_file = QDir::toNativeSeparators(QDir::cleanPath(dir.filePath(p_template)));

    if ((!QFile::exists(target_file))||(target_file == dir.absolutePath()))
    {
        throw QMKFusionException(tr("Could not find the included template '%1'.").arg(p_template));
    }

    createCFMTemplate = (createCFMTemplateDef)this->m_TemplateInstance->compileAndLoadTemplate(target_file, "");

    if (createCFMTemplate)
    {
        QCFTemplate *l_page = nullptr;

        l_page = createCFMTemplate();
        l_page->run(this->m_TemplateInstance);

        for(QString funcName : l_page->m_TemplateCustomFunctions.keys())
        {
            m_TemplateCustomFunctions[funcName] = l_page->m_TemplateCustomFunctions[funcName];
        }

        delete l_page;
        l_page = 0;
    }
    else
    {
        throw QMKFusionException(tr("Can't load template '%1'").arg(p_template));
    }
}

void QCFTemplate::f_Param(const QString &name)
{
    if(name.length() == 0)
    {
        throw QMKFusionException(
                    tr("Attribute validation error for CFPARAM."),
                    tr("The value of the NAME attribute is invalid."
                       "The length of the string, 0 character(s), must be greater than or equal to 1 character(s).")
                    );
    }

    if (!cf_IsDefined(m_TemplateInstance, name))
    {
        throw QMKFusionException(
                    tr("The required parameter '%1' was not provided.").arg(name.toUpper()),
                    tr("This page uses the cfparam tag to declare the parameter '%1' as required for this template."
                       "The parameter is not available. Ensure that you have passed or initialized the parameter correctly."
                       "To set a default value for the parameter, use the default attribute of the cfparam tag.").arg(name.toUpper())
                    );
    }
}

void QCFTemplate::f_Param(const QString &name, const QWDDX &p_default)
{
    QStringList parts;

    if(name.length() == 0)
    {
        throw QMKFusionException(
                    tr("Attribute validation error for CFPARAM."),
                    tr("The value of the NAME attribute is invalid."
                       "The length of the string, 0 character(s), must be greater than or equal to 1 character(s).")
                    );
    }


    parts = name.toUpper().split(".");

    if (parts.count() == 1)
    {
        if(!m_TemplateInstance->m_VARIABLES.m_Struct->contains(parts.at(0)))
        {
            m_TemplateInstance->m_VARIABLES.m_Struct->insert(parts.at(0), p_default);
        }

        return;
    }

    if ((parts.first() != "CGI")&&(parts.first() != "SERVER")&&(parts.first() != "APPLICATION")&&(parts.first() != "SESSION")&&(parts.first() != "URL")&&(parts.first() != "FORM")&&(parts.first() != "VARIABLES"))
    {
        parts.prepend("VARIABLES");
    }

    const QString &first = parts.takeFirst();

    QWDDX *var = &m_TemplateInstance->m_VARIABLES;

    if (first == "CGI")
    {
        var = &m_TemplateInstance->m_CGI;
    }
    else if (first == "SERVER")
    {
        var = &m_TemplateInstance->m_SERVER;
    }
    else if (first == "APPLICATION")
    {
        if (m_TemplateInstance->m_APPLICATION == nullptr)
        {
            throw QMKFusionException(tr("Appication scope not enabled."));
        }

        var = m_TemplateInstance->m_APPLICATION;
    }
    else if (first == "SESSION")
    {
        if (m_TemplateInstance->m_SESSION == nullptr)
        {
            throw QMKFusionException(tr("Session scope not enabled."));
        }

        var = m_TemplateInstance->m_SESSION;
    }
    else if (first == "URL")
    {
        var = &m_TemplateInstance->m_URL;
    }
    else if (first == "FORM")
    {
        var = &m_TemplateInstance->m_FORM;
    }
    else if (first == "VARIABLES")
    {
    }
    else
    {
        throw QMKFusionException(tr("Internal error."), tr("Unknown type(cf_IsDefined)."));
    }

    bool inserted = false;

    for(const QString &item : parts)
    {
        if ((var->m_Type != QWDDX::Struct)&&(var->m_Type != QWDDX::Null))
        {
            throw QMKFusionException(tr("Variable not object."));
        }

        if (var->m_Type == QWDDX::Null)
        {
            var->setType(QWDDX::Struct);
        }

        if (!var->m_Struct->contains(item))
        {
            var->m_Struct->insert(item, QWDDX(QWDDX::Null));

            inserted = true;
        }

        var = &(*var)[item];
    }

    if (inserted)
    {
        *var = p_default;
    }
}

bool QCFTemplate::f_FetchQueryRow(const QWDDX &query, int row)
{
    if (query.m_Type != QWDDX::Query)
    {
        throw QMKFusionException("Variable is not query.");
    }

    if (row < 1)
    {
        return false;
    }

    if (query.m_Struct->count() > 0)
    {
        for(int i = 0; i < query.m_Struct->count(); i++)
        {
            QString columnName = query.m_Struct->keys().at(i);

            QWDDX columnData = query.m_Struct->values().at(i);

            if (columnData.m_Array->count() < row)
            {
                return false;
            }

            m_TemplateInstance->m_VARIABLES[columnName] = columnData.m_Array->at(row - 1);
        }

        return true;
    }

    return false;
}

void QCFTemplate::f_Application(QString name, bool sessionManagement, bool setClientCookies)
{
    name = name.toUpper();

    if(!((QCFServer*)m_TemplateInstance->m_CFServer)->m_Applications.contains(name))
    {
        ((QCFServer*)m_TemplateInstance->m_CFServer)->m_Applications.insert(name, QCFApplication());
    }

    ((QCFServer*)m_TemplateInstance->m_CFServer)->m_Applications[name].SessionManagement = sessionManagement;
    ((QCFServer*)m_TemplateInstance->m_CFServer)->m_Applications[name].SetClientCookies = setClientCookies;

    m_TemplateInstance->m_APPLICATION = &((QCFServer*)m_TemplateInstance->m_CFServer)->m_Applications[name].data;

    if (sessionManagement)
    {
        if ((setClientCookies == true)&&(m_TemplateInstance->m_COOKIE.m_Struct->contains("CFID"))&&(m_TemplateInstance->m_COOKIE.m_Struct->contains("CFTOKEN")))
        {
            QString CFID = m_TemplateInstance->m_COOKIE[L"CFID"];
            QString CFTOKEN = m_TemplateInstance->m_COOKIE[L"CFTOKEN"];

            if (!((QCFServer*)m_TemplateInstance->m_CFServer)->m_Sessions.contains(name + "," + CFID + "," + CFTOKEN.toUpper()))
            {
                ((QCFServer*)m_TemplateInstance->m_CFServer)->createSessonStrings(CFID, CFTOKEN);
                m_TemplateInstance->m_COOKIE[L"CFID"] = CFID;
                m_TemplateInstance->m_COOKIE[L"CFTOKEN"] = CFTOKEN;
                ((QCFServer*)m_TemplateInstance->m_CFServer)->m_Sessions[name + "," + CFID + "," + CFTOKEN.toUpper()] = QWDDX(QWDDX::Struct);
                qDebug() << "New session created.";
            }

            m_TemplateInstance->m_SESSION = &((QCFServer*)m_TemplateInstance->m_CFServer)->m_Sessions[name + "," + CFID + "," + CFTOKEN.toUpper()];

            (*m_TemplateInstance->m_SESSION)[L"CFID"] = CFID;
            (*m_TemplateInstance->m_SESSION)[L"CFTOKEN"] = CFTOKEN;
            (*m_TemplateInstance->m_SESSION)[L"SESSIONID"] = name + "_" + CFID + "_" + CFTOKEN;
            (*m_TemplateInstance->m_SESSION)[L"URLTOKEN"] = "CFID=" + CFID + "&CFTOKEN=" + CFTOKEN;
        }
        else if ((setClientCookies == false)&&(m_TemplateInstance->m_URL.m_Struct->contains("CFID"))&&(m_TemplateInstance->m_URL.m_Struct->contains("CFTOKEN")))
        {
            QString CFID = m_TemplateInstance->m_URL[L"CFID"];
            QString CFTOKEN = m_TemplateInstance->m_URL[L"CFTOKEN"];

            if (!((QCFServer*)m_TemplateInstance->m_CFServer)->m_Sessions.contains(name + "," + CFID + "," + CFTOKEN.toUpper()))
            {
                m_TemplateInstance->m_COOKIE[L"CFID"] = CFID;
                m_TemplateInstance->m_COOKIE[L"CFTOKEN"] = CFTOKEN;
                ((QCFServer*)m_TemplateInstance->m_CFServer)->createSessonStrings(CFID, CFTOKEN);
                ((QCFServer*)m_TemplateInstance->m_CFServer)->m_Sessions[name + "," + CFID + "," + CFTOKEN.toUpper()] = QWDDX(QWDDX::Struct);
                qDebug() << "New session created.";
            }

            m_TemplateInstance->m_SESSION = &((QCFServer*)m_TemplateInstance->m_CFServer)->m_Sessions[name + "," + CFID + "," + CFTOKEN.toUpper()];

            (*m_TemplateInstance->m_SESSION)[L"CFID"] = CFID;
            (*m_TemplateInstance->m_SESSION)[L"CFTOKEN"] = CFTOKEN;
            (*m_TemplateInstance->m_SESSION)[L"SESSIONID"] = name + "_" + CFID + "_" + CFTOKEN;
            (*m_TemplateInstance->m_SESSION)[L"URLTOKEN"] = "CFID=" + CFID + "&CFTOKEN=" + CFTOKEN;
        }
        else
        {
            QString CFID;
            QString CFTOKEN;

            ((QCFServer*)m_TemplateInstance->m_CFServer)->createSessonStrings(CFID, CFTOKEN);

            ((QCFServer*)m_TemplateInstance->m_CFServer)->m_Sessions[name + "," + CFID + "," + CFTOKEN.toUpper()] = QWDDX(QWDDX::Struct);
            m_TemplateInstance->m_SESSION = &((QCFServer*)m_TemplateInstance->m_CFServer)->m_Sessions[name + "," + CFID + "," + CFTOKEN.toUpper()];

            if (setClientCookies)
            {
                m_TemplateInstance->m_COOKIE[L"CFID"] = CFID;
                m_TemplateInstance->m_COOKIE[L"CFTOKEN"] = CFTOKEN;
            }

            (*m_TemplateInstance->m_SESSION)[L"CFID"] = CFID;
            (*m_TemplateInstance->m_SESSION)[L"CFTOKEN"] = CFTOKEN;
            (*m_TemplateInstance->m_SESSION)[L"SESSIONID"] = name + "_" + CFID + "_" + CFTOKEN;
            (*m_TemplateInstance->m_SESSION)[L"URLTOKEN"] = "CFID=" + CFID + "&CFTOKEN=" + CFTOKEN;
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
        throw QMKFusionException("Database connection failed.<br />\nDatabase error string: " + conn.lastError().text());
    }

    //Call prepare query
    QSqlQuery query(conn);

    if (query.prepare(m_TemplateInstance->m_QueryOutput) == false)
    {
        throw QMKFusionException("Invalid query syntax.", "Database error string: " + query.lastError().text() + "<br />\n Query: " + m_TemplateInstance->m_QueryOutput);
    }

    //Send query parameters(if any)
    for(int c = 0; c < m_TemplateInstance->m_QueryParams.count(); c++)
    {
        query.bindValue(c, m_TemplateInstance->m_QueryParams.at(c).toString());
    }

    //call query exec.
    if (query.exec() == false)
    {
        throw QMKFusionException("query execute failed.<br />\nDatabase error string: " + query.lastError().text());
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

void QCFTemplate::addCustomFunction(const QString &functionName, std::function<QWDDX (QCFRunningTemplate *, const QList<QWDDX> &)> function)
{
    QCFRunningTemplate *templateInstance;

    if (m_TemplateCustomFunctions.contains(functionName))
    {
        throw QMKFusionException(tr("Function [%1] is already defined in same template.").arg(functionName));
    }

    m_TemplateCustomFunctions.insert(functionName, function);

    if (m_TemplateInstance)
    {
        templateInstance = m_TemplateInstance;
    }
    else
    {
        Qt::HANDLE threadID = QThread::currentThreadId();

        QMKFusionService *service = (QMKFusionService *)QtServiceBase::instance();

        templateInstance = service->m_CFServer.getRunningTemplateByThreadId(threadID);

        if (templateInstance == nullptr)
        {
            return;
        }
    }

    if (templateInstance->m_CustomFunctions.contains(functionName))
    {
        throw QMKFusionException(tr("Function [%1] is already defined in other template.").arg(functionName));
    }

    templateInstance->m_CustomFunctions.insert(functionName, function);
}
