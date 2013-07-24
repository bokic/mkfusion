#include "qadvancedtreewidget.h"

void QAdvancedTreeWidget::keyPressEvent(QKeyEvent *e)
{
	QTreeWidget::keyPressEvent(e);

	emit keyPress(this, e);
}
