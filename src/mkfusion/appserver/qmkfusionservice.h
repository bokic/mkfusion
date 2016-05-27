#pragma once

#include <QCoreApplication>
#include "qtservice.h"
#include <qcfserver.h>


class QMKFusionService : public QtService<QCoreApplication>
{
public:
    QMKFusionService(int argc, char **argv);
    virtual ~QMKFusionService();
    QCFServer m_CFServer;

protected:
    virtual void start();
    virtual void stop();
};
