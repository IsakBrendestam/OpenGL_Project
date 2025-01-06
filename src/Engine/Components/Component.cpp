#include "Component.h"

Component::Component(ComponentType type):
    m_type(type)
{

}

void Component::Update()
{

}

ComponentType Component::GetType()
{
    return m_type;
}