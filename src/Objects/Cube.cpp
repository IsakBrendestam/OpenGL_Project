#include "Cube.h"

#include "Engine/Resources/Light.h"

#include "Engine/Utilities/Debug.h"

Cube::Cube(glm::vec3 position, glm::vec3 rotation, float scale): Object()
{
    const glm::vec3 color = {0.6f, 0.6f, 0.6f};
    ShaderVertexColor colVertices[] = {
        // Front face
        {{-1.0f, -1.0f,  1.0f}, {color.r, color.g, color.b}, {0.0f,  0.0f,  1.0f}}, // Bottom-left
        {{ 1.0f, -1.0f,  1.0f}, {color.r, color.g, color.b}, {0.0f,  0.0f,  1.0f}}, // Bottom-right
        {{ 1.0f,  1.0f,  1.0f}, {color.r, color.g, color.b}, {0.0f,  0.0f,  1.0f}}, // Top-right
        {{-1.0f,  1.0f,  1.0f}, {color.r, color.g, color.b}, {0.0f,  0.0f,  1.0f}}, // Top-left

        // Back face
        {{ 1.0f, -1.0f, -1.0f}, {color.r, color.g, color.b}, { 0.0f,  0.0f, -1.0f}}, // Bottom-left
        {{-1.0f, -1.0f, -1.0f}, {color.r, color.g, color.b}, { 0.0f,  0.0f, -1.0f}}, // Bottom-right
        {{-1.0f,  1.0f, -1.0f}, {color.r, color.g, color.b}, { 0.0f,  0.0f, -1.0f}}, // Top-right
        {{ 1.0f,  1.0f, -1.0f}, {color.r, color.g, color.b}, { 0.0f,  0.0f, -1.0f}}, // Top-left

        // Left face
        {{-1.0f, -1.0f, -1.0f}, {color.r, color.g, color.b}, {-1.0f,  0.0f,  0.0f}}, // Bottom-left
        {{-1.0f, -1.0f,  1.0f}, {color.r, color.g, color.b}, {-1.0f,  0.0f,  0.0f}}, // Bottom-right
        {{-1.0f,  1.0f,  1.0f}, {color.r, color.g, color.b}, {-1.0f,  0.0f,  0.0f}}, // Top-right
        {{-1.0f,  1.0f, -1.0f}, {color.r, color.g, color.b}, {-1.0f,  0.0f,  0.0f}}, // Top-left

        // Right face
        {{ 1.0f, -1.0f,  1.0f}, {color.r, color.g, color.b}, { 1.0f,  0.0f,  0.0f}}, // Bottom-left
        {{ 1.0f, -1.0f, -1.0f}, {color.r, color.g, color.b}, { 1.0f,  0.0f,  0.0f}}, // Bottom-right
        {{ 1.0f,  1.0f, -1.0f}, {color.r, color.g, color.b}, { 1.0f,  0.0f,  0.0f}}, // Top-right
        {{ 1.0f,  1.0f,  1.0f}, {color.r, color.g, color.b}, { 1.0f,  0.0f,  0.0f}}, // Top-left

        // Top face
        {{-1.0f,  1.0f,  1.0f}, {color.r, color.g, color.b}, { 0.0f,  1.0f,  0.0f}}, // Bottom-left
        {{ 1.0f,  1.0f,  1.0f}, {color.r, color.g, color.b}, { 0.0f,  1.0f,  0.0f}}, // Bottom-right
        {{ 1.0f,  1.0f, -1.0f}, {color.r, color.g, color.b}, { 0.0f,  1.0f,  0.0f}}, // Top-right
        {{-1.0f,  1.0f, -1.0f}, {color.r, color.g, color.b}, { 0.0f,  1.0f,  0.0f}}, // Top-left

        // Bottom face
        {{-1.0f, -1.0f, -1.0f}, {color.r, color.g, color.b}, { 0.0f, -1.0f,  0.0f}}, // Bottom-left
        {{ 1.0f, -1.0f, -1.0f}, {color.r, color.g, color.b}, { 0.0f, -1.0f,  0.0f}}, // Bottom-right
        {{ 1.0f, -1.0f,  1.0f}, {color.r, color.g, color.b}, { 0.0f, -1.0f,  0.0f}}, // Top-right
        {{-1.0f, -1.0f,  1.0f}, {color.r, color.g, color.b}, { 0.0f, -1.0f,  0.0f}}, // Top-left
    };

    ShaderVertexTexture texVertices[] = {
        // Front face
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f,  0.0f,  1.0f}}, // Bottom-left
        {{ 1.0f, -1.0f,  1.0f}, {1.0f, 0.0f}, {0.0f,  0.0f,  1.0f}}, // Bottom-right
        {{ 1.0f,  1.0f,  1.0f}, {1.0f, 1.0f}, {0.0f,  0.0f,  1.0f}}, // Top-right
        {{-1.0f,  1.0f,  1.0f}, {0.0f, 1.0f}, {0.0f,  0.0f,  1.0f}}, // Top-left

        // Back face
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, { 0.0f,  0.0f, -1.0f}}, // Bottom-left
        {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}, { 0.0f,  0.0f, -1.0f}}, // Bottom-right
        {{-1.0f,  1.0f, -1.0f}, {1.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}}, // Top-right
        {{ 1.0f,  1.0f, -1.0f}, {0.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}}, // Top-left

        // Left face
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {-1.0f,  0.0f,  0.0f}}, // Bottom-left
        {{-1.0f, -1.0f,  1.0f}, {1.0f, 0.0f}, {-1.0f,  0.0f,  0.0f}}, // Bottom-right
        {{-1.0f,  1.0f,  1.0f}, {1.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}}, // Top-right
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}}, // Top-left

        // Right face
        {{ 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, { 1.0f,  0.0f,  0.0f}}, // Bottom-left
        {{ 1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}, { 1.0f,  0.0f,  0.0f}}, // Bottom-right
        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}}, // Top-right
        {{ 1.0f,  1.0f,  1.0f}, {0.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}}, // Top-left

        // Top face
        {{-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}}, // Bottom-left
        {{ 1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}}, // Bottom-right
        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}}, // Top-right
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}}, // Top-left

        // Bottom face
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, { 0.0f, -1.0f,  0.0f}}, // Bottom-left
        {{ 1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}, { 0.0f, -1.0f,  0.0f}}, // Bottom-right
        {{ 1.0f, -1.0f,  1.0f}, {1.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}}, // Top-right
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}}, // Top-left
    };

    unsigned int indices[] = {
        // Front face
        0, 1, 2,  
        2, 3, 0,

        // Back face
        4, 5, 6,  
        6, 7, 4,

        // Left face
        8, 9, 10, 
        10, 11, 8,

        // Right face
        12, 13, 14, 
        14, 15, 12,

        // Top face
        16, 17, 18, 
        18, 19, 16,

        // Bottom face
        20, 21, 22, 
        22, 23, 20
    };

    MeshTexture mesh = MeshTexture(texVertices, 24, indices, 36, "tiles.jpg");
    MeshColor meshCol = MeshColor(colVertices, 24, indices, 36);

    //Object::Init(meshCol, position, {0.0f, 0.0f, 90.0f}, scale);

    MeshData md;
    md.vertexInfo.vertexData = colVertices;
    md.vertexInfo.nrOfVerticesInBuffer = 24;
    md.vertexInfo.sizeOfVertex = sizeof(ShaderVertexColor);
    md.indexInfo.indexData = indices;
    md.indexInfo.nrOfIndicesInBuffer = 36;

    Object::Init({0.4f, 0.4f, 0.4f}, md, position, rotation, {scale, scale, scale});

    AddComponent(new ColliderComponent());
    GetComponent<ColliderComponent>()->AssignAABBCollider(position, {scale, scale, scale});
}

Cube::~Cube()
{

}

void Cube::Update(double deltaTime)
{
    /*
    m_rotation.x += glm::radians(2.0f) * deltaTime;
    m_rotation.y += glm::radians(2.0f) * deltaTime;
    m_rotation.z += glm::radians(2.0f) * deltaTime;
    */
}

void Cube::OnCollision(const ComponentObject& other)
{
    m_shader.Use();
    UpdateColor({1.0f, 0.0f, 0.0f});
}

void Cube::Draw()
{
    m_shader.Use();

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}