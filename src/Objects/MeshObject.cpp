#include "MeshObject.h"

#include "Engine/Resources/Light.h"

MeshObject::MeshObject(MeshData mesh, const std::string& textureName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale): 
    Object(mesh, textureName, position, rotation, scale), m_mesh(mesh)
{
    m_shader.Use();
}

MeshObject::MeshObject(glm::vec3 color, MeshData mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale):
    Object(color, mesh, position, rotation, scale), m_mesh(mesh)
{
    m_shader.Use();
}

MeshObject::~MeshObject()
{

}

void MeshObject::Update(double deltaTime)
{
    //m_rotation.x += glm::radians(2.0f) * deltaTime;
    m_rotation.y += glm::radians(2.0f) * deltaTime;
    //m_rotation.z += glm::radians(2.0f) * deltaTime;
}

void MeshObject::Draw()
{
    m_shader.Use();

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_mesh.indexInfo.nrOfIndicesInBuffer, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}