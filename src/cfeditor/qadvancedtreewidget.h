#pragma once

#include <QTreeWidget>
#include <QKeyEvent>

class QAdvancedTreeWidget: public QTreeWidget
{
    Q_OBJECT
public:
signals:
    void keyPress(QAdvancedTreeWidget*, QKeyEvent*);
protected:
    virtual void keyPressEvent(QKeyEvent*);
};
