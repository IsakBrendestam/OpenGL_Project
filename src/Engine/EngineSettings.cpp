#include "EngineSettings.h"

bool EngineSettings::g_wireframeOn = false;
bool EngineSettings::g_backFaceCullingOn = true;
bool EngineSettings::g_vsyncOn = false;
bool EngineSettings::g_smoothLinesOn = true;
bool EngineSettings::g_renderGrid = true;
bool EngineSettings::g_logMessages = true;
int EngineSettings::g_windowWidth = 1280;
int EngineSettings::g_windowHeight = 720;
glm::vec3 EngineSettings::g_clearColor(22.0f/255.0f, 79.0f/255.0f, 115.0f/255.0f);