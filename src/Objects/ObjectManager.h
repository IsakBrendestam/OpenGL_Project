#ifndef OBJECTMANAGER_HEADER
#define OBJECTMANAGER_HEADER

#include <vector>
#include <string>

#include "Object.h"

class ObjectManager
{
public:
    static void Initialize();
    static void Deconstruct();

    static void Update(double deltaTime);
    static void Draw();

    static void AddObject(const std::string& name, Object* object);
    static void AddChild(const std::string& name, Object* object);

    static unsigned int GetObjectCount();
    static std::string GetObjectName(unsigned int index);
    static Object* GetObject(unsigned int index);
    static Object* GetObject(const std::string& name);

private:
    static std::vector<std::string> m_names;
    static std::vector<Object*> m_objects;
};

#endif