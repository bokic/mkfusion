#include "qftpproject.h"
#include <QThread>

QFTPProject::QFTPProject(const QHash<QString, QString> &p_Args)
{
    m_Type = QProject::FTPProject;
    m_Url = p_Args["Url"];
    m_Path = p_Args["Path"];
    m_HostName = p_Args["Host"];
    m_Port = p_Args["Port"].toUShort();
    m_Username = p_Args["Username"];
    m_Password = p_Args["Password"];

    if (!m_Path.endsWith(getDirSeparator()))
    {
        m_Path += getDirSeparator();
    }


    if (m_Port == 0)
    {
        m_Port = 21;
    }

    /*m_FTP.connectToHost(m_HostName, m_Port);

    if ((m_Username.isEmpty())&&(m_Password.isEmpty()))
    {
    	m_FTP.login();
    }
    else
    {
        m_FTP.login(m_Username, m_Password);
    }

    while(m_FTP.currentCommand() != QFtp::None)
    {
    	QThread::currentThread()->wait(1);
    }

    if (m_FTP.error() != QFtp::NoError)
    {
    	//m_
    }*/

}

char QFTPProject::getDirSeparator()
{
    return '/';
}

QByteArray QFTPProject::ReadFile(const QString &p_File)
{
    Q_UNUSED(p_File);

    QByteArray ret;

    /*m_FTP.get(p_File);

    while(m_FTP.currentCommand() != QFtp::None)
    {
    	QThread::currentThread()->wait(1);

    	ret += m_FTP.readAll();
    }*/

    return ret;
}

void QFTPProject::WriteFile(const QString &p_File, const QByteArray &p_FileContent)
{
    Q_UNUSED(p_File);
    Q_UNUSED(p_FileContent);

    /*m_FTP.put(p_FileContent, p_File);

    while(m_FTP.currentCommand() != QFtp::None)
    {
    	QThread::currentThread()->wait(1);
    }*/
}

void QFTPProject::DeleteFile(const QString &p_File)
{
    Q_UNUSED(p_File);

    /*m_FTP.remove(p_File);

    while(m_FTP.currentCommand() != QFtp::None)
    {
    	QThread::currentThread()->wait(1);
    }*/
}

void QFTPProject::RenameFile(const QString &p_FromFilename, const QString &p_ToFilename)
{
    Q_UNUSED(p_FromFilename);
    Q_UNUSED(p_ToFilename);

    /*m_FTP.rename(p_FromFilename, p_ToFilename);

    while(m_FTP.currentCommand() != QFtp::None)
    {
    	QThread::currentThread()->wait(1);
    }*/
}

QList<QProjectFile> QFTPProject::getFolderItems(const QString &p_Folder)
{
    Q_UNUSED(p_Folder);

    QList<QProjectFile> ret;

    /*m_FTP.list(p_Folder);

    while(m_FTP.currentCommand() != QFtp::None)
    {
    	QThread::currentThread()->wait(1);
    }

    // TODO: Missing code

    std::sort(ret.begin(), ret.end());*/

    return ret;
}

void QFTPProject::CreateDir(const QString &p_Dirname)
{
    Q_UNUSED(p_Dirname);

    /*m_FTP.mkdir(p_Dirname);

    while(m_FTP.currentCommand() != QFtp::None)
    {
    	QThread::currentThread()->wait(1);
    }*/
}

void QFTPProject::DeleteDir(const QString &p_Dirname, bool p_Recursive)
{
    Q_UNUSED(p_Dirname);
    Q_UNUSED(p_Recursive); // TODO: Recursive

    /*m_FTP.rmdir(p_Dirname);

    while(m_FTP.currentCommand() != QFtp::None)
    {
    	QThread::currentThread()->wait(1);
    }*/
}

void QFTPProject::RenameDir(const QString &p_FromDir, const QString &p_ToDir)
{
    Q_UNUSED(p_FromDir);
    Q_UNUSED(p_ToDir);

    /*m_FTP.rename(p_FromDir, p_ToDir);

    while(m_FTP.currentCommand() != QFtp::None)
    {
    	QThread::currentThread()->wait(1);
    }*/
}

QString QFTPProject::getHostName()
{
    return m_HostName;
}

quint16 QFTPProject::getPort()
{
    return m_Port;
}

QString QFTPProject::getUsername()
{
    return m_Username;
}

QString QFTPProject::getPassword()
{
    return m_Password;
}
