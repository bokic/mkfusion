#pragma once

#include <QDialog>
#include <QHash>

#include "ui_parsertest1.h"

class CFTest1 : public QDialog
{
    Q_OBJECT

public:
    CFTest1(QWidget *parent = 0, Qt::WindowFlags flags = 0);

private:
    void parseDir(const QString &dir);

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_clicked();

private:
    QHash<QString, int> m_tagsHash;
    QHash<QString, int> m_functionsHash;
    Ui::CFTest1Class ui;
};
