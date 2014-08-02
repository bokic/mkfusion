#include "qcfserver.h"
#include "qcflog.h"

#include <QProcess>
#include <QString>
#include <QFile>
#include <QDir>

#ifdef Q_OS_WIN
//#include <windows.h>
//#include <Tlhelp32.h>
//#include <Psapi.h>
#elif defined Q_OS_LINUX
#include <sys/stat.h>
#include <unistd.h>
#else
#error Windows and Linux OSs are currently supported.
#endif


QCFServer * QCFServer::m_instance = nullptr;

QCFServer::QCFServer()
    : m_Scheduler(this)
{
    m_instance = this;

    m_Settings.loadFromFile();

#ifdef Q_OS_LINUX
    QProcess process;
#endif

#ifdef Q_OS_WIN
    m_osName = QStringLiteral("Windows");
#elif defined Q_OS_LINUX
    process.start("lsb_release", QStringList() << "-d");

    process.waitForFinished();

    m_osName = QString::fromUtf8(process.readAllStandardOutput());

    if(m_osName.indexOf(":") > -1)
    {
        m_osName = m_osName.right(m_osName.length() - m_osName.lastIndexOf(":") - 1).trimmed();
    }
#else
    m_osName = QStringLiteral("Other");
#endif

#ifdef Q_OS_WIN
    m_osVersion = QStringLiteral("unknown");
#elif defined Q_OS_LINUX
    process.start("lsb_release", QStringList() << "-c");

    process.waitForFinished();

    m_osVersion = QString::fromUtf8(process.readAllStandardOutput());

    if(m_osVersion.indexOf(":") > -1)
    {
        m_osVersion = m_osVersion.right(m_osVersion.length() - m_osVersion.lastIndexOf(":") - 1).trimmed();
    }
#else
    m_osVersion = QStringLiteral("unknown");
#endif
}

QCFServer::~QCFServer()
{
    m_instance = nullptr;
}

void QCFServer::start()
{
    QCFLOG(QCFLOG_DAEMON, QCFLOG_INFO, "MKFusion daemon is starting.");

    m_Templates.init();

    QFileInfo fi(getProcessExecutableFileName());
    QDir fi_dir = fi.absoluteDir();
    fi_dir.cdUp();
    m_MKFusionPath = fi_dir.absolutePath() + "/";

    QObject::connect(&m_LocalServer, &QLocalServer::newConnection, &m_Workers, &QCFWorkersManager::on_newConnection);

    if (m_LocalServer.isListening())
    {
        QCFLOG(QCFLOG_DAEMON, QCFLOG_WARNING, "Hmm strange, m_LocalServer was already listening.");
        m_LocalServer.close();
    }

#ifdef Q_OS_LINUX
    if (QFile::exists("/tmp/mkfusion"))
    {
        QCFLOG(QCFLOG_DAEMON, QCFLOG_WARNING, "File /tmp/mkfusion was found(ungraceful daemon shutdown). I will try to delete it.");
        if (!QFile::remove("/tmp/mkfusion"))
        {
            QCFLOG(QCFLOG_DAEMON, QCFLOG_ERROR, "File /tmp/mkfusion can't be deleted. Ask your admin to delete it.");
        }
    }
#endif

    if (m_LocalServer.listen("mkfusion") == false)
    {
        QCFLOG(QCFLOG_DAEMON, QCFLOG_CRITICAL, "MKFusion failed to listen for connections(another instance is running maybe?).");

        return;
    }

#ifdef Q_OS_LINUX
    ::chmod("/tmp/mkfusion", S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR|S_IWGRP|S_IWOTH);
#endif

    m_Scheduler.start(QThread::LowPriority);


    QCFLOG(QCFLOG_DAEMON, QCFLOG_INFO, "MKFusion daemon has started.");
}

void QCFServer::stop()
{
    QCFLOG(QCFLOG_DAEMON, QCFLOG_INFO, "MKFusion daemon is stoping.");

    m_LocalServer.close();

    QCFLOG(QCFLOG_DAEMON, QCFLOG_INFO, "Stoping scheduler.");
    m_Scheduler.exit();
    m_Scheduler.wait();
    QCFLOG(QCFLOG_DAEMON, QCFLOG_INFO, "Scheduler stoped.");

    m_Workers.waitForAllWorkersToFinish();

    QCFLOG(QCFLOG_DAEMON, QCFLOG_INFO, "MKFusion daemon has stoped.");
}

QString QCFServer::MKFusionPath() const
{
    return m_MKFusionPath;
}

QCFServer * QCFServer::instance()
{
    return m_instance;
}

QString QCFServer::osName() const
{
    return m_osName;
}

QString QCFServer::osVersion() const
{
    return m_osVersion;
}

void QCFServer::on_workerTerminated()
{

    // Delete worker.
    sender()->deleteLater();
}

QString QCFServer::getProcessExecutableFileName()
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
