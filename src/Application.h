#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

#include <vector>

#include "Engine/Engine.h"

#include "Objects/Object.h"
#include "Objects/Sphere.h"

class Application : public Engine
{
public:
    Application() = default;
    ~Application() = default;

    void Initialize() override;
    void Exit() override;
    void Update(double deltaTime) override;
    void Draw() override;

private:
    std::vector<Object*> m_objects;
    Sphere* m_spheres[2];
};

#endif