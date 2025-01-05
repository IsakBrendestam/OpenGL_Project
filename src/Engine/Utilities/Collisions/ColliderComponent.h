#ifndef COLLIDERCOMPONENT_HEADER
#define COLLIDERCOMPONENT_HEADER

#include "glm/gtc/type_ptr.hpp"

#include "Collider.h"

class ColliderComponent 
{
public:
    ColliderComponent() = default;
    virtual ~ColliderComponent();

    void AssignSphereCollider(glm::vec3 position, float radius);
    void AssignAABBCollider(glm::vec3 position, glm::vec3 dimensions);


    void CheckIntersection(const Collider& other);
    virtual void OnCollision(const Collider& other);

    Collider* GetCollider() const;

protected:
    Collider* m_collider = nullptr;
};

#endif