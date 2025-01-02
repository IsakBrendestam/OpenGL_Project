#include "EngineSettings.h"

bool EngineSettings::g_wireframeOn = false;
bool EngineSettings::g_backFaceCullingOn = true;
bool EngineSettings::g_vsyncOn = false;
int EngineSettings::g_windowWidth = 800;
int EngineSettings::g_windowHeight = 600;
glm::vec3 EngineSettings::g_clearColor(255.0f, 208.0f, 131.0f);