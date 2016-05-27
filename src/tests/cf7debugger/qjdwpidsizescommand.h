#pragma once

#include "qjdwpcommand.h"
#include "qjdwpdebugger.h"

class QJDWPIDSizesCommand : public QJDWPCommand
{
public:
    explicit QJDWPIDSizesCommand(QJDWPDebugger * = 0);
};
