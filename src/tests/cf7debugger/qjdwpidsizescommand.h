#ifndef QJDWPIDSIZESCOMMAND_H
#define QJDWPIDSIZESCOMMAND_H

#include "qjdwpcommand.h"
#include "qjdwpdebugger.h"

class QJDWPIDSizesCommand : public QJDWPCommand
{
public:
	explicit QJDWPIDSizesCommand(QJDWPDebugger* = 0);
};

#endif // QJDWPIDSIZESCOMMAND_H
