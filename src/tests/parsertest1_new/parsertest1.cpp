#include "parsertest1.h"
#include "qtextparser.h"
#include "qdetail.h"

#include <QListWidgetItem>
#include <QFileInfoList>
#include <QFileDialog>
#include <QColor>
#include <QDir>

CFTest1::CFTest1(QWidget *parent, Qt::WindowFlags flags)
    : QDialog(parent, flags)
{
    ui.setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);

    QTextParser::loadParserDefinitionsFromDir("../src/textparser");
}

void CFTest1::parseDir(const QString &dir)
{
    QDir d(dir);

    d.setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
    d.setSorting(QDir::DirsFirst | QDir::Name);
    QStringList filters;
    filters << "*.cfm" << "*.cfc";
    d.setNameFilters(filters);
    QFileInfoList files = d.entryInfoList();

    for (int c = 0; c < files.size(); c++)
    {
        QFileInfo fileinfo = files.at(c);

        if (fileinfo.isDir() == true)
        {
            parseDir(fileinfo.absoluteFilePath());
        }
        else
        {
            QString itemFileName = QDir::toNativeSeparators(fileinfo.filePath());
            QListWidgetItem *lastItem = new QListWidgetItem(itemFileName);
            QTextParser parser;

            this->setWindowTitle("CFTest1 - " + fileinfo.fileName()); qApp->processEvents();

            parser.parseFile(fileinfo.absoluteFilePath());

            this->setWindowTitle("CFTest1"); qApp->processEvents();

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

        for (const QString &key: keys)
        {
            ui.listWidget->addItem(new QListWidgetItem(key + " = " + QString::number(m_tagsHash[key])));
        }

        ui.listWidget->addItem(new QListWidgetItem("-------------------- CF Functions stats -------------------------"));

        keys = m_functionsHash.uniqueKeys();
        keys.sort();

        for (const QString &key: keys)
        {
            ui.listWidget->addItem(new QListWidgetItem(key + " = " + QString::number(m_functionsHash[key])));
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
