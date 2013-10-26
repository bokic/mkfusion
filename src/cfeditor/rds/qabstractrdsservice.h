#ifndef QABSTRACTRDSSERVICE_H
#define QABSTRACTRDSSERVICE_H

#include "qrdsserver.h"
#include <QByteArray>
#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>

class QAbstractRDSService : public QObject
{
public:
	QAbstractRDSService();
	virtual ~QAbstractRDSService();
	static QByteArray StringToSTR(QString);
	static QByteArray EncodePassword(QByteArray);
	static QVector<QByteArray> BreakByteArrayIntoVector(QByteArray);
	static QByteArray generateRDSCommandSocketOutput(QString, QByteArray);
	static QByteArray executeRDSCommandURL(QString, QByteArray);
	static QByteArray generatePostFromVector(QRDSServer, QVector<QString>);
	static QByteArray executeRDSCommandForByteArray(QString, QRDSServer, QVector<QString>, quint16);
	virtual QByteArray ExecuteRDSCommand(QRDSServer, quint8, QMap<QString, QString>) = 0;
	static QString prepareURL(QRDSServer, QString, quint16);
protected:
	static QByteArray ArgumentsToString(QVector<QString>);
	static QByteArray executeRDSCommandForByteArray(QString, QRDSServer, QVector<QString>);
private:
	static QByteArray GetKeyForLength(int);
	static QByteArray XORString(QByteArray);
	static int readToColumn(QByteArray&, QByteArray, int);
};

#endif // QABSTRACTRDSSERVICE_H
