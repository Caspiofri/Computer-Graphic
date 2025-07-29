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


//TODO  - move to bezier class
std::vector<Vertex> BezierCurve::buildVisualBezier() {
	int num = 100;
	std::vector<glm::vec3> sampledPoints = getSampledPoints(num);
	std::vector<Vertex> lineVertices;
	for (int i = 0; i < sampledPoints.size() - 1; i++) {
		Vertex v1, v2;
		v1.position = glm::vec4(sampledPoints[i], 1.0f);
		v2.position = glm::vec4(sampledPoints[i + 1], 1.0f);
		v1.normal = glm::vec3(0.0f);
		v2.normal = glm::vec3(0.0f);
		v1.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		v2.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		lineVertices.push_back(v1);
		lineVertices.push_back(v2);
	}

	return lineVertices;
}
//TODO  - move to bezier class
glm::mat4 BezierCurve::calcAnimation() {

	//position
	glm::vec3 position = calculateBezierPoint(Settings::_t);
	glm::mat4 translation = MathLib::translation(position);

	//rotation
	glm::mat4 rotation = MathLib::identity();
	if (Settings::_useSlerp) {
		float startQuat[4], endQuat[4];
		MathLib::convertEulerToQuaternion(Settings::_startSlerpRotX, Settings::_startSlerpRotY, Settings::_startSlerpRotZ, &startQuat[0]);
		MathLib::convertEulerToQuaternion(Settings::_endSlerpRotX, Settings::_endSlerpRotY, Settings::_endSlerpRotZ, &endQuat[0]);

		float resultQuat[4];
		MathLib::slerp_calc(&startQuat[0], &endQuat[0], Settings::_t, &resultQuat[0]);
		ConvertQuaternionToMatrix(&resultQuat[0], rotation);
	}
	else {
		glm::vec3 rotation_vec = MathLib::euler_calc();
		rotation = MathLib::rotation(rotation_vec);
	}

	return rotation * translation;
}
