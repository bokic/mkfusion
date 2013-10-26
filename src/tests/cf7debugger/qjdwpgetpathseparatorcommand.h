#ifndef QJDWPGETPATHSEPARATORCOMMAND_H
#define QJDWPGETPATHSEPARATORCOMMAND_H

#include "qjdwpcommand.h"
#include "qjdwpdebugger.h"

class QJDWPGetPathSeparatorCommand : public QJDWPCommand
{
	Q_OBJECT
public:
    explicit QJDWPGetPathSeparatorCommand(QJDWPDebugger * = 0);
	virtual ~QJDWPGetPathSeparatorCommand();
	char getPathSeparator();
	virtual void processRecivedCommand(QByteArray);
private:
	char m_PathSeparator;
    QJDWPCommand *m_SubCommand;
	enum { CLASSES_BY_SIGNATURE, BETA, GAMMA } m_Progress;
};

#endif // QJDWPGETPATHSEPARATORCOMMAND_H
