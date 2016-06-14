
#ifndef GAMELEVEL_H_
# define GAMELEVEL_H_

# include <glew.h>
# include <vector>

# include "GameObject.h"

class GameLevel
{
public:
	GameLevel();

	std::vector<GameObject> Bricks;
	void		Load(const GLchar * file, GLuint levelWidth, GLuint levelHeight);
	void		Draw(SpriteRender &renderer);
	GLboolean	IsCompleted();

private:
	void init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
};

#endif
