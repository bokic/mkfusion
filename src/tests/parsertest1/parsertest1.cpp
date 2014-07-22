#include "parsertest1.h"
#include "qcfparser.h"
#include "qdetail.h"

#include <QListWidgetItem>
#include <QFileInfoList>
#include <QFileDialog>
#include <QColor>
#include <QHash>
#include <QDir>

CFTest1::CFTest1(QWidget *parent, Qt::WindowFlags flags)
    : QDialog(parent, flags)
{
    ui.setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);
}

CFTest1::~CFTest1()
{

}

void CFTest1::findFunctionsRecursive(const QCFParserElement &parserElement)
{
    if (parserElement.m_Type == Function)
    {
        m_functionsHash[parserElement.m_Text.toLower()]++;
    }

    for(const QCFParserElement &child : parserElement.m_ChildElements)
    {
        findFunctionsRecursive(child);
    }
}

void CFTest1::parseDir(const QString &p_dir)
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
            QCFParser parser;

            this->setWindowTitle("CFTest1 - " + item.fileName()); qApp->processEvents();

            if (parser.Parse(fileContent) != NoError)
            {
                this->setWindowTitle("CFTest1"); qApp->processEvents();

                lastItem->setText(lastItem->text() + " error: " + parser.getError() + ", at position: " + QString::number(parser.getErrorPosition()));
                lastItem->setBackgroundColor(QColor(255, 0, 0));
            }
            else
            {
                this->setWindowTitle("CFTest1"); qApp->processEvents();

                if (parser.BuildTagTree() != NoError)
                {
                    lastItem->setText(lastItem->text() + " error: " + parser.getError() + ", at position: " + QString::number(parser.getErrorPosition()));
                    lastItem->setBackgroundColor(QColor(0, 255, 255));
                }
                else
                {
                    l_tags = parser.getTags();
                    for(const QCFParserTag &l_tag : l_tags)
                    {
                        if (l_tag.m_TagType == CFTagType)
                        {
                            m_tagsHash[l_tag.m_Name.toLower()]++;

                            findFunctionsRecursive(l_tag.m_Arguments);
                        }
                    }
                }
            }

            ui.listWidget->addItem(lastItem);
        }
    }
}

void CFTest1::on_pushButton_clicked()
{
    QFileDialog dialog(this);
    QStringList keys;

    dialog.setFileMode(QFileDialog::DirectoryOnly);

    if (dialog.exec() == QDialog::Accepted)
    {
        ui.listWidget->clear();
        m_tagsHash.clear();
        m_functionsHash.clear();

        parseDir(dialog.directory().absolutePath());

        ui.listWidget->addItem(new QListWidgetItem("-------------------- CF Tags stats -------------------------"));

        keys = m_tagsHash.uniqueKeys();
        keys.sort();

        for (int c = 0; c < keys.size(); c++)
        {
            ui.listWidget->addItem(new QListWidgetItem(keys[c] + " = " + QString::number(m_tagsHash[keys[c]])));
        }

        ui.listWidget->addItem(new QListWidgetItem("-------------------- CF Functions stats -------------------------"));

        keys = m_functionsHash.uniqueKeys();
        keys.sort();

        for (int c = 0; c < keys.size(); c++)
        {
            ui.listWidget->addItem(new QListWidgetItem(keys[c] + " = " + QString::number(m_functionsHash[keys[c]])));
        }

        ui.listWidget->scrollToBottom();
    }
}

void CFTest1::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString file = item->text();

    int err = file.indexOf(" error");
    if (err > -1)
    {
        file = file.left(err);
    }

#ifdef Q_OS_WIN
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
