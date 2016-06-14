#include "SpriteRender.h"

SpriteRender::SpriteRender(Shader & shader)
{
	_Shader = shader;
	initRenderData();
}

SpriteRender::~SpriteRender()
{
	glDeleteVertexArrays(1, &quadVAO);
}


void SpriteRender::DrawSprite(Texture2D & texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color)
{
	_Shader.Use();

	glm::mat4 model;

	// First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	model = glm::translate(model, glm::vec3(position, 0.0f));

	// Move origin of rotation to center of quad
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	// Then rotate
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); 
	// Move origin back
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); 
	// Last scale
	model = glm::scale(model, glm::vec3(size, 1.0f));

	_Shader.SetMatrix4f("Model", model);
	_Shader.SetVector3f("SpriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	_Shader.Disable();
}

void SpriteRender::initRenderData()
{
	GLuint VBO;
	GLfloat vertices[] = {
		//POS       //TEX
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
