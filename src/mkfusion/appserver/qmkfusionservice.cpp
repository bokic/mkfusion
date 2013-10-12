#include "qmkfusionservice.h"
#include "qtservice.h"
#include <QStringList>


QMKFusionService::QMKFusionService(int argc, char **argv)
    : QtService<QCoreApplication>(argc, argv, "MKFusion")
    , m_CFServer()
{
    setStartupType(QtServiceController::AutoStartup);
    setServiceDescription("MKFusion application server.");
}

QMKFusionService::~QMKFusionService()
{

}

void QMKFusionService::start()
{
    m_CFServer.start();
}

void QMKFusionService::stop()
{
    m_CFServer.stop();
}
