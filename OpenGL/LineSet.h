#pragma once
#include "Renderable.h"
#include "Vertex.h"
#include "Shader.h"
#include <vector>
#include "MeshLoader.h"

class LineSet : public Renderable {
public:
	LineSet(const std::vector<glm::vec3>& points, Shader* shader)
		: Renderable(shader, GL_LINES), _points(points) {
		setupBuffers();
	}
	void setupBuffers() override;

private:
	std::vector<glm::vec3> _points;
};
