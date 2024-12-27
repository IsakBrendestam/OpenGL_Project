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

    void SetBool(const std::string& name, bool value);
    void SetInt(const std::string& name, int value);
    void SetFlot(const std::string& name, float value);

    Status GetStatus() const;
    unsigned int GetShaderProgram() const;

private:
    std::string ReadShaderFile(std::string shaderName);

private:
    unsigned int m_shaderProgram;
    Status m_status;
};

#endif