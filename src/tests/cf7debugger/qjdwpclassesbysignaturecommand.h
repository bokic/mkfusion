#ifndef QJDWPCLASSESBYSIGNATURECOMMAND_H
#define QJDWPCLASSESBYSIGNATURECOMMAND_H

#include "qjdwpcommand.h"

struct QJDWPClassesBySignature
{
    QJDWPClassesBySignature()
    {
        refTypeTag = 0;
        typeID = 0;
        status = 0;
    }

    quint32 refTypeTag;
    quint64 typeID;
    qint32 status;
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

#endif // QJDWPCLASSESBYSIGNATURECOMMAND_H
