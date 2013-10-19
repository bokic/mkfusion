#include "qcftemplatesmanager.h"
#include "qcftemplate.h"

#include <QWriteLocker>
#include <QReadLocker>
#include <QThread>


QCFTemplatesManager::QCFTemplatesManager()
    : m_compiler("")
{
}

void QCFTemplatesManager::init()
{
    QReadLocker lock(&m_lock);
}

QCFTemplateInstance *QCFTemplatesManager::getTemplateInstance(const QString &sourceFile)
{
    for(; ; QThread::msleep(1))
    {
        QReadLocker lock(&m_lock);

        if (m_templates.contains(sourceFile))
        {
            if (m_templates[sourceFile].isCompiling())
            {
                continue;
            }

            if (!m_templates[sourceFile].load())
            {
                return nullptr;
            }
        }
        else
        {
            m_templates.insert(sourceFile, QCFTemplate(sourceFile));

            break;
        }
    }

    // do compile.

    {
        QReadLocker lock(&m_lock);

    }
}
