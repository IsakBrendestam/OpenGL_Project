#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aST;
layout (location = 2) in vec3 aNormal;

out vec2 textureCoord;
out vec3 normal;

uniform mat4 worldMat;
uniform mat4 viewProjectionMat;

void main()
{
    gl_Position = viewProjectionMat * worldMat * vec4(aPos, 1.0f);
    textureCoord = aST;
    normal = aNormal;
}