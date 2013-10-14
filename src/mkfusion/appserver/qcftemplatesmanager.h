#ifndef QCTEMPLATESMANAGER_H
#define QCTEMPLATESMANAGER_H

#include "qcftemplate.h"
#include "qcftemplateinstance.h"

#include <QReadWriteLock>
#include <QString>
#include <QHash>


class QCFTemplatesManager
{
public:
    QCFTemplatesManager();

    void init();
    QCFTemplateInstance *getTemplateInstanceForSource(const QString &source);

private:
    QHash<QString, QCFTemplate> m_templates;
    QReadWriteLock m_lock;
};

#endif // QCTEMPLATESMANAGER_H
