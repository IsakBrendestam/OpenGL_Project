#include "Application.h"

int main()
{
    Application* app = new Application();
    int ret = app->Run();
    delete app;


    return 0;
}
