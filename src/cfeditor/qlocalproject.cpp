#include "qlocalproject.h"
#include <QByteArray>
#include <QFile>
#include <QDir>

QLocalProject::QLocalProject(QHash<QString, QString> p_Args)
{
	m_Url = p_Args["Url"];
	m_Path = p_Args["Path"];
}

char QLocalProject::getDirSeparator()
{
	return '/';
}

QByteArray QLocalProject::ReadFile(QString p_File)
{
	QFile file(m_Path + p_File);
	
	if (!file.open(QIODevice::ReadOnly))
		return "";
	
	QByteArray ba = file.readAll();

	file.close();

	return ba;
}

void QLocalProject::WriteFile(QString p_File, QByteArray p_Content)
{
	QFile l_file(m_Path + p_File);
	
	if (!l_file.open(QIODevice::WriteOnly))
		return;
	
	l_file.write(p_Content);
	l_file.resize(p_Content.size());
	l_file.close();
}

void QLocalProject::DeleteFile(QString p_File)
{
	QFile::remove(m_Path + p_File);
}

void QLocalProject::RenameFile(QString p_FromFile, QString p_ToFile)
{
	QFile::rename(m_Path + p_FromFile, m_Path + p_ToFile);
}

QList<QProjectFile> QLocalProject::getFolderItems(QString p_Folder)
{
	QList<QProjectFile> ret;

	QDir dir(m_Path + p_Folder);
	dir.setFilter(QDir::Dirs | QDir::Files | QDir::Hidden | QDir::NoSymLinks);

	QFileInfoList list = dir.entryInfoList();

	foreach(QFileInfo item, list)
	{
		if ((item.fileName() == ".")||(item.fileName() == ".."))
			continue;

		QProjectFile file;

		file.m_FileName = item.fileName();
		file.m_IsFolder = item.isDir();
		file.m_FileSize = item.size();

		ret.append(file);
	}
	
	qSort(ret);

	return ret;
}

void QLocalProject::CreateDir(QString p_Dir)
{
	QDir l_dir;
	l_dir.mkdir(m_Path + p_Dir);
}

void QLocalProject::DeleteDir(QString p_Dir, bool p_Recursive)
{
	QDir l_dir;

	if (p_Recursive)
	{
		// TODO: Implement recursive.
	}

	l_dir.rmdir(m_Path + p_Dir);
}

void QLocalProject::RenameDir(QString p_OldDir, QString p_NewDir)
{
	QDir l_dir;
	l_dir.rename(m_Path + p_OldDir, m_Path + p_NewDir);
}
