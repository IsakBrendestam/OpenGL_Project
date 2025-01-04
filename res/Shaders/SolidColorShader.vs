#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec4 worldPos;
out vec3 normal;
out vec4 vertexColor;

uniform mat4 worldMat;
uniform mat4 viewProjectionMat;

uniform vec3 aColor;

void main()
{
    worldPos = worldMat * vec4(aPos, 1.0f);
    gl_Position = viewProjectionMat * worldPos;

    vec4 tempNormal = worldMat * vec4(aNormal, 0.0f);
    normal = tempNormal.xyz;

    vertexColor = vec4(aColor, 1.0f);
}