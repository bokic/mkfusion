#include "qprojectproperties.h"
#include "qrdsserver.h"
#include "qfileioservice.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QByteArray>
#include <QDir>

// SFTP
#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <fcntl.h>


QProjectProperties::QProjectProperties(QWidget *parent, Qt::WFlags flags): QDialog(parent, flags)
{
	ui.setupUi(this);

	setModal(true);
}

QString QProjectProperties::getConnectionString()
{
	return m_ConnectionString;
}

void QProjectProperties::fillDialog(QProject *project)
{
    if (project->getType() != QProject::BlankProject)
    {
        switch(project->getType())
        {
        case QProject::LocalProject:
            ui.tabWidget->setCurrentIndex(0);
            ui.local_ProjectPath_lineEdit->setText(project->getPath());
            ui.local_URL_lineEdit->setText(project->getUrl());
            break;
        case QProject::FTPProject:
            ui.tabWidget->setCurrentIndex(1);
            ui.ftp_Host_lineEdit->setText(((QFTPProject*)project)->getPath());
            ui.ftp_Port_spinBox->setValue(((QFTPProject*)project)->getPort());
            ui.ftp_Username_lineEdit->setText(((QFTPProject*)project)->getUsername());
            ui.ftp_Password_lineEdit->setText(((QFTPProject*)project)->getPassword());
            ui.ftp_ProjectPath_lineEdit->setText(project->getPath());
            ui.ftp_URL_lineEdit->setText(project->getUrl());
            break;
        case QProject::SFTPProject:
            ui.tabWidget->setCurrentIndex(2);
            ui.sftp_Host_lineEdit->setText(((QFTPProject*)project)->getPath());
            ui.sftp_Port_spinBox->setValue(((QFTPProject*)project)->getPort());
            ui.sftp_Username_lineEdit->setText(((QFTPProject*)project)->getUsername());
            ui.sftp_Password_lineEdit->setText(((QFTPProject*)project)->getPassword());
            ui.sftp_ProjectPath_lineEdit->setText(project->getPath());
            ui.sftp_URL_lineEdit->setText(project->getUrl());
            break;
        case QProject::RDSProject:
            ui.tabWidget->setCurrentIndex(3);
            ui.rds_Host_lineEdit->setText(((QFTPProject*)project)->getPath());
            ui.rds_Port_spinBox->setValue(((QFTPProject*)project)->getPort());
            ui.rds_Username_lineEdit->setText(((QFTPProject*)project)->getUsername());
            ui.rds_Password_lineEdit->setText(((QFTPProject*)project)->getPassword());
            ui.rds_ProjectPath_lineEdit->setText(project->getPath());
            ui.rds_URL_lineEdit->setText(project->getUrl());
            break;
        default:;
        }
    }
}

void QProjectProperties::on_local_Browse_button_clicked()
{
	QString l_dirName = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if (!l_dirName.isEmpty())
	{
		l_dirName = QDir::toNativeSeparators(l_dirName);

		ui.local_ProjectPath_lineEdit->setText(l_dirName);
	}
}

void QProjectProperties::on_ftp_Test_button_clicked()
{
	qDebug() << "void on_ftp_Test_button_clicked()";
}

void QProjectProperties::on_ftp_Browse_button_clicked()
{
	qDebug() << "void on_ftp_Browse_button_clicked()";
}

void QProjectProperties::on_sftp_Test_button_clicked()
{
	ssh_session l_SSHSession = ssh_new();

	ui.sftp_Test_button->setEnabled(false); QApplication::processEvents();

	ssh_options_set(l_SSHSession, SSH_OPTIONS_HOST, ui.sftp_Host_lineEdit->text().toLatin1());

	if (ui.sftp_Port_spinBox->value() != 0)
	{
		ssh_options_set(l_SSHSession, SSH_OPTIONS_PORT_STR, QString::number(ui.sftp_Port_spinBox->value()).toAscii());
	}

	if (ssh_connect(l_SSHSession) == 0)
	{
		if (ssh_userauth_password(l_SSHSession, ui.sftp_Username_lineEdit->text().toAscii(), ui.sftp_Password_lineEdit->text().toAscii()) == 0)
		{
			QMessageBox::information(this, tr("Information"), tr("Login successfull."));
		}
		else
		{
			QMessageBox::warning(this, tr("Error"), tr("Wrong username or password."));
		}
	}
	else
	{
		QMessageBox::warning(this, tr("Error"), tr("Can't connect to host."));
	}

	ui.sftp_Test_button->setEnabled(true); QApplication::processEvents();

	ssh_free(l_SSHSession);
}

void QProjectProperties::on_sftp_Browse_button_clicked()
{
	qDebug() << "void on_sftp_Browse_button_clicked()";
}

void QProjectProperties::on_rds_Test_button_clicked()
{
	QRDSServer l_RDSServer;

	ui.rds_Test_button->setEnabled(false); QApplication::processEvents();

	l_RDSServer.setHostName(ui.rds_Host_lineEdit->text());
	l_RDSServer.setUserName(ui.rds_Username_lineEdit->text());
	l_RDSServer.setPassword(ui.rds_Password_lineEdit->text().toAscii());

	QFileIOService l_FileIO;
	QMap<QString, QString> l_map;
	QByteArray l_ba = l_FileIO.ExecuteRDSCommand(l_RDSServer, QFileIOService::FileGetRootDirCommand, l_map);

	if ((l_ba.left(2) == "1:"))// TODO: Bad check. Example: 1:16:/opt/coldfusion9
	{
		QMessageBox::information(this, tr("Information"), tr("RDS login was successfull."));
	}
	else
	{
		QMessageBox::warning(this, tr("Warning"), tr("RDS login was not successfull."));
	}

	ui.rds_Test_button->setEnabled(true);
}

void QProjectProperties::on_rds_Browse_button_clicked()
{
	qDebug() << "void on_rds_Browse_button_clicked()";
}

void QProjectProperties::on_buttonBox_accepted()
{
	switch(ui.tabWidget->currentIndex())
	{
	case 0:
		m_ConnectionString = "Type=local;Path=" + ui.local_ProjectPath_lineEdit->text() + ";Url=" + ui.local_URL_lineEdit->text();
		break;
	case 1:
		m_ConnectionString = "Type=ftp;Host=" + ui.ftp_Host_lineEdit->text() + ";Port=" + QString::number(ui.ftp_Port_spinBox->value()) + ";Username=" + ui.ftp_Username_lineEdit->text() + ";Password=" + ui.ftp_Password_lineEdit->text() + ";Path=" + ui.ftp_ProjectPath_lineEdit->text() + ";Url=" + ui.ftp_URL_lineEdit->text();
		break;
	case 2:
		m_ConnectionString = "Type=sftp;Host=" + ui.sftp_Host_lineEdit->text() + ";Port=" + QString::number(ui.sftp_Port_spinBox->value()) + ";Username=" + ui.sftp_Username_lineEdit->text() + ";Password=" + ui.sftp_Password_lineEdit->text() + ";Path=" + ui.sftp_ProjectPath_lineEdit->text() + ";Url=" + ui.sftp_URL_lineEdit->text();
		break;
	case 3:
		m_ConnectionString = "Type=rds;Host=" + ui.rds_Host_lineEdit->text() + ";Port=" + QString::number(ui.rds_Port_spinBox->value()) + ";Username=" + ui.rds_Username_lineEdit->text() + ";Password=" + ui.rds_Password_lineEdit->text() + ";Path=" + ui.rds_ProjectPath_lineEdit->text() + ";Url=" + ui.rds_URL_lineEdit->text();
		break;
	default:
		m_ConnectionString.clear();
	}
}

void QProjectProperties::on_buttonBox_rejected()
{
	m_ConnectionString.clear();
}
