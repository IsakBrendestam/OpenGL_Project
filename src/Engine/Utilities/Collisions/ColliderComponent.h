#ifndef COLLIDERCOMPONENT_HEADER
#define COLLIDERCOMPONENT_HEADER

#include "Collider.h"
#include "SphereCollider.h"

class ColliderComponent 
{
public:
    ColliderComponent() = default;
    virtual ~ColliderComponent() = default;

    void AssignSphereCollider(glm::vec3 position, float radius);

    void CheckIntersection(const Collider& other);
    virtual void OnCollision(const Collider& other);

    Collider* GetCollider() const;

protected:
    Collider* m_collider = nullptr;
};

#endif