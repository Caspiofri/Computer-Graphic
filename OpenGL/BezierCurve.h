#pragma once
#include <glm/glm.hpp>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Settings.h"
#include "Vertex.h"
#include "MathLib.h"

class BezierCurve {
private:
	glm::vec3 _controlPoints[4];
	std::vector<glm::vec3> getSampledPoints(int num);


public:
	BezierCurve();
	void drawBezierCurve(std::vector<glm::vec3> points);
	glm::vec3 calculateBezierPoint(float t);
	void setControlPoint(glm::vec3 points ,int index);
	glm::vec3* getControlPoints() { return _controlPoints; }
	std::vector<Vertex> buildVisualBezier();

	glm::mat4 calcAnimation();
	
};