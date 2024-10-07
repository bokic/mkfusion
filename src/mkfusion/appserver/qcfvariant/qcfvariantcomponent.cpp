#include "qcfvariantcomponent.h"
#include "qcfvariant.h"

#include <QFileInfo>


QCFVariantComponent::QCFVariantComponent()
    : m_Inherit(nullptr)
    , self(QCFVariant::Struct)
    , m_TemplateFileSize(0)
    , m_TemplateFileModified(0)
{
}

QCFVariantComponent::QCFVariantComponent(const QCFVariantComponent &other)
    : m_Inherit(other.m_Inherit)
    , m_ComponentFileName(other.m_ComponentFileName)
    , self(other.self)
    , m_BindingName(other.m_BindingName)
    , m_DisplayName(other.m_DisplayName)
    , m_Extends(other.m_Extends)
    , m_Hint(other.m_Hint)
    , m_Implements(other.m_Implements)
    , m_Namespace(other.m_Namespace)
    , m_Output(other.m_Output)
    , m_PortTypeName(other.m_PortTypeName)
    , m_ServiceAddress(other.m_ServiceAddress)
    , m_ServicePortName(other.m_ServicePortName)
    , m_Style(other.m_Style)
    , m_WSDLFile(other.m_WSDLFile)
    , m_TemplateFilePath(other.m_TemplateFilePath)
    , m_TemplateFileSize(other.m_TemplateFileSize)
    , m_TemplateFileModified(other.m_TemplateFileModified)
{
}

QCFVariantComponent &QCFVariantComponent::operator=(const QCFVariantComponent &other)
{
    m_Inherit = other.m_Inherit;
    m_ComponentFileName = other.m_ComponentFileName;
    self = other.self;
    m_BindingName = other.m_BindingName;
    m_DisplayName = other.m_DisplayName;
    m_Extends = other.m_Extends;
    m_Hint = other.m_Hint;
    m_Implements = other.m_Implements;
    m_Namespace = other.m_Namespace;
    m_Output = other.m_Output;
    m_PortTypeName = other.m_PortTypeName;
    m_ServiceAddress = other.m_ServiceAddress;
    m_ServicePortName = other.m_ServicePortName;
    m_Style = other.m_Style;
    m_WSDLFile = other.m_WSDLFile;
    m_TemplateFilePath = other.m_TemplateFilePath;
    m_TemplateFileSize = other.m_TemplateFileSize;
    m_TemplateFileModified = other.m_TemplateFileModified;

    return *this;
}

QCFVariantComponent::~QCFVariantComponent()
{
    m_Inherit = nullptr;
}

bool QCFVariantComponent::isComponentLatest()
{
    QFileInfo fi(m_TemplateFilePath);

    if (!fi.exists())
    {
        return false;
    }

    if ((fi.lastModified().toSecsSinceEpoch() == m_TemplateFileModified)&&(fi.size() == m_TemplateFileSize))
    {
        return true;
    }

    return false;
}
