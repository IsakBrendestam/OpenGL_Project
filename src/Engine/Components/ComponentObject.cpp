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
            {
                m_components.erase(std::remove(m_components.begin(), m_components.end(), comp), m_components.end());
                delete comp;
            }
        }
        break;

    case ComponentType::TRANSFORM:
        {
            TransformComponent* comp = GetComponent<TransformComponent>();
            if (comp)
            {
                m_components.erase(std::remove(m_components.begin(), m_components.end(), comp), m_components.end());
                delete comp;
            }
        }
        break;
    
    default:
        break;
    }

    m_components.push_back(component);
}

void ComponentObject::DrawInspector()
{
    for (auto& comp : m_components)
        comp->Draw();
}