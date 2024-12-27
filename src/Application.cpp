#include "Application.h"

#include "Utilities/Debug.h"

#include "Objects/Rectangle.h"

void Application::Initialize()
{
    m_objects.push_back(new Rectangle());
}

void Application::Exit()
{
    for (auto& object : m_objects)
        delete object;
}

void Application::Update(double deltaTime)
{
    for (auto& object : m_objects)
        object->Update();
}

void Application::Draw()
{
    for (auto& object : m_objects)
        object->Draw();
}
