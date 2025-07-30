#version 330 core

// Inputs
in vec2 texCoord;
flat in uint texDepth;
// Outputs
out vec4 FragColor;
// Uniforms
uniform sampler2DArray terrainTex;

void main()
{
   vec4 color = texture(terrainTex, vec3(texCoord, texDepth));
   if (color.a < 1.0) {
       discard; // Discard fragments with low alpha
   }
   FragColor = color;
}