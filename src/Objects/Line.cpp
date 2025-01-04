#include "Line.h"

Line::Line(const std::vector<glm::vec3>& positions, const glm::vec3& color): Object()
{
    m_nVertices = positions.size();
    m_nIndices = (m_nVertices-1) * 2;

    ShaderVertexLine vertices[positions.size()-1];
    unsigned int indices[m_nIndices];
    for (int i = 0; i < positions.size(); i++)
    {
        if (i < m_nIndices)
        {
            indices[i*2] = i;
            indices[i*2+1] = i+1;
        }

        for (int j = 0; j < 3; j++)
        {
            vertices[i].g_position[j] = positions[i][j];
            vertices[i].g_color[j] = color[j];
        }
    }

    m_shader.LoadShader("LineShader.vs", "LineShader.fs");
    m_shader.Use();

    glGenBuffers(1, &m_VBO);  
    glGenVertexArrays(1, &m_VAO);  

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_nVertices * sizeof(ShaderVertexLine), vertices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ShaderVertexLine), (void*)0);
    glEnableVertexAttribArray(0);  

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ShaderVertexLine), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
}

Line::~Line()
{

}

void Line::Update(double deltaTime)
{
    Object::Update(deltaTime);
}

void Line::Draw()
{
    m_shader.Use();

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_LINE_STRIP, 0, m_nVertices);
    glBindVertexArray(0);
}