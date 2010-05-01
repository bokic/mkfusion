#ifndef QJDWPCLASSESBYSIGNATURECOMMAND_H
#define QJDWPCLASSESBYSIGNATURECOMMAND_H

#include "qjdwpcommand.h"

class QJDWPClassesBySignature : public QObject
{
	Q_OBJECT
public:
	quint32 refTypeTag;
	quint64 typeID;
	qint32 status;
};

class QJDWPClassesBySignatureCommand : public QJDWPCommand
{
	Q_OBJECT
public:
	QJDWPClassesBySignatureCommand(QObject* = 0);
	quint32 sendCommand(QString);
	virtual void processRecivedCommand(QByteArray);
	const QList<QJDWPClassesBySignature*> getResult();
private:
	QList<QJDWPClassesBySignature*> m_Result;
};

#endif // QJDWPCLASSESBYSIGNATURECOMMAND_H
