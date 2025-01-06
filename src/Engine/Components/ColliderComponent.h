#ifndef COLLIDERCOMPONENT_HEADER
#define COLLIDERCOMPONENT_HEADER

#include "glm/gtc/type_ptr.hpp"

#include "Component.h"
#include "Engine/Utilities/Collisions/Collider.h"

#include "Engine/Utilities/Collisions/SphereCollider.h"
#include "Engine/Utilities/Collisions/AABBCollider.h"

class ColliderComponent: public Component
{
public:
    ColliderComponent();
    ColliderComponent(Collider* colider);
    ~ColliderComponent();

    void AssignSphereCollider(glm::vec3 position, float radius);

    void AssignAABBCollider(glm::vec3 position, glm::vec3 dimensions);

    bool CheckIntersection(const ColliderComponent& other);

    Collider* GetCollider() const;

    void Update() override;
    void Draw() override;

protected:
    Collider* m_collider = nullptr;
};

#endif