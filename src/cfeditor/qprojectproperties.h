#ifndef QPROJECTPROPERTIES_H
#define QPROJECTPROPERTIES_H

#include <QtGui>

#include "ui_qprojectproperties.h"

class QProjectProperties : public QDialog
{
	Q_OBJECT

public:
	QProjectProperties(QWidget *parent = 0, Qt::WFlags flags = 0);
	QString getConnectionString();
private slots:
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();
	void on_local_Browse_button_clicked();
	void on_ftp_Test_button_clicked();
	void on_ftp_Browse_button_clicked();
	void on_sftp_Test_button_clicked();
	void on_sftp_Browse_button_clicked();
	void on_rds_Test_button_clicked();
	void on_rds_Browse_button_clicked();
private:
	Ui::Dialog ui;
	QString m_ConnectionString;
};

#endif // QPROJECTPROPERTIES_H
