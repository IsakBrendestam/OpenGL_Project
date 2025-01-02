#include "Application.h"

#include "Utilities/Debug.h"

#include "Objects/Rectangle.h"
#include "Objects/Cube.h"
#include "Objects/Line.h"

void Application::Initialize()
{
    m_objects.push_back(new Cube({0.0f, 0.0f, 0.0f}, {0.1f, 0.1f, 0.1f}));
    //m_objects.push_back(new Rectangle());
    m_objects.push_back(new Cube({2.0f, 0.0f, -2.0f}, {0.5f, 0.5f, 0.5f}));
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
