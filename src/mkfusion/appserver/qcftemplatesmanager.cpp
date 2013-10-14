#include "qcftemplatesmanager.h"
#include "qcftemplate.h"

#include <QWriteLocker>
#include <QReadLocker>


QCFTemplatesManager::QCFTemplatesManager()
{
}

void QCFTemplatesManager::init()
{

}

QCFTemplateInstance *QCFTemplatesManager::getTemplateInstanceForSource(const QString &source)
{
    {
        QReadLocker lock(&m_lock);

        if (m_templates.contains(source))
        {
            if (!m_templates[source].load())
            {
                return nullptr;
            }
        }
    }

    // compile.

    QWriteLocker lock(&m_lock);

}
