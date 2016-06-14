#version 440

layout (location = 0) in vec4 Vertex;

out vec2 TexCoords;

uniform mat4 Model;
uniform mat4 Projection;

void main()
{
	TexCoords = Vertex.zw;
	gl_Position = Projection * Model * vec4(Vertex.xy, 0.0, 1.0);
}