#include "common_glm_config.h"

#include "MathLib.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>


#define M_PI 3.14159265358979323846


//Operations on 3 dimensional vectors
glm::vec3 MathLib::add(const glm::vec3& v1, const glm::vec3& v2) {
    return glm::vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

glm::vec3 MathLib::subtract(const glm::vec3& v1, const glm::vec3& v2) {
    return glm::vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

glm::vec3 MathLib::scale(const glm::vec3& v, float scalar) {
    return glm::vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

glm::vec3 MathLib::cross(const glm::vec3& v1, const glm::vec3& v2) {
    return glm::vec3(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}

float MathLib::dot(const glm::vec3& v1, const glm::vec3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

glm::vec3 MathLib::normalize(const glm::vec3& v) {
    float mag = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return glm::vec3(v.x / mag, v.y / mag, v.z / mag);
}

glm::vec3 MathLib::reflect(const glm::vec3& L, const glm::vec3& N) {
    float dotLN = L.x * N.x + L.y * N.y + L.z * N.z;
    glm::vec3 R;
    R.x = L.x - 2.0f * dotLN * N.x;
    R.y = L.y - 2.0f * dotLN * N.y;
    R.z = L.z - 2.0f * dotLN * N.z;
    return R;
}

//Operations on 4 dimensional matrixes

glm::mat4 MathLib::multiply(const glm::mat4& m1, const glm::mat4& m2) {
    glm::mat4 result(0.0f);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return result;
}

glm::vec3 MathLib::transformPoint(const glm::mat4& matrix, const glm::vec3& point) {
    glm::vec4 temp(point, 1.0f); // Convert to homogeneous coordinates
    glm::vec4 transformed = matrix * temp;
    return glm::vec3(transformed.x / transformed.w, transformed.y / transformed.w, transformed.z / transformed.w);
}


glm::mat4 MathLib::identity() {
    return glm::mat4(1.0f);
}

glm::mat4 MathLib::translation(const glm::vec3& v1) {
    glm::mat4 mat = MathLib::identity();
    mat[0][3] = v1.x;
    mat[1][3] = v1.y;
    mat[2][3] = v1.z;
    return mat;
}

glm::mat4 MathLib::scaling(const glm::vec3& v1) {
    glm::mat4 mat = MathLib::identity();
    mat[0][0] = v1.x;
    mat[1][1] = v1.y;
    mat[2][2] = v1.z;
    return mat;
}

glm::mat4 MathLib::rotationX(float angle) {
    glm::mat4 mat = MathLib::identity();
    mat[1][1] = std::cos(angle);
    mat[1][2] = -std::sin(angle);
    mat[2][1] = std::sin(angle);
    mat[2][2] = std::cos(angle);
    return mat;
}

glm::mat4 MathLib::rotationY(float angle) {
    glm::mat4 mat = MathLib::identity();
    mat[0][0] = std::cos(angle);
    mat[0][2] = std::sin(angle);
    mat[2][0] = -std::sin(angle);
    mat[2][2] = std::cos(angle);
    return mat;
}

glm::mat4 MathLib::rotationZ(float angle) {
    glm::mat4 mat = MathLib::identity();
    mat[0][0] = std::cos(angle);
    mat[0][1] = -std::sin(angle);
    mat[1][0] = std::sin(angle);
    mat[1][1] = std::cos(angle);
    return mat;
}
glm::mat4 MathLib::rotation(glm::vec3 rotationVec) {
	glm::mat4 mat = MathLib::identity();
    mat = MathLib::rotationZ(rotationVec.z) * MathLib::rotationY(rotationVec.y) * MathLib::rotationX(rotationVec.x);
	return mat;
}


glm::mat4 MathLib::perspective(float fov, float aspect, float near, float far) {
    float fovRad = glm::radians(fov);
    if (aspect <= 0.0f) aspect = 1.0f;
    if (fov <= 0.01f) fov = 0.01f;

    float f = 1.0f / tan(fovRad / 2.0f);

    glm::mat4 result(0.0f);
    result[0][0] = f / aspect;
    result[1][1] = f;
    result[2][2] = (far + near) / (near - far);
    result[2][3] = (2 * far * near) / (near - far);
    result[3][2] = -1.0f;

    return result;
}

glm::mat4 MathLib::lookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up) {

    glm::vec3 f = glm::normalize(target - eye);     // forward
    glm::vec3 r = glm::normalize(glm::cross(f, up)); // right
    glm::vec3 u = glm::cross(r, f);                 // recalculated up

    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = r.x;
    rotation[1][0] = r.y;
    rotation[2][0] = r.z;

    rotation[0][1] = u.x;
    rotation[1][1] = u.y;
    rotation[2][1] = u.z;

    rotation[0][2] = -f.x;
    rotation[1][2] = -f.y;
    rotation[2][2] = -f.z;

    glm::mat4 translation = glm::mat4(1.0f);
    translation[0][3] = -eye.x;
    translation[1][3] = -eye.y;
    translation[2][3] = -eye.z;

    return rotation * translation;
}

void MathLib::convertEulerToQuaternion(float RotX, float RotY, float RotZ, float outQuat[4])
{
    std::cout << "RotX:" << RotX << ", Y:" << RotY << ", Z:" << RotZ << ", " << std::endl;

    float pitch = glm::radians(RotX);
    float yaw = glm::radians(RotY);
    float roll = glm::radians(RotZ);

    float cy = cos(yaw * 0.5f);
    float sy = sin(yaw * 0.5f);
    float cp = cos(pitch * 0.5f);
    float sp = sin(pitch * 0.5f);
    float cr = cos(roll * 0.5f);
    float sr = sin(roll * 0.5f);

    outQuat[3] = cr * cp * cy + sr * sp * sy; // w
    outQuat[0] = sr * cp * cy - cr * sp * sy; // x
    outQuat[1] = cr * sp * cy + sr * cp * sy; // y
    outQuat[2] = cr * cp * sy - sr * sp * cy; // z

    float length = sqrt(outQuat[0] * outQuat[0] + outQuat[1] * outQuat[1] +
        outQuat[2] * outQuat[2] + outQuat[3] * outQuat[3]);

    if (length > 0.0f) {
        for (int i = 0; i < 4; i++) {
            outQuat[i] /= length;
        }
    }
    else {
        // Fallback identity quaternion
        outQuat[0] = outQuat[1] = outQuat[2] = 0.0f;
        outQuat[3] = 1.0f;
    }
}

void MathLib::slerp_calc(const float q0[4], const float q1[4], float t, float result[4])
{
    float dot = q0[0] * q1[0] + q0[1] * q1[1] + q0[2] * q1[2] + q0[3] * q1[3];
    if (dot == 1.0f) {
        for (int i = 0; i < 4; i++) {
            result[i] = q0[i];
        }// If the quaternions are the same, return q0
        return;
    }
    float phi = acos(dot);
    float sin_phi = sin(phi);
    float a_u = sin((1.0f - t) * phi) / sin_phi;
    float b_u = sin(t * phi) / sin_phi;


    for (int i = 0; i < 4; i++) {
        result[i] = a_u * q0[i] + b_u * q1[i];
    }
}
 
glm::vec3 MathLib::euler_calc()
{
    float yaw0 = glm::radians(Settings::_startEulerRotX);
    float pitch0 = glm::radians(Settings::_startEulerRotY);
    float roll0 = glm::radians(Settings::_startEulerRotZ);
    float yaw1 = glm::radians(Settings::_endEulerRotX);
    float pitch1 = glm::radians(Settings::_endEulerRotY);
    float roll1 = glm::radians(Settings::_endEulerRotZ);
	float yaw = yaw0 + (yaw1 - yaw0) * Settings::_t;
	float pitch = pitch0 + (pitch1 - pitch0) * Settings::_t;
	float roll = roll0 + (roll1 - roll0) * Settings::_t;
	return glm::vec3(yaw, pitch, roll);
}