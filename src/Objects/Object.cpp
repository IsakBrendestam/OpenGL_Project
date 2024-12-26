#include "Object.h"

#include "../../dep/glad/glad.h"
#include <GLFW/glfw3.h>

#include "Utilities/Debug.h"

Object::Object()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };  

    m_nVertices = 9;
    m_vertices = (float*)malloc(sizeof(float) * 9);
    memcpy(m_vertices, vertices, sizeof(float) * 9);

    m_shader.LoadShader("shader.vs", "shader.fs");
}

Object::~Object()
{
    free(m_vertices);
}

void Object::Update()
{

}

void Object::Draw()
{
    m_shader.Use();

    unsigned int VBO;
    glGenBuffers(1, &VBO);  
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_nVertices * sizeof(float), m_vertices, GL_STATIC_DRAW);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);  
    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    glDrawArrays(GL_TRIANGLES, 0, 3);
}