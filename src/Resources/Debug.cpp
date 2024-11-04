#include "Debug.h"

#include "../../dep/glad/glad.h"
#include <GLFW/glfw3.h>

#include <stdio.h>

bool Debug::CheckError(unsigned int resource, ResourceType type)
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
            printf("ERROR: Failed compiling vertex shader: %s\n", infoLog);
            return true;
        }
        break;

    case PROGRAM:
        glGetProgramiv(resource, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(resource, 1024, NULL, infoLog);
            printf("ERROR: Failed creating program: %s\n", infoLog);
            return true;
        }
        break;
    
    default:
        break;
    }

    return false;
}