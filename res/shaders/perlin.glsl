#version 460 core

const float infinity = uintBitsToFloat(0x7F800000);

layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;
layout (rgba32f, binding = 1) uniform image2D screen;

uniform float seed;
uint state = (gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * imageSize(screen).x) * int(seed * 1000);

float rand(vec2 xy) {
    return fract(sin(dot(xy.xy+seed,
    vec2(12.9898,78.233)))*
	43758.5453123);
}
float rand(vec2 xy, float seed) {
    return fract(sin(dot(xy.xy+seed,
    vec2(12.9898,78.233)))*
	43758.5453123);
}
vec2 rand_vec2(vec2 xy)
{
	float tau = 6.283185;
    float angle = rand(xy) * tau;
    return vec2(cos(angle), sin(angle));
}
float perlin_noise(vec2 uv, float cells_count)
{
    vec2 coords = uv * cells_count;
    vec2 cell_pos =  floor(coords);
    vec2 local_pos = (coords - cell_pos);
    vec2 blend = local_pos * local_pos * (3.0f - 2.0f * local_pos);
    
    vec2 a = cell_pos + vec2(0, 0);
    vec2 b = cell_pos + vec2(1, 0);
    vec2 c = cell_pos + vec2(0, 1);
    vec2 d = cell_pos + vec2(1, 1);
    
    float a_dot = dot(coords - a, rand_vec2(a));
    float b_dot = dot(coords - b, rand_vec2(b));
    float c_dot = dot(coords - c, rand_vec2(c));
    float d_dot = dot(coords - d,  rand_vec2(d));
    
    float noise_value = mix(mix(a_dot, b_dot, blend.x), mix(c_dot, d_dot, blend.x), blend.y);
    
    return (0.5 + 0.5 * (noise_value / 0.7));
}
void main()
{
	ivec2 coords = ivec2(gl_GlobalInvocationID.xy);
	vec2 uv = vec2(coords) / vec2(imageSize(screen));
	
	float noise = perlin_noise(uv, 40);

	imageStore(screen, coords, vec4(noise));
}