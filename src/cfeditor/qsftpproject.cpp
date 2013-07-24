#include "qsftpproject.h"
#include <sys/stat.h>


QSFTPProject::QSFTPProject(const QHash<QString, QString> &p_Args)
{
	int err;

    m_Type = QProject::SFTPProject;
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


	m_SSHSession = ssh_new();

    ssh_options_set(m_SSHSession, SSH_OPTIONS_HOST, m_HostName.toLatin1());

    if (m_Port != 0)
	{
        ssh_options_set(m_SSHSession, SSH_OPTIONS_PORT_STR, QString::number(m_Port).toLatin1());
	}

	err = ssh_connect(m_SSHSession);
	if (err != 0)
	{
		return;
	}

    err = ssh_userauth_password(m_SSHSession, m_Username.toLatin1(), m_Password.toLatin1());
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
	sftp_free(m_SFTPSession);
	ssh_free(m_SSHSession);
}

char QSFTPProject::getDirSeparator()
{
	return '/';
}

QByteArray QSFTPProject::ReadFile(const QString &p_File)
{
	QByteArray ret;

	if (m_SFTPSession == NULL)
	{
		return "";
	}

	QString l_File = m_Path + p_File;

	sftp_file l_file = sftp_open(m_SFTPSession, l_File.toUtf8(), O_RDONLY, 0);
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

void QSFTPProject::WriteFile(const QString &p_File, const QByteArray &p_FileContent)
{
	if (m_SFTPSession == NULL)
	{
		return;
	}

	QString l_File = m_Path + p_File;

	sftp_file l_file = sftp_open(m_SFTPSession, l_File.toUtf8(), O_WRONLY | O_TRUNC | O_CREAT, 0x01A4);
	// 0x0001 = ot_exec
	// 0x0002 = ot_writ
	// 0x0004 = ot_read
	// 0x0008 = gr_exec
	// 0x0010 = gr_writ
	// 0x0020 = gr_read
	// 0x0040 = ow_exec
	// 0x0080 = ow_writ
	// 0x0100 = ow_read

	if (l_file == NULL)
	{
		return;
	}

	sftp_write(l_file, p_FileContent.data(), p_FileContent.count());

	sftp_close(l_file);
}

void QSFTPProject::DeleteFile(const QString &p_File)
{
	if (m_SFTPSession == NULL)
	{
		return;
	}

	sftp_unlink(m_SFTPSession, m_Path.toUtf8() + p_File.toUtf8());
}

void QSFTPProject::RenameFile(const QString &p_FromFile, const QString &p_ToFile)
{
	if (m_SFTPSession == NULL)
	{
		return;
	}

	sftp_rename(m_SFTPSession, m_Path.toUtf8() + p_FromFile.toUtf8(), m_Path.toUtf8() + p_ToFile.toUtf8());
}

QList<QProjectFile> QSFTPProject::getFolderItems(const QString &p_Folder)
{
	QList<QProjectFile> ret;

	if (m_SFTPSession == NULL)
	{
		return ret;
	}

	QString l_Dir = m_Path + p_Folder;

	sftp_dir dir = sftp_opendir(m_SFTPSession, l_Dir.toUtf8());
    if (dir)
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

			l_Item.m_FileName = QString::fromUtf8(file->name);

			ret.append(l_Item);
		}

		sftp_closedir(dir);
	}

	qSort(ret);

	return ret;
}

void QSFTPProject::CreateDir(const QString &p_Folder)
{
	if (m_SFTPSession == NULL)
	{
		return;
	}

	sftp_mkdir(m_SFTPSession, m_Path.toUtf8() + p_Folder.toUtf8(), 0x01ED); // 0x01ED = 755
}

void QSFTPProject::DeleteDir(const QString &p_Folder, bool p_Recursive)
{
    Q_UNUSED(p_Recursive); // TODO: Recursive

	if (m_SFTPSession == NULL)
	{
		return;
	}

	sftp_unlink(m_SFTPSession, m_Path.toUtf8() + p_Folder.toUtf8());
}

void QSFTPProject::RenameDir(const QString &p_FromFolder, const QString &p_ToFolder)
{
	if (m_SFTPSession == NULL)
	{
		return;
	}

	sftp_rename(m_SFTPSession, m_Path.toUtf8() + p_FromFolder.toUtf8(), m_Path.toUtf8() + p_ToFolder.toUtf8());
}

const QString &QSFTPProject::getHostName()
{
    return m_HostName;
}

quint16 QSFTPProject::getPort()
{
    return m_Port;
}

const QString &QSFTPProject::getUsername()
{
    return m_Username;
}

const QString &QSFTPProject::getPassword()
{
    return m_Password;
}
