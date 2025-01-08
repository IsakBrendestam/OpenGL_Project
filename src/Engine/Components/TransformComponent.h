#ifndef TRANSFORMCOMPONENT_HEADER
#define TRANSFORMCOMPONENT_HEADER

#include "glm/gtc/type_ptr.hpp"

#include "Component.h"

class TransformComponent: public Component
{
public:
    TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    ~TransformComponent() = default;

    glm::vec3 GetPosition();
    glm::vec3 GetRotation();
    glm::vec3 GetScale();

    glm::mat4 GetWorldMat();

    void SetParentWorldMat(const glm::mat4& worldMat);
    void RemoveParentWorldMat();

    void Draw() override;

private:
    glm::vec3 m_position, m_rotation, m_scale;
    glm::mat4 m_worldMat;
    glm::mat4 m_parentWorldMat;
};

#endif