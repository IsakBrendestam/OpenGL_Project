#include "Object.h"

#include "Utilities/Debug.h"

Object::Object(const Vertex* vertices, unsigned int nVertices, const unsigned int* indices, unsigned int nIndices)
{
    Init(vertices, nVertices, indices, nIndices);
}

Object::~Object()
{
}

void Object::Init(const Vertex* vertices, unsigned int nVertices, const unsigned int* indices, unsigned int nIndices)
{
    m_shader.LoadShader("shader.vs", "shader.fs");

    glGenBuffers(1, &m_VBO);  
    glGenBuffers(1, &m_EBO);
    glGenVertexArrays(1, &m_VAO);  

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);  

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}