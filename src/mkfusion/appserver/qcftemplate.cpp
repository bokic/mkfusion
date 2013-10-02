#include "qcftemplate.h"
#include "qmkfusionservice.h"
#include "qtservice.h"
#include "cffunctions.h"
#include "qcfserver.h"

#include <QElapsedTimer>
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
    Q_UNUSED(p_URL);
    Q_UNUSED(p_AddToken);
    Q_UNUSED(p_StatusCode);
}

void QCFTemplate::f_Include(const QString &p_template)
{
    if (p_template.isEmpty())
    {
        throw QMKFusionException(tr("Attribute validation error for CFINCLUDE."));
    }

    QDir templateDir = QFileInfo(this->m_isModified.m_Filename).dir();
    QString target_file = QDir::toNativeSeparators(QDir::cleanPath(templateDir.filePath(p_template)));

    if ((!QFile::exists(target_file))||(target_file == templateDir.absolutePath()))
    {
        throw QMKFusionException(tr("Could not find the included template '%1'.").arg(p_template));
    }

    createCFMTemplateDef createCFMTemplate = (createCFMTemplateDef)this->m_TemplateInstance->compileAndLoadTemplate(target_file, "");

    if (createCFMTemplate == nullptr)
    {
        throw QMKFusionException(tr("Can't load template '%1'").arg(p_template));
    }

    QCFTemplate *l_page = createCFMTemplate();
    l_page->setParent(this);
    l_page->run(this->m_TemplateInstance);

    for(const QString &funcName : l_page->m_TemplateCustomFunctions.keys())
    {
        m_TemplateCustomFunctions[funcName] = l_page->m_TemplateCustomFunctions[funcName];
    }

    delete l_page;
    l_page = 0;
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
            if (m_TemplateInstance->m_VARIABLES.m_HiddenScopeLast1)
            {
                if (m_TemplateInstance->m_VARIABLES.m_HiddenScopeLast1->m_Struct->contains(parts.at(0)))
                {
                    return;
                }
            }
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
            if (var->m_HiddenScopeLast1)
            {
                var = var->m_HiddenScopeLast1;

                if (var->m_Struct->contains(item))
                {
                    var = &(*var)[item];

                    continue;
                }
            }

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

bool QCFTemplate::f_FetchQueryRow(QWDDX &destination, QWDDX &query, int row)
{
    if (query.m_Type != QWDDX::Query)
    {
        throw QMKFusionException("Variable is not query.");
    }

    if ((row < 1)||(row > query.m_Struct->value("RECORDCOUNT"))||(query.m_Struct->value("COLUMNS").toString().isEmpty()))
    {
        return false;
    }

    query[L"CURRENTROW"] = row;

    for(int i = 0; i < query.m_Struct->value("RESULTSET").m_Struct->count(); i++)
    {
        QString columnName = query.m_Struct->value("RESULTSET").m_Struct->keys().at(i);

        QWDDX columnData = query.m_Struct->value("RESULTSET").m_Struct->values().at(i).m_Array->at(row - 1);

        updateVariable(destination, columnName, columnData);
    }

    return true;
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
                updateVariable(m_TemplateInstance->m_COOKIE, L"CFID", CFID);
                updateVariable(m_TemplateInstance->m_COOKIE, L"CFTOKEN", CFTOKEN);
                ((QCFServer*)m_TemplateInstance->m_CFServer)->m_Sessions[name + "," + CFID + "," + CFTOKEN.toUpper()] = QWDDX(QWDDX::Struct);
                qDebug() << "New session created.";
            }

            m_TemplateInstance->m_SESSION = &((QCFServer*)m_TemplateInstance->m_CFServer)->m_Sessions[name + "," + CFID + "," + CFTOKEN.toUpper()];

            updateVariable(*(m_TemplateInstance->m_SESSION), L"CFID", CFID);
            updateVariable(*(m_TemplateInstance->m_SESSION), L"CFTOKEN", CFTOKEN);
            updateVariable(*(m_TemplateInstance->m_SESSION), L"SESSIONID", name + "_" + CFID + "_" + CFTOKEN);
            updateVariable((*m_TemplateInstance->m_SESSION), L"URLTOKEN", "CFID=" + CFID + "&CFTOKEN=" + CFTOKEN);
        }
        else if ((setClientCookies == false)&&(m_TemplateInstance->m_URL.m_Struct->contains("CFID"))&&(m_TemplateInstance->m_URL.m_Struct->contains("CFTOKEN")))
        {
            QString CFID = m_TemplateInstance->m_URL[L"CFID"];
            QString CFTOKEN = m_TemplateInstance->m_URL[L"CFTOKEN"];

            if (!((QCFServer*)m_TemplateInstance->m_CFServer)->m_Sessions.contains(name + "," + CFID + "," + CFTOKEN.toUpper()))
            {
                updateVariable(m_TemplateInstance->m_COOKIE, L"CFID", CFID);
                updateVariable(m_TemplateInstance->m_COOKIE, L"CFTOKEN", CFTOKEN);
                ((QCFServer*)m_TemplateInstance->m_CFServer)->createSessonStrings(CFID, CFTOKEN);
                ((QCFServer*)m_TemplateInstance->m_CFServer)->m_Sessions[name + "," + CFID + "," + CFTOKEN.toUpper()] = QWDDX(QWDDX::Struct);
                qDebug() << "New session created.";
            }

            m_TemplateInstance->m_SESSION = &((QCFServer*)m_TemplateInstance->m_CFServer)->m_Sessions[name + "," + CFID + "," + CFTOKEN.toUpper()];

            updateVariable(*(m_TemplateInstance->m_SESSION), L"CFID", CFID);
            updateVariable(*(m_TemplateInstance->m_SESSION), L"CFTOKEN", CFTOKEN);
            updateVariable(*(m_TemplateInstance->m_SESSION), L"SESSIONID", name + "_" + CFID + "_" + CFTOKEN);
            updateVariable(*(m_TemplateInstance->m_SESSION), L"URLTOKEN", "CFID=" + CFID + "&CFTOKEN=" + CFTOKEN);
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
                updateVariable(m_TemplateInstance->m_COOKIE, L"CFID", CFID);
                updateVariable(m_TemplateInstance->m_COOKIE, L"CFTOKEN", CFTOKEN);
            }

            updateVariable(*(m_TemplateInstance->m_SESSION), L"CFID", CFID);
            updateVariable(*(m_TemplateInstance->m_SESSION), L"CFTOKEN", CFTOKEN);
            updateVariable(*(m_TemplateInstance->m_SESSION), L"SESSIONID", name + "_" + CFID + "_" + CFTOKEN);
            updateVariable(*(m_TemplateInstance->m_SESSION), L"URLTOKEN", "CFID=" + CFID + "&CFTOKEN=" + CFTOKEN);
        }
    }
}

void QCFTemplate::f_FileUploadMove(const QString &destination, const QString &fileField, const QString &accept, const QString &attributes, const QString &mode, const QString &nameConflict, const QString &result)
{
#ifdef Q_OS_WIN
    Q_UNUSED(mode);
#elif defined Q_OS_LINUX
    Q_UNUSED(attributes);
#else
    #error Windows and Linux OSs are currently supported.
#endif
    QString tmp;
    QDir destinationDir(destination);

    if (!destinationDir.exists())
    {
        throw QMKFusionException("Directory does\'t exists.", QString("Directory [%1] does\'t exists.").arg(destination));
    }

    tmp = fileField.toUpper();

    if (tmp.startsWith("FORM."))
    {
        tmp = tmp.right(fileField.length() - 5);
    }

    if (!m_TemplateInstance->m_FileUpload.contains(tmp))
    {
        throw QMKFusionException(QString("No file field with name [%1].").arg(tmp));
    }

    if (!accept.isEmpty())
    {
        QStringList acceptList = accept.split(',');
        QString contentType = m_TemplateInstance->m_FileUpload[tmp].m_ContentType.trimmed();
        bool found = false;

        for(const QString item : acceptList)
        {
            if (item.trimmed().compare(contentType, Qt::CaseInsensitive) == 0)
            {
                found = true;

                break;
            }
        }

        if (!found)
        {
            throw QMKFusionException(QString("cffile upload content-type [%1] is not permitted.").arg(contentType));
        }
    }

    QFile destinationFile(destinationDir.absoluteFilePath(m_TemplateInstance->m_FileUpload[tmp].m_Filename));
    QWDDX cffile(QWDDX::Struct);
    bool copied = false;

    //cffile.m_Struct->insert("ATTEMPTEDSERVERFILE", destinationFile.fileName());
    //cffile.m_Struct->insert("FILEEXISTED", destinationFile.exists());

    if ((nameConflict.isEmpty())||(nameConflict.compare("Error", Qt::CaseInsensitive) == 0))
    {
        /*if (destinationFile.exists())
        {
            throw QMKFusionException("cffile upload errror.", QString("Destination file [%1] allready exist.").arg(destinationFile.fileName()));
        }

        if (!m_TemplateInstance->m_FileUpload[tmp].m_File->copy(destinationFile.fileName()))
        {
            throw QMKFusionException("cffile upload errror.", QString("Error copying file [%1].").arg(destinationFile.fileName()));
        }*/
        throw QMKFusionException("cffile upload nameConflict=Error is not implemented.");
    }
    else if (nameConflict.compare("Skip", Qt::CaseInsensitive) == 0)
    {
        /*if (destinationFile.exists())
        {
            cffile.m_Struct->insert("FILEEXISTED", false);


            updateVariableQStr(m_TemplateInstance->m_VARIABLES, result, cffile);
            return;
        }*/
        throw QMKFusionException("cffile upload nameConflict=Skip is not implemented.");
    }
    else if (nameConflict.compare("Overwrite", Qt::CaseInsensitive) == 0)
    {
        /*if (destinationFile.exists())
        {
            if (!destinationFile.remove())
            {
                throw QMKFusionException("cffile upload errror.", QString("Error overwriting file [%1].").arg(destinationFile.fileName()));
            }
        }*/
        throw QMKFusionException("cffile upload nameConflict=Overwrite is not implemented.");
    }
    else if (nameConflict.compare("MakeUnique", Qt::CaseInsensitive) == 0)
    {
        if (destinationFile.exists())
        {
            QFile newFile;
            int index = 1;

            do
            {
                QFileInfo fi(destinationFile);

                QString newBaseName = fi.completeBaseName() + QString::number(index) + "." + fi.suffix();

                fi.setFile(fi.dir(), newBaseName);

                newFile.setFileName(fi.absoluteFilePath());

                index++;

            } while(newFile.exists());

            destinationFile.setFileName(newFile.fileName());
        }

        if (!m_TemplateInstance->m_FileUpload[tmp].m_File->copy(destinationFile.fileName()))
        {
            throw QMKFusionException("cffile upload errror.", QString("Error writing to file [%1].").arg(destinationFile.fileName()));
        }

        cffile.m_Struct->insert("SERVERDIRECTORY", QDir::toNativeSeparators(QFileInfo(destinationFile).path()));
        cffile.m_Struct->insert("SERVERFILE", QFileInfo(destinationFile).fileName());
        cffile.m_Struct->insert("SERVERFILENAME", QFileInfo(destinationFile).completeBaseName());
        cffile.m_Struct->insert("SERVERFILEEXT", QFileInfo(destinationFile).completeSuffix());
        cffile.m_Struct->insert("TIMECREATED", QFileInfo(destinationFile).created());
        cffile.m_Struct->insert("TIMELASTMODIFIED", QFileInfo(destinationFile).lastModified());
    }
    else
    {
        throw QMKFusionException(QString("Invalid cffile nameConflict value [%1].").arg(nameConflict));
    }

    if ((copied)&&(!mode.isEmpty()))
    {
/*#ifdef Q_OS_WIN
        ::SetFileAttributes();
#elif defined Q_OS_LINUX
        destinationFile.setPermissions();
#else
    #error Windows and Linux OSs are currently supported.
#endif*/
    }

    updateVariableQStr(m_TemplateInstance->m_VARIABLES, result, cffile);
}

void QCFTemplate::startQuery()
{
    m_TemplateInstance->m_QueryOutput.clear();
    m_TemplateInstance->m_QueryParams.clear();

    m_TemplateInstance->m_OutputType = QCFRunningTemplate::OutputTypeQuery;
}

QWDDX QCFTemplate::endQuery(const QString &p_DataSource)
{
    QElapsedTimer timer;
    QWDDX ret = cf_QueryNew("");

    timer.start();

    //Get dbconnection object
    QSqlDatabase *conn = ((QCFServer*)m_TemplateInstance->m_CFServer)->getDBConnection(p_DataSource);

    if (!conn->isOpen())
    {
        if (conn->open() == false)
        {
            throw QMKFusionDatabaseException("Database connection failed.<br />\nDatabase error string: " + conn->lastError().text());
        }
    }

    //Call prepare query
    QSqlQuery query(*conn);

    if (query.prepare(m_TemplateInstance->m_QueryOutput) == false)
    {
        throw QMKFusionDatabaseException("Invalid query syntax.", "Database error string: " + query.lastError().text() + "<br />\n Query: " + m_TemplateInstance->m_QueryOutput);
    }

    //Send query parameters(if any)
    for(int c = 0; c < m_TemplateInstance->m_QueryParams.count(); c++)
    {
        query.bindValue(c, m_TemplateInstance->m_QueryParams.at(c).toString());
    }

    //call query exec.
    if (query.exec() == false)
    {
        throw QMKFusionDatabaseException("query execute failed.<br />\nDatabase error string: " + query.lastError().text());
    }

    // copy
    for(int f = 0; f < query.record().count(); f++)
    {
        QString fieldName = query.record().fieldName(f);
        cf_QueryAddColumn(ret, fieldName);
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

    ret.m_Struct->insert("RECORDCOUNT", row - 1); // TODO: Rewrite it when possible.

    m_TemplateInstance->m_QueryOutput.clear();
    m_TemplateInstance->m_QueryParams.clear();

    m_TemplateInstance->m_OutputType = QCFRunningTemplate::OutputTypeContent;

    this->m_TemplateInstance->m_VARIABLES.m_Struct->insert("CFQUERY.EXECUTIONTIME", (int)timer.elapsed());

    return ret;
}

void QCFTemplate::endQueryNoReturn(const QString &p_DataSource)
{
    QElapsedTimer timer;
    timer.start();

    //Get dbconnection object
    QSqlDatabase *conn = ((QCFServer*)m_TemplateInstance->m_CFServer)->getDBConnection(p_DataSource);

    if (!conn->isOpen())
    {
        if (conn->open() == false)
        {
            throw QMKFusionDatabaseException("Database connection failed.<br />\nDatabase error string: " + conn->lastError().text());
        }
    }

    //Call prepare query
    QSqlQuery query(*conn);

    if (query.prepare(m_TemplateInstance->m_QueryOutput) == false)
    {
        throw QMKFusionDatabaseException("Invalid query syntax.", "Database error string: " + query.lastError().text() + "<br />\n Query: " + m_TemplateInstance->m_QueryOutput);
    }

    //Send query parameters(if any)
    for(int c = 0; c < m_TemplateInstance->m_QueryParams.count(); c++)
    {
        query.bindValue(c, m_TemplateInstance->m_QueryParams.at(c).toString());
    }

    //call query exec.
    if (query.exec() == false)
    {
        throw QMKFusionDatabaseException("query execute failed.<br />\nDatabase error string: " + query.lastError().text());
    }

    m_TemplateInstance->m_QueryOutput.clear();
    m_TemplateInstance->m_QueryParams.clear();

    m_TemplateInstance->m_OutputType = QCFRunningTemplate::OutputTypeContent;

    this->m_TemplateInstance->m_VARIABLES.m_Struct->insert("CFQUERY.EXECUTIONTIME", (int)timer.elapsed());
}

void QCFTemplate::addCustomFunction(const QString &functionName, std::function<QWDDX (QCFRunningTemplate *, const QList<QWDDX> &)> function)
{
    QCFRunningTemplate *templateInstance = nullptr;

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

        if (service)
        {
            templateInstance = service->m_CFServer.getRunningTemplateByThreadId(threadID);
        }

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

void QCFTemplate::f_SetCookie(const QString &name, const QString &value, const QString &expires)
{
    QWDDX val(QWDDX::Struct);

    val.m_Struct->insert("value", value);

    if (expires.compare("never", Qt::CaseInsensitive) == 0)
    {
        val.m_Struct->insert("expires", QLocale("en").toString(QDateTime::currentDateTime().addYears(30), "ddd, dd-MMM-yyyy hh:mm:ss").append(" GMT"));
    }
    else if (expires.compare("now", Qt::CaseInsensitive) == 0)
    {
        val.m_Struct->insert("expires", 0);
    }
    else
    {
        val.m_Struct->insert("expires", expires);
    }

    m_TemplateInstance->m_COOKIE.m_Struct->insert(name.toUpper(), value);

    m_TemplateInstance->m_SetCookies.m_Struct->insert(name.toUpper(), val);
}

void QCFTemplate::startCustomTag(const QString &path, const QString &name, const QWDDX &attributes, bool hasEndTag, QCustomTagType type)
{
    // Get customtag handle.
    QString target_file;
    QString file;

    switch(type)
    {
    case QCustomTagTypeModuleName: // Only search in app defined custom tag dir.
        {
            QStringList path;
            path = name.split(".");
            file = path.takeLast().trimmed();

            if (file.isEmpty())
            {
                throw QMKFusionException(QString("cfmodule invalid parameter name. Empty filename is not supported. [%1].").arg(name));
            }

            target_file = ((QCFServer *)m_TemplateInstance->m_CFServer)->m_CustomTagsPath + QDir::separator();

            for(int c = 0; c < path.count(); c++)
            {
                const QString subDir = path.at(c).trimmed();

                if (subDir.isEmpty())
                {
                    throw QMKFusionException(QString("cfmodule invalid parameter name. Empty subdirs are not supported. [%1].").arg(name));
                }

                target_file.append(path.at(c) + QDir::separator());
            }
        }

        target_file.append(file + ".cfm"); // TODO: custom tag with lower case extension is currently supported.

        if (!QFile::exists(target_file))
        {
            throw QMKFusionException(QString("cfmodule attribute name. Custom tag [%1] is not found.").arg(name));
        }
        break;
    case QCustomTagTypeModuleTemplate: // Only search in path relative from caller template.
        {
            QFileInfo fi(this->m_isModified.m_Filename);

            QString tmpStr = fi.absolutePath();
            QString targetPath = QDir(tmpStr + QDir::separator() + QFileInfo(name).path()).absolutePath();

            // TODO: Somehow check if targetPath goes outside app dir.

            target_file = targetPath + QDir::separator() + QFileInfo(name).fileName();
        }

        if (!QFile::exists(target_file))
        {
            throw QMKFusionException(QString("cfmodule attribute template. Custom tag [%1] is not found.").arg(name));
        }
        break;
    case QCustomTagType_: // Search caller template path first, and if not found, search app defined custom tag dir.

        target_file = QFileInfo(this->m_isModified.m_Filename).absolutePath() + QDir::separator() + name + ".cfm";

        if (!QFile::exists(target_file))
        {
            target_file = ((QCFServer *)m_TemplateInstance->m_CFServer)->m_CustomTagsPath + QDir::separator() + name + ".cfm";

            if (!QFile::exists(target_file))
            {
                throw QMKFusionException(QString("Custom tag [%1] is not found.").arg(name));
            }
        }
        break;
    case QCustomTagTypeImport:

        // TODO: Somehow check if targetPath goes outside app dir.
        target_file = QFileInfo(QFileInfo(this->m_isModified.m_Filename).absolutePath() + QDir::separator() + path + QDir::separator()).absolutePath() + QDir::separator() + name + ".cfm";

        if (!QFile::exists(target_file))
        {
            throw QMKFusionException(QString("Custom tag [%1] within path[%2] is not found.").arg(name).arg(path));
        }
        break;
    default:
        throw QMKFusionException("Unknown custom tag type.");
        break;
    }

    createCFMTemplateDef createCFMTemplate = (createCFMTemplateDef)this->m_TemplateInstance->compileAndLoadTemplate(target_file, "");

    if (createCFMTemplate == nullptr)
    {
        throw QMKFusionException(tr("Can't load template '%1'").arg(target_file));
    }

    // Save [Caller, Attributes, ThisTag] Variable vars to local var.
    QWDDX save(QWDDX::Struct);
    if (m_TemplateInstance->m_VARIABLES.m_Struct->contains("CALLER"))
    {
        updateVariableStr(save, L"Caller", m_TemplateInstance->m_VARIABLES[L"CALLER"]);
    }
    if (m_TemplateInstance->m_VARIABLES.m_Struct->contains("ATTRIBUTES"))
    {
        updateVariableStr(save, L"Attributes", m_TemplateInstance->m_VARIABLES[L"ATTRIBUTES"]);
    }
    if (m_TemplateInstance->m_VARIABLES.m_Struct->contains("THISTAG"))
    {
        updateVariableStr(save, L"ThisTag", m_TemplateInstance->m_VARIABLES[L"ThisTag"]);
    }

    // Add [Caller, Attributes, ThisTag] Variable vars.
    updateVariableStr(m_TemplateInstance->m_VARIABLES, L"Caller", QWDDX(QWDDX::Struct));
    updateVariableStr(m_TemplateInstance->m_VARIABLES, L"Attributes", attributes);
    updateVariableStr(m_TemplateInstance->m_VARIABLES, L"ThisTag", QWDDX(QWDDX::Struct));
    updateVariableStr(m_TemplateInstance->m_VARIABLES[L"ThisTag"], L"GeneratedContent", L"");
    updateVariableStr(m_TemplateInstance->m_VARIABLES[L"ThisTag"], L"executionMode", L"start");
    updateVariableStr(m_TemplateInstance->m_VARIABLES[L"ThisTag"], L"hasendtag", hasEndTag ? L"YES":L"NO");

    // Call custom tag.
    QCFTemplate *l_page = createCFMTemplate();
    l_page->setParent(this);
    l_page->m_CustomTags = m_CustomTags;
    l_page->run(this->m_TemplateInstance);
    m_CustomTags = l_page->m_CustomTags;
    delete l_page;
    l_page = 0;

    if (hasEndTag)
    {
        QWDDX customTagData(QWDDX::Struct);

        // Switch output.
        updateVariableStr(customTagData, L"OUTPUT", m_TemplateInstance->m_Output);
        m_TemplateInstance->m_Output.clear();

        // Save(push) [Caller, Attributes, ThisTag] Variable to multihash.
        updateVariableStr(customTagData, L"Name", name);
        updateVariableStr(customTagData, L"Type", (int)type);
        updateVariableStr(customTagData, L"Caller", m_TemplateInstance->m_VARIABLES[L"CALLER"]);
        updateVariableStr(customTagData, L"Attributes", attributes);
        updateVariableStr(customTagData, L"ThisTag", m_TemplateInstance->m_VARIABLES[L"THISTAG"]);

        m_CustomTags.push_back(customTagData);
    }

    // Restore [Caller, Attributes, ThisTag] Variable vars from local var.
    m_TemplateInstance->m_VARIABLES.m_Struct->remove("CALLER");
    if (save.m_Struct->contains("CALLER"))
    {
        updateVariableStr(m_TemplateInstance->m_VARIABLES, L"Caller", save[L"CALLER"]);
    }
    m_TemplateInstance->m_VARIABLES.m_Struct->remove("ATTRIBUTES");
    if (save.m_Struct->contains("ATTRIBUTES"))
    {
        updateVariableStr(m_TemplateInstance->m_VARIABLES, L"Attributes", save[L"ATTRIBUTES"]);
    }
    m_TemplateInstance->m_VARIABLES.m_Struct->remove("THISTAG");
    if (save.m_Struct->contains("THISTAG"))
    {
        updateVariableStr(m_TemplateInstance->m_VARIABLES, L"ThisTag", save[L"THISTAG"]);
    }
}

bool QCFTemplate::endCustomTag(const QString &path, const QString &name, QCustomTagType type)
{
    // Get customtag handle.
    QString target_file;
    QString file;

    switch(type)
    {
    case QCustomTagTypeModuleName: // Only search in app defined custom tag dir.
        {
            QStringList path;
            path = name.split(".");
            file = path.takeLast().trimmed();

            if (file.isEmpty())
            {
                throw QMKFusionException(QString("cfmodule invalid parameter name. Empty filename is not supported. [%1].").arg(name));
            }

            target_file = ((QCFServer *)m_TemplateInstance->m_CFServer)->m_CustomTagsPath + QDir::separator();

            for(int c = 0; c < path.count(); c++)
            {
                const QString subDir = path.at(c).trimmed();

                if (subDir.isEmpty())
                {
                    throw QMKFusionException(QString("cfmodule invalid parameter name. Empty subdirs are not supported. [%1].").arg(name));
                }

                target_file.append(path.at(c) + QDir::separator());
            }
        }

        target_file.append(file + ".cfm"); // TODO: custom tag with lower case extension is currently supported.

        if (!QFile::exists(target_file))
        {
            throw QMKFusionException(QString("cfmodule attribute name. Custom tag [%1] is not found.").arg(name));
        }
        break;
    case QCustomTagTypeModuleTemplate: // Only search in path relative from caller template.
        {
            QFileInfo fi(this->m_isModified.m_Filename);

            QString tmpStr = fi.absolutePath();
            QString targetPath = QDir(tmpStr + QDir::separator() + QFileInfo(name).path()).absolutePath();

            // TODO: Somehow check if targetPath goes outside app dir.

            target_file = targetPath + QDir::separator() + QFileInfo(name).fileName();
        }

        if (!QFile::exists(target_file))
        {
            throw QMKFusionException(QString("cfmodule attribute template. Custom tag [%1] is not found.").arg(name));
        }
        break;
    case QCustomTagType_: // Search caller template path first, and if not found, search app defined custom tag dir.

        target_file = QFileInfo(this->m_isModified.m_Filename).absolutePath() + QDir::separator() + name + ".cfm";

        if (!QFile::exists(target_file))
        {
            target_file = ((QCFServer *)m_TemplateInstance->m_CFServer)->m_CustomTagsPath + QDir::separator() + name + ".cfm";

            if (!QFile::exists(target_file))
            {
                throw QMKFusionException(QString("Custom tag [%1] is not found.").arg(name));
            }
        }
        break;
    case QCustomTagTypeImport:

        // TODO: Somehow check if targetPath goes outside app dir.
        target_file = QFileInfo(QFileInfo(this->m_isModified.m_Filename).absolutePath() + QDir::separator() + path + QDir::separator()).absolutePath() + QDir::separator() + name + ".cfm";

        if (!QFile::exists(target_file))
        {
            throw QMKFusionException(QString("Custom tag [%1] within path[%2] is not found.").arg(name).arg(path));
        }
        break;
    default:
        throw QMKFusionException("Unknown custom tag type.");
        break;
    }

    createCFMTemplateDef createCFMTemplate = (createCFMTemplateDef)this->m_TemplateInstance->compileAndLoadTemplate(target_file, "");

    if (createCFMTemplate == nullptr)
    {
        throw QMKFusionException(tr("Can't load template '%1'").arg(target_file));
    }

    // Save [Caller, Attributes, ThisTag] Variable vars to local var.
    QWDDX save(QWDDX::Struct);
    if (m_TemplateInstance->m_VARIABLES.m_Struct->contains("CALLER"))
    {
        updateVariableStr(save, L"Caller", m_TemplateInstance->m_VARIABLES[L"CALLER"]);
    }
    if (m_TemplateInstance->m_VARIABLES.m_Struct->contains("ATTRIBUTES"))
    {
        updateVariableStr(save, L"Attributes", m_TemplateInstance->m_VARIABLES[L"ATTRIBUTES"]);
    }
    if (m_TemplateInstance->m_VARIABLES.m_Struct->contains("THISTAG"))
    {
        updateVariableStr(save, L"ThisTag", m_TemplateInstance->m_VARIABLES[L"ThisTag"]);
    }

    // Restore(pop) [Caller, Attributes, ThisTag] Variable from multihash.
    QWDDX restoredVars = m_CustomTags.takeLast();

    // Add [Caller, Attributes, ThisTag] Variable vars.
    updateVariableStr(m_TemplateInstance->m_VARIABLES, L"Caller", restoredVars[L"Caller"]);
    updateVariableStr(m_TemplateInstance->m_VARIABLES, L"Attributes", restoredVars[L"Attributes"]);
    updateVariableStr(m_TemplateInstance->m_VARIABLES, L"ThisTag", restoredVars[L"ThisTag"]);
    updateVariableStr(m_TemplateInstance->m_VARIABLES[L"ThisTag"], L"GeneratedContent", m_TemplateInstance->m_Output);
    updateVariableStr(m_TemplateInstance->m_VARIABLES[L"ThisTag"], L"executionMode", L"end");
    updateVariableStr(m_TemplateInstance->m_VARIABLES[L"ThisTag"], L"hasendtag", L"YES");

    // Switch output.
    m_TemplateInstance->m_Output.clear();

    // Call custom tag.
    QCFTemplate *l_page = createCFMTemplate();
    l_page->setParent(this);
    l_page->run(this->m_TemplateInstance);
    delete l_page;
    l_page = 0;

    // Switch output.
    m_TemplateInstance->m_Output = restoredVars[L"OUTPUT"].toString() + m_TemplateInstance->m_VARIABLES[L"ThisTag"][L"GeneratedContent"].toString() + m_TemplateInstance->m_Output;

    // Restore [Caller, Attributes, ThisTag] Variable vars from local var.
    m_TemplateInstance->m_VARIABLES.m_Struct->remove("CALLER");
    if (save.m_Struct->contains("CALLER"))
    {
        updateVariableStr(m_TemplateInstance->m_VARIABLES, L"Caller", save[L"CALLER"]);
    }
    m_TemplateInstance->m_VARIABLES.m_Struct->remove("ATTRIBUTES");
    if (save.m_Struct->contains("ATTRIBUTES"))
    {
        updateVariableStr(m_TemplateInstance->m_VARIABLES, L"Attributes", save[L"ATTRIBUTES"]);
    }
    m_TemplateInstance->m_VARIABLES.m_Struct->remove("THISTAG");
    if (save.m_Struct->contains("THISTAG"))
    {
        updateVariableStr(m_TemplateInstance->m_VARIABLES, L"ThisTag", save[L"THISTAG"]);
    }

    return false;
}

void QCFTemplate::f_cfAssociate(const QString &baseTagName, const QString &keyName)
{
    for(QWDDX &customTag : m_CustomTags)
    {
        const QString &name = QString("cf_") + customTag[L"Name"].toString();

        if (name.compare(baseTagName, Qt::CaseInsensitive) == 0)
        {
            if (!cf_StructKeyExists(customTag[L"ThisTag"], keyName.toUpper()))
            {
                updateVariableQStr(customTag[L"ThisTag"], keyName, QWDDX(QWDDX::Array));
            }

            cf_ArrayAppend(customTag[L"ThisTag"][keyName.toUpper()], m_TemplateInstance->m_VARIABLES[L"Attributes"]);

            return;
        }
    }

    throw QMKFusionException(QString("Not within [%1] custom tag.").arg(baseTagName));
}
