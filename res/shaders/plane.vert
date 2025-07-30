#version 460 core

layout (location = 0) in vec3 crntPos;

out vec2 uv;

void main()
{
    uv = (crntPos.xy / 2.0f) + 0.5f;
    gl_Position = vec4(crntPos, 1.0f);
}