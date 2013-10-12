#ifndef QCFSETTINGS_H
#define QCFSETTINGS_H

#include <QString>


class QCFSettings
{
public:
    QCFSettings();
    bool setCustomTagsPath(const QString &value);
    QString customTagsPath();

private:
    QString m_customTagsPath;
    int m_schedulerThreadIntervalMS;
};

#endif // QCFSETTINGS_H
