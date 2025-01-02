#version 330 core

out vec4 FragColor;

in vec4 worldPos;
in vec3 normal;
in vec4 vertexColor;

// Light Data
struct LightData 
{
    vec3 position;
    vec3 color;
    float ambientIntensity;
    float lightIntensity;
};

uniform LightData lightData;

void main()
{
    vec4 sampleColor = vertexColor;

    // Ambient Lighting
    vec3 ambient = lightData.ambientIntensity * lightData.color;

    // Diffuse Lighting
    vec3 lightDistance = lightData.position - worldPos.xyz;
    vec3 lightDirection = normalize(lightDistance);

    float cosTheta = max(dot(normalize(normal), lightDirection), 0.0f);
    float r2 = pow(length(lightDistance), 2.0f);

    vec3 diffuse = 1 / r2 * cosTheta * lightData.color * lightData.lightIntensity;

    // Calculate Final Color
    vec3 lighting = ambient + diffuse;
    vec3 res = lighting * sampleColor.rgb;

    FragColor = vec4(res, sampleColor.a);
}