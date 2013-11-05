#include "qcfvariantcomponent.h"
#include "qcfvariant.h"


QCFVariantComponent::QCFVariantComponent()
    : m_Inherit(nullptr)
{
}

QCFVariantComponent::QCFVariantComponent(const QCFVariantComponent &other)
    : m_Inherit(other.m_Inherit)
    , m_ComponentFileName(other.m_ComponentFileName)
    , m_Methods(other.m_Methods)
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
{
}

#ifdef Q_COMPILER_RVALUE_REFS
QCFVariantComponent &QCFVariantComponent::operator=(QCFVariantComponent &&other)
{
    qSwap(m_Inherit, other.m_Inherit);
    qSwap(m_ComponentFileName, other.m_ComponentFileName);
    qSwap(m_Methods, other.m_Methods);
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

    return *this;
}
#endif

QCFVariantComponent &QCFVariantComponent::operator=(const QCFVariantComponent &other)
{
    m_Inherit = other.m_Inherit;
    m_ComponentFileName = other.m_ComponentFileName;
    m_Methods = other.m_Methods;
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

    return *this;
}

QCFVariantComponent::~QCFVariantComponent()
{
    m_Inherit = nullptr;
}
