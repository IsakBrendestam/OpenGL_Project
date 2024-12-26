#include "Application.h"

#include "Utilities/Debug.h"

#include "Objects/Rectangle.h"

void Application::Initialize()
{
    m_object = new Rectangle();
}

void Application::Exit()
{
}

void Application::Update(double deltaTime)
{
}

void Application::Draw()
{
    m_object->Draw();
}
