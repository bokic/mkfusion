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
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void CompareDialog::setLeftText(const QByteArray &p_Text)
{
	m_LeftText = p_Text;
}

void CompareDialog::setRightText(const QByteArray &p_Text)
{
	m_RightText = p_Text;
}

QByteArray CompareDialog::filterChars(const QByteArray &p_Text)
{
	QByteArray ret;

	for (int c = 0; c < p_Text.length(); c++)
	{
		if ((p_Text[c] < 32)||(p_Text[c] < 0))
		{
			ret += '.';
		}
		else
		{
			ret += p_Text[c];
		}
	}

	return ret;
}

void CompareDialog::updateEditor(QPlainTextEdit* p_TextEdit, const QByteArray &p_Text, const QByteArray &p_TextCompareTo)
{
	QString l_Text;

	int l_rows = p_Text.size() / 8;
	if ((p_Text.size() % 8) != 0)
	{
		l_rows++;
	}

	for(int c = 0; c < l_rows; c++)
	{
		QByteArray l_rowBA;

		l_rowBA = p_Text.mid(c * 8, 8);

		for(int c2 = 0; c2 < 8; c2++)
		{
			if (c2 < l_rowBA.size())
			{
				QString l_hex = QString::number(l_rowBA[c2], 16);
				if (l_hex.length() == 1)
				{
					l_hex = '0' + l_hex;
				}

				l_Text += l_hex + ' ';
			}
			else
			{
				l_Text += "   ";
			}
		}
		l_Text += "| " + filterChars(l_rowBA) + '\n';
	}


	p_TextEdit->setPlainText(l_Text);
}

void CompareDialog::updateEditors()
{
	updateEditor(ui->leftTextEdit, m_LeftText, m_RightText);
	updateEditor(ui->rightTextEdit, m_RightText, m_LeftText);
}
