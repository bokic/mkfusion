#ifndef QCFSETTINGSMANAGER_H
#define QCFSETTINGSMANAGER_H

#include "qcfsettings.h"


class QCFSettingsManager
{
public:
    QCFSettingsManager();
    QCFSettings readSettings() const;
    void writeSettings(const QCFSettings &settings);

private:

    void loadFromFile();
    void saveToFile() const;

    QCFSettings m_settings;
};

#endif // QCFSETTINGSMANAGER_H
