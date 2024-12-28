#version 330 core

out vec4 FragColor;

in vec2 textureCoord;
in vec3 normal;

uniform sampler2D textureSampler;

// Light Data
struct LightData 
{
    vec3 position;
    vec3 color;
    float ambientIntencity;
};

uniform LightData lightData;

void main()
{
    vec3 sampleColor = texture(textureSampler, textureCoord).xyz;

    vec3 res = sampleColor * lightData.ambientIntencity;
    FragColor = vec4(res, 1.0f);
}