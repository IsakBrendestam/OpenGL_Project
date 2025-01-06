#ifndef OBJECT_HEADER
#define OBJECT_HEADER

#include <vector>

#include "glad.h"
#include <GLFW/glfw3.h>
#include "glm/gtc/type_ptr.hpp"

#include <stb_image/stb_image.h>

#include "Engine/OpenGL/ShaderGL.h"
#include "Engine/Resources/Mesh.h"

#include "Engine/Components/ComponentObject.h"


class Object: public ComponentObject
{
public:
    Object();
    Object(const MeshColor& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    Object(const MeshTexture& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    Object(const MeshData& mesh, const std::string& textureName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    Object(glm::vec3 color, const MeshData& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    virtual ~Object();

    void Init(const MeshColor& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    void Init(const MeshTexture& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    void Init(const MeshData& mesh, const std::string& textureName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    void Init(glm::vec3 color, const MeshData& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    virtual void Update(double deltaTime) = 0;
    virtual void Render();

protected:
    virtual void Draw() = 0;
    virtual void UpdateLight();
    virtual void UpdateMatrices();

    void UpdateColor(const glm::vec3& color);

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