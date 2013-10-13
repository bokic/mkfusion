#ifndef QWDDXARGUMENT_H
#define QWDDXARGUMENT_H

#include <QString>


class QWDDXArgument
{
public:
    QWDDXArgument();

    QString m_Name;
    QString m_Required;
    QString m_Type;
    QString m_Default;
};

#endif // QWDDXARGUMENT_H
