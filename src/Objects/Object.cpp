#include "Object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine/Utilities/Debug.h"

#include "Engine/CameraManager.h"
#include "Engine/Resources/Light.h"

Object::Object()
{
    AddComponent(new TransformComponent({0, 0, 0}, {0, 0, 0}, {0, 0, 0}));
}

Object::Object(const MeshColor& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    Init(mesh, position, rotation, scale);
}

Object::Object(const MeshTexture& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    Init(mesh, position, rotation, scale);
}

Object::Object(const MeshData& mesh, const std::string& textureName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    Init(mesh, textureName, position, rotation, scale);
}

Object::Object(glm::vec3 color, const MeshData& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    Init(color, mesh, position, rotation, scale);
}

Object::~Object()
{
}

void Object::Init(const MeshColor& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    AddComponent(new TransformComponent(position, rotation, scale));

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

    UpdateLight();
}

void Object::Init(const MeshTexture& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    AddComponent(new TransformComponent(position, rotation, scale));

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

    // ST
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ShaderVertexTexture), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // Normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(ShaderVertexTexture), (void*)(5*sizeof(float)));
    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.g_nIndices * sizeof(unsigned int), mesh.g_indices, GL_STATIC_DRAW);

    GenerateTexture(mesh.g_textureName);
}

void Object::Init(const MeshData& mesh, const std::string& textureName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    AddComponent(new TransformComponent(position, rotation, scale));

    m_shader.LoadShader("TextureShader.vs", "TextureShader.fs");
    m_shader.Use();

    glGenBuffers(1, &m_VBO);  
    glGenBuffers(1, &m_EBO);
    glGenVertexArrays(1, &m_VAO);  


    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glBufferData(GL_ARRAY_BUFFER, 
                 mesh.vertexInfo.nrOfVerticesInBuffer * mesh.vertexInfo.sizeOfVertex, 
                 mesh.vertexInfo.vertexData, 
                 GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, mesh.vertexInfo.sizeOfVertex, (void*)0);
    glEnableVertexAttribArray(0);  

    // ST
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, mesh.vertexInfo.sizeOfVertex, (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // Normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, mesh.vertexInfo.sizeOfVertex, (void*)(5*sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                 mesh.indexInfo.nrOfIndicesInBuffer * sizeof(unsigned int),
                 mesh.indexInfo.indexData, 
                 GL_STATIC_DRAW);

    GenerateTexture(textureName);
}

void Object::Init(glm::vec3 color, const MeshData& mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    AddComponent(new TransformComponent(position, rotation, scale));

    m_shader.LoadShader("SolidColorShader.vs", "ColorShader.fs");
    m_shader.Use();

    glGenBuffers(1, &m_VBO);  
    glGenBuffers(1, &m_EBO);
    glGenVertexArrays(1, &m_VAO);  


    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glBufferData(GL_ARRAY_BUFFER, 
                 mesh.vertexInfo.nrOfVerticesInBuffer * mesh.vertexInfo.sizeOfVertex, 
                 mesh.vertexInfo.vertexData, 
                 GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, mesh.vertexInfo.sizeOfVertex, (void*)0);
    glEnableVertexAttribArray(0);  

    // Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, mesh.vertexInfo.sizeOfVertex, (void*)(5*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                 mesh.indexInfo.nrOfIndicesInBuffer * sizeof(unsigned int),
                 mesh.indexInfo.indexData, 
                 GL_STATIC_DRAW);
                
    m_shader.Setvec3("aColor", color);
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

void Object::UpdateColor(const glm::vec3& color)
{
    m_shader.Use();
    m_shader.Setvec3("aColor", color);
}

void Object::UpdateLight()
{
    m_shader.Use();

    LightData lightData = {{-1, 1, 2}, {1.0f, 1.0f, 1.0f}, 0.75f, 2.0f};
    m_shader.Setvec3("lightData.position", lightData.position);
    m_shader.Setvec3("lightData.color", lightData.color);
    m_shader.SetFlot("lightData.ambientIntensity", lightData.ambientIntensity);
    m_shader.SetFlot("lightData.lightIntensity", lightData.lightIntensity);
}

void Object::UpdateMatrices()
{
    TransformComponent* transform = GetComponent<TransformComponent>();

    m_shader.Use();
    m_shader.SetMat4("worldMat", transform->GetWorldMat());
    m_shader.SetMat4("viewProjectionMat", CameraManager::GetCurrentCamera().GetViewProjectionMatrix());
}

void Object::Render()
{
    UpdateMatrices();
    UpdateLight();
    Draw();
}