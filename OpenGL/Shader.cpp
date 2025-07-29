#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
	 _id = initShader(vertexPath, fragmentPath);
}

//create a GLSL program object from vertex and fragment shader files
GLuint Shader::initShader(std::string vertexShaderFileName, std::string fragmentShaderFileName)
{
	ShaderSource shaders[2] =
	{
		{vertexShaderFileName, GL_VERTEX_SHADER, std::string()},
		{fragmentShaderFileName, GL_FRAGMENT_SHADER, std::string()}
	};

	GLuint program = glCreateProgram();

	for (int i = 0; i < 2; ++i) {
		ShaderSource& s = shaders[i];
		s.source = readShaderSource(s.filename);
		if (shaders[i].source.empty())
		{
			std::cerr << "Failed to read " << s.filename << std::endl;
			return 0;
		}

		GLuint shader = glCreateShader(s.type);
		const GLchar* strings[1];
		strings[0] = s.source.c_str();
		glShaderSource(shader, 1, strings, NULL);

		glCompileShader(shader);

		GLint  compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			GLint  logSize = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetShaderInfoLog(shader, logSize, NULL, logMsg);
			std::cerr << logMsg << std::endl;
			delete[] logMsg;
			return 0;
		}

		glAttachShader(program, shader);
	}

	glLinkProgram(program);

	GLint  linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked) {
		std::cerr << "Shader program failed to link" << std::endl;
		GLint  logSize;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
		char* logMsg = new char[logSize];
		glGetProgramInfoLog(program, logSize, NULL, logMsg);
		std::cerr << logMsg << std::endl;
		delete[] logMsg;

		return 0;
	}


	return program;
}

void Shader::use() const {

	glUseProgram(_id);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}
void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}
void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
	glUniform3fv(glGetUniformLocation(_id, name.c_str()), 1, &value[0]);
}
void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
}

std::string Shader::readShaderSource(const std::string& shaderFileName)
{
	std::ifstream ifile(shaderFileName);
	std::string filetext;

	while (ifile.good())
	{
		std::string line;
		std::getline(ifile, line);
		filetext.append(line + "\n");
	}
	ifile.close();
	return filetext;
}

