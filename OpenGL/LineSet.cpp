#pragma once
#include "LineSet.h"

void LineSet::setupBuffers() {
	std::cerr << "[TriangleMesh] in setupBuffers" << std::endl;

	// Building buffers
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	std::cout << "[uploadFrom] _vao = " << _vao << std::endl;

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _points.size() * sizeof(Vertex), _points.data(), GL_STATIC_DRAW);
	std::cout << "[uploadFrom] _vbo = " << _vbo << std::endl;

	// Setting vertex attributes
	glEnableVertexAttribArray(0); // Location 0 - Position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	// DEBUGING
	glEnableVertexAttribArray(1); // Location 1 -color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glBindVertexArray(0); // Unbind VAO
}
