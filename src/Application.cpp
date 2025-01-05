#include "Application.h"

#include "Engine/Utilities/Debug.h"

#include "Objects/Rectangle.h"
#include "Objects/Cube.h"
#include "Objects/Line.h"
#include "Objects/MeshObject.h"
#include "Objects/Sphere.h"

#include "Engine/Utilities/ObjParser.h"

void Application::Initialize()
{
    //m_objects.push_back(new Cube({0.0f, 0.0f, 0.0f}, {0.1f, 0.1f, 0.1f}));
    //m_objects.push_back(new Rectangle());
    //m_objects.push_back(new Cube({-2.0f, 0.0f, -2.0f}, {0.5f, 0.5f, 0.5f}));

    ObjParser obj = ObjParser("res/Objects/", "Sphere.obj");

    //m_objects.push_back(new MeshObject({1.0f, 0.85f, 0.0f}, obj.GetMeshData(), {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.2f, 0.2f, 0.2f}));
    m_objects.push_back(new Sphere({0, 0.5f, 0}, 0.5f));
    m_objects.push_back(new Sphere({0.8f, 0.5f, 0}, 0.5f));
    //m_spheres[0] = new Sphere({0, 0.5f, 0}, 0.5f);
    //m_spheres[1] = new Sphere({0.8f, 0.5f, 0}, 0.5f);
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

    for (int i = 0; i < m_objects.size(); i++)
        for (int j = 0; j < m_objects.size(); j++)
            if (i != j)
                m_objects[i]->CheckIntersection(*m_objects[j]->GetCollider());

    //m_spheres[0]->Update(deltaTime);
    //m_spheres[1]->Update(deltaTime);

    //m_spheres[0]->CheckIntersection(*m_spheres[1]);
    //m_spheres[1]->CheckIntersection(*m_spheres[0]);
}

void Application::Draw()
{
    for (auto& object : m_objects)
        object->Render();

    //m_spheres[0]->Render();
    //m_spheres[1]->Render();
}
