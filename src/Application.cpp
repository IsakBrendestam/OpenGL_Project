#include "Application.h"

#include "Utilities/Debug.h"

void Application::Initialize()
{
    DebugLog("Initialize");

    m_shader.LoadShader("shader.vs", "shader.fs");
}

void Application::Exit()
{
    DebugLog("Exit");
}

void Application::Update(double deltaTime)
{
    DebugLog("Update");
}

void Application::Draw()
{
    m_shader.Use();
    DebugLog("Draw");
}
