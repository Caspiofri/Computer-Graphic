#pragma once
#include "common_glm_config.h"

enum LightType { DIRECTIONAL, POINTY };
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

class Light {
public:

	// Constructor
	Light() : _type(DIRECTIONAL), _direction(glm::vec3(0, 0, -1.0f)), _position(glm::vec3(0.0f)),
		_intensity(glm::vec3(1.0f)), enabled(true) {
	}

	//getters and setters
	LightType getType() const { return _type; }
	glm::vec3 getDirection() const { return _direction; }
	glm::vec3 getPosition() const { return _position; }
	glm::vec3 getIntensity() const { return _intensity; }
	void setType(LightType type) { _type = type; }
	void setDirection(const glm::vec3& direction) { _direction = direction; }
	void setPosition(const glm::vec3& position) { _position = position; }
	void setIntensity(const glm::vec3& intensity) { _intensity = intensity; }
	void setEnabled(bool enable) { enabled = enable; }
	bool isEnabled() const { return enabled; }


private:
	LightType _type;
	glm::vec3 _direction; // used if directional
	glm::vec3 _position;  // used if point
	glm::vec3 _intensity;     // RGB color of the light
	bool enabled;

};