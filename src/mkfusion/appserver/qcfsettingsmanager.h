#pragma once

#include "qcfsettings.h"


class QCFSettingsManager
{
public:
    QCFSettingsManager();
    QCFSettings readSettings() const;
    void writeSettings(const QCFSettings &settings);
    void loadFromFile();

private:

    void saveToFile() const;

    QCFSettings m_settings;
};
