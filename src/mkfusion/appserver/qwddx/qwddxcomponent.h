#ifndef QWDDXCOMPONENT_H
#define QWDDXCOMPONENT_H

#include "qwddxfunction.h"
#include <QString>
#include <QHash>


class QWDDXComponent
{
public:
    QWDDXComponent();

    QString m_ComponentFileName;
    QHash<QString, QWDDXFunction> m_Methods;
    QString m_BindingName;
    QString m_DisplayName;
    QString m_Extends;
    QString m_Hint;
    QString m_Implements;
    QString m_Namespace;
    QString m_Output;
    QString m_PortTypeName;
    QString m_ServiceAddress;
    QString m_ServicePortName;
    QString m_Style;
    QString m_WSDLFile;
};

#endif // QWDDXCOMPONENT_H
