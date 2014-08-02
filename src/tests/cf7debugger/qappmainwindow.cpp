#include <QMainWindow>
#include "qappmainwindow.h"

QAppMainWindow::QAppMainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
    , m_Edit(new QListView(this))
    , m_jdwpsocket(new QJDWPDebugger(this))
{
    setWindowTitle("test");

    //m_jdwpsocket->connectToHost("192.168.1.116", 8000); // CF7
    m_jdwpsocket->connectToHost("192.168.1.117", 5005); // CF8 - Debian VM1 - Laptop

    setCentralWidget(m_Edit);
}
