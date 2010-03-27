#ifndef QJDWPGETPATHSEPARATORCOMMAND_H
#define QJDWPGETPATHSEPARATORCOMMAND_H

#include "QJDWPCommand.h"
#include "QJDWPDebugger.h"

class QJDWPGetPathSeparatorCommand : public QJDWPCommand
{
	Q_OBJECT
public:
	QJDWPGetPathSeparatorCommand(QJDWPDebugger* = 0);
	char getPathSeparator();
	virtual void processRecivedCommand(QByteArray);
private:
	char m_PathSeparator;
	QJDWPCommand* m_SubCommand;
	enum { CLASSES_BY_SIGNATURE, BETA, GAMMA } m_Progress;
};

#endif // QJDWPGETPATHSEPARATORCOMMAND_H
