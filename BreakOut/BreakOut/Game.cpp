#include "Game.h"

GameObject	*Player;
BallObject	*Ball;

Game::Game(GLuint64 width, GLuint64 height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
}

Game::~Game()
{
}

void Game::Init()
{
	ResourceManager::LoadShader("sprite", "sprite.vert", "sprite.frag");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(Width), static_cast<GLfloat>(Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("Image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4f("Projection", projection);
	
	ResourceManager::LoadTexture("img/background.jpg", GL_FALSE, "background");
	ResourceManager::LoadTexture("img/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("img/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::LoadTexture("img/paddle.png", GL_TRUE, "paddle");
	ResourceManager::LoadTexture("img/ball.png", GL_TRUE, "ball");

	spriteRender = new SpriteRender(ResourceManager::GetShader("sprite"));

	GameLevel one; one.Load("levels/Level1", Width, Height * 0.5);
	GameLevel two; two.Load("levels/Level2", Width, Height * 0.5);
	GameLevel three; three.Load("levels/Level3", Width, Height * 0.5);
	GameLevel four; four.Load("levels/Level4", Width, Height * 0.5);
	Levels.push_back(one);
	Levels.push_back(two);
	Levels.push_back(three);
	Levels.push_back(four);
	Level = 0;
	glm::vec2 playerPos = glm::vec2(Width / 2 - PLAYER_SIZE_X / 2, Height - PLAYER_SIZE_Y);
	Player = new GameObject(playerPos, glm::vec2(PLAYER_SIZE_X, PLAYER_SIZE_Y), ResourceManager::GetTexture("paddle"));
	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE_X / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
	Ball = new BallObject(ballPos, BALL_RADIUS, glm::vec2(BALL_VELOCITY_X, BALL_VELOCITY_Y), ResourceManager::GetTexture("ball"));
}


void Game::ProcessInput(GLfloat deltaTime)
{
	if (State == GAME_ACTIVE)
	{
		GLfloat velocity = PLAYER_VELOCITY * deltaTime;
		if (Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0)
				Player->Position.x -= velocity;
		}
		if (Keys[GLFW_KEY_D])
		{
			if (Player->Position.x <= Width - Player->Size.x)
				Player->Position.x += velocity;
		}
		if (this->Keys[GLFW_KEY_SPACE])
			Ball->Stuck = false;
	}
}

void Game::Update(GLfloat deltaTime)
{
	Ball->Move(deltaTime, Width);
}

void Game::Render()
{
	if (State == GAME_ACTIVE)
	{
		spriteRender->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(Width, Height), 0.0f);
		Levels[Level].Draw(*spriteRender);
		Player->Draw(*spriteRender);
		Ball->Draw(*spriteRender);
	}
}