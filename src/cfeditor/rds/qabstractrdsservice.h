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
    static QByteArray StringToSTR(const QString &value);
    static QByteArray EncodePassword(const QByteArray &value);
    static QVector<QByteArray> BreakByteArrayIntoVector(const QByteArray &value);
    static QByteArray generateRDSCommandSocketOutput(const QString &url, const QByteArray &post);
    static QByteArray executeRDSCommandURL(const QString &url, const QByteArray &post);
    static QByteArray generatePostFromVector(const QRDSServer &rdsserver, const QVector<QString> &map);
    static QByteArray executeRDSCommandForByteArray(const QString &command, const QRDSServer &rdsserver, const QVector<QString> &map, quint16 port);
    virtual QByteArray ExecuteRDSCommand(const QRDSServer &rdsserver, quint8 command, const QMap<QString, QString> &map) = 0;
    static QString prepareURL(const QRDSServer &rdsserver, const QString &command, quint16 port);
protected:
    static QByteArray ArgumentsToString(const QVector<QString> &args);
    static QByteArray executeRDSCommandForByteArray(const QString &command, const QRDSServer &rdsserver, const QVector<QString> &map);
private:
    static QByteArray GetKeyForLength(int len);
    static QByteArray XORString(const QByteArray &value);
    static int readToColumn(QByteArray &str, const QByteArray &buf, int offset);
};

#endif // QABSTRACTRDSSERVICE_H
