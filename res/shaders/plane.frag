#version 460 core

out vec4 FragColor;

uniform sampler2D screen;
uniform float numRenderedFrames;
in vec2 uv;

void main()
{
    FragColor = texture(screen, uv);
}