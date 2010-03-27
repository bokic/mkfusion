#include "qadvancedtextedit.h"

void QAdvancedTextEdit::keyPressEvent(QKeyEvent* e)
{
	QTextEdit::keyPressEvent(e);

	emit keyPress(this, e);
}
