#ifndef COLLISIONS_HEADER
#define COLLISIONS_HEADER

#include "glm/gtc/type_ptr.hpp"

struct Sphere
{
    glm::vec3 position;
    float radius;
};

class Collisions
{
public:
    static bool SphereSphereCollision(const Sphere& s1, const Sphere& s2);
};

#endif