#pragma once
namespace Settings {
	extern bool _BBoxBtn; // Show Bounding Box button
	extern bool _vertexNormalsBtn; // Show Vertex Normals button
	extern double _normalScale; // Scale for vertex normals
	extern bool _isMeshLoaded; // Flag to check if mesh is loaded

	// object transformation settings:
	extern float _scale; // Scale factor for the model

	//object settings :
	extern float _objQuaternion[4]; // Quaternion for rotation [x, y, z, w]
	extern double _objTransX, _objTransY, _objTransZ;

	//world settings :
	extern float _worldQuaternion[4]; // Quaternion for rotation [x, y, z, w]
	extern double _worldTransX, _worldTransY, _worldTransZ;
}