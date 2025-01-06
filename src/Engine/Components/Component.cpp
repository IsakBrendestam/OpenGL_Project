#include "Component.h"

Component::Component(ComponentType type):
    m_type(type)
{

}

ComponentType Component::GetType()
{
    return m_type;
}