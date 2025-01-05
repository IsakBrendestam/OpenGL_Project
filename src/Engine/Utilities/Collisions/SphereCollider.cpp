#include "SphereCollider.h"

#include "Collisions.h"

SphereCollider::SphereCollider(glm::vec3 position, float radius):
    Collider(ColliderType::SPHERE), m_position(position), m_radius(radius)
{

}

bool SphereCollider::Intersection(const Collider& other)
{
    switch (other.GetType())
    {
        case ColliderType::SPHERE:
        {
            const SphereCollider* o = dynamic_cast<const SphereCollider*>(&other);
            return Collisions::SphereSphereCollision(m_position, m_radius, o->m_position, o->m_radius);
        }
        break;

        case ColliderType::BOX:

        break;
    }
}