#pragma once
#include <glm/glm.hpp>
#include <vector>

class BBox {
private:
	glm::vec3 _minCorner;
	glm::vec3 _maxCorner;

public:
	BBox();
	void compute(const std::vector<glm::vec3>& vertices);
	void reset();

	const glm::vec3& getMinCorner() const { return _minCorner; }
	const glm::vec3& getMaxCorner() const { return _maxCorner; }

	std::vector<glm::vec3> getCorners() const;
};
#pragma once
