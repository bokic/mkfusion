#include "parsertest1.h"
#include "qcfparser.h"
#include "qdetail.h"

#include <QtGui/QListWidgetItem>
#include <QtCore/QFileInfoList>
#include <QtGui/QColor>
#include <QtCore/QHash>
#include <QtGui/QFileDialog>
#include <QtCore/QDir>

CFTest1::CFTest1(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);
}

CFTest1::~CFTest1()
{

}

void CFTest1::parseDir(QString p_dir)
{
	QDir dir(p_dir);

	dir.setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
	dir.setSorting(QDir::DirsFirst | QDir::Name);
	QStringList filters;
	filters << "*.cfm" << "*.cfc";
    dir.setNameFilters(filters);
	QFileInfoList files = dir.entryInfoList();

	for (int c = 0; c < files.size(); c++)
	{
		QFileInfo item = files.at(c);
		if (item.isDir() == true)
		{
			parseDir(item.absoluteFilePath());
		}
		else
		{
			QString itemFileName = QDir::toNativeSeparators(item.filePath());
			QListWidgetItem* lastItem = new QListWidgetItem(itemFileName);

			QFile file(itemFileName);
			file.open(QIODevice::ReadOnly);
			QString fileContent = file.readAll();
			file.close();

			QList<QCFParserTag> l_tags;
			QCFParser* parser = new QCFParser();

			this->setWindowTitle("CFTest1 - " + item.fileName());qApp->processEvents();

			if (parser->Parse(fileContent) != NoError)
			{
				this->setWindowTitle("CFTest1");qApp->processEvents();

				lastItem->setText(lastItem->text() + " error: " + parser->getError() + ", at position: " + QString::number(parser->getErrorPosition()));
				lastItem->setBackgroundColor(QColor(255, 0, 0));
			}
			else
			{
				this->setWindowTitle("CFTest1");qApp->processEvents();

				if (parser->BuildTagTree() != NoError)
				{
				lastItem->setText(lastItem->text() + " error: " + parser->getError() + ", at position: " + QString::number(parser->getErrorPosition()));
				lastItem->setBackgroundColor(QColor(0, 255, 255));
				}
				else
				{
					l_tags = parser->getTags();
					for (int c = 0; c < l_tags.size(); c++)
					{
						if (l_tags[c].m_TagType == CFTagType)
						{
							m_hash[l_tags[c].m_Name.toLower()]++;
						}
					}
				}
			}

			ui.listWidget->addItem(lastItem);
			delete parser;
		}
	}
}

void CFTest1::on_pushButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::DirectoryOnly);

    if (dialog.exec() == QDialog::Accepted)
    {
        ui.listWidget->clear();
        m_hash.clear();

        parseDir(dialog.directory().absolutePath());

        ui.listWidget->addItem(new QListWidgetItem("-------------------- CF Tags stats -------------------------"));

        QStringList keys = m_hash.uniqueKeys();
        keys.sort();

        for (int c = 0; c < keys.size(); c++)
        {
            ui.listWidget->addItem(new QListWidgetItem(keys[c] + " = " + QString::number(m_hash[keys[c]])));
        }

        ui.listWidget->scrollToBottom();
    }
}

void CFTest1::on_listWidget_itemDoubleClicked(QListWidgetItem* item)
{
    QString file = item->text();

    int err = file.indexOf(" error");
    if (err > -1)
    {
        file = file.left(err);
    }

#ifdef Q_WS_WIN
	if ((file.count() > 3)&&(file.at(1) == ':')&&(file.at(2) == QDir::separator()))
	{
		QDetail detailForm(this);

		detailForm.setFileForParsing(file);
		detailForm.setModal(true);

		detailForm.exec();
	}
#else
	if (file.at(0) == QDir::separator())
	{
		QDetail detailForm(this);

		detailForm.setFileForParsing(file);
		detailForm.setModal(true);

		detailForm.exec();
	}
#endif
}
