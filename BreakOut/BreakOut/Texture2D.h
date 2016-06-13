
#ifndef TEXTURE2D_H_
# define TEXTURE2D_H_

#include <glew.h>

class Texture2D
{
public:

	GLuint	ID;
	GLuint	Width;
	GLuint	Heigth;
	GLuint	Internal_Format;
	GLuint	Image_Format;
	GLuint	Wrap_S;
	GLuint	Wrap_T;
	GLuint	Filter_Min;
	GLuint	Filter_Max;

	Texture2D();
	void	Bind();
	void	Generate(GLuint width, GLuint heigth, unsigned char * data);
};

#endif
