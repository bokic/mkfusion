#include <qappmainwindow.h>
#include <qcodeeditwidget.h>
#include <qprojectfile.h>
#include <QTreeWidgetItem>
#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QComboBox>
#include <QToolBar>
#include <QList>

QAppMainWindow::QAppMainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	setWindowTitle("CFEditor v0.4.1");

	QMenu* menu_File = new QMenu();
	menu_File->setTitle(tr("&File"));
	menu_File->addAction(QIcon(":/CFEditor/Commands/new.png"), tr("&New"), this, SLOT(slotFileNew()));
	menu_File->addAction(tr("&Open"), this, SLOT(slotFileOpen()));
	menu_File->addSeparator();
	menu_File->addAction(tr("&Close"), this, SLOT(slotFileClose()));
	menu_File->addAction(tr("Close A&ll"), this, SLOT(slotFileCloseAll()));
	menu_File->addSeparator();
	menu_File->addAction(QIcon(":/CFEditor/Commands/save.png"), tr("&Save"), this, SLOT(slotFileSave()));
	menu_File->addAction(QIcon(":/CFEditor/Commands/save_as.png"), tr("Save As"), this, SLOT(slotFileSaveAs()));
	menu_File->addAction(QIcon(":/CFEditor/Commands/save_all.png"), tr("Sav&e All"), this, SLOT(slotFileSaveAll()));
	menu_File->addSeparator();
	menu_File->addAction(QIcon(":/CFEditor/Commands/print.png"), tr("&Print"), this, SLOT(slotFilePrint()));
	menu_File->addAction(QIcon(":/CFEditor/Commands/print_preview.png"), tr("Print Previe&w"), this, SLOT(slotFilePrintPreview()));
	menu_File->addSeparator();
	menu_File->addAction(QIcon(":/CFEditor/Commands/settings.png"), tr("P&roperties"), this, SLOT(slotFileProperties()));
	menu_File->addSeparator();
	menu_File->addSeparator();
	menu_File->addAction(tr("E&xit"), this, SLOT(slotFileExit()));
	menu_File->addSeparator();

	QMenu* edit_File = new QMenu();
	edit_File->setTitle(tr("&Edit"));
	edit_File->addAction(tr("&Undo"), this, SLOT(slotEditUndo()));
	edit_File->addAction(tr("&Redo"), this, SLOT(slotEditRedo()));
	edit_File->addSeparator();
	edit_File->addAction(QIcon(":/CFEditor/Commands/copy.png"), tr("&Copy"), this, SLOT(slotEditCopy()));
	edit_File->addAction(QIcon(":/CFEditor/Commands/cut.png"), tr("&Cut"), this, SLOT(slotEditCut()));
	edit_File->addAction(QIcon(":/CFEditor/Commands/paste.png"), tr("&Paste"), this, SLOT(slotEditPaste()));
	edit_File->addSeparator();
	edit_File->addAction(tr("Select &All"), this, SLOT(slotEditSelectAll()));
	edit_File->addSeparator();
	edit_File->addAction(QIcon(":/CFEditor/Commands/find.png"), tr("&Find"), this, SLOT(slotEditFind()));
	edit_File->addAction(tr("Goto &Line"), this, SLOT(slotEditGotoLine()));

	QMenu* project_File = new QMenu();
	project_File->setTitle(tr("&Project"));
	project_File->addAction(tr("&Open Project"), this, SLOT(slotProjectOpenProject()));
	project_File->addAction(tr("&Close Project"), this, SLOT(slotProjectCloseProject()));
	project_File->addSeparator();
	project_File->addAction(QIcon(":/CFEditor/Commands/settings.png"), tr("P&roperties"), this, SLOT(slotProjectProperties()));

	QMenu* tools_File = new QMenu();
	tools_File->setTitle(tr("&Tools"));
	tools_File->addAction(QIcon(":/CFEditor/Commands/validate.png"), tr("&Check Project"), this, SLOT(slotToolsCheckProject()));

	QMenu* window_File = new QMenu();
	window_File->setTitle(tr("&Window"));
	window_File->addAction(QIcon(":/CFEditor/Commands/fullscreen.png"), tr("&Full Screen"), this, SLOT(slotWindowFullScreen()));

	QMenu* help_File = new QMenu();
	help_File->setTitle(tr("&Help"));
	help_File->addAction(QIcon(":/CFEditor/Commands/help.png"), tr("&ColdFusion Help"), this, SLOT(slotHelpColdfusionHelp()));
	help_File->addSeparator();
	help_File->addAction(QIcon(":/CFEditor/Commands/about.png"), tr("&About"), this, SLOT(slotHelpAbout()));

	menuBar()->addMenu(menu_File);
	menuBar()->addMenu(edit_File);
	menuBar()->addMenu(project_File);
	menuBar()->addMenu(tools_File);
	menuBar()->addMenu(window_File);
	menuBar()->addMenu(help_File);

	QToolBar* mainToolBar = new QToolBar(this);
	mainToolBar->addWidget(new QComboBox(mainToolBar));
	mainToolBar->addSeparator();

	addToolBar(mainToolBar);

	m_TabPanel = new QTabWidget(this);

	setCentralWidget(m_TabPanel);
	connect(m_TabPanel, SIGNAL(currentChanged(int)), SLOT(on_m_TabPanel_currentChanged(int)));
	connect(m_TabPanel, SIGNAL(tabCloseRequested(int)), SLOT(on_m_TabPanel_tabCloseRequested(int)));

	m_ProjectDock = new QDockWidget(tr("Project Files"), this);
	m_ProjectDock->setObjectName("m_ProjectDock");
	m_ProjectDock->setFeatures(QDockWidget::DockWidgetClosable);
	m_ProjectTree = new QAdvancedTreeWidget();
	m_ProjectTree->setParent(m_ProjectDock);

	m_ProjectTree->setObjectName("m_ProjectTree");
	m_ProjectTree->header()->hide();

	connect(m_ProjectTree, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, SLOT(on_m_ProjectTree_itemExpanded(QTreeWidgetItem*)));
	connect(m_ProjectTree, SIGNAL(itemCollapsed(QTreeWidgetItem*)), this, SLOT(on_m_ProjectTree_itemCollapsed(QTreeWidgetItem*)));
	connect(m_ProjectTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(on_m_ProjectTree_itemDoubleClicked(QTreeWidgetItem*, int)));
	connect(m_ProjectTree, SIGNAL(keyPress(QAdvancedTreeWidget*, QKeyEvent*)), this, SLOT(on_m_ProjectTree_keyPress(QAdvancedTreeWidget*, QKeyEvent*)));

	m_ProjectDock->setWidget(m_ProjectTree);

	addDockWidget(Qt::LeftDockWidgetArea,m_ProjectDock);

	m_StructureDock = new QDockWidget(tr("Structure"), this);
	m_StructureTree = new QTreeWidget(m_StructureDock);
	m_StructureTree->header()->hide();
	m_StructureDock->setWidget(m_StructureTree);

	addDockWidget(Qt::RightDockWidgetArea,m_StructureDock);

	m_BrowserDock = new QDockWidget(tr("Browser"), this);
	m_BrowserDock->setFixedHeight(150);
	m_Browser = new QWebView(m_BrowserDock);
	m_Browser->setGeometry(0, 0, 0, 150);
	m_BrowserDock->setWidget(m_Browser);
	m_Browser->load(QUrl());

	addDockWidget(Qt::BottomDockWidgetArea,m_BrowserDock);

	statusBar()->showMessage("");

	if (qApp->argc() > 1)
	{
		m_Project = QProject::LoadProjectFromFile(qApp->argv()[1]);
		if (m_Project == NULL)
		{
			qDebug("m_Project = null");
		} else {
			m_Project->setParent(this);
			m_Browser->load(QUrl(m_Project->getUrl()));

			UpdateProjectFileList("", NULL);
		}
	}
}

QAppMainWindow::~QAppMainWindow()
{

}

void QAppMainWindow::UpdateProjectFileList(QString level, QTreeWidgetItem* parentItem)
{// Todo: Please finish me!!
	QTreeWidgetItem* item;
	int c = 0;

	QList<QProjectFile> l_files = m_Project->getFolderItems(level);

	if (parentItem == NULL)
	{
		foreach(QProjectFile l_file, l_files)
		{
			if (m_ProjectTree->topLevelItemCount() <= c)
			{
				item = new QTreeWidgetItem(m_ProjectTree, 0);
				item->setText(0, l_file.m_FileName);
				if (l_file.m_IsFolder == true)
				{
					item->setIcon(0, QIcon(":/CFEditor/dir.gif"));
					item->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
					item->setData(0, Qt::UserRole, QVariant(true));
				}
				else
				{
					if (l_file.m_FileName.endsWith(".cfm"))
					{
						item->setIcon(0, QIcon(":/CFEditor/cfm_editor.gif"));
					}
					else if (l_file.m_FileName.endsWith(".cfc"))
					{
						item->setIcon(0, QIcon(":/CFEditor/cfc_editor.gif"));
					}
					else
					{
						item->setIcon(0, QIcon(":/CFEditor/file_obj.gif"));
					}
				}
			} else {
			}

			c++;
		}
	}
	else
	{
		foreach(QProjectFile l_file, l_files)
		{
			if (parentItem->childCount() <= c)
			{
				item = new QTreeWidgetItem(parentItem, 0);
				item->setText(0, l_file.m_FileName);
				if (l_file.m_IsFolder == true)
				{
					item->setIcon(0, QIcon(":/CFEditor/dir.gif"));
					item->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
					item->setData(0, Qt::UserRole, QVariant(true));
				}
				else
				{
					if (l_file.m_FileName.endsWith(".cfm"))
					{
						item->setIcon(0, QIcon(":/CFEditor/cfm_editor.gif"));
					}
					else if (l_file.m_FileName.endsWith(".cfc"))
					{
						item->setIcon(0, QIcon(":/CFEditor/cfc_editor.gif"));
					}
					else
					{
						item->setIcon(0, QIcon(":/CFEditor/file_obj.gif"));
					}
				}
			}
			else
			{
			}

			c++;
		}
	}
}

void QAppMainWindow::on_m_ProjectTree_itemExpanded(QTreeWidgetItem* item)
{
	if (item->data(0, Qt::UserRole) == true)
	{
		QString path = "";
		QTreeWidgetItem* currentitem = item;

		item->setIcon(0, QIcon(":/CFEditor/dir_open.gif"));
		do
		{
			path = currentitem->text(0) + m_Project->getDirSeparator() + path;
			currentitem = currentitem->parent();
		} while (currentitem != NULL);

	UpdateProjectFileList(path, item);
	}
}

void QAppMainWindow::on_m_ProjectTree_itemCollapsed(QTreeWidgetItem* item)
{
	if (item->data(0, Qt::UserRole) == true)
	{
		item->setIcon(0, QIcon(":/CFEditor/dir.gif"));
	}
}

void QAppMainWindow::on_m_ProjectTree_itemDoubleClicked(QTreeWidgetItem* item, int /*column*/)
{
	if (item->data(0, Qt::UserRole) == true)
		return;

	QString file = item->text(0);
	QTreeWidgetItem* currentitem = item;

	while(currentitem->parent() != NULL)
	{
		currentitem = currentitem->parent();
		file = currentitem->text(0) + m_Project->getDirSeparator() + file;
	}

	for(int c = 0; c < m_TabPanel->count(); c++)
	{
		if ((m_TabPanel->tabText(c) == file)||(m_TabPanel->tabText(c) == file + "*"))
		{
			m_TabPanel->setCurrentIndex(c);
			m_TabPanel->currentWidget()->setFocus();
			return;
		}
	}

	m_TabPanel->setTabsClosable(true);

	QCodeEditWidget* l_textEdit = new QCodeEditWidget();    //QAdvancedTextEdit* l_textEdit = new QAdvancedTextEdit();
	l_textEdit->setParent(m_TabPanel);                      //l_textEdit->setParent(m_TabPanel);
															//l_textEdit->setTabStopWidth(32);
															//l_textEdit->setWordWrapMode(QTextOption::NoWrap);
															//l_textEdit->setFont(QFont("Courier", 10, 0, false));
	l_textEdit->setText(m_Project->ReadFile(file));         //l_textEdit->setPlainText(m_Project->ReadFile(file));
															//connect(l_textEdit, SIGNAL(keyPress(QAdvancedTextEdit*, QKeyEvent*)), this, SLOT(on_m_TabPanel_Item_keyPress(QAdvancedTextEdit*, QKeyEvent*)));
															//connect(l_textEdit, SIGNAL(textChanged()), this, SLOT(on_m_TabPanel_Item_textChanged()));
	m_TabPanel->setCurrentIndex(m_TabPanel->addTab(l_textEdit, file));
	l_textEdit->setFocus();                                 //l_textEdit->setFocus();
	recolor();
}

void QAppMainWindow::on_m_ProjectTree_keyPress(QAdvancedTreeWidget* tree, QKeyEvent* e)
{
	//int a = e->key();
	QTreeWidgetItem* currentitem;
	QString newDir;
	QString oldFile, newFile;

	switch(e->key())
	{
	case 0x01000031: // F2
		if (tree->selectedItems().size() > 0)
		{
			currentitem = tree->selectedItems()[0];

			oldFile = currentitem->text(0);
			newFile = QInputDialog::getText(this, tr("Rename File"), tr("Enter new filename."), QLineEdit::Normal, oldFile);

			m_Project->RenameFile(oldFile, newFile);
			UpdateProjectFileList("", NULL);
		}
		break;
	case 0x01000034: // F5
		break;
	case 0x01000036: // F7
		newDir = QInputDialog::getText(this, tr("New Directorium"), tr("Enter name of new directorium."));
		break;
	case 0x01000006: // Insert

		newFile = QInputDialog::getText(this, tr("New File"), tr("Enter name of new file."));
		// Todo: First check if that file allready exists.

		if (tree->selectedItems().size() > 0)
		{
			currentitem = tree->selectedItems()[0];
			if (currentitem->data(0, Qt::UserRole) == true)
				newFile = currentitem->text(0) + m_Project->getDirSeparator() + newFile;

			while(currentitem->parent() != NULL)
			{
				currentitem = currentitem->parent();
				newFile = currentitem->text(0) + m_Project->getDirSeparator() + newFile;
			}
		}

		m_Project->WriteFile(newFile, QByteArray());
		UpdateProjectFileList("", NULL);
		break;
	case 0x01000007: // Delete

		if (tree->selectedItems().size() < 1)
			return;

		if (QMessageBox::warning(this, tr("Warning"), tr("Are you sure to delete the selected file"), QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
			return;

		currentitem = tree->selectedItems()[0];
		QString file = currentitem->text(0);
		while(currentitem->parent() != NULL)
		{
			currentitem = currentitem->parent();
			file = currentitem->text(0) + m_Project->getDirSeparator() + file;
		}

		m_Project->DeleteFile(file);
		UpdateProjectFileList("", NULL);
		break;
	}
}

/*void QAppMainWindow::on_m_TabPanel_Item_keyPress(QAdvancedTextEdit* edit, QKeyEvent* e)
{
	if (e->key() == 0x01000034) // F5
	{
		int index = m_TabPanel->indexOf(edit);
		QString panelText = m_TabPanel->tabText(index);

		if (panelText.endsWith("*"))
		{
			statusBar()->showMessage(tr("Saving file."));
			QCoreApplication::processEvents();
			QString newPanelText = panelText.left(panelText.size() - 1);
			m_Project->WriteFile(newPanelText, edit->toPlainText().toUtf8()); // Todo: needs complex-dynamic charset conversation
			m_TabPanel->setTabText(index, newPanelText);
			panelText = newPanelText;
			statusBar()->clearMessage();
			QCoreApplication::processEvents();
		}

		panelText = panelText.replace("\\", "/");
		QString fileUrl = m_Project->getUrl() + panelText;
		m_Browser->setUrl(QUrl(fileUrl));
	}
}*/

void QAppMainWindow::on_m_TabPanel_Item_textChanged()
{
	int index = m_TabPanel->currentIndex();
	QString panelText = m_TabPanel->tabText(index);

	if (!panelText.endsWith("*"))
	{
		m_TabPanel->setTabText(index, panelText + "*");
	}

	recolor();
}

void QAppMainWindow::recolor()
{
	QCFParser parser;
	QCodeEditWidget *edit = ((QCodeEditWidget*) m_TabPanel->currentWidget());
	QString panelText = edit->getText();
	parser.Parse(panelText);

	statusBar()->showMessage(parser.getError());
	QList<QCFParserTag> tags = parser.getTags();

	edit->clearFormatting();

	QCodeEditWidget::QCodeEditWidgetColorItem tagColor;

	tagColor.underline = QCodeEditWidget::UnderlineTypeNoUnderline;
	tagColor.underlineColor = QColor(255, 255, 255);

	foreach(QCFParserTag tag, tags)
	{
#ifdef QT_DEBUG
		if (tag.m_TagType == CommentTagType)
		{
			tagColor.backgroundColor = QColor(128, 128, 128);
			tagColor.foregroundColor = QColor(0, 0, 0);
		} else {
			tagColor.backgroundColor = QColor(255, 0, 0);
			tagColor.foregroundColor = QColor(0, 0, 0);
		}
#else
		if (tag.m_TagType == CommentTagType)
		{
			tagColor.backgroundColor = QColor(255, 255, 255);
			tagColor.foregroundColor = QColor(128, 128, 128);
		} else {
			tagColor.backgroundColor = QColor(255, 255, 255);
			tagColor.foregroundColor = QColor(128, 0, 0);
		}

#endif
		edit->addFormat(tag.m_Start, tag.m_Length, tagColor);

		colorElement(tag.m_Arguments);
	}

	edit->update();
}

void QAppMainWindow::colorElement(const QCFParserElement &p_Element)
{
	QCodeEditWidget *edit = ((QCodeEditWidget*) m_TabPanel->currentWidget());

	QCodeEditWidget::QCodeEditWidgetColorItem tagColor;

	tagColor.underline = QCodeEditWidget::UnderlineTypeNoUnderline;
	tagColor.underlineColor = QColor(255, 255, 255);
	tagColor.backgroundColor = QColor(255, 255, 255);
	tagColor.foregroundColor = QColor(0, 0, 0);

	switch (p_Element.m_Type)
	{
#ifdef QT_DEBUG
		case CFTagArguments:
			tagColor.backgroundColor = QColor(255, 128, 0);
			break;
		case CFTagArgument:
			tagColor.backgroundColor = QColor(255, 255, 0);
			break;
		case Variable:
			tagColor.backgroundColor = QColor(0, 0, 255);
			break;
		case Operator:
			tagColor.backgroundColor = QColor(0, 255, 255);
			break;
		case Number:
			tagColor.backgroundColor = QColor(128, 255, 128);
			break;
		case String:
			tagColor.backgroundColor = QColor(128, 0, 128);
			break;
		case Function:
			tagColor.backgroundColor = QColor(0, 128, 128);
			break;
		case Expression:
			tagColor.backgroundColor = QColor(192, 192, 192);
		default:
			break;
#else
		case CFTagArguments:
			//tagColor.foregroundColor = QColor(255, 128, 0);
			break;
		case CFTagArgument:
			tagColor.foregroundColor = QColor(255, 255, 0);
			break;
		case Variable:
			tagColor.foregroundColor = QColor(128, 128, 0);
			break;
		case Operator:
			tagColor.foregroundColor = QColor(0, 0, 0);
			break;
		case Number:
			tagColor.foregroundColor = QColor(0, 255, 0);
			break;
		case String:
			tagColor.foregroundColor = QColor(0, 0, 255);
			break;
		case Expression:
			tagColor.foregroundColor = QColor(92, 92, 0);
			break;
		default:
			break;
#endif
	}

	edit->addFormat(p_Element.m_Position, p_Element.m_Size, tagColor);

	foreach(QCFParserElement l_ChildElement, p_Element.m_ChildElements)
	{
		colorElement(l_ChildElement);
	}
}

void QAppMainWindow::on_m_TabPanel_currentChanged(int index)
{
	// Update Structure widget.
}

void QAppMainWindow::on_m_TabPanel_tabCloseRequested(int index)
{
	if (m_TabPanel->tabText(index).endsWith("*"))
	{
		QMessageBox::StandardButtons l_DlgResult = QMessageBox::question(this, tr("Question"), tr("Save file before close?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

		if (l_DlgResult == QMessageBox::Cancel)
		{
			return;
		}

		if (l_DlgResult == QMessageBox::Yes)
		{
			// Save
		}
	}
	m_TabPanel->removeTab(index);
}
