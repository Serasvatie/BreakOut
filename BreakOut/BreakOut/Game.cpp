#include "Game.h"
#include "Breakout.h"

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
}

void Game::ProcessInput(GLfloat deltaTime)
{
}

void Game::Update(GLfloat deltaTime)
{
}

void Game::Render()
{
	if (State == GAME_ACTIVE)
	{
		spriteRender->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(Width, Height), 0.0f);
		Levels[Level].Draw(*spriteRender);
	}
}