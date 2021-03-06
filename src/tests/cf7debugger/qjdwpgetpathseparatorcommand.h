#pragma once

#include "qjdwpcommand.h"
#include "qjdwpdebugger.h"

class QJDWPGetPathSeparatorCommand : public QJDWPCommand
{
    Q_OBJECT
public:
    explicit QJDWPGetPathSeparatorCommand(QJDWPDebugger * = 0);
    virtual ~QJDWPGetPathSeparatorCommand();
    char getPathSeparator();
    virtual void processRecivedCommand(const QByteArray &p_Data) override;
private:
    char m_PathSeparator;
    QJDWPCommand *m_SubCommand;
    enum { CLASSES_BY_SIGNATURE, BETA, GAMMA } m_Progress;
};
