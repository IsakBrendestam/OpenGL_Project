#include "Object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine/Utilities/Debug.h"

#include "Engine/CameraManager.h"

Object::Object(const MeshColor& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    Init(mesh, position, rotation, scale);
}

Object::Object(const MeshTexture& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    Init(mesh, position, rotation, scale);
}

Object::~Object()
{
}

void Object::Init(const MeshColor& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    m_position = position;
    m_rotation = rotation;
    m_scale = scale;

    m_shader.LoadShader("ColorShader.vs", "ColorShader.fs");
    m_shader.Use();

    glGenBuffers(1, &m_VBO);  
    glGenBuffers(1, &m_EBO);
    glGenVertexArrays(1, &m_VAO);  

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.g_nVertices * sizeof(ShaderVertexColor), mesh.g_vertices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ShaderVertexColor), (void*)0);
    glEnableVertexAttribArray(0);  

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ShaderVertexColor), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // Normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(ShaderVertexColor), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.g_nIndices * sizeof(unsigned int), mesh.g_indices, GL_STATIC_DRAW);
}

void Object::Init(const MeshTexture& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    m_position = position;
    m_rotation = rotation;
    m_scale = scale;

    m_shader.LoadShader("TextureShader.vs", "TextureShader.fs");
    m_shader.Use();

    glGenBuffers(1, &m_VBO);  
    glGenBuffers(1, &m_EBO);
    glGenVertexArrays(1, &m_VAO);  


    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.g_nVertices * sizeof(ShaderVertexTexture), mesh.g_vertices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ShaderVertexTexture), (void*)0);
    glEnableVertexAttribArray(0);  

    // Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ShaderVertexTexture), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // ST
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ShaderVertexTexture), (void*)(5*sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.g_nIndices * sizeof(unsigned int), mesh.g_indices, GL_STATIC_DRAW);

    GenerateTexture(mesh.g_textureName);
}

void Object::GenerateTexture(const std::string& textureName)
{
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::string texturePath = "res/Textures/" + textureName;
    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(true);  
    unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nChannels, 0);

    if (!data)
    {
        DebugLog("ERROR: Loading texture " + textureName + " failed");
        return;
    }
    
    if (nChannels == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void Object::Update(double deltaTime)
{
    m_transformMat = glm::identity<glm::mat4>();

    m_transformMat = glm::translate(m_transformMat, m_position);
    m_transformMat = glm::rotate(m_transformMat, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_transformMat = glm::rotate(m_transformMat, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_transformMat = glm::rotate(m_transformMat, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_transformMat = glm::scale(m_transformMat, m_scale);

    m_shader.Use();
    m_shader.SetMat4("worldMat", m_transformMat);
    m_shader.SetMat4("viewProjectionMat", CameraManager::GetCurrentCamera().GetViewProjectionMatrix());
}