#include "Shader.h"

#include <../../dep/glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>

#include "Debug.h"
#include <stdlib.h>
#include <stdio.h>

#include <iostream>

Shader::Shader()
{

}

Shader::~Shader()
{
    glDeleteProgram(m_shaderProgram);
}

void Shader::LoadShader(std::string vShaderName, std::string fShaderName)
{
    std::string shaderData;

    unsigned int vertexShader; 

    shaderData = ReadShaderFile(vShaderName);
    const char* vsSource = shaderData.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vsSource, NULL);
    glCompileShader(vertexShader);

    Debug::CheckError(vertexShader, ResourceType::SHADER);

    // Fragment Shader
    unsigned int fragmentShader;

    shaderData = ReadShaderFile(fShaderName);
    const char* fsSource = shaderData.c_str();

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fsSource, NULL);
    glCompileShader(fragmentShader);

    // Check compilation
    Debug::CheckError(fragmentShader, ResourceType::SHADER);

    // Create shader program
    m_shaderProgram = glCreateProgram();

    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    Debug::CheckError(m_shaderProgram, ResourceType::PROGRAM);

    // Destory shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 
}

void Shader::Use()
{
    glUseProgram(m_shaderProgram);
}

std::string Shader::ReadShaderFile(std::string shaderName)
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

bool Shader::GetStatus()
{
    return m_status;
}

unsigned int Shader::GetShaderProgram()
{
    return m_shaderProgram;
}