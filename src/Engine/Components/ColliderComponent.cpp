#include "ColliderComponent.h"

#include "Engine/Utilities/Debug.h"

#include "imgui.h"

ColliderComponent::ColliderComponent():
    Component(ComponentType::COLLIDER), m_collider(nullptr)
{

}

ColliderComponent::ColliderComponent(Collider* colider):
    Component(ComponentType::COLLIDER), m_collider(colider)
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

void ColliderComponent::Draw()
{
    std::string header;
    switch (m_collider->GetType())
    {
    case ColliderType::SPHERE:
        header = "Sphere Collider";
        break;

    case ColliderType::BOX_AABB:
        header = "AABB Collider";
        break;
    
    default:
        break;
    }

    ImGui::Text(header.c_str());
}