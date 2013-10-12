#include <qcfsettings.h>

#include <QString>


QCFSettings::QCFSettings()
    : m_customTagsPath()
    , m_schedulerThreadIntervalMS(5000)
{
}

bool QCFSettings::setCustomTagsPath(const QString &value)
{
    m_customTagsPath = value;

    return true;
}

QString QCFSettings::customTagsPath()
{
    return m_customTagsPath;
}
