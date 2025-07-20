#include <iostream>

#include <AntTweakBar/include/AntTweakBar.h>
#include <Glew/include/gl/glew.h>
#include <freeglut/include/GL/freeglut.h>

#include <vector>
#include <Windows.h>
#include <assert.h>
#include <iostream>

#include "Utils/Utils.h"
#include "Utils/wavefront_obj.h"

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Scene.h"
#include "Shader.h"
#include "Renderer.h"
#include "Settings.h"

LARGE_INTEGER ElapsedMicroseconds;

//Variables of Main:
//Scene _scene;
Renderer _renderer;
bool _isMeshLoaded = false;



void TW_CALL loadOBJModel(void* clientData);
void initScene();
void initGraphics(int argc, char *argv[]);
void Display();
void Reshape(int width, int height);
void MouseButton(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void PassiveMouseMotion(int x, int y);
void Keyboard(unsigned char k, int x, int y);
void Special(int k, int x, int y);
void Terminate(void);

//custom functions:
void TweakBarSettings(void);

int main(int argc, char *argv[])
{
	// Initialize openGL, glut, glew
	initGraphics(argc, argv);

	antTeakBar_UIscale();

	// Initialize AntTweakBar
	TwInit(TW_OPENGL_CORE, NULL);
	// Set GLUT callbacks
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(PassiveMouseMotion);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);

	//send 'glutGetModifers' function pointer to AntTweakBar.
	//required because the GLUT key event functions do not report key modifiers states.
	//TwGLUTModifiersFunc(glutGetModifiers);

	// Initialize Shaders
	_renderer.initScene();

	// Init the scene
	
	std::cout << "\n-- Step 2 : Done!  ";

	atexit(Terminate);  // called after glutMainLoop ends

	//// Create a tweak bar
	//TweakBarSettings();

	std::cout << "\n-- Step 3 : call TweakBar.. -- ";

	// Create a tweak bar
	TweakBarSettings();
	
	std::cout << "\n-- Step 4 : call glutMainLoop.. -- ";

	// Call the GLUT main loop
	glutMainLoop();

	return 0;
}


void TweakBarSettings()
{

	TwBar* bar = TwNewBar("TweakBar");

	TwEnumVal shadingMenu[] = {
	{ SIMPLE, "simple" },
	{ GOURAUD,   "Gouraud" },
	{ PHONG,     "Phong" }
	};

	TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with GLUT and OpenGL.' "); // Message added to the help bar.
	TwDefine(" TweakBar size='350 800' color='96 216 224' "); // change default tweak bar size and color
	TwAddButton(bar, "open", loadOBJModel, NULL, " label='Open OBJ File...' ");

	//read only - displaying the draw timer in micro seconds
	TwAddVarRO(bar, "time (us)", TW_TYPE_UINT32, &ElapsedMicroseconds.LowPart, "help='shows the drawing time in micro seconds'");
	//add 'g_scale' to 'bar': this is a modifiable (RW) variable of type TW_TYPE_FLOAT. Its key shortcuts are [s] and [S].
	TwAddVarRW(bar, "Scale", TW_TYPE_FLOAT, &Settings::_scale, " label='Scale' min=0.01 max=10.0 step=0.01 group=Engine keyIncr=s keyDecr=S");
	//add 'g_objQuaternion' to 'bar': this is a variable of type TW_TYPE_QUAT4D which defines the object's orientation using quaternions
	
	// Object Transformations
	TwAddVarRW(bar, "Object Rotation", TW_TYPE_QUAT4F, &Settings::_objQuaternion,
		" group='Object Transform' label='Object rotation' opened=true help='This is object rotation' ");
	TwAddVarRW(bar, "Translate Object X", TW_TYPE_DOUBLE, &Settings::_objTransX, " group='Object Transform' min=-10 max=10 step=0.1 ");
	TwAddVarRW(bar, "Translate Object Y", TW_TYPE_DOUBLE, &Settings::_objTransY, "group='Object Transform' min=-10 max=10 step=0.1 ");
	TwAddVarRW(bar, "Translate Object Z", TW_TYPE_DOUBLE, &Settings::_objTransZ, "group='Object Transform' min=-10 max=10 step=0.1 ");
	
	// world Transformations
	TwAddVarRW(bar, "World Rotation", TW_TYPE_QUAT4F, &Settings::_worldQuaternion,
		" group='World Transform' label='World rotation' opened=true help='This is World rotation' ");	
	TwAddVarRW(bar, "Translate World X", TW_TYPE_DOUBLE, &Settings::_worldTransX, " group='World Transform' step=0.1 ");
	TwAddVarRW(bar, "Translate World Y", TW_TYPE_DOUBLE, &Settings::_worldTransY, " group='World Transform' step=0.1 ");
	TwAddVarRW(bar, "Translate World Z", TW_TYPE_DOUBLE, &Settings::_worldTransZ, " group='World Transform' step=0.1 ");

	// Perspective
	TwAddVarRW(bar, "Near Plane", TW_TYPE_DOUBLE, &Settings::_nearPlane,"group='Perspective' min=0.01 max=10 step=0.01");
	TwAddVarRW(bar, "Far Plane", TW_TYPE_DOUBLE, &Settings::_farPlane,"group='Perspective' min=11 max=5000 step=10");
	TwAddVarRW(bar, "Field of View", TW_TYPE_DOUBLE, &Settings::_fov,"group='Perspective' min=0.1 max=120 step=1");

	// Camera Controls
	TwAddVarRW(bar, "Translate Camera X", TW_TYPE_DOUBLE, &Settings::_camTransX, " group='Camera Controls' min=-10 max=10 step=0.1 ");
	TwAddVarRW(bar, "Translate Camera Y", TW_TYPE_DOUBLE, &Settings::_camTransY, "group='Camera Controls' min=-10 max=10 step=0.1 ");
	TwAddVarRW(bar, "Translate Camera Z", TW_TYPE_DOUBLE, &Settings::_camTransZ, "group='Camera Controls' min=-10 max=10 step=0.1 ");
	TwAddVarRW(bar, "Rotate Camera X", TW_TYPE_DOUBLE, &Settings::_camRotX, "group='Camera Controls' min=-180 max=180 step=1 ");
	TwAddVarRW(bar, "Rotate Camera Y", TW_TYPE_DOUBLE, &Settings::_camRotY, "group='Camera Controls' min=-89.0f max=89.0f step=1 ");
	TwAddVarRW(bar, "Rotate Camera Z", TW_TYPE_DOUBLE, &Settings::_camRotZ, "group='Camera Controls' min=-180 max=180 step=1 ");

	// Object Geometry Visualization
	TwAddVarRW(bar, "Show Bounding Box", TW_TYPE_BOOL8, &Settings::_BBoxBtn, " group='Object Geometry Visualization' label='Show Bounding Box' ");
	TwAddVarRW(bar, "Show Vertex Normals", TW_TYPE_BOOL8, &Settings::_vertexNormalsBtn, " group='Object Geometry Visualization' label='Show Vertex Normals' ");
	TwAddVarRW(bar, "Normal Scale", TW_TYPE_DOUBLE, &Settings::_normalScale, " group='Object Geometry Visualization' min=0.1 max=5 step=0.1 ");


	// Material property sliders
	TwAddVarRW(bar, "Ambient k_a", TW_TYPE_FLOAT, &Settings::_ambient,
		" group='Material properties' min=0.0 max=1.0 step=0.1 help='Ambient reflection coefficient'");
	TwAddVarRW(bar, "Diffuse k_d", TW_TYPE_FLOAT, &Settings::_diffuse,
		" group='Material properties' min=0.0 max=1.0 step=0.1 help='Diffuse reflection coefficient'");
	TwAddVarRW(bar, "Specular k_s", TW_TYPE_FLOAT, &Settings::_specular,
		" group='Material properties' min=0.0 max=1.0 step=0.1 help='Specular reflection coefficient'");
	TwAddVarRW(bar, "Shininess", TW_TYPE_FLOAT, &Settings::_shininess,
		" group='Material properties' min=1.0 max=100.0 step=1.0 help='Specular highlight shininess exponent'");
	// Base color as RGB
	TwAddVarRW(bar, "Material Color", TW_TYPE_COLOR3F, &Settings::_baseColor,
		" group='Material properties' label='Base Color' help='Base material color (RGB)' ");
	// Double-sided lighting toggle
	TwAddVarRW(bar, "Double-Sided", TW_TYPE_BOOL8, &Settings::_doubleSided,
		" group='Material properties' label='Double-Sided Lighting' help='If enabled, light back faces by inverting normal'");
	/*TwType zModeType = TwDefineEnum("ZBufferMode", zBufferModes, 3);
	TwAddVarRW(bar, "Z-Buffer Mode", zModeType, &Settings::_zBufferMode, " group='Material propertiess' ");*/

	//Light properties

	// Light type enum for AntTweakBar
	TwEnumVal lightTypeMenu[] = { {DIRECTIONAL, "Directional"}, {POINTY, "Point"} };
	TwType lightTypeTW = TwDefineEnum("LightType", lightTypeMenu, 2);

	//// Global ambient light color
	TwAddVarRW(bar, "Ambient Light", TW_TYPE_COLOR3F, &Settings::_ambientLight,
		"group='Global Light properties' label='Ambient Light' help='Global ambient light intensity (RGB)' ");

	TwType shadingType = TwDefineEnum("ShadingMode", shadingMenu, 3);
	TwAddVarRW(bar, "Shading Mode", shadingType, &Settings::_shadingMode, " group='Global Light properties' ");

	// Light1 controls
	TwAddVarRW(bar, "Light1 Type", lightTypeTW, &Settings::_light1Type,
		" group='Light1 properties' label='Light 1 Type' help='Select directional or point light'");
	TwAddVarRW(bar, "Light1 Direction", TW_TYPE_DIR3F, &Settings::_light1Direction,
		" group='Light1 properties' label='Light 1 Direction' opened=true help='Direction for directional light (normalized)' ");
	TwAddVarRW(bar, "Light1 Position", TW_TYPE_DIR3F, &Settings::_light1Pos,
		" group='Light1 properties' label='Light 1 Position' opened=true help='Position for point light (world coordinates)' ");
	TwAddVarRW(bar, "Light1 Color", TW_TYPE_COLOR3F, &Settings::_light1Intensity,
		" group='Light1 properties' label='Light 1 Color' help='Intensity/Color of Light 1' ");

	// Light2 controls (including enable toggle)
	TwAddVarRW(bar, "Light2 Enabled", TW_TYPE_BOOL8, &Settings::_light2Enabled,
		" group='Light2 properties' label='Enable Light 2' help='Toggle second light source on/off' ");
	TwAddVarRW(bar, "Light2 Type", lightTypeTW, &Settings::_light2Type,
		" group='Light2 properties' label='Light 2 Type' help='Select directional or point light'");
	TwAddVarRW(bar, "Light2 Direction", TW_TYPE_DIR3F, &Settings::_light2Direction,
		" group='Light2 properties' label='Light 2 Direction' opened=true help='Direction for Light 2 (if directional)' ");
	TwAddVarRW(bar, "Light2 Position", TW_TYPE_DIR3F, &Settings::_light2Pos,
		" group='Light2 properties' label='Light 2 Position' opened=true help='Position for Light 2 (if point)' ");
	TwAddVarRW(bar, "Light2 Color", TW_TYPE_COLOR3F, &Settings::_light2Intensity,
		" group='Light2 properties' label='Light 2 Color' help='Intensity/Color of Light 2' ");
	
}


void TW_CALL loadOBJModel(void *data)
{
	std::wstring fileName = getOpenFileName();
	bool result = _renderer.loadModelToScene(fileName);

	if(result)
	{
		_isMeshLoaded = true;
	}
	else
	{
		std::cerr << "Failed to load obj file" << std::endl;
	}
	std::cout << "The number of vertices in the model is: " << _renderer.getScene().getObject().getMeshLoader().getVertices().size() << std::endl;
	std::cout << "The number of triangles in the model is: " << _renderer.getScene().getObject().getMeshLoader().getIndices().size() << std::endl;

}


void initGraphics(int argc, char* argv[])
{
	// Set the DPI awareness to Per-Monitor DPI Awareness
	bool res = SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE);


	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitContextVersion(4, 6); //latest most advanced version of OpenGL
	glutInitContextProfile(GLUT_CORE_PROFILE); // Request a core profile

											   //for some reason, the forward compatible mode causes errors on my surface laptop with Nvidia card. It might be related to AntTweakBar
	//glutInitContextFlags(GLUT_FORWARD_COMPATIBLE); // Request forward-compatible context
	//
	// Request a debug context
	//glutInitContextFlags(GLUT_DEBUG);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //use a framebuffer with double buffering and RGBA format. Use a z-buffer
	glutInitWindowSize(1600, 900);
	glutCreateWindow("Computer Graphics Skeleton using: OpenGL, AntTweakBar, freeGlut, glew");
	glutCreateMenu(NULL);

	// Initialize OpenGL
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	initGlew();

	debugOutputOpenGL();

	displaySoftwareStatus();
}


//callback function called by GLUT to render screen
void Display()
{

	glClearColor(0.0, 0.0, 0.0, 1.0); //set the background color to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //init z-buffer and framebuffer


	LARGE_INTEGER EndingTime;
	LARGE_INTEGER StartingTime;
	LARGE_INTEGER Frequency;

	QueryPerformanceCounter(&StartingTime);

	_renderer.drawScene();

	//time measuring - don't delete
	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	ElapsedMicroseconds.QuadPart *= 1000000;
	//initialize the timer frequency
	QueryPerformanceFrequency(&Frequency);

	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

	//draw tweak bars
	TwDraw();

	//swap back and front frame buffers
	glutSwapBuffers();
}


// Callback function called by GLUT when window size changes
void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	Settings::setScreenSize(width, height);
	// Send the new window size to AntTweakBar
	TwWindowSize(width, height);
	glutPostRedisplay();
}


void MouseButton(int button, int state, int x, int y)
{
	TwEventMouseButtonGLUT(button, state, x, y);
	glutPostRedisplay();
}

void MouseMotion(int x, int y)
{
	TwEventMouseMotionGLUT(x, y);
	glutPostRedisplay();
}

void PassiveMouseMotion(int x, int y)
{
	TwEventMouseMotionGLUT(x, y);
	glutPostRedisplay();
}


void Keyboard(unsigned char k, int x, int y)
{
	TwEventKeyboardGLUT(k, x, y); //do not delete this line!
	glutPostRedisplay();
}

void Special(int k, int x, int y)
{
	TwEventSpecialGLUT(k, x, y);
	glutPostRedisplay();
}


// Function called at exit
void Terminate(void)
{
	TwTerminate();
	//to do: add code for releasing OpenGL data such as textures and buffers
}
