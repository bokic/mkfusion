#ifndef QPROJECTPROPERTIES_H
#define QPROJECTPROPERTIES_H

#include <QtGui>

#include "ui_qprojectproperties.h"

class QProjectProperties : public QDialog
{
	Q_OBJECT

public:
	QProjectProperties(QWidget *parent = 0, Qt::WFlags flags = 0);
	//QString GetURL();
	//bool GetStartImmedietely();
private slots:
	void on_buttonBox_accepted();
	void on_RDS_Test_pushButton_clicked();
	//void on_dialogButtonBox_rejected();
private:
	Ui::Dialog ui;
};

#endif // QPROJECTPROPERTIES_H
