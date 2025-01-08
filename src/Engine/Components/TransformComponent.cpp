#include "TransformComponent.h"

#include "Engine/Utilities/Debug.h"

TransformComponent::TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale):
    Component(ComponentType::TRANSFORM), m_position(position), m_rotation(rotation), m_scale(scale)
{

}

glm::vec3 TransformComponent::GetPosition()
{
    return m_position;
}

glm::vec3 TransformComponent::GetRotation()
{
    return m_rotation;
}

glm::vec3 TransformComponent::GetScale()
{
    return m_scale;
}

glm::mat4 TransformComponent::GetWorldMat()
{
    m_worldMat = glm::identity<glm::mat4>();

    m_worldMat = glm::translate(m_worldMat, m_position);
    m_worldMat = glm::rotate(m_worldMat, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_worldMat = glm::rotate(m_worldMat, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_worldMat = glm::rotate(m_worldMat, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_worldMat = glm::scale(m_worldMat, m_scale);

    return m_worldMat;
}

void TransformComponent::Draw()
{
    if (ImGui::TreeNode("Transform"))
    {
        const float min = -100.0f;
        const float max = 100.0f;
        ImGui::DragFloat3("Position", (float*)&m_position, 0.1f, min, max);
        ImGui::DragFloat3("Rotation", (float*)&m_rotation, 0.1f, min, max);
        ImGui::DragFloat3("Scale", (float*)&m_scale, 0.1f, min, max);

        ImGui::TreePop();
    }
}
