#pragma once
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

	extern void setScreenSize(int width, int height);
}