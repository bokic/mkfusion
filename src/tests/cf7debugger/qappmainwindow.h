#pragma once

#include <QMainWindow>
#include <QListView>
#include "qjdwpdebugger.h"


class QAppMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QAppMainWindow(QWidget *parent = nullptr);
private:
    QListView *m_Edit = nullptr;
    QJDWPDebugger *m_jdwpsocket = nullptr;
};
