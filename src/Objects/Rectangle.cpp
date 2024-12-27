#include "Rectangle.h"

Rectangle::Rectangle(): Object()
{
    Vertex vertices[] = {
        {0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f}, // top right
        {0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f}, // bottom right
        {-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f}, // bottom left
        {-0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f} // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    
    Object::Init(vertices, 4, indices, 6);
}

Rectangle::~Rectangle()
{

}

void Rectangle::Update()
{

}

void Rectangle::Draw()
{
    m_shader.Use();

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}