#ifndef QADVANCEDTREEWIDGET_H
#define QADVANCEDTREEWIDGET_H

#include <QTreeWidget>
#include <QKeyEvent>

class QAdvancedTreeWidget: public QTreeWidget
{
	Q_OBJECT
public:
protected:
	virtual void keyPressEvent(QKeyEvent*); 
private:
public:
signals:
	void keyPress(QAdvancedTreeWidget*, QKeyEvent*);
};

#endif // QADVANCEDTREEWIDGET_H