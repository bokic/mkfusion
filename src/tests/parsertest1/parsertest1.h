#ifndef PARSERTEST1_H
#define PARSERTEST1_H

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
	void parseDir(QString);
	QHash<QString, int> m_hash;
private:
	Ui::CFTest1Class ui;

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem* item);
 void on_pushButton_clicked();
};

#endif // CFTEST1_H
