#ifndef SHADER_HEADER
#define SHADER_HEADER

#include <string>

class Shader
{
public:
    Shader();
    void LoadShader(std::string vShaderName, std::string fShaderName);
    void Use();
    bool GetStatus();

    unsigned int GetShaderProgram();

private:
    std::string ReadShaderFile(std::string shaderName);

private:
    unsigned int m_shaderProgram;
    bool m_status;
};

#endif