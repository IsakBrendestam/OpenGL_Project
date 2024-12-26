#ifndef OBJECT_HEADER
#define OBJECT_HEADER

#include <vector>

#include "Engine/Resources/Shader.h"

class Object
{
public:
    Object();
    ~Object();

    void Update();
    void Draw();

private:
    unsigned int m_VBO;
    unsigned int m_VAO;

    Shader m_shader;
};

#endif