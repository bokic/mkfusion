#pragma once

#include <QByteArray>
#include <QObject>


class QJDWPCommand : public QObject
{
    Q_OBJECT
public:
    explicit QJDWPCommand(QObject *parent = nullptr);
    quint32 getCommandID() const;
    virtual void processRecivedCommand(const QByteArray &data) = 0;

protected:
    quint32 m_CommandID = 0;
};
