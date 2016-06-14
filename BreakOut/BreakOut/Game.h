
#ifndef GAME_H_
# define GAME_H_

#include <glew.h>
#include <glfw3.h>

#include "ResourceManager.h"
#include "SpriteRender.h"

typedef enum gameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
} GameState;

class Game
{
public:
	Game(GLuint64 width, GLuint64 height);
	~Game();

	GameState	State;
	GLboolean	Keys[1024];
	GLuint64	Width, Height;
	ResourceManager *resourceManager;
	SpriteRender *spriteRender;
	
	void		Init();
	void		ProcessInput(GLfloat deltaTime);
	void		Update(GLfloat deltaTime);
	void		Render();
};

#endif