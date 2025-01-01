#ifndef OBJECT_HEADER
#define OBJECT_HEADER

#include "glad.h"
#include <GLFW/glfw3.h>
#include "glm/gtc/type_ptr.hpp"

#include <stb_image/stb_image.h>

#include "Engine/OpenGL/ShaderGL.h"
#include "Engine/Resources/Mesh.h"

class Object
{
public:
    Object() = default;
    Object(const MeshColor& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    Object(const MeshTexture& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    virtual ~Object();

    void Init(const MeshColor& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    void Init(const MeshTexture& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    virtual void Update(double deltaTime);
    virtual void Draw() = 0;

protected:
    void GenerateTexture(const std::string& textureName);

protected:
    unsigned int m_VBO;
    unsigned int m_VAO;
    unsigned int m_EBO;

    unsigned int m_texture;

    ShaderGL m_shader;

    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;

    glm::mat4 m_transformMat;
};

#endif