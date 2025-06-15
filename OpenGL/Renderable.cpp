#include "Renderable.h"
#include <iostream>

Renderable::Renderable(Shader* shader, GLenum drawMode)
	: _shader(shader), _drawMode(drawMode), _vao(0), _vbo(0), _ebo(0), _indexCount(0) {
}

Renderable::~Renderable() {
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
	glDeleteVertexArrays(1, &_vao);
}

void Renderable::draw(const glm::mat4& rotation, const glm::mat4& translation, const glm::mat4& projection , const float scale)
{
	std::cout << "[Renderable::draw]: start drawing" << std::endl;

	if (!_shader) {
		std::cerr << "[Renderable::draw] Error: shader is null!" << std::endl;
		return;
	}

	std::cout << "[Renderable::draw]: activating shader" << std::endl;
	_shader->use();

	std::cout << "[Renderable::draw]: sending rotation matrix" << std::endl;
	_shader->setMat4("rotation", rotation);

	std::cout << "[Renderable::draw]: sending translation matrix" << std::endl;
	_shader->setMat4("translation", translation);

	std::cout << "[Renderable::draw]: sending projection matrix" << std::endl;
	_shader->setMat4("projection", projection);

	_shader->setFloat("scale", scale);

	std::cout << "[Renderable::draw]: binding VAO (id=" << _vao << ")" << std::endl;
	glBindVertexArray(_vao);

	std::cout << "[Renderable::draw]: drawing elements, index count = " << _indexCount << std::endl;
	glDrawElements(_drawMode, _indexCount, GL_UNSIGNED_INT, 0);

	std::cout << "[Renderable::draw]: unbinding VAO" << std::endl;
	glBindVertexArray(0);

	std::cout << "[Renderable::draw]: done drawing" << std::endl;
}