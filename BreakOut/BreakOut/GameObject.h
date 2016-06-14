
#ifndef GAMEOBJECT_H_
# define GAMEOBJECT_H_

# include "SpriteRender.h"

class ResourceManager;

class GameObject
{
public:

	glm::vec2	Position, Size, Velocity;
	glm::vec3	Color;

	GLfloat		Rotation;
	GLboolean	IsSolid, Destroyed;

	Texture2D	Sprite;

	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	virtual void Init();
	virtual void ProcessInput();
	virtual void Update(GLfloat deltaTime);
	virtual void Draw(SpriteRender & renderer);
};

#endif