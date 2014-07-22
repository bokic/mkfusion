#include "qlocalproject.h"
#include <QByteArray>
#include <QFile>
#include <QDir>

QLocalProject::QLocalProject(const QHash<QString, QString> &p_Args)
{
    m_Type = QProject::LocalProject;
    m_Url = p_Args["Url"];
    m_Path = p_Args["Path"];

    if (!m_Path.endsWith(QLocalProject::getDirSeparator()))
    {
        m_Path.append(QLocalProject::getDirSeparator());
    }
}

QLocalProject::~QLocalProject()
{
}

char QLocalProject::getDirSeparator()
{
    return '/';
}

QByteArray QLocalProject::ReadFile(const QString &p_File)
{
    QFile file(m_Path + p_File);

    if (!file.open(QIODevice::ReadOnly))
        return "";

    QByteArray ba = file.readAll();

    file.close();

    return ba;
}

void QLocalProject::WriteFile(const QString &p_File, const QByteArray &p_Content)
{
    QFile l_file(m_Path + p_File);

    if (!l_file.open(QIODevice::WriteOnly))
        return;

    l_file.write(p_Content);
    l_file.resize(p_Content.size());
    l_file.close();
}

void QLocalProject::DeleteFile(const QString &p_File)
{
    QFile::remove(m_Path + p_File);
}

void QLocalProject::RenameFile(const QString &p_FromFile, const QString &p_ToFile)
{
    QFile::rename(m_Path + p_FromFile, m_Path + p_ToFile);
}

QList<QProjectFile> QLocalProject::getFolderItems(const QString &p_Folder)
{
    QList<QProjectFile> ret;

    QDir dir(m_Path + p_Folder);
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::Hidden | QDir::NoSymLinks);

    QFileInfoList list = dir.entryInfoList();

    for(const QFileInfo &item: list)
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

void QLocalProject::CreateDir(const QString &p_Dir)
{
    QDir l_dir;
    l_dir.mkdir(m_Path + p_Dir);
}

void QLocalProject::DeleteDir(const QString &p_Dir, bool p_Recursive)
{
    QDir l_dir;

    if (p_Recursive)
    {
        // TODO: Implement recursive.
    }

    l_dir.rmdir(m_Path + p_Dir);
}

void QLocalProject::RenameDir(const QString &p_OldDir, const QString &p_NewDir)
{
    QDir l_dir;
    l_dir.rename(m_Path + p_OldDir, m_Path + p_NewDir);
}
