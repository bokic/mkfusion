#include "qcfserver.h"
#include "qmkfusionexception.h"
#include "qcfgenerator.h"
#include "qcfrunningtemplate.h"
#include "qcftemplate.h"
#include "qcfparser.h"

#include <QProcessEnvironment>
#include <QCoreApplication>
#include <QTextCodec>
#include <QLocalSocket>
#include <QWriteLocker>
#include <QSettings>
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


QCFServer::QCFServer()
    : m_mainTimer(0)
{
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

    while(m_LocalServer.hasPendingConnections())
    {
        QLocalSocket *l_LocalSocket = m_LocalServer.nextPendingConnection();

        if (l_LocalSocket == nullptr)
        {
            qDebug() << "Got nullptr local connection.";

            break;
        }

        if (m_RunnuingTemplatesByThreadId.count() >= m_MaxSimulRunningTemplates)
        {
            l_LocalSocket->write("\x04\x00\x00\x00", 4);
            l_LocalSocket->write("Maximum running templates.");
            l_LocalSocket->waitForBytesWritten();

            l_LocalSocket->disconnectFromServer();
            l_LocalSocket->waitForDisconnected();
            l_LocalSocket->deleteLater();

            return;
        }

        if (l_LocalSocket->waitForConnected(1000) == false)
        {
            qDebug() << "failed to connect with local socket.";

            return;
        }

        QThread *l_thread = new QThread(this);

        QCFRunningTemplate *l_runningTemplate = new QCFRunningTemplate();

        l_runningTemplate->m_CFServer = this;
        l_runningTemplate->moveToThread(l_thread);
        l_runningTemplate->m_Socket = l_LocalSocket;
        l_LocalSocket->setParent(nullptr);
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

    l_sender->deleteLater();
    l_sender = nullptr;

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

    m_LocalServer.setSocketOptions(QLocalServer::WorldAccessOption);

    if (m_LocalServer.listen("mkfusion") == false)
    {
        return;
    }

#ifdef Q_OS_LINUX
    ::chmod("/tmp/mkfusion", S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR|S_IWGRP|S_IWOTH);
#endif

    QDir fi_dir(QCoreApplication::applicationDirPath());
    fi_dir.cdUp();
    m_MKFusionPath = fi_dir.absolutePath() + "/";

#ifdef Q_OS_WIN
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    if (env.contains("APPDATA"))
    {
        m_TemplatesPath = env.value("APPDATA") + "\\MKFusion\\templates\\";
    }
    else
    {
        m_TemplatesPath = QDir::toNativeSeparators(QDir::tempPath()) + "\\";
    }
#elif defined Q_OS_LINUX
    m_TemplatesPath = "/var/cache/mkfusion/templates/";

#else
#error Windows and Linux OSs are currently supported.
#endif

    if (!QDir(m_TemplatesPath).exists())
    {
        QDir().mkpath(m_TemplatesPath);
    }

    readConfig();

    QLibrary l_TemplateLib;

    QDir l_TemplatesDir(m_TemplatesPath);
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
        l_TemplateLib.setFileName(m_TemplatesPath + l_Template);
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
                    l_page = nullptr;
                }
            }

            l_TemplateLib.unload();
        }

        if (l_DeleteTemplate == true)
        {
            QFile::remove(m_TemplatesPath + l_Template);
        }
        else
        {
            if (m_CompiledTemplates.contains(l_TemplateModifyInfo.m_Filename) == true)
            {
                QFile::remove(m_TemplatesPath + m_CompiledTemplates[l_TemplateModifyInfo.m_Filename].m_CompiledFileName);
            }

            QCFCompiledTemplateItem l_TemplateItem;
            l_TemplateItem.m_CompiledFileName = l_Template;
            l_TemplateItem.m_ModifiedInfo = l_TemplateModifyInfo;
            m_CompiledTemplates.insert(l_TemplateModifyInfo.m_Filename, l_TemplateItem);
        }
    }

    m_mainTimer = startTimer(1000);
}

void QCFServer::stop()
{
    killTimer(m_mainTimer);
    m_LocalServer.close();
}

void QCFServer::readConfig()
{
#ifdef Q_OS_WIN
    QSettings iniFile(QCoreApplication::applicationDirPath() + QDir::separator() + "mkfusion.ini", QSettings::IniFormat);
#elif defined Q_OS_LINUX
    QSettings iniFile("/etc/mkfusion.conf", QSettings::IniFormat);
#else
#error Windows and Linux OSs are currently supported.
#endif

    iniFile.beginGroup("Setup");
    QString path = iniFile.value("CustomTagsDir").toString();
    iniFile.endGroup();

    if (path.isEmpty())
    {
#ifdef Q_OS_WIN
        path = QDir(m_MKFusionPath + QDir::separator() + "../CustomTags").absolutePath();
#elif defined Q_OS_LINUX
        path = "/var/mkfusion/CustomTags";
#else
#error Windows and Linux OSs are currently supported.
#endif

    }

    m_CustomTagsPath = path;

    iniFile.beginGroup("Setup");
    m_LeaveGeneratedFilesPath = iniFile.value("LeaveGeneratedFilesPath").toString();
    iniFile.endGroup();

    iniFile.beginGroup("Database");
    for(const QString &group : iniFile.childKeys())
    {
        int sep = group.lastIndexOf('_');

        if (sep < 1)
        {
            qDebug() << "Invalid database connection.";

            continue;
        }

        const QString &connectionName = group.left(sep);
        const QString &connectionDriver = group.right(group.length() - sep - 1);
        const QString &connectionString = iniFile.value(group).toString();

        if (connectionDriver == "QSQLITE")
        {
            QSqlDatabase db = QSqlDatabase::addDatabase(connectionDriver, connectionName.toUpper());

            db.setDatabaseName(connectionString);
        }
        else if (connectionDriver == "QODBC")
        {
            QSqlDatabase db = QSqlDatabase::addDatabase(connectionDriver, connectionName.toUpper());

            db.setDatabaseName(connectionString);
        }
        else if (connectionDriver == "QMYSQL")
        {
            QSqlDatabase db = QSqlDatabase::addDatabase(connectionDriver, connectionName.toUpper());

            for(const QString item : connectionString.split(';'))
            {
                QStringList key_value = item.split(':');

                if (key_value.count() != 2)
                {
                    continue;
                }

                QString key = key_value.first();
                QString value = QByteArray::fromBase64(key_value.last().toLatin1());

                if (key.compare("hostname", Qt::CaseInsensitive) == 0)
                {
                    db.setHostName(value);
                }
                else if (key.compare("databasename", Qt::CaseInsensitive) == 0)
                {
                    db.setDatabaseName(value);
                }
                else if (key.compare("username", Qt::CaseInsensitive) == 0)
                {
                    db.setUserName(value);
                }
                else if (key.compare("password", Qt::CaseInsensitive) == 0)
                {
                    db.setPassword(value);
                }
                else if (key.compare("port", Qt::CaseInsensitive) == 0)
                {
                    db.setPort(value.toInt());
                }
            }
        }
        else
        {
            qDebug() << "Unsupported database connection(" << connectionDriver << ")";
        }
    }
    iniFile.endGroup();
}

QSqlDatabase *QCFServer::getDBConnection(const QString &datasource)
{
    if (!m_DatabasePool.contains(datasource))
    {
        m_DatabasePool[datasource] = QSqlDatabase::database(datasource.toUpper());
    }

    return &(m_DatabasePool[datasource]);
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
        return "Parsing error.\nError: " + l_parser.getError();
    }

    l_parseError = l_parser.prioritizeOperators();
    if (l_parseError != NoError)
    {
        return "Parsing error.\nError: " + l_parser.getError();
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
    QString l_CopyGeneratedFilesToDir;

    if (p_Filename.indexOf(m_LeaveGeneratedFilesPath) == 0)
    {
        l_CopyGeneratedFilesToDir = QFileInfo(p_Filename).absolutePath();
    }

    QString ret = l_generator.compile(l_parser, m_TemplatesPath + l_NewTemplateFile, m_MKFusionPath, l_CopyGeneratedFilesToDir);

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

QCFRunningTemplate *QCFServer::getRunningTemplateByThreadId(Qt::HANDLE threadId)
{
    if (m_RunnuingTemplatesByThreadId.contains(threadId))
    {
        return m_RunnuingTemplatesByThreadId[threadId];
    }

    return nullptr;
}

void QCFServer::createSessonStrings(QString &cfid, QString &cftoken)
{
    static int global_cfid = 1000;

    global_cfid++;

    cfid = QString::number(global_cfid);
    cftoken.clear();

    for(int c = 0; c < 24; c++)
    {
        QString byte = QString::number(rand() % 256, 16);
        while(byte.length() < 2)
        {
            byte.prepend('0');
        }

        if (c >= 8)
        {
            byte = byte.toUpper();
        }

        if ((c == 8)||(c == 12)||(c == 14)||(c == 16))
        {
            cftoken.append('-');
        }

        cftoken.append(byte);
    }
}
