
#ifndef GAME_H_
# define GAME_H_

#include <glew.h>
#include <glfw3.h>

#include "ResourceManager.h"
#include "SpriteRender.h"
#include "GameLevel.h"
#include "BallObject.h"

typedef enum gameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
} GameState;

#define PLAYER_SIZE_X 100
#define PLAYER_SIZE_Y 20
#define PLAYER_VELOCITY 500.0f

#define BALL_VELOCITY_X 100.f
#define BALL_VELOCITY_Y -350.f
#define BALL_RADIUS 12.5f

class Game
{
public:
	Game(GLuint64 width, GLuint64 height);
	~Game();

	GameState	State;
	GLboolean	Keys[1024];
	GLuint64	Width, Height;
	SpriteRender *spriteRender;
	
	std::vector<GameLevel> Levels;
	GLuint		Level;

	void		Init();
	void		ProcessInput(GLfloat deltaTime);
	void		Update(GLfloat deltaTime);
	void		Render();
};

#endif