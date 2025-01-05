#ifndef COLLISIONS_HEADER
#define COLLISIONS_HEADER

#include "glm/gtc/type_ptr.hpp"

class Collisions
{
public:
    static bool SphereSphereCollision(glm::vec3 p1, float r1, glm::vec3 p2, float r2);
};

#endif