
#ifndef PARTICLEGENERATOR_H_
# define PARTICLEGENERATOR_H_

# include <glm.hpp>
# include <glew.h>
# include <vector>

# include "Texture2D.h"
# include "Shader.h"
# include "GameObject.h"

struct Particle
{
	glm::vec2 Position, Velocity;
	glm::vec4 Color;
	GLfloat Life;

	Particle() : Position(0.f), Velocity(0.0f), Color(0.0f), Life(0.0f) { }
};

class ParticleGenerator
{
public:
	ParticleGenerator(Shader shader, Texture2D texture, GLuint amount);

	Texture2D texture;
	GLuint VAO;

	void respawnParticle(Particle & particle, GameObject & object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
	void Update(GLfloat deltaTime, GameObject & object, GLuint newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
	void Draw();

private:
	std::vector<Particle> particles;
	GLuint amount;
	Shader shader;

	void init();
	GLuint firstUnusedParticle();
};

#endif