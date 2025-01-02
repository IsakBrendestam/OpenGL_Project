#ifndef IMGUIMANAGER_HEADER
#define IMGUIMANAGER_HEADER

#include <GLFW/glfw3.h>
#include <string>

class ImGuiManager
{
public:
    static void Initialize(GLFWwindow* window, const std::string& glslVersion);
    static void Deconstruct();
    static void Update(double deltaTime);
    static void Sleep(int milliseconds);
    static void NewFrame();
    static void Render();

    static void ScreenStatistics(double deltaTime);
    static void EngineSettings();
};

#endif