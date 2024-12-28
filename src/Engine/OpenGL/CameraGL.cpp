#include "CameraGL.h"


CameraGL::CameraGL(const ProjectionInfo& projectionInfo, glm::vec3 position, glm::vec3 rotation):
    m_position(position), m_rotation(rotation)
{
    m_rotation = {0.0f, -90.0f, 0.0f};
    m_projectionMat = glm::perspective(projectionInfo.fovAngleY,
                                       projectionInfo.aspectRatio,
                                       projectionInfo.nearZ,
                                       projectionInfo.farZ);

}

void CameraGL::Update(double deltaTime, GLFWwindow* window)
{
    /*
    m_rotation.y -= 0.01f * deltaTime;
    m_rotation.x -= 0.01f * deltaTime;
    */

    m_direction.x = cos(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));
    m_direction.y = sin(glm::radians(m_rotation.x));
    m_direction.z = sin(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_position += (m_moveSpeed * (float)deltaTime) * m_direction;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_position -= (m_moveSpeed * (float)deltaTime) * m_direction;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_position += (m_moveSpeed * (float)deltaTime) * glm::cross(m_direction, m_up);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_position -= (m_moveSpeed * (float)deltaTime) * glm::cross(m_direction, m_up);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_position += (m_moveSpeed * (float)deltaTime) * m_up;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        m_position -= (m_moveSpeed * (float)deltaTime) * m_up;

    m_target = m_position + glm::normalize(m_direction);
    m_viewMat = glm::lookAtRH(m_position, m_target, m_up);
}

glm::mat4 CameraGL::GetViewProjectionMatrix() const
{
    return m_projectionMat * m_viewMat;
}

glm::mat4 CameraGL::GetViewMatrix() const
{
    return m_viewMat;
}

glm::mat4 CameraGL::GetProjectionMatrix() const
{
    return m_projectionMat;
}