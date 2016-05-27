#pragma once

#include <QByteArray>
#include <QObject>

class QJDWPCommand : public QObject
{
    Q_OBJECT
public:
    explicit QJDWPCommand(QObject *parent = 0);
    virtual ~QJDWPCommand();
    quint32 getCommandID() const;
    virtual void processRecivedCommand(const QByteArray &p_Data) = 0;

protected:
    quint32 m_CommandID;
};
