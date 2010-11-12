#include "qmkfusionexception.h"
#include "qcfgenerator.h"
#include "qcftemplate.h"
#include "qcfserver.h"
#include "qcfparser.h"

//#include <QCoreApplication>
#include <QTextCodec>
#include <QLocalSocket>
#include <QFileInfo>
#include <QLibrary>
#include <QDir>

#ifdef Q_WS_WIN
#include <windows.h>
#include <Tlhelp32.h>
#include <Psapi.h>
#elif defined Q_WS_X11
#include<sys/stat.h>
#else
#error Windows and Linux OSs are currently supported.
#endif

QString getCurrentModuleFileName(void* p_Pointer) // TODO: This function is for windows only. Please implement Linux version.
{
		QString ret;
#ifdef Q_WS_WIN
		tagMODULEENTRY32W l_moduleEntry;
		l_moduleEntry.dwSize = sizeof(tagMODULEENTRY32W);
		bool l_MoreModules;

		if (p_Pointer == NULL)
		{
				p_Pointer = (void*)&getCurrentModuleFileName;
		}

		HANDLE l_handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
		if (l_handle != INVALID_HANDLE_VALUE)
		{
				for(l_MoreModules = Module32FirstW(l_handle, &l_moduleEntry); l_MoreModules == true; l_MoreModules = Module32NextW(l_handle, &l_moduleEntry))
				{
						if ((((quint32)p_Pointer) >= (((quint32)l_moduleEntry.modBaseAddr)))&&(((quint32)p_Pointer) < (((quint32)l_moduleEntry.modBaseAddr + l_moduleEntry.modBaseSize))))
						{
								ret = QString::fromWCharArray(l_moduleEntry.szExePath);
								break;
						}
				}

				CloseHandle(l_handle);
		}
#elif defined Q_WS_X11
		Q_UNUSED(p_Pointer);

		ret = "/opt/mkfusion/bin/";
#else
#error Windows and Linux OSs are currently supported.
#endif

	return ret;
}

QCFServer::QCFServer()
{
	m_mainTimer = 0;

	connect(&m_LocalServer, SIGNAL(newConnection()), SLOT(on_newConnection()));
}

void QCFServer::timerEvent(QTimerEvent *event)
{
	return;
}

void QCFServer::on_newConnection()
{
	for (; ; )
	{
		QLocalSocket* l_LocalSocket = m_LocalServer.nextPendingConnection();

		if (l_LocalSocket == NULL)
		{
			break;
		}

		m_runningTemplatesLock.lockForWrite();

		if (m_runningTemplates.count() >= m_MaxSimulRunningTemplates)
		{
			m_runningTemplatesLock.unlock();

			l_LocalSocket->write("\4\0\0\0", 4);
			l_LocalSocket->write("Maximum running templates.");
			l_LocalSocket->waitForBytesWritten(30000);

			l_LocalSocket->disconnectFromServer();
			l_LocalSocket->waitForDisconnected(30000);
			l_LocalSocket->deleteLater();
			return;
		}

		if (l_LocalSocket->waitForConnected(1000) == false)
		{
			m_runningTemplatesLock.unlock();
			return;
		}

		QThread* l_thread = new QThread(this);

		m_runningTemplates.append(l_thread);

		QCFRunningTemplate* l_runningTemplate = new QCFRunningTemplate();

		l_runningTemplate->m_CFServer = this;
		l_runningTemplate->moveToThread(l_thread);
		l_runningTemplate->m_Socket = l_LocalSocket;
		l_LocalSocket->setParent(NULL);
		l_LocalSocket->moveToThread(l_thread);

		l_runningTemplate->connect(l_thread, SIGNAL(started()), SLOT(worker()));
		l_thread->connect(l_runningTemplate, SIGNAL(finished()), SLOT(quit()));
		connect(l_thread, SIGNAL(finished()), SLOT(on_workerTerminated()));

		l_thread->start();

		m_runningTemplatesLock.unlock();
	}
}

void QCFServer::on_workerTerminated()
{
	QThread* l_sender = (QThread*)sender();

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

#ifdef Q_WS_X11
	if (QFile::exists("/tmp/mkfusion"))
	{
		QFile::remove("/tmp/mkfusion");
	}
#endif

	if (m_LocalServer.listen("mkfusion") == false)
	{
		return;
	}

#ifdef Q_WS_X11
	::chmod("/tmp/mkfusion", S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR|S_IWGRP|S_IWOTH);
#endif


	m_mainTimer = startTimer(1000);

	QFileInfo fi(getCurrentModuleFileName((void*)&getCurrentModuleFileName));
	QDir fi_dir = fi.absoluteDir();
	fi_dir.cdUp();
	m_MKFusionPath = fi_dir.absolutePath() + "/";
	QLibrary l_TemplateLib;

	QDir l_TemplatesDir(m_MKFusionPath + "templates");
#ifdef Q_WS_WIN
	QStringList l_Templates = l_TemplatesDir.entryList(QStringList() << "*.dll", QDir::Files, QDir::Name);
#elif defined Q_WS_X11
	QStringList l_Templates = l_TemplatesDir.entryList(QStringList() << "*.so", QDir::Files, QDir::Name);
#else
#error Windows and Linux OSs are currently supported.
#endif

	foreach(QString l_Template, l_Templates)
	{
		bool l_DeleteTemplate = true;
		l_TemplateLib.setFileName(m_MKFusionPath + "templates/" + l_Template);
		QIsTemplateModified l_TemplateModifyInfo;

		if (l_TemplateLib.load() == true)
		{
			createCFMTemplateDef createCFMTemplate = (createCFMTemplateDef) l_TemplateLib.resolve("createCFMTemplate");
			if (createCFMTemplate != NULL)
			{
				QCFTemplate* l_page = createCFMTemplate();
				if ((l_page != NULL)&&(QFile::exists(l_page->m_isModified.m_Filename) == true))
				{
					QFileInfo l_FileInfo(l_page->m_isModified.m_Filename);
					if ((l_FileInfo.size() == l_page->m_isModified.m_Size)&&(l_FileInfo.lastModified().toTime_t() == l_page->m_isModified.m_Modified))
					{
						l_DeleteTemplate = false;
						l_TemplateModifyInfo = l_page->m_isModified;
					}
				}

				if (l_page != NULL)
				{
					delete l_page;
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
	if (!file.open(QIODevice::ReadOnly))
	{
		throw QMKFusionTemplateException("File not found: " + p_URI);
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
#ifdef Q_WS_WIN
	QString l_NewTemplateFile = QFileInfo(p_Filename).baseName() + "_" + QString::number(QDateTime::currentDateTime().toTime_t()) + ".dll";
#elif defined Q_WS_X11
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
