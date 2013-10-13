#ifndef QCTEMPLATESMANAGER_H
#define QCTEMPLATESMANAGER_H

#include "qcftemplate.h"
#include "qcftemplateinstance.h"

#include <QString>
#include <QMutex>
#include <QHash>


class QCFTemplatesManager
{
public:
    QCFTemplatesManager();

    QCFTemplateInstance *getTemplateInstanceForSource(const QString &source);

private:
    QHash<QString, QCFTemplate> m_libraries;
    QMutex m_mutex;
};

#endif // QCTEMPLATESMANAGER_H
