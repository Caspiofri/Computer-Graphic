#pragma once
#include <string>
#include <Glew/include/gl/glew.h>
#include <glm/glm.hpp>
#include <vector>

class Shader {

	struct ShaderSource
	{
		std::string filename;
		GLenum      type;
		std::string source;
	};

public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void use() const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;

	void setFloat(const std::string& name, float value) const;


	GLuint initShader(std::string vertexShaderFileName, std::string fragmentShaderFileName);
	GLuint getID() const { return _id; }


private:
	GLuint _id;
	std::string filename;
	GLenum      type;
	std::string source;
	std::string readShaderSource(const std::string& shaderFileName);

};

