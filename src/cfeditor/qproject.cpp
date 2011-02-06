#include "qproject.h"
#include "qlocalproject.h"
#include "qrdsproject.h"
#include "qftpproject.h"
#include "qsftpproject.h"
#include <QStringList>
#include <QFile>

QProject::QProject()
{
}

QProject* QProject::LoadProjectFromFile(const QString& p_File)
{
	QFile file(p_File);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return NULL;

	QProject *ret = LoadProjectFromText(file.readAll());
	ret->m_ProjectFileSaved = true;
	ret->m_ProjectFile = p_File;

	return ret;
}

QProject* QProject::LoadProjectFromText(const QString& p_Text)
{
	QHash<QString, QString> hashList;
	QStringList strList = p_Text.split('\n').at(0).split(";");

	foreach(QString item, strList)
	{
		if (item.indexOf('=') >= 0)
		{
			QString key = item.left(item.indexOf('='));
			QString value = item.right(item.length() - item.indexOf('=') - 1);

			hashList.insert(key, value);
		}
	}

	if (hashList["Type"] == "local")
	{
		QLocalProject *ret = new QLocalProject(hashList);

		ret->m_ProjectFileSaved = false;

		return ret;
	}
	else if (hashList["Type"] == "rds")
	{
		QRDSProject *ret = new QRDSProject(hashList);

		ret->m_ProjectFileSaved = false;

		return ret;
	}
	else if (hashList["Type"] == "ftp")
	{
		QFTPProject *ret = new QFTPProject(hashList);

		ret->m_ProjectFileSaved = false;

		return ret;
	}
	else if (hashList["Type"] == "sftp")
	{
		QSFTPProject *ret = new QSFTPProject(hashList);

		ret->m_ProjectFileSaved = false;

		return ret;
	}
	else
		return NULL;
}

const QString& QProject::getUrl()
{
	return m_Url;
}
