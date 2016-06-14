#include "BallObject.h"



BallObject::BallObject()
	: GameObject(), Radius(12.5f), Stuck(true)
{
}

BallObject::BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite)
	: GameObject(pos, glm::vec2(radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity),
	Radius(radius), Stuck(true)
{
}

glm::vec2 BallObject::Move(GLfloat deltaTime, GLuint window_width)
{
	if (!Stuck)
	{
		Position += Velocity * deltaTime;

		if (Position.x <= 0.0f)
		{
			Velocity.x = -Velocity.x;
			Position.x = 0.f;
		}
		else if (Position.x + Size.x >= window_width)
		{
			Velocity.x = -Velocity.x;
			Position.x = window_width - Size.x;
		}
		if (Position.y <= 0.0f)
		{
			Velocity.y = -Velocity.y;
			Position.y = 0.f;
		}
	}
	return Position;
}

void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	Position = position;
	Velocity = velocity;
	Stuck = true;
}