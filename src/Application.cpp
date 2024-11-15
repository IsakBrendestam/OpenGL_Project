#include "Application.h"

#include "stdio.h"

void Application::Initialize()
{
    printf("Initialize\n");
}

void Application::Exit()
{
    printf("Exit\n");
}

void Application::Update(double deltaTime)
{
    printf("Update\n");
}

void Application::Draw()
{
    printf("Draw\n");
}
