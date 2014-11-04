//Header Files. Here are the includes for the Input/Output streams and SDL
#include <iostream>
#include "Vertex.h"
#include <SDL.h>
#include<gl/glew.h>
#include <SDL_opengl.h> //includes the openGL header
#include<gl/GLU.h> //Allows GLU to be used.
#include "Shader.h"
#include "Texture.h"
//maths headers
#include <glm/glm.hpp>
#include <Windows.h>
#include <vector>
#include "GameObject.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
using glm::mat4;
using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#ifdef _DEBUG && WIN32
const std::string ASSET_PATH = "assets/";

#else

const std::string ASSET_PATH = "assets";
#endif
const std::string TEXTURE_PATH = "textures/";
const std::string SHADER_PATH = "shaders/";

//Put Global variables here
GLuint texture = 0;
//Pointer to the SDL Windows
SDL_Window* window;

//the context for SDL GL
SDL_GLContext glcontext = NULL;

std::vector<GameObject*> displayList;



GameObject* mainCamera;


//matrices
mat4 viewMatrix;
mat4 projMatrix;
mat4 worldMatrix;
GLuint shaderProgram = 0;

//Gobal variables for the triangles
GLuint triangleEBO;

Vertex triangleData[] = {

	//Front
		{ vec3{ -0.5f, 0.5f, 0.5f }, vec2(0.0f, 0.0f), vec4{ 1.0f, 0.0f, 0.0f, 1.0f } },// Top Left

		{ vec3{ -0.5f, -0.5f, 0.5f }, vec2(0.0f, 1.0f), vec4{ 1.0f, 0.0f, 0.0f, 1.0f } },// Bottom Left

		{ vec3{ 0.5f, -0.5f, 0.5f }, vec2(1.0f, 1.0f), vec4{ 1.0f, 0.0f, 0.0f, 1.0f } }, //Bottom Right

		{ vec3{ 0.5f, 0.5f, 0.5f }, vec2(1.0f, 0.0f), vec4{ 1.0f, 0.0f, 0.0f, 1.0f } },// Top Right


	//back
		{ vec3{ -0.5f, 0.5f, -0.5f }, vec2(0.0f, 0.0f),vec4{ 1.0f, 0.0f, 0.0f, 1.0f } },// Top Left

		{ vec3{ -0.5f, -0.5f, -0.5f }, vec2(0.0f, 1.0f),vec4{ 1.0f, 0.0f, 0.0f, 1.0f } },// Bottom Left

		{ vec3{ 0.5f, -0.5f, -0.5f }, vec2(1.0f, 1.0f), vec4{ 1.0f, 0.0f, 0.0f, 1.0f } }, //Bottom Right

		{ vec3{ 0.5f, 0.5f, -0.5f }, vec2(1.0f, 0.0f), vec4{ 1.0f, 0.0f, 0.0f, 1.0f } },// Top Right

};
		
GLuint indices[] = {
	//front
	0, 1, 2,
	0, 3, 2,

	//left
	4, 5, 1,
	4, 1, 0,

	//right
	3, 7, 2,
	7, 6, 2,

	//bottom
	1, 5, 2,
	6, 2, 1,

	//top
	5, 0, 7,
	5, 7, 3,

	//back
	4, 5, 6,
	4, 7, 6
};

//constants to control the window's variables

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int FRAMES_PER_SECOND = 60;

//the boolean value which will determine the running of the game loop. In essence, the boolean value determines if the program is running or not.

bool running = true;
GLuint triangleVBO;

GLuint VAO;


void CheckForErrors()
{
	GLenum error;
	do{
		error = glGetError();
	} while (error != GL_NO_ERROR);
}
//This initialises the window. Height, width and a fullscreen boolean are used here.
void InitWindow(int width, int height, bool fullscreen){
	//creating the window
	window = SDL_CreateWindow("Lab1", //window title 
		SDL_WINDOWPOS_CENTERED, //x position
		SDL_WINDOWPOS_CENTERED,//y position
		width,
		height,
		SDL_WINDOW_OPENGL
		);
}
//The cleanup method. This i used to clean up memory once we exit the game loop.
void CleanUp()
{
	//glDeleteTextures(1, &texture);
	//glDeleteProgram(shaderProgram);
	//glDeleteBuffers(1, &triangleEBO);
	//glDeleteBuffers(1, &triangleVBO);
	//glDeleteBuffers(1, &VAO);

	auto iter = displayList.begin();
	while (iter != displayList.end())
	{
		(*iter)->destroy();
		if ((*iter))
		{
			delete (*iter);
			(*iter) = NULL;
			iter = displayList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	displayList.clear();
	SDL_GL_DeleteContext(glcontext); //Clears up the memory allocated to handle the OpenGL functionality.
	SDL_DestroyWindow(window); //clears up the memory allocated to call and create the window.
	SDL_Quit(); //clears up the memory allocated to initialise the SDL library.
}

void initOpenGL() //This function initialises OpenGL
{
	//ask for the 3.2 version of OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//creating the OpenGL context
	glcontext = SDL_GL_CreateContext(window);

	//for when something goes wrong in establishing the context
	if (!glcontext)
	{
		std::cout << "Error creating OpenGL context" << SDL_GetError() << std::endl;

	}

	//This sets the shading to smooth
	glShadeModel(GL_SMOOTH);

	//This changes the background to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//This changes the depth buffer to 1
	glClearDepth(1.0f);

	//This enables testing of the depth
	glEnable(GL_DEPTH_TEST);

	//This sets the testing framework to be used

	glDepthFunc(GL_LEQUAL);

	//This turns on best perspective correction.
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong*/
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}
}



void setViewport(int width, int height){

	//the screen ratio
	GLfloat ratio;

	//the height must always be above 0
	if (height == 0)
	{
		height = 1;
	}
	
	//This caclulates the screen ratio
	ratio = (GLfloat)width / (GLfloat)height;

	//This sets up the viewprt

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	//The following code sets up the Perspective Transformation

	
}

void Initialise()
{
	mainCamera = new GameObject();
	mainCamera->setName("MainCamera");

	Transform *t = new Transform();
	t->setPosition(0.0f, 0.0f, 10.0f);
	mainCamera->setTransform(t);

	Camera * c = new Camera();
	c->setAspectRatio((float)(WINDOW_WIDTH / WINDOW_HEIGHT));
	c->setFOV(45.0f);
	c->setNearClip(0.1f);
	c->setFarClip(1000.0f);

	mainCamera->setCamera(c);
	displayList.push_back(mainCamera);


	GameObject * cube = new GameObject();
	cube->setName("Cube");
	Transform *transform = new Transform();
	transform->setPosition(0.0f, 0.0f, 0.0f);
	cube->setTransform(transform);

	Material * material = new Material();
	std::string vsPath = ASSET_PATH + SHADER_PATH + "simpleVS.glsl";
	std::string fsPath = ASSET_PATH + SHADER_PATH + "simpleFS.glsl";
	material->loadShader(vsPath, fsPath);
	cube->setMaterial(material);

	Mesh * mesh = new Mesh();
	cube->setMesh(mesh);
	displayList.push_back(cube);


	//alternative sytanx
	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	{
		(*iter)->init();
	}

	mesh->copyVertexData(8, sizeof(Vertex), (void**)triangleData);
	mesh->copyIndexData(36, sizeof(int), (void**)indices);
}

//This function draws objects to be rendered.
void render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // This sets the clear colour AKA the background.
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	{
		(*iter)->render();

		Mesh * currentMesh = (*iter)->getMesh();
		Transform * currentTransform = (*iter)->getTransform();
		Material * currentMaterial = (*iter)->getMaterial();

		if (currentMesh && currentMaterial && currentTransform)
		{
			currentMaterial->bind();
			currentMesh->Bind();

			GLint MVPLocation = currentMaterial->getUniformLocation("MVP");

			Camera * cam = mainCamera->getCamera();
			mat4 MVP = cam->getProjection()*cam->getView()*currentTransform->getModelMatrix();
			glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));

			glDrawElements(GL_TRIANGLES, currentMesh->getIndexCount(), GL_UNSIGNED_INT, 0);
		}
	}

	SDL_GL_SwapWindow(window); //VERY IMPORTANT!!!! Used to swap the back and front buffer.
}



//This function updates the state of the game

void update()
{
	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	{
		(*iter)->update();
	}
}


//The main method. This is the entry point for the project.
int main(int argc, char* arg[]){

	
	// the following if statement initialises the SDL library. If a value other than 0 is returned, an error has occured and we will be shown what that error is.
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR IN SDL_Init" << SDL_GetError() << std::endl;

		return -1;
	}

	int imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int returnInitFlags = IMG_Init(imageInitFlags);
	if (((returnInitFlags)&(imageInitFlags)) != imageInitFlags) {
		std::cout << "ERROR SDL_Image Init" << IMG_GetError() << std::endl;
		//handle error
	}

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);

	initOpenGL(); //The call for the InitOpenGL Function
	//initGeometry();
	CheckForErrors();
	
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);// Sets the viewport.

	SDL_Event event; //This holds the event data generated by the program. Most window based applications are event driven, which means that different events will be generated by the user's interaction during the program's lifecycle.
	//createTexture();
	//createShader();
	
	Initialise();
	//SDL_Event event;
	while (running) //the game loop
	{
		

		while (SDL_PollEvent(&event)){ //checks to see if there are any events in the queue. If there is, a positive result is returned. If not, 0 is returned.
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) // In the event of the application closing or quiting.
			{
				running = false; //close the game loop.
			}

		}

		update(); //Calls the update function
		render(); // Calls the render function
		}
	CleanUp();
	return 0;
}