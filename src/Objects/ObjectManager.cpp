#include "ObjectManager.h"

#include "Engine/Utilities/Debug.h"

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
        object->InternalUpdate(deltaTime);

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
    for (int i = 0; i < m_objects.size(); i++)
        if (GetObjectName(i) == name)
        {
            DebugLog("Object with name: \"" + name + "\" already exists");
            return;
        }

    object->SetName(name);
    m_objects.push_back(object);
}

void ObjectManager::AddChild(const std::string& name, Object* object, const std::string& parentName)
{
    object->SetName(name);
    GetObject(parentName)->AddChild(object);
}

unsigned int ObjectManager::GetObjectCount()
{
    return m_objects.size();
}

std::string ObjectManager::GetObjectName(unsigned int index)
{
    if (index < m_objects.size())
        return m_objects[index]->GetName();
    DebugLog("Index out of bounds");
    return "";
}

Object* ObjectManager::GetObject(unsigned int index)
{
    if (index < m_objects.size())
        return m_objects[index];
    DebugLog("Index out of bounds");
    return nullptr;
}

Object* ObjectManager::GetObject(const std::string& name)
{
    return QueryObjects([&name](Object* obj) -> bool {return obj->GetName() == name; });
}

Object* ObjectManager::GetObjectByID(unsigned int id)
{
    return QueryObjects([&id](Object* obj) -> bool {return obj->GetID() == id; });
}

Object* ObjectManager::QueryObjects(std::function<bool(Object*)> f)
{
    for (auto& object : m_objects)
    {
        Object* temp = RecursiveObjectSearch(object, f);
        if (temp)
            return temp;
    }

    return nullptr;
}

Object* ObjectManager::RecursiveObjectSearch(Object* object, std::function<bool(Object*)> f)
{
    if (f(object))
        return object;

    for (auto& child : object->GetChildren())
    {
        Object* temp = RecursiveObjectSearch(child, f);
        if (temp)
            return temp;
    }
    return nullptr;
}