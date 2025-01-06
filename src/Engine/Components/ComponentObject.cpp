#include "ComponentObject.h"

#include "Engine/Utilities/Debug.h"

ComponentObject::~ComponentObject()
{
    for (auto& comp : m_components)
        delete comp;
}

void ComponentObject::CheckIntersection(const ComponentObject& other)
{
    ColliderComponent* colComp = GetComponent<ColliderComponent>();
    ColliderComponent* othercol = other.GetComponent<ColliderComponent>();
    if (colComp != nullptr && othercol != nullptr)
        if (colComp->CheckIntersection(*othercol))
        {
            OnCollision(other);
        }
}

void ComponentObject::OnCollision(const ComponentObject& other)
{

}

void ComponentObject::AddComponent(Component* component)
{
    switch (component->GetType())
    {
    case ComponentType::COLLIDER:
        {
            ColliderComponent* comp = GetComponent<ColliderComponent>();
            if (comp)
                delete comp;
        }
        break;

    case ComponentType::TRANSFORM:
        {
        }
        break;
    
    default:
        break;
    }

    m_components.push_back(component);
}