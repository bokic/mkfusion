#ifndef QCFVARIANTCOMPONENT_H
#define QCFVARIANTCOMPONENT_H

#include <QString>
#include <QHash>

class QCFVariant;


class QCFVariantComponent
{
public:
    QCFVariantComponent();
    QCFVariantComponent(const QCFVariantComponent &other);
#ifdef Q_COMPILER_RVALUE_REFS
    QCFVariantComponent &operator=(QCFVariantComponent &&other);
#endif
    QCFVariantComponent &operator=(const QCFVariantComponent &other);
    ~QCFVariantComponent();

    QCFVariantComponent *m_Inherit;
    QString m_ComponentFileName;
    QHash<QString, QCFVariant> self;
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

#endif // QCFVARIANTCOMPONENT_H
