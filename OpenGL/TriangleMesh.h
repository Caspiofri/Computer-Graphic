#pragma once
#include "Renderable.h"
#include "Vertex.h"
#include "Shader.h"
#include <vector>
#include "MeshLoader.h"

class TriangleMesh : public Renderable {
public:
	TriangleMesh(const std::vector<Vertex>& vertices,
		const std::vector<unsigned int>& indices,
		Shader* shader);
	void setupBuffers() override;

private:
	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;
};