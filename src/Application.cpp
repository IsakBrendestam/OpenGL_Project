#include "Application.h"

#include "Utilities/Debug.h"

#include "Objects/Rectangle.h"
#include "Objects/Cube.h"

void Application::Initialize()
{
    m_objects.push_back(new Rectangle());
    m_objects.push_back(new Cube());
}

void Application::Exit()
{
    for (auto& object : m_objects)
        delete object;
}

void Application::Update(double deltaTime)
{
    for (auto& object : m_objects)
        object->Update(deltaTime);
}

void Application::Draw()
{
    for (auto& object : m_objects)
        object->Draw();
}
