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

QProject* QProject::LoadProjectFromFile(QString p_File)
{
	QFile file(p_File);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return NULL;

	return LoadProjectFromText(file.readAll());
}

QProject* QProject::LoadProjectFromText(QString p_Text)
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
		return new QLocalProject(hashList);
	}
	else if (hashList["Type"] == "rds")
	{
		return new QRDSProject(hashList);
	}
	else if (hashList["Type"] == "ftp")
	{
		return new QFTPProject(hashList);
	}
	else if (hashList["Type"] == "sftp")
	{
		return new QSFTPProject(hashList);
	} 
	else
		return NULL;
}

QString QProject::getUrl()
{
	return m_Url;
}
