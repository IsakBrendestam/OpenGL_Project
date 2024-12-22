#include "Application.h"

#include "Utilities/Debug.h"

void Application::Initialize()
{
    DebugLog("Initialize");
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
    DebugLog("Draw");
}
