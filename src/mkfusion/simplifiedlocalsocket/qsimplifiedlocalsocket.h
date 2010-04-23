#ifndef QSIMPLIFIEDLOCALSOCKET_H
#define QSIMPLIFIEDLOCALSOCKET_H

#include <windows.h>
#include <QByteArray>
#include <QString>

class QSimplifiedLocalSocket
{
public:
	QSimplifiedLocalSocket();
	~QSimplifiedLocalSocket();
	void connectToServer(QString, int = 500);
	bool waitForConnected();
	int write(QByteArray);
	bool isValid();
	bool waitForReadyRead();
	QByteArray readAll();
private:
#ifdef Q_WS_WIN
	HANDLE m_Handle;
#endif
};

#endif // QSIMPLIFIEDLOCALSOCKET_H
