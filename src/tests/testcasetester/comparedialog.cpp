#include "comparedialog.h"
#include "ui_comparedialog.h"

CompareDialog::CompareDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompareDialog)
{
    ui->setupUi(this);
}

CompareDialog::~CompareDialog()
{
    delete ui;
}

void CompareDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void CompareDialog::setLeftText(const QByteArray &text)
{
    m_LeftText = text;
}

void CompareDialog::setRightText(const QByteArray &text)
{
    m_RightText = text;
}

QByteArray CompareDialog::filterChars(const QByteArray &text)
{
    QByteArray ret;

    for (int c = 0; c < text.length(); c++)
    {
        if (text[c] < 32)
        {
            ret += '.';
        }
        else
        {
            ret += text[c];
        }
    }

    return ret;
}

void CompareDialog::updateEditor(QPlainTextEdit *widget, const QByteArray &p_Text, const QByteArray &p_TextCompareTo)
{
    Q_UNUSED(p_TextCompareTo);

    QString text, hex;
    QByteArray row;
    int rowCount;

    rowCount = p_Text.size() / 8;
    if ((p_Text.size() % 8) != 0)
    {
        rowCount++;
    }

    for(int c = 0; c < rowCount; c++)
    {

        row = p_Text.mid(c * 8, 8);

        for(int c2 = 0; c2 < 8; c2++)
        {
            if (c2 < row.size())
            {
                hex = QString::number((uint)row[c2], 16);

                if (hex.length() == 1)
                {
                    hex = '0' + hex;
                }

                text.append(hex + ' ');
            }
            else
            {
                text.append("   ");
            }
        }

        text.append("| " + filterChars(row) + '\n');
    }

    widget->setPlainText(text);
}

void CompareDialog::updateEditors()
{
    updateEditor(ui->leftTextEdit, m_LeftText, m_RightText);
    updateEditor(ui->rightTextEdit, m_RightText, m_LeftText);
}
