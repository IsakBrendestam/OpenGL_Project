#include "ObjectManager.h"

#include "Engine/Utilities/Debug.h"

std::vector<std::string> ObjectManager::m_names;
std::vector<Object*> ObjectManager::m_objects;

void ObjectManager::Initialize()
{

}

void ObjectManager::Deconstruct()
{
    for (auto& object : m_objects)
        delete object;
}

void ObjectManager::Update(double deltaTime)
{
    for (auto& object : m_objects)
        object->Update(deltaTime);

    for (int i = 0; i < m_objects.size(); i++)
        for (int j = 0; j < m_objects.size(); j++)
            if (i != j)
                m_objects[i]->CheckIntersection(*m_objects[j]);
}

void ObjectManager::Draw()
{
    for (auto& object : m_objects)
        object->Render();
}

void ObjectManager::AddObject(const std::string& name, Object* object)
{
    if (std::find(m_names.begin(), m_names.end(), name) != m_names.end())
    {
        DebugLog("Object with name: \"" + name + "\" already exists");
        return;
    }

    m_objects.push_back(object);
    m_names.push_back(name);
}

unsigned int ObjectManager::GetObjectCount()
{
    return m_objects.size();
}

std::string ObjectManager::GetObjectName(unsigned int index)
{
    if (index < m_names.size())
        return m_names[index];
    DebugLog("Index out of bounds");
}

Object* ObjectManager::GetObject(unsigned int index)
{
    if (index < m_objects.size())
        return m_objects[index];
    DebugLog("Index out of bounds");
}