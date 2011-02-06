#include "qftpproject.h"
#include <QThread>

QFTPProject::QFTPProject(const QHash<QString, QString>& p_Args)
{
	m_Url = p_Args["Url"];
	m_Path = p_Args["Path"];

	if (!m_Path.endsWith(getDirSeparator()))
	{
		m_Path += getDirSeparator();
	}

	QString l_Host = p_Args["Host"];
	quint16 l_Port = p_Args["Port"].toUShort();
	QString l_Username = p_Args["Username"];
	QString l_Password = p_Args["Password"];

	if (l_Port == 0)
	{
		l_Port = 21;
	}

	m_FTP.connectToHost(l_Host, l_Port);

	if ((l_Username.isEmpty())&&(l_Password.isEmpty()))
	{
		m_FTP.login();
	}
	else
	{
		m_FTP.login(l_Username, l_Password);
	}

	while(m_FTP.currentCommand() != QFtp::None)
	{
		QThread::currentThread()->wait(1);
	}

	if (m_FTP.error() != QFtp::NoError)
	{
		//m_
	}

}

char QFTPProject::getDirSeparator()
{
	return '/';
}

QByteArray QFTPProject::ReadFile(const QString& p_File)
{
	QByteArray ret;

	m_FTP.get(p_File);

	while(m_FTP.currentCommand() != QFtp::None)
	{
		QThread::currentThread()->wait(1);

		ret += m_FTP.readAll();
	}

	return ret;
}

void QFTPProject::WriteFile(const QString& p_File, const QByteArray& p_FileContent)
{
	m_FTP.put(p_FileContent, p_File);

	while(m_FTP.currentCommand() != QFtp::None)
	{
		QThread::currentThread()->wait(1);
	}
}

void QFTPProject::DeleteFile(const QString& p_File)
{
	m_FTP.remove(p_File);

	while(m_FTP.currentCommand() != QFtp::None)
	{
		QThread::currentThread()->wait(1);
	}
}

void QFTPProject::RenameFile(const QString& p_FromFilename, const QString& p_ToFilename)
{
	m_FTP.rename(p_FromFilename, p_ToFilename);

	while(m_FTP.currentCommand() != QFtp::None)
	{
		QThread::currentThread()->wait(1);
	}
}

QList<QProjectFile> QFTPProject::getFolderItems(const QString& p_Folder)
{
	QList<QProjectFile> ret;

	m_FTP.list(p_Folder);

	while(m_FTP.currentCommand() != QFtp::None)
	{
		QThread::currentThread()->wait(1);
	}

	// TODO: Missing code

	qSort(ret);

	return ret;
}

void QFTPProject::CreateDir(const QString& p_Dirname)
{
	m_FTP.mkdir(p_Dirname);

	while(m_FTP.currentCommand() != QFtp::None)
	{
		QThread::currentThread()->wait(1);
	}
}

void QFTPProject::DeleteDir(const QString& p_Dirname, bool p_Recursive)
{
	m_FTP.rmdir(p_Dirname); // TODO: Recursive

	while(m_FTP.currentCommand() != QFtp::None)
	{
		QThread::currentThread()->wait(1);
	}
}

void QFTPProject::RenameDir(const QString& p_FromDir, const QString& p_ToDir)
{
	m_FTP.rename(p_FromDir, p_ToDir);

	while(m_FTP.currentCommand() != QFtp::None)
	{
		QThread::currentThread()->wait(1);
	}
}
