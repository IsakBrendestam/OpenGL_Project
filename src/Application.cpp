#include "Application.h"

#include "Engine/Utilities/Debug.h"

#include "Objects/Rectangle.h"
#include "Objects/Cube.h"
#include "Objects/Line.h"
#include "Objects/MeshObject.h"

#include "Engine/Utilities/ObjParser.h"

void Application::Initialize()
{
    //m_objects.push_back(new Cube({0.0f, 0.0f, 0.0f}, {0.1f, 0.1f, 0.1f}));
    //m_objects.push_back(new Rectangle());
    m_objects.push_back(new Cube({-2.0f, 0.0f, -2.0f}, {0.5f, 0.5f, 0.5f}));

    ObjParser* object = new ObjParser("res/Objects/", "Dragon.obj");

    //m_objects.push_back(new MeshObject(object->GetMeshData(), {1.0f, 0.0f, 0.0f}, {2.0f, 0.5f, -2.0f}, {0.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f}));

    m_objects.push_back(new MeshObject({1.0f, 0.85f, 0.0f}, object->GetMeshData(), {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.2f, 0.2f, 0.2f}));
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
