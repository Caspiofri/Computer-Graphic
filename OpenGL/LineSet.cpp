#pragma once
#include "LineSet.h"

LineSet::LineSet(const std::vector<Vertex>& points,
	Shader* shader)
	: Renderable(shader, GL_LINES)
{
	_points = points;
	_indexCount = static_cast<GLsizei>(_points.size());
	_usesEBO = false;
	setupBuffers();
}


void LineSet::setupBuffers() {

	// Building buffers
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	GLint currentVAO = 0;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVAO);

	glGenBuffers(1, &_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _points.size() * sizeof(Vertex), _points.data(), GL_STATIC_DRAW);

	// Setting vertex attributes
	glEnableVertexAttribArray(0); // Location 0 - Position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	GLenum err1 = glGetError();
	if (err1 != GL_NO_ERROR) std::cerr << "[ERROR] position attrib failed: 0x" << std::hex << err1 << std::endl;

	// DEBUGING
	glEnableVertexAttribArray(1); // Location 1 - color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	GLenum err2 = glGetError();
	if (err2 != GL_NO_ERROR) {
		std::cerr << "[ERROR] glVertexAttribPointer failed! Code: 0x" << std::hex << err2 << std::endl;
	}

	glBindVertexArray(0); // Unbind VAO


}
