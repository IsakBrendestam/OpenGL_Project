#ifndef OBJECT_HEADER
#define OBJECT_HEADER

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "stb_image/stb_image.h"

#include "Engine/Resources/Shader.h"
#include "Engine/Resources/Vertex.h"

class Object
{
public:
    Object() = default;
    Object(const VertexColor* vertices, unsigned int nVertices, const unsigned int* indices, unsigned int nIndices);
    Object(const VertexTexture* vertices, unsigned int nVertices, const unsigned int* indices, unsigned int nIndices, const std::string& textureName);

    virtual ~Object();

    void Init(const VertexColor* vertices, unsigned int nVertices, const unsigned int* indices, unsigned int nIndices);
    void Init(const VertexTexture* vertices, unsigned int nVertices, const unsigned int* indices, unsigned int nIndices, const std::string& textureName);

    virtual void Update() = 0;
    virtual void Draw() = 0;

protected:
    void GenerateTexture(const std::string& textureName);

protected:
    unsigned int m_VBO;
    unsigned int m_VAO;
    unsigned int m_EBO;

    unsigned int m_texture;

    Shader m_shader;
};

#endif