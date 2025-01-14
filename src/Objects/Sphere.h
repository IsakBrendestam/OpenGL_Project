#ifndef SPHERE_HEADER
#define SPHERE_HEADER

#include "Object.h"

#include "Engine/Utilities/Collisions/SphereCollider.h"

class Sphere : public Object
{
public:
    Sphere(glm::vec3 position, float radius);
    ~Sphere() = default;

    void Update(double deltaTime) override;
    void Draw() override;

    void OnCollision(const ComponentObject& other) override;

private:
    float m_radius;
    glm::vec3 m_color;

    MeshData m_mesh;
};

#endif