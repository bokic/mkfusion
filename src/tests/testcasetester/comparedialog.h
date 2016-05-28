#pragma once

#include <QPlainTextEdit>
#include <QDialog>

namespace Ui
{
class CompareDialog;
}

class CompareDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CompareDialog(QWidget *parent = 0);
    virtual ~CompareDialog();

    void setLeftText(const QByteArray &text);
    void setRightText(const QByteArray &text);
    void updateEditors();
protected:
    void changeEvent(QEvent *e);

private:
    static QByteArray filterChars(const QByteArray &text);
    static void updateEditor(QPlainTextEdit *, const QByteArray &, const QByteArray &);
    Ui::CompareDialog *ui;

    QByteArray m_LeftText;
    QByteArray m_RightText;
};
