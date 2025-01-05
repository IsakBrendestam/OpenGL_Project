#include "AABBCollider.h"

#include "Collisions.h"

#include "SphereCollider.h"

AABBCollider::AABBCollider(glm::vec3 position, glm::vec3 dimensions):
    Collider(ColliderType::BOX_AABB), m_position(position), m_dimensions(dimensions)
{

}

bool AABBCollider::Intersection(const Collider& other)
{
    switch (other.GetType())
    {
        case ColliderType::SPHERE:
        {
            const SphereCollider* o = dynamic_cast<const SphereCollider*>(&other);
            return Collisions::SphereAABBCollision({o->GetPosition(), o->GetRadius()}, {m_position, m_dimensions});
        }
        break;

        case ColliderType::BOX_AABB:
            break;
    }
}

glm::vec3 AABBCollider::GetPosition() const
{
    return m_position;
}

glm::vec3 AABBCollider::GetDimensions() const
{
    return m_dimensions;
}