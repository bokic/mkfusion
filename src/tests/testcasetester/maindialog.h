#pragma once

#include <QDialog>
#include <QListWidgetItem>

namespace Ui
{
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = nullptr);
    virtual ~Dialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Dialog *ui;

private slots:
    void on_urlslist_itemDoubleClicked(QListWidgetItem *item);
    void on_start_clicked();
};
