#version 330 core

out vec4 FragColor;

in vec3 crntPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

float sigmoid(float x, float n)
{
   return pow(x, n) / (pow(x, n) + pow(1.0f - x, n));
}

vec4 pointLight()
{
   vec3 lightVec = lightPos - crntPos;
   float dist = length(lightVec);
   float a = 0.05f;
   float b = 0.7f;
   float intensity = 1.0f;
   // float intensity = 1.0f / (a * dist * dist + b * dist + 1.0f);

   // Ambient Lighting
   float ambient = 0.0f;

   // Diffuse Lighting
   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(lightVec);
   float diffusion = max(dot(norm, lightDir), 0.0f);

   // Specular lighting (uses a sigmoid function on the specular map to change the intensity)
   float specularLight = 5 * 1.5f;
   vec3 viewDir = normalize(camPos - crntPos);
   vec3 reflectDir = normalize(reflect(-lightDir, norm));
   float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 16);
   float specular = specAmount * specularLight;

   return (texture(diffuse0, texCoord) * (diffusion + ambient + specular) * intensity) * lightColor;
   // return specularLight * vec4(1.0f);
}

void main()
{
   FragColor = pointLight();
}