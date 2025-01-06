#ifndef COLLIDERCOMPONENT_HEADER
#define COLLIDERCOMPONENT_HEADER

#include "glm/gtc/type_ptr.hpp"

#include "Engine/Components/Component.h"
#include "Collider.h"

#include "SphereCollider.h"
#include "AABBCollider.h"

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