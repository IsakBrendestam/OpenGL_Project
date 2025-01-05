#ifndef COLLISIONS_HEADER
#define COLLISIONS_HEADER

#include "glm/gtc/type_ptr.hpp"

struct Sphere
{
    glm::vec3 position;
    float radius;
};

struct AABB
{
    glm::vec3 position;
    glm::vec3 dimensions;
};

class Collisions
{
public:
    static bool SphereSphereCollision(const Sphere& s1, const Sphere& s2);
    static bool SphereAABBCollision(const Sphere& s, const AABB& b);
};

#endif