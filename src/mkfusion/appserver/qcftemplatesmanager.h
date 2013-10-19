#ifndef QCTEMPLATESMANAGER_H
#define QCTEMPLATESMANAGER_H

#include "qcftemplate.h"
#include "qcftemplateinstance.h"
#include "qcfcompiler.h"

#include <QReadWriteLock>
#include <QString>
#include <QHash>


class QCFTemplatesManager
{
public:
    QCFTemplatesManager();

    void init();
    QCFTemplateInstance *getTemplateInstance(const QString &sourceFile);

private:
    QHash<QString, QCFTemplate> m_templates;
    QCFCompiler m_compiler;
    QReadWriteLock m_lock;
};

#endif // QCTEMPLATESMANAGER_H
