#include "qcftemplatesmanager.h"

#include <QMutexLocker>


QCFTemplatesManager::QCFTemplatesManager()
{
}

QCFTemplateInstance *QCFTemplatesManager::getTemplateInstanceForSource(const QString &source)
{
    QMutexLocker lock(&m_mutex);


}
