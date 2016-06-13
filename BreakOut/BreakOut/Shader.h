
#ifndef SHADER_H_
# define SHADER_H_

#include <string>
#include <iostream>
#include <map>

#include <glew.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class Shader
{
private:
	enum class ObjectType
	{
		SHADER, PROGRAM
	};

public:
	GLuint		ID;
	Shader &	Use();
	Shader &	Disable();

	void		Compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = 0);

	void		SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
	void		SetBoolean(const GLchar *name, GLboolean value, GLboolean useShader = false);
	void		SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
	void		SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void		SetVector2f(const GLchar *name, glm::vec2 &vec, GLboolean useShader = false);
	void		SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void		SetVector3f(const GLchar *name, glm::vec3 &vec, GLboolean useShader = false);
	void		SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void		SetVector4f(const GLchar *name, glm::vec4 &vec, GLboolean useShader = false);

	void		SetMatrix3f(const GLchar *name, glm::mat3 &mat, GLboolean useShader = false);
	void		SetMatrix4f(const GLchar *name, glm::mat4 &mat, GLboolean useShader = false);

	GLuint		Attribute(const std::string attributeName);
	GLuint		Uniform(const std::string uniformName);

	int			AddAttribute(const std::string attributeName);
	int			AddUniform(const std::string uniformName);

private:
	std::map<std::string, int> attributeMap;
	std::map<std::string, int> uniformMap;

	bool initialised;

	void		checkCompileErrors(GLuint object, std::string type);
};

#endif