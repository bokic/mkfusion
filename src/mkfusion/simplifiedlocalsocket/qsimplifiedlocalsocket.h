#pragma once

#include <qglobal.h>
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
    int m_Handle;
    int m_Timeout;
};
