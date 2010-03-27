#ifndef COMPAREDIALOG_H
#define COMPAREDIALOG_H

#include <QPlainTextEdit>
#include <QDialog>

namespace Ui {
    class CompareDialog;
}

class CompareDialog : public QDialog {
    Q_OBJECT
public:
    CompareDialog(QWidget *parent = 0);
    ~CompareDialog();

	void setLeftText(const QByteArray&);
	void setRightText(const QByteArray&);
	void updateEditors();
protected:
    void changeEvent(QEvent *e);

private:
	static QByteArray filterChars(const QByteArray&);
	static void updateEditor(QPlainTextEdit*, const QByteArray&, const QByteArray&);
	Ui::CompareDialog *ui;

	QByteArray m_LeftText;
	QByteArray m_RightText;
private slots:
};

#endif // COMPAREDIALOG_H
