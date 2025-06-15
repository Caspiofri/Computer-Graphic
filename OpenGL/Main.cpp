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

LARGE_INTEGER ElapsedMicroseconds;


float g_scale = 1.0f;
float g_quaternion[4] = {0.0f, 0.0f, 0.0f, 1.0f}; //[x,y,z,w] - w is the real part

Shader* triangleShader = nullptr;


//Variables of Main:
Scene _scene;
bool _isMeshLoaded = true;


void TW_CALL loadOBJModel(void* clientData);
void initScene();
void initGraphics(int argc, char *argv[]);
void drawScene();
void Display();
void Reshape(int width, int height);
void MouseButton(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void PassiveMouseMotion(int x, int y);
void Keyboard(unsigned char k, int x, int y);
void Special(int k, int x, int y);
void Terminate(void);
////custom functions:
//void TweakBarSettings(void);

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
	std::cout << "\n-- Step 1 : Setting Shader .. -- ";


	triangleShader = new Shader("..\\Shaders\\vertexShader.glsl", "..\\Shaders\\fragmentShader.glsl");
	if(!triangleShader->getID())
	{
		std::cout << "\nFatal Error in shader creation!\n\a\a\a";
		return 0;
	}
	std::cout << "\n -- Step 1 : Done!  ";

	std::cout << "\n-- Step 2 : init Scene With Cube .. -- ";
	// Init the scene
	_scene.initSceneWithCube(triangleShader);
	
	std::cout << "\n-- Step 2 : Done!  ";

	atexit(Terminate);  // called after glutMainLoop ends

	//// Create a tweak bar
	//TweakBarSettings();

	std::cout << "\n-- Step 3 : call TweakBar.. -- ";

	// Create a tweak bar
	TwBar* bar = TwNewBar("TweakBar");

	TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with GLUT and OpenGL.' "); // Message added to the help bar.
	TwDefine(" TweakBar size='350 800' color='96 216 224' "); // change default tweak bar size and color
	TwAddButton(bar, "open", loadOBJModel, NULL, " label='Open OBJ File...' ");

	//read only - displaying the draw timer in micro seconds
	TwAddVarRO(bar, "time (us)", TW_TYPE_UINT32, &ElapsedMicroseconds.LowPart, "help='shows the drawing time in micro seconds'");
	//add 'g_scale' to 'bar': this is a modifiable (RW) variable of type TW_TYPE_FLOAT. Its key shortcuts are [s] and [S].
	TwAddVarRW(bar, "Scale", TW_TYPE_FLOAT, &g_scale, " label='Scale' min=0.01 max=10.0 step=0.01 group=Engine keyIncr=s keyDecr=S");
	//add 'g_quaternion' to 'bar': this is a variable of type TW_TYPE_QUAT4D which defines the object's orientation using quaternions
	TwAddVarRW(bar, "Rotation", TW_TYPE_QUAT4F, &g_quaternion, " label='Object rotation' opened=true help='This is object rotation' ");

	std::cout << "\n-- Step 4 : call glutMainLoop.. -- ";

	// Call the GLUT main loop
	glutMainLoop();

	return 0;
}



void TW_CALL loadOBJModel(void *data)
{
	std::cerr << "[loadOBJModel]:calling loadOBJModel" << std::endl;

	std::wstring fileName = getOpenFileName();
	Scene* _scene = static_cast<Scene*>(data);
	if (!_scene) {
		std::cerr << "Error: Scene instance is null!" << std::endl;
		return;
	}
	std::cout << "[loadOBJModel]: try loading model" << std::endl;

	bool result = _scene->loadModel(fileName , triangleShader);

	if(result)
	{
		std::cout << "[loadOBJModel]: model loaded successfully" << std::endl;
		//std::cout << "The obj file was loaded successfully" << std::endl;
		////clear the mesh if it was loaded before	
		//if (_isMeshLoaded)
		//{
		//	_mesh.reset();
		//}
		////upload the data to the mesh
		//_mesh.uploadFrom(objScene);

		_isMeshLoaded = true;

	}
	else
	{
		std::cerr << "Failed to load obj file" << std::endl;
	}

	std::cout << "The number of vertices in the model is: " << _scene->getMeshLoader().getVertices().size() << std::endl;
	std::cout << "The number of triangles in the model is: " << _scene->getMeshLoader().getIndices().size() << std::endl;

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



void drawScene()
{
	std::cerr << "[drawScene] starting .. " << std::endl;

	if (!triangleShader->getID())
	{
		std::cerr << "[drawScene] no triangleShader id.. exiting .. " << std::endl;
		return;
	}

	glm::mat4x4 mat_rotation;
	ConvertQuaternionToMatrix(g_quaternion, mat_rotation);

	glm::mat4x4 mat_translation;
	createTranslationMatrix(0.0f, 0.0f, -5.0f, mat_translation);

	glm::mat4x4 mat_projection;

	const float nearPlane = 1.0f;
	const float farPlane = 1000.0f;
	float top = 0.0f;
	float right = 0.0f;

	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	float aspectRatio = (float)width / (float)height;
	if (width > height)
	{
		top = 0.25f;
		right = aspectRatio * top;
	}
	else
	{
		right = 0.25f;
		top = right/aspectRatio;
	}

	createPerspectiveProjectionMatrix(nearPlane, farPlane, right, top, mat_projection);



	if (_isMeshLoaded)
	{
		std::cout << "[drawScene]: _isMeshLoaded is true... " << std::endl;

		// Bind the VAO of the mesh
		_scene.draw(mat_rotation, mat_translation, mat_projection);

		std::cout << "[drawScene]: draw mesh executed !" <<  std::endl;

	}
	else
	{
		std::cout << "[drawScene]: no mesh loaded - rendering cube ... " << std::endl;
		// If no mesh is loaded, draw a default cube
		int numIndices = 36; // 6 faces * 2 triangles per face * 3 indices per triangle
		std::cout << "[drawScene]: calling initSceneWithCube" << std::endl;
		_scene.initSceneWithCube(triangleShader);
		
		std::cout << "[drawScene]: calling draw scene" << std::endl;
		_scene.draw(mat_rotation, mat_translation, mat_projection);
	}

	// Unbind the shader program after drawing
	glUseProgram(0);

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

	drawScene();

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


//void initScene()
//{
//	std::vector<glm::vec4> positions;
//	std::vector<glm::vec4> colors;
//	std::vector<glm::uvec3> triangleIndices; //triplets of indices
//	createCube(positions, colors, triangleIndices);
//	
//	GLuint vertexArrayObjectID = 0;
//	//create a Vertex Array Object (VAO)
//	glGenVertexArrays(1, &vertexArrayObjectID);
//	glBindVertexArray(vertexArrayObjectID);
//
//	GLuint vertexBufferObjectID = 0;
//	//create and initialize a Vertex Buffer Object (VBO)
//	glGenBuffers(1, &vertexBufferObjectID);
//	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectID);
//
//	int numV = 8;
//
//	//this will allocate memory for the buffer object on the GPU
//	glBufferData(GL_ARRAY_BUFFER, numV*(sizeof(glm::vec4) + sizeof(glm::vec4)), NULL, GL_STATIC_DRAW);
//	//this will copy the data from CPU memory to GPU memory
//	//glBufferSubData redefines the data store for the buffer object currently bound to target
//	glBufferSubData(GL_ARRAY_BUFFER, 0, numV*sizeof(glm::vec4), positions.data());
//	//the colors are appended to the buffer right after the positions
//	glBufferSubData(GL_ARRAY_BUFFER, numV*sizeof(glm::vec4), numV*sizeof(glm::vec4), colors.data());
//
//	//create, load, compile, attach vertex and fragment shader
//	g_programID = Shader::initShader("..\\Shaders\\vertexShader.glsl", "..\\Shaders\\fragmentShader.glsl");
//	if(!g_programID)
//	{
//		std::cout << "\nFatal Error in shader creation!\n\a\a\a";
//		return;
//	}
//
//	//get the identifier of the attribute "vPosition" in the active gl program
//	GLint vPosition_id = glGetAttribLocation(g_programID, "vPosition");
//	//this enables the generic vertex attribute array such that the values in the generic vertex attribute array
//	//will be accessed and used for rendering when calls are made to vertex array commands such as glDrawArrays or glDrawElements.
//	glEnableVertexAttribArray(vPosition_id);
//	//specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target
//	glVertexAttribPointer(vPosition_id, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
//
//
//	GLuint vColor_id = glGetAttribLocation(g_programID, "vColor" );
//	glEnableVertexAttribArray(vColor_id);
//	//note that the pointer offset is not 0, indicating that the color data in the vertex array buffer starts right after the geometry data.
//	glVertexAttribPointer(vColor_id, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(numV*sizeof(glm::vec4)));
//
//	GLuint indexBufferObjectID = 0;
//	// Create and bind an Element Buffer Object (EBO)
//	glGenBuffers(1, &indexBufferObjectID);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObjectID);
//
//	// Allocate and transfer the index data to the GPU
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleIndices.size() * sizeof(glm::uvec3), triangleIndices.data(), GL_STATIC_DRAW);
//}
