#include "Cube.h"

Cube::Cube(glm::vec3 position): Object()
{
    VertexColor vertices[] = {
        {-1.0f, -1.0f,  1.0,  0.0f, 0.0f, 1.0f}, //0
        { 1.0f, -1.0f,  1.0,  1.0f, 0.0f, 0.0f}, //1
        {-1.0f,  1.0f,  1.0,  0.0f, 0.0f, 1.0f}, //2
        { 1.0f,  1.0f,  1.0,  1.0f, 1.0f, 0.0f}, //3
        {-1.0f, -1.0f, -1.0,  1.0f, 1.0f, 0.0f}, //4
        { 1.0f, -1.0f, -1.0,  1.0f, 0.0f, 0.0f}, //5
        {-1.0f,  1.0f, -1.0,  0.0f, 0.0f, 1.0f}, //6
        { 1.0f,  1.0f, -1.0,  0.0f, 1.0f, 0.0f}, //7
    };

    VertexTexture texVertices[] = {
        {-1.0f, -1.0f,  1.0f,  0.0f, 0.0f}, //0
        { 1.0f, -1.0f,  1.0f,  1.0f, 0.0f}, //1
        {-1.0f,  1.0f,  1.0f,  0.0f, 0.0f}, //2
        { 1.0f,  1.0f,  1.0f,  1.0f, 1.0f}, //3
        {-1.0f, -1.0f, -1.0f,  1.0f, 1.0f}, //4
        { 1.0f, -1.0f, -1.0f,  1.0f, 0.0f}, //5
        {-1.0f,  1.0f, -1.0f,  0.0f, 0.0f}, //6
        { 1.0f,  1.0f, -1.0f,  0.0f, 1.0f}, //7
    };

    unsigned int indices[] = {
        //Top
        2, 6, 7,
        2, 3, 7,

        //Bottom
        0, 4, 5,
        0, 1, 5,

        //Left
        0, 2, 6,
        0, 4, 6,

        //Right
        1, 3, 7,
        1, 5, 7,

        //Front
        0, 2, 3,
        0, 1, 3,

        //Back
        4, 6, 7,
        4, 5, 7
    };

    MeshTexture mesh = MeshTexture(texVertices, 8, indices, 36, "rust.png");
    MeshColor meshCol = MeshColor(vertices, 8, indices, 36);

    Object::Init(meshCol, position, {0.0f, 0.0f, 90.0f}, {0.5f, 0.5f, 0.5f});

    m_shader.Use();
}

Cube::~Cube()
{

}

void Cube::Update(double deltaTime)
{
    m_rotation.x += glm::radians(2.0f) * deltaTime;
    m_rotation.y += glm::radians(2.0f) * deltaTime;
    m_rotation.z += glm::radians(2.0f) * deltaTime;

    Object::Update(deltaTime);
}

void Cube::Draw()
{
    m_shader.Use();

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}