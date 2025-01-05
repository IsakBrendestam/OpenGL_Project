#include "Collider.h"

#include "Engine/Utilities/Debug.h"

Collider::Collider(ColliderType type):
    m_type(type)
{

}

Collider::Collider(const Collider& other)
{
    m_type = other.m_type;
}

Collider::~Collider()
{

}

ColliderType Collider::GetType() const
{
    return m_type;
}