#include "ColliderComponent.h"

#include "Engine/Utilities/Debug.h"

ColliderComponent::ColliderComponent():
    m_collider(nullptr)
{

}

ColliderComponent::ColliderComponent(Collider* colider):
    m_collider(colider)
{
    
}

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

bool ColliderComponent::CheckIntersection(const ColliderComponent& other)
{
    if (m_collider)
        if (m_collider->Intersection(*other.GetCollider())) 
            return true;
    return false;
}


Collider* ColliderComponent::GetCollider() const
{
    return m_collider;
}

void ColliderComponent::Update()
{

}

void ColliderComponent::Draw()
{

}