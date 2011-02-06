#include "qrdsproject.h"
#include "qfileioservice.h"

QRDSProject::QRDSProject(const QHash<QString, QString>& p_Args)
{
	m_Url = p_Args["Url"];
	m_Path = p_Args["Path"];
	m_DirSeparator = 0;

	m_Server.setHostName(p_Args["Host"]);
	m_Server.setUserName(p_Args["Username"]);
	m_Server.setPassword(p_Args["Password"].toAscii());
	m_Server.setPort(p_Args["Port"].toInt());

	if (!m_Path.endsWith(getDirSeparator()))
	{
		m_Path += getDirSeparator();
	}
}

char QRDSProject::getDirSeparator()
{
	if (m_DirSeparator == 0)
	{
		QMap<QString, QString> l_map;
		QByteArray l_ba;

		QFileIOService fileIO;
		l_ba = fileIO.ExecuteRDSCommand(m_Server, QFileIOService::FileGetRootDirCommand, l_map);

		QVector<QByteArray> l_elements = fileIO.BreakByteArrayIntoVector(l_ba);

		if(l_elements.size() > 0)
		{
			if (l_elements[0].left(1) == "/")
			{
				m_DirSeparator = '/';
			}
			else
			{
				m_DirSeparator = '\\';
			}
		}
		else
		{
			m_DirSeparator = '/';
		}
	}

	return m_DirSeparator;
}

QByteArray QRDSProject::ReadFile(const QString& file)
{
	QMap<QString, QString> map;
	QByteArray ba;

	QFileIOService fileIO;
	
	map.clear();
	map.insert("NAME", m_Path + file);
	ba = fileIO.ExecuteRDSCommand(m_Server, QFileIOService::FileReadCommand, map);

	QVector<QByteArray> elements = fileIO.BreakByteArrayIntoVector(ba);

	if (elements.size() > 0)
	{
		return elements[0];
	}
	else
	{
		return "";
	}
}

void QRDSProject::WriteFile(const QString& p_File, const QByteArray& p_Content)
{
	QMap<QString, QString> map;
	QByteArray ba;

	QFileIOService fileIO;
	
	map.clear();
	map.insert("NAME", m_Path + p_File);
	map.insert("FILE_CONTENTS", QString::fromUtf8(p_Content, p_Content.size()));
	ba = fileIO.ExecuteRDSCommand(m_Server, QFileIOService::FileWriteCommand, map);

	QVector<QByteArray> elements = fileIO.BreakByteArrayIntoVector(ba);
}

void QRDSProject::DeleteFile(const QString& p_File)
{
	QMap<QString, QString> map;
	QByteArray ba;

	QFileIOService fileIO;
	
	map.clear();
	map.insert("NAME", m_Path + p_File);
	ba = fileIO.ExecuteRDSCommand(m_Server, QFileIOService::FileRemoveFileCommand, map);

	QVector<QByteArray> elements = fileIO.BreakByteArrayIntoVector(ba);
}

void QRDSProject::RenameFile(const QString& p_OldFile, const QString& p_NewFile)
{
	QMap<QString, QString> map;
	QByteArray ba;

	QFileIOService fileIO;

	map.insert("NAME", m_Path + p_OldFile);
	map.insert("NEW_NAME", m_Path + p_NewFile);

	ba = fileIO.ExecuteRDSCommand(m_Server, QFileIOService::FileRenameCommand, map);

	QVector<QByteArray> elements = fileIO.BreakByteArrayIntoVector(ba);
}

QList<QProjectFile> QRDSProject::getFolderItems(const QString& p_Folder)
{
	QList<QProjectFile> ret;

	QFileIOService fileIO;
	QMap<QString, QString> map;
	QByteArray ba;

	map.insert("NAME", m_Path + p_Folder);
	map.insert("MASK", "");

	ba = fileIO.ExecuteRDSCommand(m_Server, QFileIOService::BrowseDirCommand, map);

	QVector<QByteArray> elements = fileIO.BreakByteArrayIntoVector(ba);
	QProjectFile file;

	for(int c = 0; c < elements.size() / 5; c++)
	{
		if (elements[c * 5] == "D:")
		{
			file.m_IsFolder = true;
		}
		else
		{
			file.m_IsFolder = false;
		}

		file.m_FileName = QString::fromUtf8(elements[(c * 5) + 1], elements[(c * 5) + 1].length());
		file.m_FileSize = elements[(c * 5) + 3].toLong();

		ret.append(file);
	}

	qSort(ret);

	return ret;
}

void QRDSProject::CreateDir(const QString& p_NewDir)
{
	QMap<QString, QString> map;
	QByteArray ba;

	QFileIOService fileIO;

	map.insert("NAME", m_Path + p_NewDir);

	ba = fileIO.ExecuteRDSCommand(m_Server, QFileIOService::FileCreateDirCommand, map);

	QVector<QByteArray> elements = fileIO.BreakByteArrayIntoVector(ba);
}

void QRDSProject::DeleteDir(const QString& p_Dir, bool)
{
	QMap<QString, QString> map;
	QByteArray ba;

	QFileIOService fileIO;

	map.insert("NAME", m_Path + p_Dir);

	ba = fileIO.ExecuteRDSCommand(m_Server, QFileIOService::FileRemoveDirectoryCommand, map);

	QVector<QByteArray> elements = fileIO.BreakByteArrayIntoVector(ba);
}

void QRDSProject::RenameDir(const QString& p_OldDir, const QString& p_NewDir)
{
	QMap<QString, QString> map;
	QByteArray ba;

	QFileIOService fileIO;

	map.insert("NAME", m_Path + p_OldDir);
	map.insert("NEW_NAME", m_Path + p_NewDir);

	ba = fileIO.ExecuteRDSCommand(m_Server, QFileIOService::FileRenameCommand, map);

	QVector<QByteArray> elements = fileIO.BreakByteArrayIntoVector(ba);
}
