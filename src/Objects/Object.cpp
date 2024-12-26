#include "Object.h"

#include "../../dep/glad/glad.h"
#include <GLFW/glfw3.h>

Object::Object()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };  

    // Vertex Buffer
    glGenBuffers(1, &m_VBO);  
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Vertex Array
    glGenVertexArrays(1, &m_VAO);  
    glBindVertexArray(m_VAO);

    m_shader.LoadShader("shader.vs", "shader.fs");
}

Object::~Object()
{

}

void Object::Update()
{

}

void Object::Draw()
{
    m_shader.Use();
}