#include "Engine.h"


#include "../Utilities/Debug.h"

#include "EngineSettings.h"

float myVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};  

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
}

void Engine::Render()
{
    Draw();

    unsigned int VBO;
    glGenBuffers(1, &VBO);  
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(myVertices), myVertices, GL_STATIC_DRAW);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);  
    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    glDrawArrays(GL_TRIANGLES, 0, 3);
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

    while(!glfwWindowShouldClose(m_window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ProcessInput();

        if (EngineSettings::g_wireframeOn)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        Update(0);
        Render();

        glfwSwapBuffers(m_window);
        glfwPollEvents();    
    }

    Exit();
}