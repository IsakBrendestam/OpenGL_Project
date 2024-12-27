#ifndef OBJECT_HEADER
#define OBJECT_HEADER

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image/stb_image.h>

#include "Engine/Resources/Shader.h"
#include "Engine/Resources/Mesh.h"

class Object
{
public:
    Object() = default;
    Object(const MeshColor& mesh);
    Object(const MeshTexture& mesh);

    virtual ~Object();

    void Init(const MeshColor& mesh);
    void Init(const MeshTexture& mesh);

    virtual void Update();
    virtual void Draw() = 0;

protected:
    void GenerateTexture(const std::string& textureName);

protected:
    unsigned int m_VBO;
    unsigned int m_VAO;
    unsigned int m_EBO;

    unsigned int m_texture;

    Shader m_shader;

    glm::mat4 m_transformMat;
};

#endif