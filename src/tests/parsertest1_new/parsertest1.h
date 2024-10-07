#pragma once

#include <QDialog>
#include <QMultiHash>

#include "ui_parsertest1.h"

class CFTest1 : public QDialog
{
    Q_OBJECT

public:
    CFTest1(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::Widget);

private:
    void parseDir(const QString &dir);

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_clicked();

private:
    QMultiHash<QString, int> m_tagsHash;
    QMultiHash<QString, int> m_functionsHash;
    Ui::CFTest1Class ui;
};
