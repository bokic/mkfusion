#ifndef PARSERTEST1_H
#define PARSERTEST1_H

#include "qcfparser.h"

#include <QDialog>
#include <QHash>

#include "ui_parsertest1.h"

class CFTest1 : public QDialog
{
    Q_OBJECT

public:
    CFTest1(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    virtual ~CFTest1();
private:
    void findFunctionsRecursive(const QCFParserElement &parserElement);
    void parseDir(const QString &p_dir);

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_clicked();

private:
    QHash<QString, int> m_tagsHash;
    QHash<QString, int> m_functionsHash;
    Ui::CFTest1Class ui;
};

#endif // CFTEST1_H
