#pragma once

#include "qcfvariant.h"

#include <QString>
#include <QHash>


class QCFVariantComponent
{
public:
    QCFVariantComponent();
    QCFVariantComponent(const QCFVariantComponent &other);
#ifdef Q_COMPILER_RVALUE_REFS
    inline QCFVariantComponent &operator=(QCFVariantComponent &&other)
    {
        qSwap(m_Inherit, other.m_Inherit);
        qSwap(m_ComponentFileName, other.m_ComponentFileName);
        qSwap(self, other.self);
        qSwap(m_BindingName, other.m_BindingName);
        qSwap(m_DisplayName, other.m_DisplayName);
        qSwap(m_Extends, other.m_Extends);
        qSwap(m_Hint, other.m_Hint);
        qSwap(m_Implements, other.m_Implements);
        qSwap(m_Namespace, other.m_Namespace);
        qSwap(m_Output, other.m_Output);
        qSwap(m_PortTypeName, other.m_PortTypeName);
        qSwap(m_ServiceAddress, other.m_ServiceAddress);
        qSwap(m_ServicePortName, other.m_ServicePortName);
        qSwap(m_Style, other.m_Style);
        qSwap(m_WSDLFile, other.m_WSDLFile);
        qSwap(m_TemplateFilePath, other.m_TemplateFilePath);
        qSwap(m_TemplateFileSize, other.m_TemplateFileSize);
        qSwap(m_TemplateFileModified, other.m_TemplateFileModified);

        return *this;
    }
#endif
    QCFVariantComponent &operator=(const QCFVariantComponent &other);
    ~QCFVariantComponent();

    bool isComponentLatest();

    QCFVariantComponent *m_Inherit;
    QString m_ComponentFileName;
    QCFVariant self;
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

    QString m_TemplateFilePath;
    qint64 m_TemplateFileSize;
    uint m_TemplateFileModified;
};
