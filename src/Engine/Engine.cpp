#include "Engine.h"

#include <chrono>

#include "Utilities/Debug.h"

#include "EngineSettings.h"
#include "CameraManager.h"

#include "Managers/ImGuiManager.h"

Engine::Engine()
{
    Init();
}

Engine::~Engine()
{
    delete m_grid;

    CameraManager::Deconstruct();
    ImGuiManager::Deconstruct();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int Engine::Init()
{
    // Init GLFW
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
        return 1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create GLFW Window
    m_window = glfwCreateWindow(EngineSettings::g_windowWidth, EngineSettings::g_windowHeight, "LearnOpenGL", NULL, NULL);
    if (m_window == NULL)
    {
        DebugLog("Failed creating window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(m_window);


    ImGuiManager::Initialize(m_window, "#version 330");

    // Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        DebugLog("Fialed initializeing GLAD");
        return -1;
    }   

    glfwSetFramebufferSizeCallback(m_window, SetViewportSize); 

    glEnable(GL_DEPTH_TEST);


    ProjectionInfo projInfo = {glm::radians(45.0f), (float)EngineSettings::g_windowWidth / (float)EngineSettings::g_windowHeight, 0.1f, 100.0f};
    CameraManager::AddCamera(projInfo, {0.0f, 3.0f, 10.0f}, {0.0f, -90.0f, 0.0f});

    m_grid = new Grid(20, 10);

    return 0;
}

void Engine::Render()
{
    glClearColor(EngineSettings::g_clearColor.r, EngineSettings::g_clearColor.g, EngineSettings::g_clearColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (EngineSettings::g_wireframeOn)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (EngineSettings::g_backFaceCullingOn)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    if (EngineSettings::g_smoothLinesOn)
        glEnable(GL_LINE_SMOOTH);
    else
        glDisable(GL_LINE_SMOOTH);

    if (EngineSettings::g_renderGrid)
    {
        m_grid->Update(0);
        m_grid->Draw();
    }
    Draw();
}

void Engine::SetViewportSize(GLFWwindow* window, int width, int height)
{
    EngineSettings::g_windowWidth = width;
    EngineSettings::g_windowHeight = height;
    ProjectionInfo projInfo = {glm::radians(45.0f), (float)EngineSettings::g_windowWidth / (float)EngineSettings::g_windowHeight, 0.1f, 100.0f};
    CameraManager::UpdatePorjections(projInfo);
    
    glViewport(0, 0, EngineSettings::g_windowWidth, EngineSettings::g_windowHeight);
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
        glfwPollEvents();
        ProcessInput();

        if (glfwGetWindowAttrib(m_window, GLFW_ICONIFIED) != 0)
        {
            ImGuiManager::Sleep(10);
            continue;
        }

        if (EngineSettings::g_vsyncOn)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);


        ImGuiManager::NewFrame();

        CameraManager::Update(deltaTime, m_window);

        Update(deltaTime);
        Render();

        ImGuiManager::Update(deltaTime);
        ImGuiManager::Render();

        glfwSwapBuffers(m_window);

        const auto end {std::chrono::steady_clock::now() };
        deltaTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>( end - start).count();
        start = end;
        fps = 1000/deltaTime;
    }

    Exit();

    return 1;
}