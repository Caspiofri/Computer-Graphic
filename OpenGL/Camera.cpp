#include "common_glm_config.h"
#include "Camera.h"
#include <stdexcept>
#include "MathLib.h"
#include "Settings.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>

//custom matrix calculations library


// ====== Constructor ====== //
Camera::Camera() :
    _basePosition(0.0f, 0.0f, 5.0f),  // Default camera position
    _position(0.0f, 0.0f, 5.0f),    // Default target at origin
    _target(0.0f, 0.0f, 0.0f),    // Default target at origin
    _up(0.0f, 1.0f, 0.0f),        // Default up vector (Y-axis)
    _projectionMatrix(glm::mat4(1.0f)),
    _viewMatrix(glm::mat4(1.0f))
{
    updateViewMatrix();
}

// ====== Setters ====== //

// Set camera position
void Camera::setPosition(const glm::vec3& pos) {
    _position = pos;
}

void Camera::setTarget(const glm::vec3& tar) {
    _target = tar;
}

// Set the up vector (re-normalized)
void Camera::setUpVector(const glm::vec3& upVector) {
    _up = MathLib::normalize(upVector); // Use MathLib for normalization
}

// Point the camera at a specific target
void Camera::lookAt(const glm::vec3& target) {
    _target = target;
    updateViewMatrix();

}

// ====== Getters ====== //

// Compute the view matrix
glm::mat4 Camera::getViewMatrix() const {
    return _viewMatrix;
}

// Compute the perspective projection matrix (using FoV and aspect ratio)
glm::mat4 Camera::getProjectionMatrix() const {
    return _projectionMatrix;
}

// Get camera position
glm::vec3 Camera::getPosition() const {
    return _position;
}

// Get camera target
glm::vec3 Camera::getTarget() const {
    return _target;
}

// Get up vector
glm::vec3 Camera::getUpVector() const {
    return _up;
}

void Camera::focusOnObject()
{
    glm::vec3 objectCenter = glm::vec3(0, 0, 0);
    setPosition(objectCenter + glm::vec3(0, 0, 5));  // Set camera behind the object
    setTarget(objectCenter);  // Look at the object's center
}
void Camera::updateViewMatrix() {
    _viewMatrix = MathLib::lookAt(_position, _target, _up);
}

void Camera::setPerspective() {

    _projectionMatrix = MathLib::perspective(Settings::_fov, Settings::_aspectRatio, Settings::_nearPlane, Settings::_farPlane);
}


//official camera update function
void Camera::updateFromUI() {
  /*  if (Settings::_skipNextCameraUpdate) {
        return;
    }*/

    // Step 0: data from controlers
    _position = glm::vec3(Settings::_camTransX, Settings::_camTransY, Settings::_camTransZ);

    float yaw = glm::radians(Settings::_camRotY);
    float pitch = glm::radians(Settings::_camRotX);
    float roll = glm::radians(Settings::_camRotZ);

    // Step 1: Forward vector
    _forward.x = cos(pitch) * sin(yaw);
    _forward.y = sin(pitch);
    _forward.z = cos(pitch) * cos(yaw);
    _forward = MathLib::normalize(_forward);

    if (glm::length(_forward) < 1e-6f) {
        std::cerr << "[Camera] Invalid forward vector. Yaw/Pitch values may be unstable.\n";
        return;
    }

    _target = _position + _forward;

    glm::vec3 worldUp = glm::vec3(0, 1, 0);
    _up = MathLib::normalize(worldUp);

    float cosRoll = cos(roll);
    float sinRoll = sin(roll);
    glm::vec3 upRotated = _up * cosRoll + MathLib::cross(_forward, _up) * sinRoll + _forward * MathLib::dot(_forward, _up) * (1.0f - cosRoll);
    _up = MathLib::normalize(upRotated);

}
