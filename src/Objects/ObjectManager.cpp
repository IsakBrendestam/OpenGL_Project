#include "ObjectManager.h"

#include "Engine/Utilities/Debug.h"

std::map<std::string, Object*> ObjectManager::m_objects;

void ObjectManager::Initialize()
{

}

void ObjectManager::Deconstruct()
{
    for (const auto & [key, value] : m_objects)
        delete value;
}

void ObjectManager::Update(double deltaTime)
{
    for (const auto & [key, value] : m_objects)
        value->Update(deltaTime);

    int i=0, j=0;
    for (const auto & [key1, value1] : m_objects)
    {
        for (const auto & [key2, value2] : m_objects)
        {
            if (value1 != value2 && i < j)
                value1->CheckIntersection(*value2);
            j++;
        }
        i++;
    }
}

void ObjectManager::Draw()
{
    for (const auto & [key, value] : m_objects)
        value->Render();
}

void ObjectManager::AddObject(const std::string& name, Object* object)
{
    if (m_objects.find(name) == m_objects.end())
        m_objects[name] = object;
    else
        DebugLog("Object with name: \"" + name + "\" already exists");
}