#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

#include <vector>

#include "Engine/Engine.h"

#include "Objects/Object.h"

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
};

#endif