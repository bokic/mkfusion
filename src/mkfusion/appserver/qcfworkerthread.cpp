#include "qcfworkerthread.h"
#include "qmkfusionexception.h"
#include "qcftemplateinstance.h"
#include "qcfserver.h"

#include <qcflog.h>


QCFWorkerThread::QCFWorkerThread(QLocalSocket *socket, QObject *parent): QThread(parent)
{
    m_Socket = socket;
    m_Socket->setParent(nullptr);
    m_Socket->moveToThread(this);
}

QCFWorkerThread::~QCFWorkerThread()
{
    if (m_Socket)
    {
        delete m_Socket;
        m_Socket = nullptr;
    }
}

void QCFWorkerThread::run()
{
    QCFLOG(CFLOG_WORKER, QCFLOG_INFO_PERF, "Worker thread started.");

    try
    {
        if (!readRequest())
        {
            QCFLOG(CFLOG_WORKER, QCFLOG_ERROR, "Reading worker request failed.");

            throw QMKFusionException("Unknown HTTP Method.");
        }

        // LoadCompiledFile
        QString err;
        QCFTemplateInstance *instance = QCFServer::instance()->m_Templates.getTemplateInstanceForSource(m_Request.m_Filename);

    }
    catch (const QMKFusionCFAbortException &ex)
    {
        Q_UNUSED(ex);
    }
    catch (const QMKFusionTemplateException &ex)
    {
        m_StatusCode = 500;

        writeException(ex);
    }
    catch (const QMKFusionException &ex)
    {
        m_StatusCode = 500;

        writeException(ex);
    }
#ifndef QT_DEBUG
    catch(...)
    {
        m_StatusCode = 500;

        writeException(QMKFusionException("Internal error."));
    }
#endif

    writeResponse();

    m_Socket->close();

    QCFLOG(CFLOG_WORKER, QCFLOG_INFO_PERF, "Worker thread ended.");
}

bool QCFWorkerThread::readRequest()
{
    return true;
}

bool QCFWorkerThread::writeResponse()
{
    return true;
}

void QCFWorkerThread::writeException(const QMKFusionException &ex)
{
    m_Output.append("<font style=\"COLOR: black; FONT: 16pt/18pt verdana\">The web site you are accessing has experienced an unexpected error.<br>Please contact the website administrator.</font>\n");
    m_Output.append("<br>\n");
    m_Output.append("<br>\n");
    m_Output.append("<table border=\"1\" cellpadding=\"3\" bordercolor=\"#000808\" bgcolor=\"#e7e7e7\">\n");
    m_Output.append("\t<tr>\n");
    m_Output.append("\t\t<td bgcolor=\"#000066\">\n");
    m_Output.append("\t\t\t<font style=\"COLOR: white; FONT: 11pt/13pt verdana\" color=\"white\">The following information is meant for the website developer for debugging purposes.</font>\n");
    m_Output.append("\t\t</td>\n");
    m_Output.append("\t<tr>\n");
    m_Output.append("\t<tr>\n");
    m_Output.append("\t\t<td bgcolor=\"#4646EE\">\n");
    m_Output.append("\t\t\t<font style=\"COLOR: white; FONT: 11pt/13pt verdana\" color=\"white\">Error Occurred While Processing Request</font>\n");
    m_Output.append("\t\t</td>\n");
    m_Output.append("\t</tr>\n");
    m_Output.append("\t<tr>\n");
    m_Output.append("\t\t<td>\n");
    m_Output.append("\t\t\t<font style=\"COLOR: black; FONT: 8pt/11pt verdana\">\n");
    m_Output.append("\t\t\t\t<table width=\"500\" cellpadding=\"0\" cellspacing=\"0\" border=\"0\">\n");
    m_Output.append("\t\t\t\t\t<tr>\n");
    m_Output.append("\t\t\t\t\t\t<td id=\"tableProps2\" align=\"left\" valign=\"middle\" width=\"500\">\n");
    m_Output.append("\t\t\t\t\t\t\t<h1 id=\"textSection1\" style=\"COLOR: black; FONT: 13pt/15pt verdana\">" + ex.m_Message + "</h1>\n");
    m_Output.append("\t\t\t\t\t\t\t" + ex.m_Detail + "\n");
    m_Output.append("\t\t\t\t\t\t</td>\n");
    m_Output.append("\t\t\t\t\t</tr>\n");
    m_Output.append("\t\t\t\t\t<tr>\n");
    m_Output.append("\t\t\t\t\t\t<td id=\"tablePropsWidth\" width=\"400\" colspan=\"2\">\n");
    m_Output.append("\t\t\t\t\t\t\t<font style=\"COLOR: black; FONT: 8pt/11pt verdana\"></font>\n");
    m_Output.append("\t\t\t\t\t\t</td>\n");
    m_Output.append("\t\t\t\t\t</tr>\n");
    m_Output.append("\t\t\t\t\t<tr>\n");
    m_Output.append("\t\t\t\t\t\t<td height>&nbsp;</td>\n");
    m_Output.append("\t\t\t\t\t</tr>\n");
    m_Output.append("\t\t\t\t\t<tr>\n");
    m_Output.append("\t\t\t\t\t\t<td colspan=\"2\">\n");
    m_Output.append("\t\t\t\t\t\t\t<font style=\"COLOR: black; FONT: 8pt/11pt verdana\">\n");
    m_Output.append("\t\t\t\t\t\t\t\tResources:\n");
    m_Output.append("\t\t\t\t\t\t\t\t<ul>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<li>Enable Robust Exception Information to provide greater detail about the source of errors.  In the Administrator, click Debugging & Logging > Debug Output Settings, and select the Robust Exception Information option.</li>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<li>Check the <a href='http://www.bokicsoft.com/mkfusion/docs/' target=\"new\">ColdFusion documentation</a> to verify that you are using the correct syntax.</li>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<li>Search the <a href='http://www.bokicsoft.com/mkfusion/kb/' target=\"new\">Knowledge Base</a> to find a solution to your problem.</li>\n");
    m_Output.append("\t\t\t\t\t\t\t\t</ul>\n");
    m_Output.append("\t\t\t\t\t\t\t</font>\n");
    m_Output.append("\t\t\t\t\t\t</td>\n");
    m_Output.append("\t\t\t\t\t</tr>\n");
    m_Output.append("\t\t\t\t\t<tr>\n");
    m_Output.append("\t\t\t\t\t\t<td colspan=\"2\">\n");
    m_Output.append("\t\t\t\t\t\t\t<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\">\n");
    m_Output.append("\t\t\t\t\t\t\t\t<tr>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">Browser&nbsp;&nbsp;</td>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">" + m_Request.m_UserAgent + "</td>\n");
    m_Output.append("\t\t\t\t\t\t\t\t</tr>\n");
    m_Output.append("\t\t\t\t\t\t\t\t<tr>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">Remote Address&nbsp;&nbsp;</td>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">" + m_Request.m_Host + "</td>\n");
    m_Output.append("\t\t\t\t\t\t\t\t</tr>\n");
    m_Output.append("\t\t\t\t\t\t\t\t<tr>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">Referrer&nbsp;&nbsp;</td>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">" + m_Request.m_Referer + "</td>\n");
    m_Output.append("\t\t\t\t\t\t\t\t</tr>\n");
    m_Output.append("\t\t\t\t\t\t\t\t<tr>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">Date/Time&nbsp;&nbsp;</td>\n");
    m_Output.append("\t\t\t\t\t\t\t\t\t<td><font style=\"COLOR: black; FONT: 8pt/11pt verdana\">" + QDateTime::currentDateTime().toString("dd-MMM-yy hh:mm AP") + "</td>\n");
    m_Output.append("\t\t\t\t\t\t\t\t</tr>\n");
    m_Output.append("\t\t\t\t\t\t\t</table>\n");
    m_Output.append("\t\t\t\t\t\t</td>\n");
    m_Output.append("\t\t\t\t\t</tr>\n");
    m_Output.append("\t\t\t\t</table>\n");
    m_Output.append("\t\t\t</font>\n");
    m_Output.append("\t\t</td>\n");
    m_Output.append("\t</tr>\n");
    m_Output.append("</table>\n");
}
