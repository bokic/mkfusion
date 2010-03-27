#ifndef QPROJECTFILE_H
#define QPROJECTFILE_H

#include <QString>
#include <QHash>
#include <QList>

class QProjectFile
{
public:
	//QProjectFile();
	QString m_FileName;
	bool m_IsFolder;
	qint64 m_FileSize;
protected:
private:
};

bool operator<(const QProjectFile&, const QProjectFile&);

#endif // QPROJECTFILE_H
