#ifndef QADVANCEDTEXTEDIT_H
#define QADVANCEDTEXTEDIT_H

#include <QTextEdit>
#include <QKeyEvent>

class QAdvancedTextEdit: public QTextEdit
{
	Q_OBJECT
public:
protected:
	virtual void keyPressEvent(QKeyEvent*); 
private:
public:
signals:
	void keyPress(QAdvancedTextEdit*, QKeyEvent*);
};

#endif // QADVANCEDTEXTEDIT_H
