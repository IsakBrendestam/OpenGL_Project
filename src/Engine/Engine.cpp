#include "Engine.h"

Engine::Engine()
{

}

Engine::~Engine()
{

}

int Engine::Run()
{
    Initialize();

    // Update function here
    Update(0);
    Draw();

    Exit();
}