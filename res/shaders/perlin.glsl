#version 460 core

const float infinity = uintBitsToFloat(0x7F800000);

layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;
layout (rgba32f, binding = 0) uniform image2D screen;

uniform float seed;
uint state = (gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * imageSize(screen).x) * int(seed * 1000);

float rand()
{
	state = state * 747796405 + 2891336453;
	uint result = ((state >> ((state >> 28) + 4)) ^ state) * 277803737;
	result = (result >> 22) ^ result;
	return result / 4294967296.0;
}
float rand_normal()
{
	float theta = 2 * 3.1415926 * rand();
	float phi = sqrt(-2 * log(rand()));
	return phi * cos(theta);
}
vec3 rand_unit_vector()
{
	float x = rand_normal();
	float y = rand_normal();
	float z = rand_normal();
	return normalize(vec3(x, y, z));
}

void main()
{
	ivec2 coords = ivec2(gl_GlobalInvocationID.xy);
    imageStore(screen, coords, vec4(1.0, 0.0, 0.0, 1.0));
}