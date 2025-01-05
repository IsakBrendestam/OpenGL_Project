#include "Collisions.h"

#include <glm/glm.hpp>


bool Collisions::SphereSphereCollision(const Sphere& s1, const Sphere& s2)
{
    glm::vec3 diff = s1.position - s2.position;
    float squareRadius = s1.radius + s2.radius;
    squareRadius *= squareRadius;
    return glm::dot(diff, diff) < squareRadius;
}

bool Collisions::SphereAABBCollision(const Sphere& s, const AABB& b)
{
    float sqDist = 0.0f;
    for( int i = 0; i < 3; i++ ){
        const float min = b.position[i] - b.dimensions[i];
        const float max = b.position[i] + b.dimensions[i];
        const float v = s.position[i];
        if( v < min ) sqDist += (min - v) * (min - v);
        if( v > max ) sqDist += (v - max) * (v - max);
    }

    return sqDist <= s.radius * s.radius;
}