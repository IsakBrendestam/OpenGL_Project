#version 330 core

out vec4 FragColor;

in vec2 textureCoord;

uniform float scalar;

uniform sampler2D textureSampler;

void main()
{
    //FragColor = vec4(textureCoord, 0, 1);
    FragColor = texture(textureSampler, textureCoord);
}