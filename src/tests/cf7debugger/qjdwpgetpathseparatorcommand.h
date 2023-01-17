#pragma once

#include "qjdwpcommand.h"
#include "qjdwpdebugger.h"


class QJDWPGetPathSeparatorCommand : public QJDWPCommand
{
    Q_OBJECT
public:
    explicit QJDWPGetPathSeparatorCommand(QJDWPDebugger *parent = nullptr);
    virtual ~QJDWPGetPathSeparatorCommand();
    char getPathSeparator();
    virtual void processRecivedCommand(const QByteArray &data) override;

private:
    char m_PathSeparator = '\0';
    QJDWPCommand *m_SubCommand = nullptr;
    enum { CLASSES_BY_SIGNATURE, BETA, GAMMA } m_Progress = CLASSES_BY_SIGNATURE;
};
