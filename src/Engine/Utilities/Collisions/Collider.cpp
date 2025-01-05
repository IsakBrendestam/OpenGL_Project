#include "Collider.h"

#include "Engine/Utilities/Debug.h"

Collider::Collider(ColliderType type):
    m_type(type)
{

}

Collider::~Collider()
{

}

void Collider::CheckIntersection(const Collider& other)
{
    if (Intersection(other)) 
    {
        DebugLog("Colliding");
        OnCollision(other);
    }
}

ColliderType Collider::GetType() const
{
    return m_type;
}