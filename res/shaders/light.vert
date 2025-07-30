#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

out vec3 crntPos;
out vec2 texCoord;

uniform mat4 transform;
uniform mat4 camMatrix;

void main()
{
	crntPos = vec3(transform * vec4(aPos, 1.0f));
	texCoord = aTex;
	gl_Position = camMatrix * vec4(crntPos, 1.0f);
}