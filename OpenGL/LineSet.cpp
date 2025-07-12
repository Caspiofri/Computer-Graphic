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
	std::cerr << "[LineSet] in setupBuffers" << std::endl;
	std::cout << "[DEBUG] using shader program ID: " << _shader->getID() << std::endl;
	std::cout << "[DEBUG] using shader program ID: " << _shader->getID() << std::endl;

	for (const auto& v : _points) {
		std::cout << "[LineSet] BBox Vertex: " << v.position.x << ", " << v.position.y << ", " << v.position.z << ", " << v.position.w << std::endl;
		std::cout << "[LineSet] BBox Vertex: " << v.color.x << ", " << v.color.y << ", " << v.color.z << ", " << v.color.w << std::endl;
	}
	// Building buffers
	glGenVertexArrays(1, &_vao);
	std::cout << "[DEBUG] trying to bind VAO: " << _vao << std::endl;
	glBindVertexArray(_vao);

	GLint currentVAO = 0;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVAO);
	std::cout << "[DEBUG] actually bound VAO: " << currentVAO << std::endl;	std::cout << "[LineSet] _vao = " << _vao << std::endl;

	glGenBuffers(1, &_vbo);
	std::cout << "[DEBUG] allocating VBO: size = " << (_points.size() * sizeof(Vertex)) << " bytes" << std::endl;
	std::cout << "[DEBUG] _indexCount = " << _indexCount << ", _points.size() = " << _points.size() << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _points.size() * sizeof(Vertex), _points.data(), GL_STATIC_DRAW);
	std::cout << "[LineSet] _vbo = " << _vbo << std::endl;

	// Setting vertex attributes
	glEnableVertexAttribArray(0); // Location 0 - Position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	std::cout << "VAO ID: " << _vao << ", VBO ID: " << _vbo << ", index count: " << _indexCount << std::endl;
	GLenum err1 = glGetError();
	if (err1 != GL_NO_ERROR) std::cerr << "[ERROR] position attrib failed: 0x" << std::hex << err1 << std::endl;

	// DEBUGING
	glEnableVertexAttribArray(1); // Location 1 -color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	GLenum err2 = glGetError();
	if (err2 != GL_NO_ERROR) {
		std::cerr << "[ERROR] glVertexAttribPointer failed! Code: 0x" << std::hex << err2 << std::endl;
	}

	glBindVertexArray(0); // Unbind VAO


}
