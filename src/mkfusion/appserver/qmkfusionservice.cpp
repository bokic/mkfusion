#include "qmkfusionservice.h"
#include "qtservice.h"
#include <QStringList>


QMKFusionService::QMKFusionService(int argc, char **argv)
    : QtService<QCoreApplication>(argc, argv, "mkfusion-service")
{
    setStartupType(QtServiceController::AutoStartup);
    setServiceDescription("MKFusion application server.");
#ifdef Q_OS_WIN
    setDependsOnServices(QStringList() << "Tcpip");
#elif defined Q_OS_LINUX
#else
#error Windows and Linux OSs are currently supported.
#endif
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
