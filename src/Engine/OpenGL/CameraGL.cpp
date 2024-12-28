#include "CameraGL.h"


CameraGL::CameraGL(const ProjectionInfo& projectionInfo, glm::vec3 position, glm::vec3 rotation):
    m_position(position), m_rotation(rotation)
{
    m_projectionMat = glm::perspective(projectionInfo.fovAngleY,
                                       projectionInfo.aspectRatio,
                                       projectionInfo.nearZ,
                                       projectionInfo.farZ);

}

void CameraGL::Update(double deltaTime)
{
    m_target = {0, 0, 0};
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