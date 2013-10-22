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

/*QCFTemplateInstance *QCFTemplatesManager::getTemplateInstance(const QString &sourceFile, QString &error)
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

    // do compile.

    {
        QReadLocker lock(&m_lock);

    }
}
*/
