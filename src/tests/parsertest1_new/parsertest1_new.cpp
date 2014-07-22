#include "parsertest1_new.h"
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

    QTextParser::loadParserDefinitionsFromDir(".");
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
        QFileInfo file = files.at(c);

        if (file.isDir() == true)
        {
            parseDir(file.absoluteFilePath());
        }
        else
        {
            QString itemFileName = QDir::toNativeSeparators(file.filePath());
            QListWidgetItem *lastItem = new QListWidgetItem(itemFileName);

            this->setWindowTitle("CFTest1");
            qApp->processEvents();

            ui.listWidget->addItem(lastItem);
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
            const QString key = keys.at(c);

            ui.listWidget->addItem(new QListWidgetItem(key + " = " + QString::number(m_hash[key])));
        }

        ui.listWidget->scrollToBottom();
    }
}

void CFTest1::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString file = item->text();

    /*int err = file.indexOf(" error");
    if (err > -1)
    {
        file = file.left(err);
    }*/

    if (QFile::exists(file))
    {
        QDetail detailForm(this);

        detailForm.setFileForParsing(file);
        detailForm.setModal(true);

        detailForm.exec();
    }
}
