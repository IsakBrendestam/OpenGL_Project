#include "CameraGL.h"


CameraGL::CameraGL(const ProjectionInfo& projectionInfo, glm::vec3 position, glm::vec3 rotation):
    m_position(position), m_rotation(rotation)
{
    m_viewMat = glm::identity<glm::mat4>();
    m_viewMat = glm::translate(m_viewMat, m_position);
    m_viewMat = glm::rotate(m_viewMat, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_viewMat = glm::rotate(m_viewMat, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_viewMat = glm::rotate(m_viewMat, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    m_projectionMat = glm::perspective(projectionInfo.fovAngleY,
                                       projectionInfo.aspectRatio,
                                       projectionInfo.nearZ,
                                       projectionInfo.farZ);

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