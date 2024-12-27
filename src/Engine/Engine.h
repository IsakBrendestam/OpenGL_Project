#ifndef ENGINE_HEADER
#define ENGINE_HEADER

#include "glad/glad.h"
#include <GLFW/glfw3.h>

class Engine
{
public:
    Engine();
    virtual ~Engine();
    int Run();

private:
    int Init();
    void Render();

    void ProcessInput();

private:
    GLFWwindow* m_window;

protected:
    virtual void Initialize() = 0;
    virtual void Exit() = 0;
    virtual void Update(double deltaTime) = 0;
    virtual void Draw() = 0;

    static void SetViewportSize(GLFWwindow* window, int width, int height);
};

#endif