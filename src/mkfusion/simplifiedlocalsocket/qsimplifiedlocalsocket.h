#pragma once

#include <qglobal.h>
#ifdef Q_OS_WIN
#include <windows.h>
#endif
#include <QByteArray>
#include <QString>

class QSimplifiedLocalSocket
{
public:
    QSimplifiedLocalSocket();
    virtual ~QSimplifiedLocalSocket();
    void connectToServer(QString, int = 500);
    bool waitForConnected();
    int write(QByteArray);
    bool isValid();
    bool waitForReadyRead();
    QByteArray readAll();
    void close();
private:
#ifdef Q_OS_WIN
    HANDLE m_Handle;
#endif
#ifdef Q_OS_LINUX
    int m_Handle;
    int m_Timeout;
#endif
};
