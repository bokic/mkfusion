#include "qappmainwindow.h"
#include "ui_qappmainwindow.h"

#include "qprojectproperties.h"
#include "qcodeeditwidget.h"

QAppMainWindow::QAppMainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::QAppMainWindow),
	m_Project(NULL)
{
    ui->setupUi(this);

	if (qApp->argc() > 1)
	{
		LoadProject(qApp->argv()[1]);
	}
}

QAppMainWindow::~QAppMainWindow()
{
	if (m_Project != NULL)
	{
		delete m_Project;
		m_Project = NULL;
	}

    delete ui;
}

void QAppMainWindow::on_m_Browser_titleChanged(QString title)
{
	if (!title.isEmpty())
	{
		ui->m_BrowserDock->setWindowTitle(tr("Browser - ") + title);
	}
	else
	{
		ui->m_BrowserDock->setWindowTitle(tr("Browser"));
	}
}

void QAppMainWindow::on_action_New_activated()
{

}

void QAppMainWindow::on_action_Open_activated()
{

}

void QAppMainWindow::on_action_Close_activated()
{
}

void QAppMainWindow::on_action_Close_All_activated()
{

}

void QAppMainWindow::on_action_Save_activated()
{

}

void QAppMainWindow::on_action_Save_As_activated()
{

}

void QAppMainWindow::on_action_Save_All_activated()
{

}

void QAppMainWindow::on_action_Print_activated()
{

}

void QAppMainWindow::on_action_Print_Preview_activated()
{

}

void QAppMainWindow::on_action_Exit_activated()
{
	QApplication::quit();
}

void QAppMainWindow::on_action_Undo_activated()
{

}

void QAppMainWindow::on_action_Redo_activated()
{

}

void QAppMainWindow::on_action_Cut_activated()
{

}

void QAppMainWindow::on_action_Copy_activated()
{

}

void QAppMainWindow::on_action_Paste_activated()
{

}

void QAppMainWindow::on_action_Select_All_activated()
{

}

void QAppMainWindow::on_action_Find_activated()
{

}

void QAppMainWindow::on_action_Goto_Line_activated()
{

}

void QAppMainWindow::on_action_Open_Project_activated()
{
	QString l_FileName = QFileDialog::getOpenFileName(this, tr("Open Project"), "", tr("ColdFusion project (*.cfes)"));

	if (!l_FileName.isEmpty())
	{
		if (m_Project != NULL)
		{
			on_action_Close_Project_activated(); // m_Project is deleted/nulled here

			QApplication::processEvents();
		}

		m_Project = QProject::LoadProjectFromFile(l_FileName);

        if (m_Project != NULL)
        {
            m_Project->setParent(this);

            ui->m_Browser->setUrl(QUrl(m_Project->getUrl()));

            UpdateProjectFileList();
        }
        else
        {
            statusBar()->showMessage(tr("Could't load project file."));
        }
	}
}

void QAppMainWindow::on_action_Save_Project_activated()
{
	QString l_FileName;

	if (m_ProjectFileName.isEmpty())
	{
		QString l_FileName = QFileDialog::getSaveFileName(this, tr("Save Project"), "", tr("ColdFusion project (*.cfes)"));

		if (l_FileName.isEmpty())
		{
			return;
        }

		QApplication::processEvents();
	}

	l_FileName = m_ProjectFileName;
	on_action_Close_Project_activated();
	m_ProjectFileName = l_FileName;

	m_Project = QProject::LoadProjectFromFile(l_FileName);
	m_ProjectFileName = l_FileName;

    if (m_Project != NULL)
    {
        m_Project->setParent(this);

        ui->m_Browser->setUrl(QUrl(m_Project->getUrl()));

        UpdateProjectFileList();
    }
    else
    {
        statusBar()->showMessage(tr("Could't load project file."));
    }
}

void QAppMainWindow::on_action_Close_Project_activated()
{
	if (m_Project != NULL)
	{
		delete m_Project;
		m_Project = NULL;
	}

	while (ui->centralwidget->count() > 0)
	{
		ui->centralwidget->removeTab(0);
	}

	ui->m_ProjectTree->clear();

	ui->m_StructureTree->clear();

	ui->m_Browser->setUrl(QUrl());

	m_ProjectFileName.clear();
}

void QAppMainWindow::on_action_Project_Properties_activated()
{
	// TODO: Asks should open files be closed and saved.

	QProjectProperties l_ProjectProperties;

    l_ProjectProperties.fillDialog(m_Project);

	if (l_ProjectProperties.exec() == QDialog::Accepted)
	{
		on_action_Close_Project_activated();

		m_Project = QProject::LoadProjectFromText(l_ProjectProperties.getConnectionString());

		if (m_Project != NULL)
		{
			m_Project->setParent(this);

			ui->m_Browser->setUrl(QUrl(m_Project->getUrl()));

			ui->m_ProjectTree->clear();
			UpdateProjectFileList();

			ui->action_Save_Project->setEnabled(true);
		}
		else
		{
			statusBar()->showMessage(tr("Could't load project file."));
		}
	}
}

void QAppMainWindow::on_action_Check_Project_activated()
{

}

void QAppMainWindow::on_action_Full_Screen_activated()
{
	setWindowState(windowState() ^ Qt::WindowFullScreen);
}

void QAppMainWindow::on_action_ColdFusion_Help_activated()
{

}

void QAppMainWindow::on_action_About_activated()
{

}

void QAppMainWindow::LoadProject(const QString& p_File)
{
	if (m_Project)
	{
		delete m_Project;
		m_Project = NULL;
	}

	m_Project = QProject::LoadProjectFromFile(p_File);

	if (m_Project != NULL)
	{
		m_Project->setParent(this);

		ui->m_Browser->setUrl(QUrl(m_Project->getUrl()));

		UpdateProjectFileList();
	}
	else
	{
		statusBar()->showMessage(tr("Could't load project file."));
	}
}

void QAppMainWindow::UpdateProjectFileList(const QString& level, QTreeWidgetItem* parentItem)
{// Todo: Please finish me!! Bad coding style...
	QTreeWidgetItem* item;
	int c = 0;

	QList<QProjectFile> l_files = m_Project->getFolderItems(level);

	if (parentItem == NULL)
	{
		foreach(QProjectFile l_file, l_files)
		{
			if (ui->m_ProjectTree->topLevelItemCount() <= c)
			{
				item = new QTreeWidgetItem(ui->m_ProjectTree, 0);
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

void QAppMainWindow::on_m_ProjectTree_itemDoubleClicked(QTreeWidgetItem* item, int column)
{
	Q_UNUSED(column);

	if (item->data(0, Qt::UserRole) == true)
		return;

	QString file = item->text(0);
	QTreeWidgetItem* currentitem = item;

	while(currentitem->parent() != NULL)
	{
		currentitem = currentitem->parent();
		file = currentitem->text(0) + m_Project->getDirSeparator() + file;
	}

	for(int c = 0; c < ui->centralwidget->count(); c++)
	{
		if ((ui->centralwidget->tabText(c) == file)||(ui->centralwidget->tabText(c) == file + "*"))
		{
			ui->centralwidget->setCurrentIndex(c);
			ui->centralwidget->currentWidget()->setFocus();
			return;
		}
	}

	ui->centralwidget->setTabsClosable(true);

	QCodeEditWidget* l_textEdit = new QCodeEditWidget();

    QFileInfo finfo(file);
    l_textEdit->setFileExtension(finfo.suffix());

    connect(l_textEdit, SIGNAL(on_key_press(QKeyEvent *)), this, SLOT(onmy_textedit_key_press(QKeyEvent *)));
    connect(l_textEdit, SIGNAL(on_text_change()), this, SLOT(onmy_textedit_text_change()));
    connect(l_textEdit, SIGNAL(on_breakpoint_change(int)), this, SLOT(onmy_textedit_breakpoint_change(int)));

	l_textEdit->setParent(ui->centralwidget);

    l_textEdit->setText(m_Project->ReadFile(file));

	ui->centralwidget->setCurrentIndex(ui->centralwidget->addTab(l_textEdit, file));
	l_textEdit->setFocus();

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
			UpdateProjectFileList();
		}
		break;
	case 0x01000034: // F5
		break;
	case 0x01000036: // F7
		newDir = QInputDialog::getText(this, tr("New Directorium"), tr("Enter name of new directorium."));

		if (!newDir.isEmpty())
		{
			m_Project->CreateDir(newDir);

			UpdateProjectFileList();
		}

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

		UpdateProjectFileList();
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
		UpdateProjectFileList();
		break;
	}
}

void QAppMainWindow::on_centralwidget_tabCloseRequested(int index)
{
	if (ui->centralwidget->tabText(index).endsWith("*"))
	{
		QMessageBox::StandardButtons l_DlgResult = QMessageBox::question(this, tr("Question"), tr("Save file before close?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

		if (l_DlgResult == QMessageBox::Cancel)
		{
			return;
		}

		if (l_DlgResult == QMessageBox::Yes)
		{
			QString l_Filename = ui->centralwidget->tabText(index);
			l_Filename = l_Filename.left(l_Filename.length() - 1);

			QByteArray l_FileContent = ((QCodeEditWidget*)ui->centralwidget->currentWidget())->getText().toUtf8();

			statusBar()->showMessage(tr("Saving file.")); QApplication::processEvents();
			m_Project->WriteFile(l_Filename, l_FileContent);
			statusBar()->clearMessage(); QApplication::processEvents();
		}
	}

	ui->centralwidget->removeTab(index);
}

/*void QAppMainWindow::on_centralwidget_Item_textChanged()
{
    int index = ui->centralwidget->currentIndex();
    QString panelText = ui->centralwidget->tabText(index);

    if (!panelText.endsWith("*"))
    {
        ui->centralwidget->setTabText(index, panelText + "*");
    }

    recolor();
}*/

void QAppMainWindow::on_centralwidget_currentChanged(int index)
{
	Q_UNUSED(index);

	// Update Structure widget.
}

void QAppMainWindow::onmy_textedit_key_press(QKeyEvent *event)
{
	if ((event->key() == Qt::Key_F5)&&(event->modifiers() == Qt::NoModifier))
	{
		int index = ui->centralwidget->currentIndex();
		QString panelText = ui->centralwidget->tabText(index);

		if (!panelText.isEmpty())
		{
			if (panelText.endsWith("*"))
			{
				statusBar()->showMessage(tr("Saving file.")); QApplication::processEvents();

				panelText = panelText.left(panelText.size() - 1);
				m_Project->WriteFile(panelText, ((QCodeEditWidget*)sender())->getText().toUtf8()); // Todo: needs complex-dynamic charset conversation
				ui->centralwidget->setTabText(index, panelText);

				statusBar()->clearMessage(); QApplication::processEvents();
			}

			ui->m_Browser->setUrl(QUrl(m_Project->getUrl() + panelText));
		}
	}
}

void QAppMainWindow::onmy_textedit_text_change()
{
	int index = ui->centralwidget->currentIndex();
	QString panelText = ui->centralwidget->tabText(index);

	if (!panelText.endsWith("*"))
	{
		ui->centralwidget->setTabText(index, panelText + "*");
		ui->action_Save->setEnabled(true);
		ui->action_Save_All->setEnabled(true);
	}
}

void QAppMainWindow::onmy_textedit_breakpoint_change(int line)
{
	QCodeEditWidget *edit = ((QCodeEditWidget*) sender());

    if (edit->breakpoint(line) != QCodeEditWidget::BreakpointTypeBreakpoint)
	{
        edit->setBreakpoint(line, QCodeEditWidget::BreakpointTypeBreakpoint);
	}
	else
	{
        edit->setBreakpoint(line, QCodeEditWidget::BreakpointTypeNoBreakpoint);
	}
}

void QAppMainWindow::recolor()
{
	QCodeEditWidget *edit = ((QCodeEditWidget*) ui->centralwidget->currentWidget());
	QString panelText = edit->getText();

/*	QCFParser parser;
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
		tagColor.index = tag.m_Start;
		tagColor.length = tag.m_Length;
		edit->addFormat(tagColor);

		colorElement(tag.m_Arguments);
    }*/

	edit->update();
}

/*void QAppMainWindow::colorElement(const QCFParserElement &p_Element)
{
	QCodeEditWidget *edit = ((QCodeEditWidget*) ui->centralwidget->currentWidget());

    QTextParser::QTextParserColorItem tagColor;

    tagColor.underline = QTextParser::UnderlineTypeNoUnderline;
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

	tagColor.index = p_Element.m_Position;
	tagColor.length = p_Element.m_Size;
    //edit->addFormat(tagColor);

	foreach(QCFParserElement l_ChildElement, p_Element.m_ChildElements)
	{
		colorElement(l_ChildElement);
	}
}*/
