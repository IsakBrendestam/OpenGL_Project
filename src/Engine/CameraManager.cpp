#include "CameraManager.h"

std::vector<CameraGL*> CameraManager::m_cameras;
unsigned int CameraManager::m_currentCamera = 0;

void CameraManager::Deconstruct()
{
    for (auto& camera : m_cameras)
        delete camera;
}

void CameraManager::Update(double deltaTime, GLFWwindow* window)
{
    for (auto& camera : m_cameras)
        camera->Update(deltaTime, window);
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

CameraGL CameraManager::GetCurrentCamera()
{
    return GetCamera(m_currentCamera);
}

void CameraManager::SetCurrentCamera(unsigned int index)
{
    m_currentCamera = index;
}

void CameraManager::UpdatePorjections(const ProjectionInfo& projectionInfo)
{
    for (auto& camera : m_cameras)
        camera->SetProjectionInfo(projectionInfo);
}