#include "ColliderComponent.h"

#include "SphereCollider.h"
#include "AABBCollider.h"

#include "Engine/Utilities/Debug.h"

ColliderComponent::~ColliderComponent()
{
    delete m_collider;
}

ColliderComponent::ColliderComponent(const ColliderComponent& other)
{
    if (m_collider)
        delete m_collider;
    m_collider = nullptr;

    SphereCollider* sphere = dynamic_cast<SphereCollider*>(other.m_collider);
    if (sphere)
    {
        m_collider = new SphereCollider(*sphere);
        return;
    }

    AABBCollider* aabb = dynamic_cast<AABBCollider*>(other.m_collider);
    if (aabb)
    {
        m_collider = new AABBCollider(*aabb);
        return;
    }
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

void ColliderComponent::CheckIntersection(const ColliderComponent& other)
{
    if (m_collider)
        if (m_collider->Intersection(*other.m_collider)) 
            OnCollision(other);
}

void ColliderComponent::OnCollision(const ColliderComponent& other)
{

}

Collider* ColliderComponent::GetCollider() const
{
    return m_collider;
}