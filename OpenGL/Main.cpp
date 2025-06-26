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

	TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with GLUT and OpenGL.' "); // Message added to the help bar.
	TwDefine(" TweakBar size='350 800' color='96 216 224' "); // change default tweak bar size and color
	TwAddButton(bar, "open", loadOBJModel, NULL, " label='Open OBJ File...' ");

	//read only - displaying the draw timer in micro seconds
	TwAddVarRO(bar, "time (us)", TW_TYPE_UINT32, &ElapsedMicroseconds.LowPart, "help='shows the drawing time in micro seconds'");
	//add 'g_scale' to 'bar': this is a modifiable (RW) variable of type TW_TYPE_FLOAT. Its key shortcuts are [s] and [S].
	TwAddVarRW(bar, "Scale", TW_TYPE_FLOAT, &Settings::_scale, " label='Scale' min=0.01 max=10.0 step=0.01 group=Engine keyIncr=s keyDecr=S");
	//add 'g_quaternion' to 'bar': this is a variable of type TW_TYPE_QUAT4D which defines the object's orientation using quaternions
	TwAddVarRW(bar, "Rotation", TW_TYPE_QUAT4F, &Settings:: _quaternion, " label='Object rotation' opened=true help='This is object rotation' ");

}


void TW_CALL loadOBJModel(void *data)
{
	std::cerr << "================[loadOBJModel]:calling loadOBJModel ============" << std::endl;

	std::wstring fileName = getOpenFileName();

	std::cout << "[loadOBJModel]: try loading model" << std::endl;

	bool result = _renderer.loadModelToScene(fileName);

	if(result)
	{
		std::cout << "[loadOBJModel]: model loaded successfully" << std::endl;

		_isMeshLoaded = true;

	}
	else
	{
		std::cerr << "Failed to load obj file" << std::endl;
	}

	std::cout << "The number of vertices in the model is: " << _renderer.getScene().getMeshLoader().getVertices().size() << std::endl;
	std::cout << "The number of triangles in the model is: " << _renderer.getScene().getMeshLoader().getIndices().size() << std::endl;

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
//  	static int counter = 0;
//  	std::cout << "C: " << counter << std::endl;
//  	counter++;

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
