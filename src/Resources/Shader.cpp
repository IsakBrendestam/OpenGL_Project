#include "Shader.h"

#include <../../dep/glad/glad.h>
#include <GLFW/glfw3.h>

//#include "Debug.h"

Shader::Shader()
{

}

void Shader::LoadShader(std::string vShaderPath, std::string fShaderPath)
{
    unsigned int vertexShader; 

    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Debug::CheckError(vertexShader, ResourceType::SHADER);

    // Fragment Shader
    unsigned int fragmentShader;

    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check compilation
    //Debug::CheckError(fragmentShader, ResourceType::SHADER);

    // Create shader program
    m_shaderProgram = glCreateProgram();

    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    //Debug::CheckError(m_shaderProgram, ResourceType::PROGRAM);

    // Destory shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 
}

void Shader::Use()
{
    glUseProgram(m_shaderProgram);
}

std::string Shader::ReadShaderFile(std::string shaderPath)
{

}

bool Shader::GetStatus()
{
    return m_status;
}

unsigned int Shader::GetShaderProgram()
{
    return m_shaderProgram;
}