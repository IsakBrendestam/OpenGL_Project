#ifndef OBJECT_HEADER
#define OBJECT_HEADER

#include "../../dep/glad/glad.h"
#include <GLFW/glfw3.h>

#include "Engine/Resources/Shader.h"

class Object
{
public:
    Object() = default;
    Object(float* vertices, unsigned int nVertices, unsigned int* indices, unsigned int nIndices);
    virtual ~Object();

    void Init(float* vertices, unsigned int nVertices, unsigned int* indices, unsigned int nIndices);

    virtual void Update() = 0;
    virtual void Draw() = 0;

protected:
    unsigned int m_VBO;
    unsigned int m_VAO;
    unsigned int m_EBO;

    Shader m_shader;
};

#endif