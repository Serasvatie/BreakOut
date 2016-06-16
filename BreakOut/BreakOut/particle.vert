#version 440

layout (location = 0) in vec4 Vertex;

out vec2 TexCoords;
out vec4 ParticleColor;

uniform mat4 Projection;
uniform vec2 Offset;
uniform vec4 Color;

void main()
{
	float Scale = 10.f;
	TexCoords = Vertex.zw;
	ParticleColor = Color;
	gl_Position = Projection * vec4((Vertex.xy * Scale) + Offset, 0.0f,1.0f);
}