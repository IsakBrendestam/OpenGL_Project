#ifndef CAMERAGL_HEADER
#define CAMERAGL_HEADER

#include "Engine/EngineSettings.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

struct ProjectionInfo
{
    float fovAngleY = 0.0f;
    float aspectRatio = 0.0f;
    float nearZ = 0.0f;
    float farZ = 0.0f;
};

class CameraGL
{
public:
    CameraGL() = default;
    CameraGL(const ProjectionInfo& projectionInfo, glm::vec3 position, glm::vec3 rotation);

    void Update(double deltaTime, GLFWwindow* window);

    glm::mat4 GetViewProjectionMatrix() const;
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

private:
    glm::mat4 m_viewMat, m_projectionMat;

    glm::vec3 m_position;
    glm::vec3 m_rotation;

    glm::vec3 m_target;
    glm::vec3 m_direction;
    const glm::vec3 m_up = {0.0f, 1.0f, 0.0f};

    const float m_moveSpeed = 0.0025f;
    const float m_rotSpeed = 0.025f;
};

#endif