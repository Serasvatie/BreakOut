#version 440

in vec2 TexCoords;
in vec4 ParticleColor;

out vec4 FragColor;

uniform sampler2D Sprite;

void main()
	{
	FragColor = (texture(Sprite, TexCoords) * ParticleColor);
}
