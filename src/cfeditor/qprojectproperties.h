#pragma once

#include "ui_qprojectproperties.h"

#include "qproject.h"

#include <QDialog>
#include <QWidget>
#include <QString>

class QProjectProperties : public QDialog
{
    Q_OBJECT

public:
    QProjectProperties(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::Widget);
    QString getConnectionString();
    void fillDialog(QProject *project);
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
