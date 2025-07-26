#pragma once
#include <glm/glm.hpp>
#include "Light.h"

enum ShadingMode { SIMPLE, GOURAUD, PHONG };

namespace Settings {
	extern bool _BBoxBtn; // Show Bounding Box button
	extern bool _vertexNormalsBtn; // Show Vertex Normals button
	extern double _normalScale; // Scale for vertex normals
	extern bool _isMeshLoaded; // Flag to check if mesh is loaded
	extern bool _worldAxisBtn;
	extern bool _objAxisBtn;
	extern bool _ShowBezierCurve;

	//camera settings :
	extern int _screenWidth, _screenHeight;
	extern float _aspectRatio;
	extern double _normalScale, _nearPlane, _farPlane, _fov;

	// Camera Controls
	extern double _camRotX, _camRotY, _camRotZ;
	extern double _camTransX, _camTransY, _camTransZ;

	// object transformation settings:
	extern float _scale; 

	//object settings :
	extern float _objQuaternion[4];
	extern double _objTransX, _objTransY, _objTransZ;

	//world settings :
	extern float _worldQuaternion[4]; 
	extern double _worldTransX, _worldTransY, _worldTransZ;

	//material settings :
	extern float _ambient, _diffuse, _specular, _shininess;
	extern glm::vec3 _baseColor;
	extern bool _doubleSided;
	extern bool _materialChanged;
	//extern ZBufferMode _zBufferMode;

	// Animation
	extern glm::vec3 _P0, _P1, _P2, _P3; // Control points for Bezier curve
	extern float _t;
	extern bool _useBezier;
	extern bool _playAnimation;
	extern bool _useSlerp;
	extern float _animationSpeed;

	// slerp 
	extern double _startSlerpRotX, _startSlerpRotY, _startSlerpRotZ;
	extern double _endSlerpRotX, _endSlerpRotY, _endSlerpRotZ;
	
	//Euler
	extern double _startEulerRotX, _startEulerRotY, _startEulerRotZ;
	extern double _endEulerRotX, _endEulerRotY, _endEulerRotZ;

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