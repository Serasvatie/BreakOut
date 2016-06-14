
#ifndef SPRITERENDER_H_
# define SPRITERENDER_H_

# include <glew.h>
# include <glm.hpp>
# include <gtc\matrix_transform.hpp>

# include "Shader.h"
# include "Texture2D.h"

class SpriteRender
{
public:
	SpriteRender(Shader &shader);
	~SpriteRender();

	void DrawSprite(Texture2D & texture, glm::vec2 position, glm::vec2 size = glm::vec2(10,10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:
	Shader _Shader;
	GLuint quadVAO;

	void initRenderData();
};

#endif