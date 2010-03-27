#ifndef QJDWPCOMMAND_H
#define QJDWPCOMMAND_H

#include <QObject>
#include <QByteArray>

class QJDWPCommand : public QObject
{
	Q_OBJECT
public:
	QJDWPCommand(QObject* = 0);
	quint32 getCommandID();
	virtual void processRecivedCommand(QByteArray) = 0;
protected:
	quint32 m_CommandID;
};

#endif // QJDWPCOMMAND_H
