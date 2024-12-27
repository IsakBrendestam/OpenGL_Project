#include "CameraManager.h"

std::vector<CameraGL*> CameraManager::m_cameras;

void CameraManager::Deconstruct()
{
    for (auto& camera : m_cameras)
        delete camera;
}

void CameraManager::AddCamera(const ProjectionInfo& projectionInfo, glm::vec3 position, glm::vec3 rotation)
{
    m_cameras.push_back(new CameraGL(projectionInfo, position, rotation));
}

CameraGL CameraManager::GetCamera(unsigned int index)
{
    if (index < m_cameras.size())
        return *m_cameras[index];
    return CameraGL();
}
