#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Settings.h"
class Camera {
public:
    Camera();

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void setPosition(const glm::vec3& position);
    void setRotation(const glm::vec3& rot) { _rotation = rot; }
    void lookAt(const glm::vec3& target);
    void setPerspective();
    void setUpVector(const glm::vec3& upVector);
    void Camera::UpdateAspectRatio(float aspectRatio);


    // Rotations
    void rotateY(float angleDegrees);  // Rotate around Y-axis
    void rotateX(float angleDegrees); // Rotate around X-axis
    void rotateZ(float angleDegrees);  // Rotate around Z-axis
    void orbitAroundTarget(float angleDegrees, const glm::vec3& axis); // Orbit around target

    //getters
    glm::vec3 getPosition() const;
    glm::vec3 getTarget() const;
    glm::vec3 getUpVector() const;


    //setters
    //void setPosition(const glm::vec3& position);
    void setTarget(const glm::vec3& target);
    void setFov(float fov);
    void setNearPlane(float nearPlane);
    void setFarPlane(float farPlane);
    void focusOnObject();
    void updateViewMatrix();
    void updateFromUI();

private:
    glm::vec3 _basePosition, _position, _rotation, _forward, _up, _target;
    glm::mat4 _projectionMatrix, _viewMatrix;

    void validatePerspectiveParameters() const;
    void updateOrientation();
};