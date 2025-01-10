#ifndef CAMERAMANAGER_HEADER
#define CAMERAMANAGER_HEADER

#include <vector>

#include "OpenGL/CameraGL.h"
#include <GLFW/glfw3.h>

class CameraManager
{
public:
    static void Deconstruct();

    static void Update(double deltaTime, GLFWwindow* window);

    static void AddCamera(const ProjectionInfo& projectionInfo, glm::vec3 position, glm::vec3 rotation, CameraType type = CameraType::PERSPECTIVE);
    static CameraGL GetCamera(unsigned int index);

    static CameraGL GetCurrentCamera();
    static void SetCurrentCamera(unsigned int index);

    static void UpdatePorjections(const ProjectionInfo& projectionInfo);

private:
    static std::vector<CameraGL*> m_cameras;
    static unsigned int m_currentCamera;
};

#endif