#ifndef COMPONENTOBJECT_HEADER
#define COMPONENTOBJECT_HEADER

#include <vector>

#include "Component.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"

class ComponentObject
{
public:
    ComponentObject() = default;
    virtual ~ComponentObject();

    template<class T>
    inline T* GetComponent() const
    {
        for (auto& comp : m_components)
        {
            T* temp = dynamic_cast<T*>(comp);
            if (temp != nullptr)
                return temp;
        }
        return nullptr;
    }

    void AddComponent(Component* component);
    void DrawComponentsUI();

    // Collider Specific Functions
    void CheckIntersection(const ComponentObject& other);
    virtual void OnCollision(const ComponentObject& other);

private:
    std::vector<Component*> m_components;
};

#endif