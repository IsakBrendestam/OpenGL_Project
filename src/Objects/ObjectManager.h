#ifndef OBJECTMANAGER_HEADER
#define OBJECTMANAGER_HEADER

#include <vector>
#include <string>

#include "Object.h"

#include <functional>

class ObjectManager
{
public:
    static void Initialize();
    static void Deconstruct();

    static void Update(double deltaTime);
    static void Draw();

    static void AddObject(const std::string& name, Object* object);
    static void AddChild(const std::string& name, Object* object, const std::string& parentName);

    static unsigned int GetObjectCount();
    static std::string GetObjectName(unsigned int index);
    static Object* GetObject(unsigned int index);
    static Object* GetObject(const std::string& name);
    static Object* GetObjectByID(unsigned int id);
    static Object* QueryObjects(std::function<bool(Object*)> f);

private:
    static Object* RecursiveObjectSearch(Object* object, std::function<bool(Object*)> f);

private:
    static std::vector<Object*> m_objects;
};

#endif