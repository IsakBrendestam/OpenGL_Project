#include "Object.h"

#include "Utilities/Debug.h"

Object::Object(const VertexColor* vertices, unsigned int nVertices, const unsigned int* indices, unsigned int nIndices)
{
    Init(vertices, nVertices, indices, nIndices);
}

Object::Object(const VertexTexture* vertices, unsigned int nVertices, const unsigned int* indices, unsigned int nIndices, const std::string& textureName)
{
    Init(vertices, nVertices, indices, nIndices, textureName);
}

Object::~Object()
{
}

void Object::Init(const VertexColor* vertices, unsigned int nVertices, const unsigned int* indices, unsigned int nIndices)
{
    m_shader.LoadShader("ColorShader.vs", "ColorShader.fs");

    glGenBuffers(1, &m_VBO);  
    glGenBuffers(1, &m_EBO);
    glGenVertexArrays(1, &m_VAO);  

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(VertexColor), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColor), (void*)0);
    glEnableVertexAttribArray(0);  

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColor), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

void Object::Init(const VertexTexture* vertices, unsigned int nVertices, const unsigned int* indices, unsigned int nIndices, const std::string& textureName)
{
    m_shader.LoadShader("TextureShader.vs", "TextureShader.fs");

    glGenBuffers(1, &m_VBO);  
    glGenBuffers(1, &m_EBO);
    glGenVertexArrays(1, &m_VAO);  


    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(VertexTexture), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexTexture), (void*)0);
    glEnableVertexAttribArray(0);  

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexTexture), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    GenerateTexture(textureName);
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