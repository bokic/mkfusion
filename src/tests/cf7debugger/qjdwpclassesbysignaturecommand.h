#pragma once

#include "qjdwpcommand.h"

struct QJDWPClassesBySignature
{
    quint32 refTypeTag = 0;
    quint64 typeID = 0;
    qint32 status = 0;
};

class QJDWPClassesBySignatureCommand : public QJDWPCommand
{
    Q_OBJECT
public:
    explicit QJDWPClassesBySignatureCommand(QObject * = 0);
    virtual ~QJDWPClassesBySignatureCommand();
    quint32 sendCommand(const QString &p_ClassName);
    virtual void processRecivedCommand(const QByteArray &p_Data);
    QList<QJDWPClassesBySignature> result() const;

private:
    QList<QJDWPClassesBySignature> m_Result;
};
