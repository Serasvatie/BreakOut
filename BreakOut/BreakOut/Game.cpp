#include "Game.h"

static ResourceManager *RM;

Game::Game(GLuint64 width, GLuint64 height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
	resourceManager = new ResourceManager();
	RM = resourceManager;
}

Game::~Game()
{
	delete resourceManager;
}

void Game::Init()
{
	RM->LoadShader("sprite", "sprite.vert", "sprite.frag");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(Width), static_cast<GLfloat>(Height), 0.0f, -1.0f, 1.0f);
	RM->GetShader("sprite").Use().SetInteger("Image", 0);
	RM->GetShader("sprite").SetMatrix4f("Projection", projection);

	RM->LoadTexture("awesomeface.png", GL_TRUE, "face");
	spriteRender = new SpriteRender(RM->GetShader("sprite"));
}

void Game::ProcessInput(GLfloat deltaTime)
{
}

void Game::Update(GLfloat deltaTime)
{
}

void Game::Render()
{
	spriteRender->DrawSprite(RM->GetTexture("face"),
		glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f,
			1.0f, 0.0f));
}
