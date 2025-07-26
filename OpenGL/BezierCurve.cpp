#include "BezierCurve.h"

BezierCurve::BezierCurve()
{
	_controlPoints[0] = Settings::_P0;
	_controlPoints[1] = Settings::_P1;
	_controlPoints[2] = Settings::_P2;
	_controlPoints[3] = Settings::_P3;
}
glm::vec3 BezierCurve::calculateBezierPoint(float t) {

	float u = 1 - t;
	float bo = u * u * u;
	float b1 = 3 * u * u * t;
	float b2 = 3 * u * t * t;
	float b3 = t * t * t;
	glm::vec3 point = Settings::_P0 * bo + Settings::_P1 * b1 + Settings::_P2 * b2 + Settings::_P3 * b3;
	return point;
}

void BezierCurve::setControlPoint(glm::vec3 point, int index) {
	_controlPoints[index] = point;
}

std::vector<glm::vec3> BezierCurve::getSampledPoints(int num) {
	std::vector<glm::vec3> points;
	float step = 1.0f / num;
	for (float t = 0.0f; t <= 1.0f; t += step) {
		glm::vec3 point = calculateBezierPoint(t);
		points.push_back(point);
	}
	return points;
}