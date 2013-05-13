#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include "qtservice.h"

#include <qcfserver.h>


class QMKFusionService : public QtService<QCoreApplication>
{
public:
	QMKFusionService(int argc, char **argv): QtService<QCoreApplication>(argc, argv, "MKFusion")
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

protected:
	void start()
	{
		m_CFServer.start();
	}

	void stop()
	{
		m_CFServer.stop();
	}

private:
	QCFServer m_CFServer;
};

int main(int argc, char **argv)
{
	QMKFusionService service(argc, argv);
	return service.exec();
}
