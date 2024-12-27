#include "Rectangle.h"

Rectangle::Rectangle(): Object()
{
    VertexColor vertices[] = {
        { 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f}, // top right
        { 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f}, // bottom right
        {-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f}, // bottom left
        {-0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f} // top left 
    };

    VertexTexture texVertices[] = {
        { 0.5f,  0.5f, 0.0f,   1.0f, 1.0f}, // top right
        { 0.5f, -0.5f, 0.0f,   1.0f, 0.0f}, // bottom right
        {-0.5f, -0.5f, 0.0f,   0.0f, 0.0f}, // bottom left
        {-0.5f,  0.5f, 0.0f,   0.0f, 1.0f} // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    MeshTexture mesh = MeshTexture(texVertices, 4, indices, 6, "rust.png");
    
    Object::Init(mesh, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 90.0f}, {0.5f, 0.5f, 0.5f});

    m_shader.Use();
    m_shader.SetFlot("scalar", 1.0f);
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