#include <QMainWindow>
#include "QAppMainWindow.h"

QAppMainWindow::QAppMainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	setWindowTitle("test");

	m_Edit = new QListView(this);
	m_jdwpsocket = new QJDWPDebugger(this);
	//m_jdwpsocket->connectToHost("192.168.1.116", 8000); // CF7
	m_jdwpsocket->connectToHost("192.168.1.117", 5005); // CF8 - Debian VM1 - Laptop

	setCentralWidget(m_Edit);
}
