#ifndef QCFWORKERSMANAGER_H
#define QCFWORKERSMANAGER_H

#include <QString>
#include <QObject>

class QCFWorkersManager : public QObject
{
public:
    QCFWorkersManager();
    QString compile(const QString &file, bool checkForNewer = true);

public slots:
    void on_newConnection();
};

#endif // QCFWORKERSMANAGER_H
