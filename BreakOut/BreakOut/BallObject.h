
#ifndef BALLOBJECT_H_
# define BALLOBJECT_H_

#include "GameObject.h"

class BallObject :
	public GameObject
{
public:
	BallObject();
	BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);

	GLfloat		Radius;
	GLboolean	Stuck;

	glm::vec2	Move(GLfloat deltaTime, GLuint window_width);
	void		Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif