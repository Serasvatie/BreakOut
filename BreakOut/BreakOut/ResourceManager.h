
#ifndef RESOURCEMANAGER_H_
# define RESOURCEMANAGER_H_

#include <map>

#include "Shader.h"
#include "Texture2D.h"

class ResourceManager
{
public:
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture2D> Textures;

	static Shader		LoadShader(std::string name, GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	static Shader		GetShader(std::string name);

	static Texture2D	LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
	static Texture2D	GetTexture(std::string name);

	static void		Clear();

private:
	ResourceManager();
	static	Shader		loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	static Texture2D	loadTextureFromFile(const GLchar *file, GLboolean alpha);
};

static ResourceManager *RM;

#endif