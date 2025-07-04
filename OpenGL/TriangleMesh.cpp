#include "TriangleMesh.h"
#include "MeshLoader.h"

TriangleMesh::TriangleMesh(const std::vector<Vertex>& vertices,
	const std::vector<unsigned int>& indices,
	Shader* shader)
	: Renderable(shader, GL_TRIANGLES),
	_vertices(vertices),
	_indices(indices) {
	_indexCount = static_cast<GLsizei>(_indices.size());
	setupBuffers();
}

void TriangleMesh::setupBuffers() {
	std::cerr << "[TriangleMesh] in setupBuffers" << std::endl;

	// Building buffers
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	std::cout << "[uploadFrom] _vao = " << _vao << std::endl;

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), _vertices.data(), GL_STATIC_DRAW);
	std::cout << "[uploadFrom] _vbo = " << _vbo << std::endl;

	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);

	std::cout << "[uploadFrom] _ebo = " << _ebo << std::endl;

	// Setting vertex attributes
	glEnableVertexAttribArray(0); // Position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	// DEBUGING
	glEnableVertexAttribArray(1); // color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));


	//glEnableVertexAttribArray(1); // Normal
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	//glEnableVertexAttribArray(2); // Texture 
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));


	glBindVertexArray(0); // Unbind VAO
}
