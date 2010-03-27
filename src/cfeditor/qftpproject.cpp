#include "qftpproject.h"

QFTPProject::QFTPProject(QHash<QString, QString> /*p_Args*/)
{
}

char QFTPProject::getDirSeparator()
{
	return '/';
}

QByteArray QFTPProject::ReadFile(QString /*p_File*/)
{
	return "";
}

void QFTPProject::WriteFile(QString /*p_File*/, QByteArray /*p_FileContent*/)
{
}

void QFTPProject::DeleteFile(QString /*p_File*/)
{
}

void QFTPProject::RenameFile(QString /*p_FromFilename*/, QString /*p_ToFilename*/)
{
}

QList<QProjectFile> QFTPProject::getFolderItems(QString /*p_Folder*/)
{
	QList<QProjectFile> ret;

	qSort(ret);

	return ret;
}

void QFTPProject::CreateDir(QString /*p_Dirname*/)
{
}

void QFTPProject::DeleteDir(QString /*p_Dirname*/, bool /*p_Recursive*/)
{
}

void QFTPProject::RenameDir(QString /*p_FromDir*/, QString /*p_ToDir*/)
{
}
