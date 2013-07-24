#ifndef QDEFAULTSERVICE_H
#define QDEFAULTSERVICE_H

#include "qabstractrdsservice.h"
#include <QObject>
#include <QString>
#include <QVector>
#include <QList>
#include <QMap>

class QDefaultService : public QAbstractRDSService
{
public:
	enum Command {
		IdeDefaultCommand
	};

	QDefaultService() : QAbstractRDSService(){};
	virtual ~QDefaultService() {};
	virtual QByteArray ExecuteRDSCommand(QRDSServer, quint8, QMap<QString, QString>);
protected:
private:
	QByteArray IdeDefault(QRDSServer);
};

#endif // QDEFAULTSERVICE_H
