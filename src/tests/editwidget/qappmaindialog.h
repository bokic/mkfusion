#pragma once

#include <QDialog>

namespace Ui
{
class QAppMainDialog;
}

class QAppMainDialog : public QDialog
{
    Q_OBJECT
public:
    explicit QAppMainDialog(QWidget *parent = nullptr);
    virtual ~QAppMainDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::QAppMainDialog *ui;
};
