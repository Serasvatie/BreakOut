
#ifndef RESOURCEMANAGER_H_
# define RESOURCEMANAGER_H_

#include <map>

#include "Shader.h"
#include "Texture2D.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	std::map<std::string, Shader> Shaders;
	std::map<std::string, Texture2D> Textures;

	Shader		LoadShader(std::string name, GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	Shader		GetShader(std::string name);

	Texture2D	LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
	Texture2D	GetTexture(std::string name);

	void		Clear();

private:
	Shader		loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	Texture2D	loadTextureFromFile(const GLchar *file, GLboolean alpha);
};

#endif