#ifndef ENGINESETTINGS_HEADER
#define ENGINESETTINGS_HEADER

#include "glm/gtc/type_ptr.hpp"

class EngineSettings
{
public:
    static bool g_wireframeOn;
    static bool g_backFaceCullingOn;
    static bool g_vsyncOn;
    static bool g_smoothLinesOn;
    static bool g_renderGrid;
    static bool g_logMessages;
    static int g_windowWidth;
    static int g_windowHeight;
    static glm::vec3 g_clearColor;
};

#endif