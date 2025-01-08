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
    ObjectManager::Initialize();

    ObjectManager::AddObject("Sphere", new Sphere({0, 0.5f, 0}, 0.3f));
    ObjectManager::AddObject("Sphere 2", new Sphere({1.7f, 0.5f, 0}, 0.5f));
    ObjectManager::AddObject("Box", new Box({-1.5f, 0.5f, 0}, {0, 0, 0}, {1.5f, 0.5f, 0.5f}));
    ObjectManager::AddObject("Box 2", new Cube({0.5f, 0.5f, -1.5f}, {0, 0, 0}, 0.5f));

    ObjectManager::AddChild("Temp Sphere", new Sphere({0, 1, 0}, 0.5f), "Box");
    ObjectManager::AddChild("Temp Sphere 2", new Sphere({1, 1, 0}, 0.5f), "Box");

    ObjectManager::AddChild("Temp", new Sphere({0, 1, 0}, 0.5f), "Sphere 2");
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
