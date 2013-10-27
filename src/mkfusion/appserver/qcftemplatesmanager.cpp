#include "qcftemplatesmanager.h"
#include "qcftemplateinfo.h"
#include "qcftemplate.h"
#include "qcfserver.h"

#include <QWriteLocker>
#include <QReadLocker>
#include <QFileInfo>
#include <QProcess>
#include <QThread>
#include <QDir>


QCFTemplatesManager::QCFTemplatesManager()
{
}

void QCFTemplatesManager::init()
{
    QReadLocker lock(&m_lock);

#ifdef Q_OS_WIN
    m_cachePath = QCFServer::MKFusionPath();
#elif defined Q_OS_LINUX
    m_cachePath = "/var/cache/mkfusion/";
#else
#error Windows and Linux OSs are currently supported.
#endif

    m_compiler.setTargetPath(m_cachePath);

#ifdef Q_OS_WIN
    QStringList l_Templates = QDir(m_cachePath + "templates").entryList(QStringList() << "*.dll", QDir::Files, QDir::Name);
#elif defined Q_OS_LINUX
    QStringList l_Templates = QDir(m_cachePath + "templates").entryList(QStringList() << "*.so", QDir::Files, QDir::Name);
#else
#error Windows and Linux OSs are currently supported.
#endif

    for(const QString &l_Template: l_Templates)
    {
        QLibrary l_TemplateLib;
        bool l_DeleteTemplate = true;
        QCFTemplateInfo l_page;

        QString templateFilePath = m_cachePath + "templates" + QDir::separator() + l_Template;

        l_TemplateLib.setFileName(templateFilePath);

        if (l_TemplateLib.load() == true)
        {
            typedef QCFTemplateInfo (*getTemplateInfoDef)();

            getTemplateInfoDef getTemplateInfo = (getTemplateInfoDef) l_TemplateLib.resolve("getTemplateInfo");
            if (getTemplateInfo)
            {
                l_page = getTemplateInfo();
            }

            l_TemplateLib.unload();

            if (!l_page.m_FilePath.isEmpty())
            {
                QFileInfo fi(l_page.m_FilePath);

                if ((fi.lastModified().toTime_t() == l_page.m_FileModified)&&(fi.size() == l_page.m_FileSize))
                {
                    m_templates.insert(l_page.m_FilePath, QCFTemplate(templateFilePath, l_page, false));

                    l_DeleteTemplate = false;
                }
            }
        }

        if (l_DeleteTemplate == true)
        {
            QFile::remove(templateFilePath);
        }
    }
}

QCFWorkerThread * QCFTemplatesManager::getWorker(const QString &sourceFile, QString &error)
{
    QString cppFile, libFile;

    forever
    {
        {
            QWriteLocker lock(&m_lock);

            if (m_templates.contains(sourceFile))
            {
                if (m_templates[sourceFile].isCompiling())
                {
                    QThread::msleep(1);

                    continue;
                }

                if (m_templates[sourceFile].load())
                {
                    return m_templates[sourceFile].getTemplateObject();
                }
                else
                {
                    error = m_templates[sourceFile].error();

                    return nullptr;
                }
            }
            else
            {
                m_templates.insert(sourceFile, QCFTemplate());

                break;
            }
        }

        QThread::msleep(1);
    }

    // do cfml2c++ conversion.
    error = m_compiler.generateCpp(sourceFile, cppFile);
    if (!error.isEmpty())
    {
        QReadLocker lock(&m_lock);

        m_templates[sourceFile].setCompiling(false);

        m_templates[sourceFile].setError(error);

        return nullptr;
    }

    // do compile.
    error = m_compiler.compile(cppFile, libFile);
    if (!error.isEmpty())
    {
        QReadLocker lock(&m_lock);

        m_templates[sourceFile].setCompiling(false);

        m_templates[sourceFile].setError(error);

        return nullptr;
    }

    {
        QReadLocker lock(&m_lock);

        m_templates[sourceFile].setCompiling(false);

        m_templates[sourceFile].setLibrary(libFile);

        if (!m_templates[sourceFile].load())
        {
            return nullptr;
        }

        return m_templates[sourceFile].getTemplateObject();
    }

    return nullptr;
}
