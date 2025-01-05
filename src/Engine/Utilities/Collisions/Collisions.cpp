#include "Collisions.h"

#include <glm/glm.hpp>


bool Collisions::SphereSphereCollision(glm::vec3 p1, float r1, glm::vec3 p2, float r2)
{
    glm::vec3 diff = p1 - p2;
    float squareRadius = r1 + r2;
    squareRadius *= squareRadius;
    return glm::dot(diff, diff) < squareRadius;
}