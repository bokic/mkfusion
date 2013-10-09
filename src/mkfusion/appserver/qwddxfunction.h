#ifndef QWDDXFUNCTION_H
#define QWDDXFUNCTION_H

#include "qwddxargument.h"
#include <QString>
#include <QHash>


class QWDDXFunction
{
public:
    QWDDXFunction();

    QHash<QString, QWDDXArgument> m_Methods;

    QString m_ReturnType;
    QString m_Roles;
    QString m_Access;
    QString m_Output;
    QString m_DisplayName;
    QString m_Hint;
    QString m_Description;
};

#endif // QWDDXFUNCTION_H
