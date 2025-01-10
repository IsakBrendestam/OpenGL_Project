#include "InspectorComponent.h"

InspectorComponent::InspectorComponent(const std::string& name):
    m_name(name)
{

}

std::string InspectorComponent::GetName() const
{
    return m_name;
}

void InspectorComponent::SetName(const std::string& name)
{
    m_name = name;
}