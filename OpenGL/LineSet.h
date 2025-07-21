#pragma once
#include "Renderable.h"
#include "Vertex.h"
#include "Shader.h"
#include <vector>
#include "MeshLoader.h"

class LineSet : public Renderable {
public:
	LineSet(const std::vector<Vertex>& points, Shader* shader);
	void setupBuffers() override;

private:
	std::vector<Vertex> _points;
};
