#ifndef QSIMPLIFIEDLOCALSOCKET_H
#define QSIMPLIFIEDLOCALSOCKET_H

#include <qglobal.h>
#ifdef Q_WS_WIN
#include <windows.h>
#endif
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
	void close();
private:
#ifdef Q_WS_WIN
	HANDLE m_Handle;
#endif
#ifdef Q_WS_X11
	int m_Handle;
	int m_Timeout;
#endif
};

#endif // QSIMPLIFIEDLOCALSOCKET_H
