#ifndef OBJECT_HEADER
#define OBJECT_HEADER

#include "../../dep/glad/glad.h"
#include <GLFW/glfw3.h>

#include "Engine/Resources/Shader.h"
#include "Engine/Resources/Vertex.h"

class Object
{
public:
    Object() = default;
    Object(const Vertex* vertices, unsigned int nVertices, const unsigned int* indices, unsigned int nIndices);
    virtual ~Object();

    void Init(const Vertex* vertices, unsigned int nVertices, const unsigned int* indices, unsigned int nIndices);

    virtual void Update() = 0;
    virtual void Draw() = 0;

protected:
    unsigned int m_VBO;
    unsigned int m_VAO;
    unsigned int m_EBO;

    Shader m_shader;
};

#endif