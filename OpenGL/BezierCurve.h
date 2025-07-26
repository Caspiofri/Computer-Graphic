#pragma once
#include <glm/glm.hpp>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Settings.h"

class BezierCurve {
private:
	glm::vec3 _controlPoints[4];

public:
	BezierCurve();
	void drawBezierCurve(std::vector<glm::vec3> points);
	glm::vec3 calculateBezierPoint(float t);
	void setControlPoint(glm::vec3 points ,int index);
	std::vector<glm::vec3> getSampledPoints(int num);
	glm::vec3* getControlPoints() { return _controlPoints; }

};