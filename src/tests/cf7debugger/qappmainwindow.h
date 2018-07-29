#pragma once

#include <QMainWindow>
#include <QListView>
#include "qjdwpdebugger.h"

class QAppMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QAppMainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = 0);
private:
    QListView *m_Edit;
    QJDWPDebugger *m_jdwpsocket;
};
