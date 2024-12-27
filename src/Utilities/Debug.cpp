#include "Debug.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include <iostream>
#include <ctime>

#ifdef DEBUG

void DebugLog(std::string msg)
{
    time_t now = std::time(0);
    tm* ltm = std::localtime(&now);

    std::string timestamp = "[" + std::to_string(5 + ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec) + "] ";

    std::cout << timestamp << msg << std::endl;

}

#endif

bool CheckError(unsigned int resource, ResourceType type)
{
    int success;
    char infoLog[512];

    switch (type)
    {
    case SHADER:
        glGetShaderiv(resource, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(resource, 512, NULL, infoLog);
            DebugLog("ERROR: Failed compiling vertex shader: " + std::string(infoLog));
        }
        break;

    case PROGRAM:
        glGetProgramiv(resource, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(resource, 1024, NULL, infoLog);
            DebugLog("ERROR: Failed creating program: " + std::string(infoLog));
        }
        break;
    
    default:
        break;
    }

    return !success;
}
