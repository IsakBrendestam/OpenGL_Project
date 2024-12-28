#include "ShaderGL.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>

#include "Utilities/Debug.h"
#include <stdlib.h>
#include <stdio.h>

#include <iostream>

ShaderGL::ShaderGL():
    m_status(Status::OK)
{

}

ShaderGL::~ShaderGL()
{
    glDeleteProgram(m_shaderProgram);
}

void ShaderGL::LoadShader(std::string vShaderName, std::string fShaderName)
{
    std::string shaderData;

    // Vertex Shader
    unsigned int vertexShader; 

    shaderData = ReadShaderFile(vShaderName);
    const char* vsSource = shaderData.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vsSource, NULL);
    glCompileShader(vertexShader);

    // Check compilation
    CheckError(vertexShader, ResourceType::SHADER);

    // Fragment Shader
    unsigned int fragmentShader;

    shaderData = ReadShaderFile(fShaderName);
    const char* fsSource = shaderData.c_str();

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fsSource, NULL);
    glCompileShader(fragmentShader);

    // Check compilation
    if (CheckError(fragmentShader, ResourceType::SHADER))
        m_status = Status::ERROR;

    // Create shader program
    m_shaderProgram = glCreateProgram();

    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    if (CheckError(m_shaderProgram, ResourceType::PROGRAM))
        m_status = Status::ERROR;

    // Destory shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 
}

void ShaderGL::Use()
{
    glUseProgram(m_shaderProgram);
}

std::string ShaderGL::ReadShaderFile(std::string shaderName)
{
    std::ifstream file("res/Shaders/" + shaderName, std::ios::binary | std::ios::ate);

    if (!file.is_open())
        return "";

    std::streamsize size = file.tellg();
    file.seekg(0);

    std::string buffer(size, '\0');
    if (!file.read(&buffer[0], size))
        return "";

    return buffer;
}

void ShaderGL::SetBool(const std::string& name, bool value)
{
    glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), (int)value);
}

void ShaderGL::SetInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
}

void ShaderGL::SetFlot(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
}

void ShaderGL::Setvec3(const std::string& name, glm::vec3 value)
{
    glUniform3fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &value[0]); 
}

void ShaderGL::SetMat4(const std::string& name, glm::mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

Status ShaderGL::GetStatus() const
{
    return m_status;
}

unsigned int ShaderGL::GetShaderProgram() const
{
    return m_shaderProgram;
}