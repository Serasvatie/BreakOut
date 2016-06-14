#include "Texture2D.h"

Texture2D::Texture2D()
	: Width(0), Heigth(0),
	Internal_Format(GL_RGB), Image_Format(GL_RGB),
	Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT),
	Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
	glGenTextures(1, &this->ID);
}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

#include <iostream>

void Texture2D::Generate(GLuint width, GLuint heigth, unsigned char * data)
{
	Width = width;
	Heigth = heigth;

	glBindTexture(GL_TEXTURE_2D, ID);

	glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, heigth, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}
