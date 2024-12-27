#ifndef SHADER_HEADER
#define SHADER_HEADER

#include <string>

enum Status
{
    OK,
    ERROR
};

class Shader
{
public:
    Shader();
    ~Shader();
    void LoadShader(std::string vShaderName, std::string fShaderName);
    void Use();
    Status GetStatus();

    unsigned int GetShaderProgram();

private:
    std::string ReadShaderFile(std::string shaderName);

private:
    unsigned int m_shaderProgram;
    Status m_status;
};

#endif