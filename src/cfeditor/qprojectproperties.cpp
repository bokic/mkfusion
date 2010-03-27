#include "qprojectproperties.h"
#include "qrdsserver.h"
#include "qfileioservice.h"
#include <QMessageBox>
#include <QByteArray>

QProjectProperties::QProjectProperties(QWidget *parent, Qt::WFlags flags): QDialog(parent, flags)
{
	ui.setupUi(this);

	setModal(true);
}

void QProjectProperties::on_RDS_Test_pushButton_clicked()
{
	QRDSServer rdsServer;

	ui.RDS_Test_pushButton->setEnabled(false);
	QCoreApplication::processEvents();

	rdsServer.setHostName(ui.RDS_Host_lineEdit->text());
	rdsServer.setUserName(ui.RDS_Username_lineEdit->text());
	rdsServer.setPassword(ui.RDS_Password_lineEdit->text().toAscii());

	QFileIOService fileIO;
	QMap<QString, QString> map;
	QByteArray ba = fileIO.ExecuteRDSCommand(rdsServer, QFileIOService::FileGetRootDirCommand, map);

	if ((ba.size() > 0)&&(ba[0] != '-'))
		QMessageBox::information(this, tr("Information"), tr("RDS login was successfull."));
	else
		QMessageBox::warning(this, tr("Warning"), tr("RDS login was not successfull."));

	ui.RDS_Test_pushButton->setEnabled(true);
}

void QProjectProperties::on_buttonBox_accepted()
{

}
