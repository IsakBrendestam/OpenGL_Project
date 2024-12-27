#ifndef SHADERGL_HEADER
#define SHADERGL_HEADER

#include <string>

#include <glm/gtc/type_ptr.hpp>

enum Status
{
    OK,
    ERROR
};

class ShaderGL
{
public:
    ShaderGL();
    ~ShaderGL();
    void LoadShader(std::string vShaderName, std::string fShaderName);
    void Use();

    void SetBool(const std::string& name, bool value);
    void SetInt(const std::string& name, int value);
    void SetFlot(const std::string& name, float value);
    void SetMat4(const std::string& name, glm::mat4 value);

    Status GetStatus() const;
    unsigned int GetShaderProgram() const;

private:
    std::string ReadShaderFile(std::string shaderName);

private:
    unsigned int m_shaderProgram;
    Status m_status;
};

#endif