#pragma once
namespace Settings {
	extern bool _BBoxBtn; // Show Bounding Box button
	extern bool _vertexNormalsBtn; // Show Vertex Normals button
	extern double _normalScale; // Scale for vertex normals
	extern bool _isMeshLoaded; // Flag to check if mesh is loaded

	// object transformation settings:
	extern float _scale; // Scale factor for the model
	extern float _quaternion[4]; // Quaternion for rotation [x, y, z, w]

	//object settings :
	extern double _objTransX, _objTransY, _objTransZ;
}