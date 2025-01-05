#include "ColliderComponent.h"

#include "SphereCollider.h"
#include "AABBCollider.h"

#include "Engine/Utilities/Debug.h"

ColliderComponent::~ColliderComponent()
{
    delete m_collider;
}

void ColliderComponent::AssignSphereCollider(glm::vec3 position, float radius)
{
    if (m_collider)
        delete m_collider;
    m_collider = new SphereCollider(position, radius);
}

void ColliderComponent::AssignAABBCollider(glm::vec3 position, glm::vec3 dimensions)
{
    if (m_collider)
        delete m_collider;
    m_collider = new AABBCollider(position, dimensions);
}

void ColliderComponent::CheckIntersection(const Collider& other)
{
    if (m_collider)
        if (m_collider->Intersection(other)) 
        {
            DebugLog("Collision");
            OnCollision(other);
        }
}

void ColliderComponent::OnCollision(const Collider& other)
{

}

Collider* ColliderComponent::GetCollider() const
{
    return m_collider;
}