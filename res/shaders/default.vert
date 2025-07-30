#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;
layout (location = 3) in uint aTexDepth;

out vec3 crntPos;
out vec3 normal;
out vec2 texCoord;
flat out uint texDepth;
out mat4 projection;

uniform mat4 camMatrix;

void main()
{
   crntPos = aPos;
   normal = aNormal;
   texCoord = aTex;
   texDepth = aTexDepth;
   projection = camMatrix;
   gl_Position = projection * vec4(crntPos, 1.0f);
}