#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
	std::cout << "\nsetting Shader\n\a\a\a";
	 _id = initShader(vertexPath, fragmentPath);
	 std::cerr << "Shader id is :  " << _id << std::endl;

}

//create a GLSL program object from vertex and fragment shader files
GLuint Shader::initShader(std::string vertexShaderFileName, std::string fragmentShaderFileName)
{
	std::cerr << "[initShader] in initShader" << std::endl;

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
			std::cerr << s.filename << " failed to compile:" << std::endl;
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

	/* link  and error check */
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
		//exit( EXIT_FAILURE );
	}

	std::cerr << "[Shader] ended initShader" << std::endl;

	return program;
}

void Shader::use() const {
	std::cerr << "[Shader] call use" << std::endl;

	glUseProgram(_id);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
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

