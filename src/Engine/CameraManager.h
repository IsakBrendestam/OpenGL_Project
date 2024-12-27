#ifndef CAMERAMANAGER_HEADER
#define CAMERAMANAGER_HEADER

#include <vector>

#include "OpenGL/CameraGL.h"

class CameraManager
{
public:
    static void Deconstruct();

    static void AddCamera(const ProjectionInfo& projectionInfo, glm::vec3 position, glm::vec3 rotation);
    static CameraGL GetCamera(unsigned int index);

private:
    static std::vector<CameraGL*> m_cameras;
};

#endif