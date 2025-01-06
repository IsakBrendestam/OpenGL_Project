#include "Application.h"

#include "Engine/Utilities/Debug.h"

#include "Objects/Rectangle.h"
#include "Objects/Cube.h"
#include "Objects/Box.h"
#include "Objects/Line.h"
#include "Objects/MeshObject.h"
#include "Objects/Sphere.h"

#include "Engine/Utilities/ObjParser.h"

#include "Objects/ObjectManager.h"

void Application::Initialize()
{
    //m_objects.push_back(new Cube({0.0f, 0.0f, 0.0f}, {0.1f, 0.1f, 0.1f}));
    //m_objects.push_back(new Rectangle());
    //m_objects.push_back(new Cube({-2.0f, 0.0f, -2.0f}, {0.5f, 0.5f, 0.5f}));

    //ObjParser obj = ObjParser("res/Objects/", "Dragon.obj");

    //m_objects.push_back(new MeshObject({1.0f, 0.85f, 0.0f}, obj.GetMeshData(), {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.2f, 0.2f, 0.2f}));
    ObjectManager::Initialize();

    ObjectManager::AddObject("Sphere", new Sphere({0, 0.5f, 0}, 0.3f));
    ObjectManager::AddObject("Sphere 2", new Sphere({1.7f, 0.5f, 0}, 0.5f));
    ObjectManager::AddObject("Box", new Box({-1.5f, 0.5f, 0}, {0, 0, 0}, {1.5f, 0.5f, 0.5f}));
    ObjectManager::AddObject("Box 2", new Cube({0.5f, 0.5f, -1.5f}, {0, 0, 0}, 0.5f));
}

void Application::Exit()
{
    ObjectManager::Deconstruct();
}

void Application::Update(double deltaTime)
{
    ObjectManager::Update(deltaTime);
}

void Application::Draw()
{
    ObjectManager::Draw();
}
