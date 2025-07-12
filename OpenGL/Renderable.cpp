#include "Renderable.h"
#include <iostream>

Renderable::Renderable(Shader* shader, GLenum drawMode)
	: _shader(shader), _drawMode(drawMode), _vao(0), _vbo(0), _ebo(0), _indexCount(0) {
}

Renderable::~Renderable() {
	std::cerr << "[Renderable] destructor called! Deleting VAO: " << _vao << ", VBO: " << _vbo << std::endl;
	std::cerr << "[Renderable::~Renderable] deleting this = " << this << std::endl;

	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
	glDeleteVertexArrays(1, &_vao);
}

void Renderable::draw(const glm::mat4& objectMatrix, const glm::mat4& worldMatrix, const glm::mat4& view , const glm::mat4& projection,const float scale)
{
	std::cout << "[Renderable::draw]: start drawing" << std::endl;

	if (!_shader) {
		std::cerr << "[Renderable::draw] Error: shader is null!" << std::endl;
		return;
	}

	_shader->use();
	_shader->setMat4("objectMatrix", objectMatrix);
	_shader->setMat4("worldMatrix", worldMatrix);
	_shader->setMat4("view", view);
	_shader->setMat4("projection", projection);

	_shader->setFloat("scale", scale);
	GLboolean isVAO = glIsVertexArray(_vao);
	std::cout << "[DEBUG] glIsVertexArray(" << _vao << ") = " << isVAO << std::endl;

	glBindVertexArray(_vao);

	if (_usesEBO) {
		std::cout << "[Renderable::draw]: glDrawElements, index count = " << _indexCount << std::endl;
		glDrawElements(_drawMode, _indexCount, GL_UNSIGNED_INT, 0);
	}
	else {
		std::cout << "[Renderable::draw]: glDrawArrays, index count = " << _indexCount << std::endl;
		glDrawArrays(_drawMode, 0, _indexCount);
	}

	std::cout << "[Renderable::draw]: unbinding VAO" << std::endl;
	glBindVertexArray(0);

	std::cout << "[Renderable::draw]: done drawing" << std::endl;
}