#ifndef QAPPMAINWINDOW_H
#define QAPPMAINWINDOW_H

#include <qproject.h>

#include <QMainWindow>
#include "qadvancedtreewidget.h"

namespace Ui {
    class QAppMainWindow;
}

class QAppMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QAppMainWindow(QWidget *parent = 0);
    ~QAppMainWindow();

private slots:
	void on_m_Browser_titleChanged(QString title);

	void on_action_New_activated();
	void on_action_Open_activated();
	void on_action_Close_activated();
	void on_action_Close_All_activated();
	void on_action_Save_activated();
	void on_action_Save_As_activated();
	void on_action_Save_All_activated();
	void on_action_Print_activated();
	void on_action_Print_Preview_activated();
	void on_action_Exit_activated();
	void on_action_Undo_activated();
	void on_action_Redo_activated();
	void on_action_Cut_activated();
	void on_action_Copy_activated();
	void on_action_Paste_activated();
	void on_action_Select_All_activated();
	void on_action_Find_activated();
	void on_action_Goto_Line_activated();
	void on_action_Open_Project_activated();
	void on_action_Save_Project_activated();
	void on_action_Close_Project_activated();
	void on_action_Project_Properties_activated();
	void on_action_Check_Project_activated();
	void on_action_Full_Screen_activated();
    void on_action_Hide_Everything_activated();
    void on_action_ColdFusion_Help_activated();
	void on_action_About_activated();
	void on_m_ProjectTree_itemExpanded(QTreeWidgetItem*);
	void on_m_ProjectTree_itemCollapsed(QTreeWidgetItem*);
	void on_m_ProjectTree_itemDoubleClicked(QTreeWidgetItem*, int);
	void on_m_ProjectTree_keyPress(QAdvancedTreeWidget*, QKeyEvent*);
    //void on_centralwidget_Item_textChanged();
	void on_centralwidget_currentChanged(int);
	void on_centralwidget_tabCloseRequested(int);
    void onmy_textedit_key_press(QKeyEvent*);
    void onmy_textedit_text_change();
    void onmy_textedit_breakpoint_change(int);

private:
	void LoadProject(const QString&);
	void UpdateProjectFileList(const QString& = "", QTreeWidgetItem* = NULL);
	void recolor();
//	void colorElement(const QCFParserElement &);
	Ui::QAppMainWindow *ui;
	QProject *m_Project;
	QString m_ProjectFileName;
};

#endif // QAPPMAINWINDOW_H
