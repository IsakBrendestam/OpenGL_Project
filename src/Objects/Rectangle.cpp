#include "Rectangle.h"

Rectangle::Rectangle(): Object()
{
    VertexColor vertices[] = {
        { 1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f}, // top right
        { 1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f}, // bottom right
        {-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f}, // bottom left
        {-1.0f,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f} // top left 
    };

    VertexTexture texVertices[] = {
        { 1.0f,  1.0f, 0.0f,   1.0f, 1.0f}, // top right
        { 1.0f, -1.0f, 0.0f,   1.0f, 0.0f}, // bottom right
        {-1.0f, -1.0f, 0.0f,   0.0f, 0.0f}, // bottom left
        {-1.0f,  1.0f, 0.0f,   0.0f, 1.0f} // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    MeshColor meshCol = MeshColor(vertices, 4, indices, 6);
    MeshTexture mesh = MeshTexture(texVertices, 4, indices, 6, "grid.jpg");

    //Object::Init(mesh, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 90.0f}, {0.5f, 0.5f, 0.5f});
    Object::Init(mesh, {0.0f, -1.0f, -5.0f}, {90.0f, 0.0f, 0.0f}, {5.0f, 5.0f, 5.0f});

    m_shader.Use();
}

Rectangle::~Rectangle()
{

}

void Rectangle::Update(double deltaTime)
{
    Object::Update(deltaTime);
}

void Rectangle::Draw()
{
    m_shader.Use();

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}