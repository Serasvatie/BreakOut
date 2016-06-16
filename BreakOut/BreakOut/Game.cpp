#include "Game.h"
#include "ParticleGenerator.h"

GameObject	*Player;
BallObject	*Ball;
ParticleGenerator * Particles;

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
	ResourceManager::LoadShader("particle", "particle.vert", "particle.frag");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(Width), static_cast<GLfloat>(Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("Image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4f("Projection", projection);
	ResourceManager::GetShader("particle").Use().SetInteger("Sprite", 0);
	ResourceManager::GetShader("particle").Use().SetMatrix4f("Projection", projection);

	ResourceManager::LoadTexture("img/background.jpg", GL_FALSE, "background");
	ResourceManager::LoadTexture("img/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("img/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::LoadTexture("img/paddle.png", GL_TRUE, "paddle");
	ResourceManager::LoadTexture("img/ball.png", GL_TRUE, "ball");
	ResourceManager::LoadTexture("img/particle.png", GL_TRUE, "particle");

	spriteRender = new SpriteRender(ResourceManager::GetShader("sprite"));
	Particles = new ParticleGenerator(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("particle"), 500);

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
	DoCollision();
	Particles->Update(deltaTime, *Ball, 2, glm::vec2(Ball->Radius / 2));
	if (Ball->Position.y >= Height)
	{
		ResetLevel();
		ResetPlayer();
	}
	if (Levels[Level].IsCompleted() && Level < Levels.size() - 1)
		Level++;
	if (Level == Levels.size())
		State = GAME_WIN;
}

void Game::Render()
{
	if (State == GAME_ACTIVE)
	{
		spriteRender->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(Width, Height), 0.0f);
		Levels[Level].Draw(*spriteRender);
		Player->Draw(*spriteRender);
		Particles->Draw();
		Ball->Draw(*spriteRender);
	}
}

void Game::ResetLevel()
{
	if (this->Level == 0)this->Levels[0].Load("levels/Level1", this->Width, this->Height * 0.5f);
	else if (this->Level == 1)
		this->Levels[1].Load("levels/Level2", this->Width, this->Height * 0.5f);
	else if (this->Level == 2)
		this->Levels[2].Load("levels/Level3", this->Width, this->Height * 0.5f);
	else if (this->Level == 3)
		this->Levels[3].Load("levels/Level4", this->Width, this->Height * 0.5f);
}

void Game::ResetPlayer()
{
	// Reset player/ball stats
	Player->Size = glm::vec2(PLAYER_SIZE_X, PLAYER_SIZE_Y);
	Player->Position = glm::vec2(this->Width / 2 - PLAYER_SIZE_X / 2, this->Height - PLAYER_SIZE_Y);
	Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE_X / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)), glm::vec2(BALL_VELOCITY_X, BALL_VELOCITY_Y));
}

GLboolean Game::CheckCollision(GameObject & one, GameObject & two)
{
	// Collision x-axis?
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	// Collision y-axis?
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	// Collision only if on both axes
	return collisionX && collisionY;
}

// CHECK CHECKCOLLISION
Collision Game::CheckCollision(BallObject & one, GameObject & two)
{
	glm::vec2 center(one.Position + one.Radius);

	// Calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);

	// Get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

	// Add clamped value to AABB_center and we get the value of box closest	to circle
	glm::vec2 closest = aabb_center + clamped;

	// Retrieve vector between center circle and closest point AABB and check if length <= radius
	difference = closest - center;
	if (glm::length(difference) < one.Radius)
		return std::make_tuple(GL_TRUE, VectorDirection(difference), difference);
	else
		return std::make_tuple(GL_FALSE, UP, glm::vec2(0.f, 0.f));
}

void Game::DoCollision()
{
	for (GameObject &box : Levels[Level].Bricks)
	{
		if (box.Destroyed == false )
		{
			Collision collision = CheckCollision(*Ball, box);
			if (std::get<0>(collision))
			{
				if (!box.IsSolid)
					box.Destroyed = GL_TRUE;
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);
				if (dir == LEFT || dir == RIGHT)
				{
					Ball->Velocity.x = -Ball->Velocity.x;
					GLfloat penetration = Ball->Radius - std::abs(diff_vector.x);
					if (dir == LEFT)
						Ball->Position.x += penetration;
					else
						Ball->Position.x -= penetration;
				}
				else
				{
					Ball->Velocity.y = -Ball->Velocity.y;
					GLfloat penetration = Ball->Radius - std::abs(diff_vector.y);
					if (dir == UP)
						Ball->Position.y -= penetration;
					else
						Ball->Position.y += penetration;
				}
			}
		}
	}
	Collision result = CheckCollision(*Ball, *Player);
	if (!Ball->Stuck && std::get<0>(result))
	{
		GLfloat centerBoard = Player->Position.x + Player->Size.x / 2;
		GLfloat distance = (Ball->Position.x + Ball->Radius) - centerBoard;
		GLfloat percentage = distance / (Player->Position.x / 2);
	
		GLfloat strength = 20.f;
		glm::vec2 oldVelocity = Ball->Velocity;
		Ball->Velocity.x = BALL_VELOCITY_X * percentage * strength;
		Ball->Velocity.y = -Ball->Velocity.y;
		Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);

		Ball->Velocity.y = -1 * abs(Ball->Velocity.y);
	}
}

Direction Game::VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f,1.f), //up
		glm::vec2(1.f, 0.f), //right
		glm::vec2(0.f, -1.f), //down;
		glm::vec2(-1.f, 0.f) // left
	};
	GLfloat max = 0.f;
	GLuint best_match = -1;
	for (int i = 0; i < 4; i++)
	{
		GLfloat dot = glm::dot(glm::normalize(target), compass[i]);
		if (dot > max)
		{
			max = dot;
			best_match = i;
		}
	}
	return (Direction)best_match;
}
