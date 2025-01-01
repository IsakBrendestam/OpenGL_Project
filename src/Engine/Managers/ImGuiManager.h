#ifndef IMGUIMANAGER_HEADER
#define IMGUIMANAGER_HEADER

#include <GLFW/glfw3.h>
#include <string>

class ImGuiManager
{
public:
    static void Initialize(GLFWwindow* window, const std::string& glslVersion);
    static void Update();
    static void Sleep(int milliseconds);
    static void NewFrame();
    static void Render();

};

#endif