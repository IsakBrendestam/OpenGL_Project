#ifndef SPHERECOLLIDER_HEADER
#define SPHERECOLLIDER_HEADER

#include "glm/gtc/type_ptr.hpp"

#include "Collider.h"

class SphereCollider: public Collider
{
public:
    SphereCollider(glm::vec3 position, float radius);
    ~SphereCollider() = default;

    bool Intersection(const Collider& other) override;

    glm::vec3 GetPosition() const;
    float GetRadius() const;

private:
    glm::vec3 m_position;
    float m_radius;
};

#endif