#ifndef OBJECTMANAGER_HEADER
#define OBJECTMANAGER_HEADER

#include <map>
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

private:
    static std::map<std::string, Object*> m_objects;
};

#endif