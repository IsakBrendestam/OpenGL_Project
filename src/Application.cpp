#include "Application.h"

#include "Utilities/Debug.h"

void Application::Initialize()
{
    DebugLog("Initialize");
    m_object = new Object();
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
    m_object->Draw();
    DebugLog("Draw");
}
