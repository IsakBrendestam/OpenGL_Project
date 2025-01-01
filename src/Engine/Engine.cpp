#include "Engine.h"

#include <chrono>

#include "Utilities/Debug.h"

#include "EngineSettings.h"
#include "CameraManager.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

Engine::Engine()
{
    Init();
}

Engine::~Engine()
{
    glfwTerminate();

    CameraManager::Deconstruct();
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

    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create GLFW Window
    m_window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (m_window == NULL)
    {
        DebugLog("Failed creating window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(m_window);
    //glfwSwapInterval(1); // vsync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        DebugLog("Fialed initializeing GLAD");
        return -1;
    }   

    glfwSetFramebufferSizeCallback(m_window, SetViewportSize); 

    glEnable(GL_DEPTH_TEST);

    if (EngineSettings::g_backFaceCullingOn)
        glEnable(GL_CULL_FACE);

    ProjectionInfo projInfo = {glm::radians(45.0f), (float)EngineSettings::g_windowWidth / (float)EngineSettings::g_windowHeight, 0.1f, 100.0f};
    CameraManager::AddCamera(projInfo, {0.0f, 3.0f, 10.0f}, {0.0f, -90.0f, 0.0f});

    return 0;
}

void Engine::Render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
        glfwPollEvents();
        ProcessInput();

        if (glfwGetWindowAttrib(m_window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // New ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        ImGui::Begin("Test Window");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from test window!");
        ImGui::End();

        CameraManager::Update(deltaTime, m_window);

        Update(deltaTime);
        Render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_window);

        const auto end {std::chrono::steady_clock::now() };
        deltaTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>( end - start).count();
        start = end;
        fps = 1000/deltaTime;
    }

    Exit();

    return 1;
}