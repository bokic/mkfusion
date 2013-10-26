#include "qcftemplatesmanager.h"
#include "qcftemplate.h"
#include "qcfserver.h"

#include <QWriteLocker>
#include <QReadLocker>
#include <QProcess>
#include <QThread>


QCFTemplatesManager::QCFTemplatesManager()
{
}

void QCFTemplatesManager::init()
{
    QReadLocker lock(&m_lock);

#ifdef Q_OS_WIN
    m_compiler.setTargetPath(QCFServer::MKFusionPath());
#elif defined Q_OS_LINUX
    m_compiler.setTargetPath("/var/cache/mkfusion/");
#else
#error Windows and Linux OSs are currently supported.
#endif
}

QCFWorkerThread * QCFTemplatesManager::getWorker(const QString &sourceFile, QString &error)
{
    QString cppFile;

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

                if (!m_templates[sourceFile].load())
                {
                    error = m_templates[sourceFile].error();

                    return nullptr;
                }
            }
            else
            {
                m_templates.insert(sourceFile, QCFTemplate(sourceFile));

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
    error = m_compiler.compile(cppFile);
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

        if (!m_templates[sourceFile].load())
        {
            return nullptr;
        }
    }


    return nullptr;
}

