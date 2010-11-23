#include "qsftpproject.h"


QSFTPProject::QSFTPProject(QHash<QString, QString> p_Args)
{
	int err;

	m_Url = p_Args["Url"];
	m_Path = p_Args["Path"];

	m_SSHSession = ssh_new();
	ssh_options_set(m_SSHSession, SSH_OPTIONS_HOST, p_Args["Host"].toLatin1());

	if (p_Args["Port"].toInt() != 0)
	{
		ssh_options_set(m_SSHSession, SSH_OPTIONS_PORT_STR, p_Args["Port"].toLatin1());
	}

	err = ssh_connect(m_SSHSession);
	if (err != 0)
	{
		return;
	}

	err = ssh_userauth_password(m_SSHSession, p_Args["Username"].toLatin1(), p_Args["Password"].toLatin1());
	if (err != 0)
	{
		return;
	}

	m_SFTPSession = sftp_new(m_SSHSession);
	if (m_SFTPSession == 0)
	{
		return;
	}

	err = sftp_init(m_SFTPSession);
	if (err != 0)
	{
		return;
	}
}

QSFTPProject::~QSFTPProject()
{

}

char QSFTPProject::getDirSeparator()
{
	return '/';
}

QByteArray QSFTPProject::ReadFile(QString p_File)
{
	QByteArray ret;

	if (m_SFTPSession == NULL)
	{
		return "";
	}


	QString l_File = m_Path + p_File;

	sftp_file l_file = sftp_open(m_SFTPSession, l_File.toLatin1(), O_RDONLY, 0);
	if (l_file == NULL)
	{
		return NULL;
	}

	sftp_attributes attr = sftp_fstat(l_file);
	if (attr == NULL)
	{
		sftp_close(l_file);
		return NULL;
	}

	ret.resize(attr->size);

	ssize_t readed = sftp_read(l_file, ret.data(), attr->size);
	if ((uint64_t)readed != attr->size)
	{
		ret.clear();
	}

	sftp_close(l_file);

	return ret;
}

void QSFTPProject::WriteFile(QString p_File, QByteArray p_FileContent)
{
	if (m_SFTPSession == NULL)
	{
		return;
	}

	QString l_File = m_Path + p_File;

	sftp_file l_file = sftp_open(m_SFTPSession, l_File.toLatin1(), O_WRONLY | O_TRUNC, 0);
	if (l_file == NULL)
	{
		return;
	}

	sftp_write(l_file, p_FileContent.data(), p_FileContent.count());

	sftp_close(l_file);
}

void QSFTPProject::DeleteFile(QString p_File)
{
    Q_UNUSED(p_File);
}

void QSFTPProject::RenameFile(QString, QString)
{
}

QList<QProjectFile> QSFTPProject::getFolderItems(QString p_Folder)
{
	QList<QProjectFile> ret;

	if (m_SFTPSession == NULL)
	{
		return ret;
	}

	QString l_Dir = m_Path + p_Folder;

	sftp_dir dir = sftp_opendir(m_SFTPSession, l_Dir.toLatin1());
	if (dir != NULL)
	{
		sftp_attributes file;

		while((file = sftp_readdir(m_SFTPSession, dir)))
		{
			QProjectFile l_Item;

			if ((file->type & 2) == 2)
			{ // 2 == dir
				if((!strcmp(file->name, "."))||(!strcmp(file->name, "..")))
					continue;
				l_Item.m_FileSize = 0;
				l_Item.m_IsFolder = true;
			}
			else
			{
				l_Item.m_FileSize = file->size;
				l_Item.m_IsFolder = false;
			}

			l_Item.m_FileName = file->name;

			ret.append(l_Item);
		}

		sftp_closedir(dir);
	}

	qSort(ret);

	return ret;
}

void QSFTPProject::CreateDir(QString)
{
}

void QSFTPProject::DeleteDir(QString, bool)
{
}

void QSFTPProject::RenameDir(QString, QString)
{
}
