#ifndef QAPPMAINWINDOW_H
#define QAPPMAINWINDOW_H

#include <qadvancedtreewidget.h>
#include <qadvancedtextedit.h>
#include <qcfparser.h>
#include <qproject.h>

#include <QtGui/QMainWindow>
#include <QtGui/QDockWidget>
#include <QtGui/QDockWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtWebKit/QWebView>

class QAppMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	QAppMainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QAppMainWindow();
private:
	QDockWidget *m_ProjectDock;
	QDockWidget *m_StructureDock;
	QDockWidget *m_BrowserDock;
	QAdvancedTreeWidget *m_ProjectTree;
	QTreeWidget *m_StructureTree;
	QWebView *m_Browser;// TODO: later move to WebKit
	QTabWidget *m_TabPanel;
	bool m_EditorUpdating;
	QProject *m_Project;
private:
	void UpdateProjectFileList(QString, QTreeWidgetItem*);
	void recolor();
	void colorElement(const QCFParserElement &);
private slots:
	void on_m_ProjectTree_itemExpanded(QTreeWidgetItem*);
	void on_m_ProjectTree_itemCollapsed(QTreeWidgetItem*);
	void on_m_ProjectTree_itemDoubleClicked(QTreeWidgetItem*, int);
	void on_m_ProjectTree_keyPress(QAdvancedTreeWidget*, QKeyEvent*);
	void on_m_TabPanel_Item_keyPress(QAdvancedTextEdit*, QKeyEvent*);
	void on_m_TabPanel_Item_textChanged();
	void on_m_TabPanel_currentChanged(int);
	void on_m_TabPanel_tabCloseRequested(int);
};

#endif // QAPPMAINWINDOW_H
