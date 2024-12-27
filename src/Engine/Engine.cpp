#include "Engine.h"

#include <chrono>

#include "Utilities/Debug.h"

#include "EngineSettings.h"

Engine::Engine()
{
    Init();
}

Engine::~Engine()
{
    glfwTerminate();
}

int Engine::Init()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFW Window
    m_window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (m_window == NULL)
    {
        DebugLog("Failed creating window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(m_window);

    // Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        DebugLog("Fialed initializeing GLAD");
        return -1;
    }   

    glfwSetFramebufferSizeCallback(m_window, SetViewportSize); 

    return 0;
}

void Engine::Render()
{
    if (EngineSettings::g_wireframeOn)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Draw();
}

void Engine::SetViewportSize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Engine::ProcessInput()
{
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);
}

int Engine::Run()
{
    Initialize();

    double deltaTime = 0;
    double fps = 0;

    auto start { std::chrono::steady_clock::now() };

    while(!glfwWindowShouldClose(m_window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ProcessInput();

        Update(deltaTime);
        Render();

        glfwSwapBuffers(m_window);
        glfwPollEvents();

        const auto end {std::chrono::steady_clock::now() };
        deltaTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>( end - start).count();
        start = end;
        fps = 1000/deltaTime;
    }

    Exit();

    return 1;
}