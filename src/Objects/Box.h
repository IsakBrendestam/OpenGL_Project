#ifndef BOX_HEADER
#define BOX_HEADER

#include "Object.h"

class Box : public Object
{
public:
    Box(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    ~Box();

    void Update(double deltaTime) override;
    void Draw() override;

    void OnCollision(const ColliderComponent& other) override;

private:
};

#endif