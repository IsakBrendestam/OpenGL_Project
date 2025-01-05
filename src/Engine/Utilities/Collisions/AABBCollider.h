#ifndef AABBCOLLIDER_HEADER
#define AABBCOLLIDER_HEADER

#include "glm/gtc/type_ptr.hpp"

#include "Collider.h"

class AABBCollider: public Collider
{
public:
    AABBCollider(glm::vec3 position, glm::vec3 dimensions);
    ~AABBCollider() = default;

    bool Intersection(const Collider& other) override;

    glm::vec3 GetPosition() const;
    glm::vec3 GetDimensions() const;

private:
    glm::vec3 m_position, m_dimensions;
};

#endif