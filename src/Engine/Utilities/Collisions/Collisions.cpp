#include "Collisions.h"

#include <glm/glm.hpp>


bool Collisions::SphereSphereCollision(const Sphere& s1, const Sphere& s2)
{
    glm::vec3 diff = s1.position - s2.position;
    float squareRadius = s1.radius + s2.radius;
    squareRadius *= squareRadius;
    return glm::dot(diff, diff) < squareRadius;
}