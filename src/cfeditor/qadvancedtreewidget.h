#pragma once

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
