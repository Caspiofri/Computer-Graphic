#pragma once
#include <glm/glm.hpp>
#include "Light.h"

enum ShadingMode { SIMPLE, GOURAUD, PHONG };

namespace Settings {
	extern bool _BBoxBtn; // Show Bounding Box button
	extern bool _vertexNormalsBtn; // Show Vertex Normals button
	extern double _normalScale; // Scale for vertex normals
	extern bool _isMeshLoaded; // Flag to check if mesh is loaded

	//camera settings :
	extern int _screenWidth, _screenHeight;
	extern float _aspectRatio;
	extern double _normalScale, _nearPlane, _farPlane, _fov;

	// Camera Controls
	extern double _camRotX, _camRotY, _camRotZ;
	extern double _camTransX, _camTransY, _camTransZ;

	// object transformation settings:
	extern float _scale; // Scale factor for the model

	//object settings :
	extern float _objQuaternion[4]; // Quaternion for rotation [x, y, z, w]
	extern double _objTransX, _objTransY, _objTransZ;

	//world settings :
	extern float _worldQuaternion[4]; // Quaternion for rotation [x, y, z, w]
	extern double _worldTransX, _worldTransY, _worldTransZ;

	//material settings :
	extern float _ambient, _diffuse, _specular, _shininess;
	extern glm::vec3 _baseColor;
	extern bool _doubleSided;
	extern bool _materialChanged;
	//extern ZBufferMode _zBufferMode;

	//light settings: 
	extern ShadingMode _shadingMode;

	extern glm::vec3 _ambientLight;
	extern bool _light2Enabled;
	extern LightType _light1Type, _light2Type;
	extern glm::vec3 _light1Pos, _light2Pos;
	extern glm::vec3 _light1Intensity, _light2Intensity;
	extern glm::vec3 _light1Direction, _light2Direction;

	extern void setScreenSize(int width, int height);
}