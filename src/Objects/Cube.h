#ifndef CUBE_HEADER
#define CUBE_HEADER

#include "Object.h"

class Cube : public Object
{
public:
    Cube(glm::vec3 position, glm::vec3 scale);
    ~Cube();

    void Update(double deltaTime) override;
    void Draw() override;

private:
};

#endif