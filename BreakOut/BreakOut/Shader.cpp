#include "Shader.h"

Shader & Shader::Use()
{
	glUseProgram(ID);
	return *this;
}

Shader & Shader::Disable()
{
	glUseProgram(0);
	return *this;
}

void Shader::Compile(const GLchar * vertexSource, const GLchar * fragmentSource, const GLchar * geometrySource)
{
	GLuint sVertex, sFragment, gShader;
	// Vertex Shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");
	// Fragment Shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAGMENT");
	// If geometry shader source code is given, also compile geometry shader
	if (geometrySource != nullptr)
	{
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &geometrySource, NULL);
		glCompileShader(gShader);
		checkCompileErrors(gShader, "GEOMETRY");
	}
	// Shader Program
	this->ID = glCreateProgram();
	glAttachShader(this->ID, sVertex);
	glAttachShader(this->ID, sFragment);
	if (geometrySource != nullptr)
		glAttachShader(this->ID, gShader);
	glLinkProgram(this->ID);
	checkCompileErrors(this->ID, "PROGRAM");
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometrySource != nullptr)
		glDeleteShader(gShader);
}

void Shader::SetFloat(const GLchar * name, GLfloat value, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform1f(GetLocation(name), value);
}

void Shader::SetBoolean(const GLchar * name, GLboolean value, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform1d(GetLocation(name), value);
}

void Shader::SetInteger(const GLchar * name, GLint value, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform1i(GetLocation(name), value);
}

void Shader::SetVector2f(const GLchar * name, GLfloat x, GLfloat y, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform2f(GetLocation(name), x, y);
}

void Shader::SetVector2f(const GLchar * name, glm::vec2 & vec, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform2f(GetLocation(name), vec.x, vec.y);
}

void Shader::SetVector3f(const GLchar * name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform3f(GetLocation(name), x, y, z);
}

void Shader::SetVector3f(const GLchar * name, glm::vec3 & vec, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform3f(GetLocation(name), vec.x, vec.y, vec.z);
}

void Shader::SetVector4f(const GLchar * name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform4f(GetLocation(name), x, y, z, w);
}

void Shader::SetVector4f(const GLchar * name, glm::vec4 & vec, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform4f(GetLocation(name), vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetMatrix3f(const GLchar * name, glm::mat3 & mat, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniformMatrix3fv(GetLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::SetMatrix4f(const GLchar * name, glm::mat4 & mat, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

GLuint Shader::Attribute(const std::string attributeName)
{
	auto attributeIter = attributeMap.find(attributeName);
	if (attributeIter == attributeMap.end())
		std::cout << "Could not find attribute in shader program: " << attributeName;
	return attributeMap[attributeName];
}

GLuint Shader::Uniform(const std::string uniformName)
{
	auto uniformIter = uniformMap.find(uniformName);
	if (uniformIter == uniformMap.end())
		std::cout << "Could not find uniform in shader program: " << uniformName << std::endl;
	return uniformMap[uniformName];
}

int Shader::AddAttribute(const std::string attributeName)
{
	attributeMap[attributeName] = glGetAttribLocation(ID, attributeName.c_str());

	if (attributeMap[attributeName] == -1)
		std::cout << "Could not add attribute: " << attributeName << " - location returned -1." << std::endl;
	else // Valid attribute location? Inform user if we're in debug mode.
	{
#ifdef DEBUG
		std::cout << "Attribute " << attributeName << " bound to location: " << attributeMap[attributeName] << std::endl;
#endif
	}
	return attributeMap[attributeName];

}

int Shader::AddUniform(const std::string uniformName)
{
	uniformMap[uniformName] = glGetUniformLocation(ID, uniformName.c_str());

	if (uniformMap[uniformName] == -1)
		std::cout << "Could not add uniform: " << uniformName << " - location returned -1." << std::endl;
	else // Valid uniform location? Inform user if we're in debug mode.
	{
#ifdef DEBUG
		std::cout << "Uniform " << uniformName << " bound to location: " << uniformMap[uniformName] << std::endl;
#endif
	}
	return uniformMap[uniformName];
}

void Shader::checkCompileErrors(GLuint object, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
}

GLuint Shader::GetLocation(const GLchar * name)
{
	int ret = glGetUniformLocation(ID, name);
	if (ret < 0)
		std::cout << "Could not find Uniform Location : " + std::string(name) << std::endl;
	return ret;
}
