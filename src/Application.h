#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

#include "Engine/Engine.h"

class Application : public Engine
{
public:
    Application() = default;
    ~Application() = default;

    void Initialize() override;
    void Exit() override;
    void Update(double deltaTime) override;
    void Draw() override;
};

#endif