#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 vertexColor;

uniform mat4 worldMat;
uniform mat4 viewProjectionMat;

void main()
{
    gl_Position = viewProjectionMat * worldMat * vec4(aPos, 1.0f);
    vertexColor = vec4(aColor, 1.0f);
}