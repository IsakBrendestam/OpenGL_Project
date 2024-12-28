#ifndef LIGHT_HEADER
#define LIGHT_HEADER

#include <glm/gtc/type_ptr.hpp>

struct LightData
{
    glm::vec3 position;
    glm::vec3 color;
    float ambientIntencity;
};


#endif