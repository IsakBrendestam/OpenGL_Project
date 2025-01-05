#include "ColliderComponent.h"

void ColliderComponent::AssignSphereCollider(glm::vec3 position, float radius)
{
    m_collider = new SphereCollider(position, radius);
}

void ColliderComponent::CheckIntersection(const Collider& other)
{
    if (m_collider)
        if (m_collider->Intersection(other)) 
            OnCollision(other);
}

void ColliderComponent::OnCollision(const Collider& other)
{

}

Collider* ColliderComponent::GetCollider() const
{
    return m_collider;
}