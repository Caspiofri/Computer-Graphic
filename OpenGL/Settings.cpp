#include "Settings.h"
#include <iostream>
#include <glm/ext/vector_float3.hpp>


namespace Settings {
	bool _BBoxBtn = false; // Show Bounding Box button
	bool _vertexNormalsBtn = false; // Show Vertex Normals button
	double _normalScale = 1.0; // Scale for vertex normals
	bool _isMeshLoaded = false; // Flag to check if mesh is loaded
	bool _worldAxisBtn = false, _objAxisBtn = false;

	// camera settings :
	int _screenWidth = 600;
	int _screenHeight = 800;
	float _aspectRatio = 600 / 800;


	// object transformation settings:
	float _scale = 1.0; // Scale factor for the model

	// object Transformations
	float _objQuaternion[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //[x,y,z,w] - w is the real part
	double _objTransX = 0.0, _objTransY = 0.0, _objTransZ = 0.0;

	//world Transformations
	float _worldQuaternion[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //[x,y,z,w] - w is the real part
	double _worldTransX = 0.0, _worldTransY = 0.0, _worldTransZ = 0.0;

	 // Perspective
    double _nearPlane = 0.1, _farPlane = 1000.0, _fov = 45.0;

    // Camera Controls
    double _camTransX = 0.0, _camTransY = 0.0, _camTransZ = 5.0;
	double _camRotX = 0.0, _camRotY = 0.0, _camRotZ = 0.0;


	//settings for material 
	float _ambient = 1.0f;
	float _diffuse = 1.0f;
	float _specular = 1.0f;
	float _shininess = 32.0f;
	glm::vec3 _baseColor = glm::vec3(1.0f, 1.0f, 1.0f);
	bool _doubleSided = false;
	//ZBufferMode _zBufferMode = ZBUFFER_MODE1;

	//settings for light
	glm::vec3 _ambientLight = glm::vec3(0.0f);
	ShadingMode _shadingMode = SIMPLE;


	//Light 1
	bool _light1Enabled = true;
	glm::vec3 _light1Pos = glm::vec3(0.0f, 0.0f, 5.0f);
	glm::vec3 _light1Intensity = glm::vec3(1.0f);
	glm::vec3 _light1Direction = glm::vec3(0.0f, 0.0f, -1.0f);
	LightType _light1Type = DIRECTIONAL;

	//Light 2
	bool _light2Enabled = false;
	glm::vec3 _light2Pos = glm::vec3(0.0f, 0.0f, 5.0f);
	glm::vec3 _light2Intensity = glm::vec3(1.0f);
	glm::vec3 _light2Direction = glm::vec3(0.0f, 0.0f, -1.0f);
	LightType _light2Type = DIRECTIONAL;
	
	// Animation
	bool _ShowBezierCurve = false;
	bool _useBezier = false;
	glm::vec3 _P0 = glm::vec3(-1.0f, 0.0f, 0.0f), _P1 = glm::vec3(-0.5f, 1.0f, 0.0f), _P2 = glm::vec3(0.5f, -1.0f, 0.0f), _P3 = glm::vec3(1.0f, 0.0f, 0.0f);// control points for Bizier curve
	float _t = 1.0f;
	bool _playAnimation = false;
	float _animationSpeed = 0.2f;


	// screen propeties
	void setScreenSize(int width, int height) {
		_screenWidth = width;
		_screenHeight = height;
		_aspectRatio = static_cast<float>(_screenWidth) / _screenHeight;
	}

	int getAspectRatio() {
		return _aspectRatio;
	}

	int getScreenWidth() {
		return _screenWidth;
	}

	int getScreenHeight() {
		return _screenHeight;
	}
	

}