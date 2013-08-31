#include "qcfserver.h"
#include "qmkfusionexception.h"
#include "qcfgenerator.h"
#include "qcftemplate.h"
#include "qcfparser.h"

//#include <QCoreApplication>
#include <QTextCodec>
#include <QLocalSocket>
#include <QWriteLocker>
#include <QFileInfo>
#include <QLibrary>
#include <QDir>

#ifdef Q_OS_WIN
#include <windows.h>
#include <Tlhelp32.h>
#include <Psapi.h>
#elif defined Q_OS_LINUX
#include <sys/stat.h>
#include <unistd.h>
#else
#error Windows and Linux OSs are currently supported.
#endif


QString getCurrentExecutableFileName()
{
	QString ret;
#ifdef Q_OS_WIN
	static volatile int dummy = 0;

	tagMODULEENTRY32W l_moduleEntry;
	l_moduleEntry.dwSize = sizeof(tagMODULEENTRY32W);
	bool l_MoreModules;

	HANDLE l_handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	if (l_handle != INVALID_HANDLE_VALUE)
	{
		for(l_MoreModules = Module32FirstW(l_handle, &l_moduleEntry); l_MoreModules == true; l_MoreModules = Module32NextW(l_handle, &l_moduleEntry))
		{
			if ((((quint32)&dummy) >= (((quint32)l_moduleEntry.modBaseAddr)))&&(((quint32)&dummy) < (((quint32)l_moduleEntry.modBaseAddr + l_moduleEntry.modBaseSize))))
			{
				ret = QString::fromWCharArray(l_moduleEntry.szExePath);
				break;
			}
		}

		CloseHandle(l_handle);
	}
#elif defined Q_OS_LINUX

	QFile filename("/proc/" + QString::number(getpid()) + "/cmdline");
	filename.open(QFile::ReadOnly);

	ret = filename.readLine();
#else
#error Windows and Linux OSs are currently supported.
#endif

	return ret;
}

QCFServer::QCFServer()
{
	m_mainTimer = 0;

    connect(&m_LocalServer, &QLocalServer::newConnection, this, &QCFServer::on_newConnection);
}

QCFServer::~QCFServer()
{
}

void QCFServer::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

	return;
}

void QCFServer::on_newConnection()
{
    QWriteLocker lock(&m_runningTemplatesLock);

	for (; ; )
	{
		QLocalSocket *l_LocalSocket = m_LocalServer.nextPendingConnection();

		if (l_LocalSocket == NULL)
		{
			break;
		}

		if (m_runningTemplates.count() >= m_MaxSimulRunningTemplates)
		{
			l_LocalSocket->write("\x04\x00\x00\x00", 4);
			l_LocalSocket->write("Maximum running templates.");
			l_LocalSocket->waitForBytesWritten(30000);

			l_LocalSocket->disconnectFromServer();
			l_LocalSocket->waitForDisconnected(30000);
			l_LocalSocket->deleteLater();
			return;
		}

		if (l_LocalSocket->waitForConnected(1000) == false)
		{
			return;
		}

		QThread *l_thread = new QThread(this);

		m_runningTemplates.append(l_thread);

		QCFRunningTemplate *l_runningTemplate = new QCFRunningTemplate();

		l_runningTemplate->m_CFServer = this;
		l_runningTemplate->moveToThread(l_thread);
		l_runningTemplate->m_Socket = l_LocalSocket;
		l_LocalSocket->setParent(NULL);
		l_LocalSocket->moveToThread(l_thread);

        connect(l_thread, &QThread::started, l_runningTemplate, &QCFRunningTemplate::worker);
        connect(l_runningTemplate, &QCFRunningTemplate::finished, l_thread, &QThread::quit);
        connect(l_thread, &QThread::finished, this, &QCFServer::on_workerTerminated);

		l_thread->start();
	}
}

void QCFServer::on_workerTerminated()
{
	QThread *l_sender = (QThread*)sender();

	m_runningTemplates.removeOne(l_sender);

	l_sender->deleteLater();

	//qApp->quit();
}

void QCFServer::start()
{
	m_MaxSimulRunningTemplates = 400;

	if (m_LocalServer.isListening())
	{
		m_LocalServer.close();
	}

	if (m_mainTimer != 0)
	{
		killTimer(m_mainTimer);
	}

#ifdef Q_OS_LINUX
	if (QFile::exists("/tmp/mkfusion"))
	{
		QFile::remove("/tmp/mkfusion");
	}
#endif

	if (m_LocalServer.listen("mkfusion") == false)
	{
		return;
	}

#ifdef Q_OS_LINUX
	::chmod("/tmp/mkfusion", S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR|S_IWGRP|S_IWOTH);
#endif


	m_mainTimer = startTimer(1000);

	QFileInfo fi(getCurrentExecutableFileName());
	QDir fi_dir = fi.absoluteDir();
	fi_dir.cdUp();
	m_MKFusionPath = fi_dir.absolutePath() + "/";
	QLibrary l_TemplateLib;

	QDir l_TemplatesDir(m_MKFusionPath + "templates");
#ifdef Q_OS_WIN
	QStringList l_Templates = l_TemplatesDir.entryList(QStringList() << "*.dll", QDir::Files, QDir::Name);
#elif defined Q_OS_LINUX
	QStringList l_Templates = l_TemplatesDir.entryList(QStringList() << "*.so", QDir::Files, QDir::Name);
#else
#error Windows and Linux OSs are currently supported.
#endif

    for(const QString &l_Template: l_Templates)
	{
		bool l_DeleteTemplate = true;
		l_TemplateLib.setFileName(m_MKFusionPath + "templates/" + l_Template);
		QIsTemplateModified l_TemplateModifyInfo;

		if (l_TemplateLib.load() == true)
		{
			createCFMTemplateDef createCFMTemplate = (createCFMTemplateDef) l_TemplateLib.resolve("createCFMTemplate");
            if (createCFMTemplate)
			{
                QCFTemplate *l_page = createCFMTemplate();
                if (l_page)
                {
                    if(QFile::exists(l_page->m_isModified.m_Filename))
                    {
                        QFileInfo l_FileInfo(l_page->m_isModified.m_Filename);
                        if ((l_FileInfo.size() == l_page->m_isModified.m_Size)&&(l_FileInfo.lastModified().toTime_t() == l_page->m_isModified.m_Modified))
                        {
                            l_DeleteTemplate = false;
                            l_TemplateModifyInfo = l_page->m_isModified;
                        }
                    }

					delete l_page;
                    l_page = NULL;
				}
			}

			l_TemplateLib.unload();
		}

		if (l_DeleteTemplate == true)
		{
			QFile::remove(m_MKFusionPath + "templates/" + l_Template);
		}
		else
		{
			if (m_CompiledTemplates.contains(l_TemplateModifyInfo.m_Filename) == true)
			{
				QFile::remove(m_MKFusionPath + "templates/" + m_CompiledTemplates[l_TemplateModifyInfo.m_Filename].m_CompiledFileName);
			}

			QCFCompiledTemplateItem l_TemplateItem;
			l_TemplateItem.m_CompiledFileName = l_Template;
			l_TemplateItem.m_ModifiedInfo = l_TemplateModifyInfo;
			m_CompiledTemplates.insert(l_TemplateModifyInfo.m_Filename, l_TemplateItem);
		}
	}
}

void QCFServer::stop()
{
	killTimer(m_mainTimer);
	m_LocalServer.close();
}

QSqlDatabase QCFServer::getDBConnection(const QString &datasource)
{
    QSqlDatabase ret;

    ret = QSqlDatabase::addDatabase("QSQLITE", datasource);

    ret.setDatabaseName("test.db");

    return ret;
}

QString QCFServer::compileTemplate(const QString &p_Filename, const QString &p_URI)
{
	if (m_CompiledTemplates.contains(p_Filename))
	{
		QFileInfo l_fi(p_Filename);

		if ((l_fi.size() == m_CompiledTemplates[p_Filename].m_ModifiedInfo.m_Size)&&(l_fi.lastModified().toTime_t() == m_CompiledTemplates[p_Filename].m_ModifiedInfo.m_Modified))
		{
			return "";
		}
		else
		{
			m_CompiledTemplates.remove(p_Filename);
		}
	}

	QFile file(p_Filename);

    if (!file.exists())
    {
        throw QMKFusionTemplateException("File not found: " + p_URI);
    }

	if (!file.open(QIODevice::ReadOnly))
	{
        throw QMKFusionTemplateException("Can\'t open file: " + p_URI);
    }

	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QString l_FileContent = codec->toUnicode(file.readAll());
	file.close();

	// ---- Parse .cfm file. ----
	QCFParser l_parser(CompilerMode);
	QFileInfo fileinfo(p_Filename);
	l_parser.m_FileName = p_Filename;
	l_parser.m_CFMFileSize = fileinfo.size();
	l_parser.m_CFMModifyDateTime = fileinfo.lastModified().toTime_t();
	QCFParserErrorType l_parseError = l_parser.Parse(l_FileContent);
	if (l_parseError != NoError)
	{
		return "Parsing error.";
	}

	l_parseError = l_parser.BuildTagTree();
	if (l_parseError != NoError)
	{
		return "Parsing error(at building tag-tree).";
	}

	// Generate c file, compile it to dll/so, move it to target dir.
#ifdef Q_OS_WIN
	QString l_NewTemplateFile = QFileInfo(p_Filename).baseName() + "_" + QString::number(QDateTime::currentDateTime().toTime_t()) + ".dll";
#elif defined Q_OS_LINUX
	QString l_NewTemplateFile = QFileInfo(p_Filename).baseName() + "_" + QString::number(QDateTime::currentDateTime().toTime_t()) + ".so";
#else
#error Windows and Linux OSs are currently supported.
#endif

	QCFGenerator l_generator;
	QString ret = l_generator.compile(l_parser, m_MKFusionPath + "templates/" + l_NewTemplateFile, m_MKFusionPath);

	if (ret.isEmpty())
	{
		QCFCompiledTemplateItem item;
		item.m_CompiledFileName = l_NewTemplateFile;
		item.m_ModifiedInfo.m_Filename = p_Filename;
		item.m_ModifiedInfo.m_Size = fileinfo.size();
		item.m_ModifiedInfo.m_Modified = fileinfo.lastModified().toTime_t();
		m_CompiledTemplates.insert(p_Filename, item);
	}

	return ret;
}
