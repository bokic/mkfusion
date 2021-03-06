#pragma once

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
    QCFVariant getComponent(const QString &sourceFile, QCFWorkerThread &worker, QString &error);

private:
    QHash<QString, QCFTemplate> m_templates;
    QCFCompiler m_compiler;
    QReadWriteLock m_lock;
    QString m_cachePath;
};
