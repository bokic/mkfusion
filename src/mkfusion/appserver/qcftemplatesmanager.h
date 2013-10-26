#ifndef QCTEMPLATESMANAGER_H
#define QCTEMPLATESMANAGER_H

#include "qcfworkerthread.h"
#include "qcftemplate.h"
#include "qcfcompiler.h"

#include <QReadWriteLock>
#include <QString>
#include <QHash>


class QCFTemplatesManager
{
public:
    QCFTemplatesManager();

    void init();
    QCFWorkerThread * getWorker(const QString &sourceFile, QString &error);

private:
    QHash<QString, QCFTemplate> m_templates;
    QCFCompiler m_compiler;
    QReadWriteLock m_lock;
};

#endif // QCTEMPLATESMANAGER_H
