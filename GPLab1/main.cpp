//Header Files. Here are the includes for the Input/Output streams and SDL
#include <iostream>
#include "Vertex.h"
#include <SDL.h>
#include<gl/glew.h>
#include <SDL_opengl.h> //includes the openGL header
#include<gl/GLU.h> //Allows GLU to be used.
#include "Shader.h"
#ifdef _DEBUG && WIN32
const std::string ASSET_PATH = "../assets";
#else
const std::string ASSET_PATH = "assets";
#endif

const std::string SHADER_PATH = "/shaders";

//Put Global variables here

//Pointer to the SDL Windows
SDL_Window* window;

//the context for SDL GL
SDL_GLContext glcontext = NULL;


Uint32 old_time, current_time;
float deltatime = 0;

//Gobal variables for the triangles
GLuint triangleEBO;

Vertex triangleData[] = {

	//front
		{ -0.5f, 0.5f, 0.5f,
		1.0f,0.0f,1.0f,1.0f}, //top left
		{-0.5f,-0.5f,0.5f,
		1.0f,1.0f,0.0f,1.0f}, //bottom left
		{ 0.5f, -0.5f, 0.5f,
		0.0f, 1.0f, 1.0f, 1.0f }, //bottom right
		{0.5f,0.5f,0.5f,
		1.0f,0.0f,1.0f,1.0f}, //top right

	//back
		{-0.5f, 0.5f,-0.5f,
		1.0f,0.0f,1.0f,1.0f}, // top left
		{ -0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 0.0f, 1.0f }, // bottom left
		{0.5f,-0.5f,-0.5f,
		0.0f,1.0f,1.0f,1.0f}, // bottom right
		{0.5f,0.5f,-0.5f,
		1.0f,0.0f,1.0f,1.0f}, // top right

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
	glDeleteBuffers(1, &triangleEBO);
	glDeleteBuffers(1, &triangleVBO);
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

void initGeometry()
{
	

	//Create buffer
	glGenBuffers(1, &triangleVBO);
	//make the new VBO active
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	//Copy Vertex Data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);


	//create Element Buffer
	glGenBuffers(1, &triangleEBO);
	//Make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);
	//Copy Index Data into the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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

//This function draws objects to be rendered.
void render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // This sets the clear colour AKA the background.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Empties the colour and depth buffer

	//Make the new VBO active. repeat here as a sanity check (may hav changed sine installation)
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);

	
	//Actually draw the triangle, giving the number of vertices provided
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

	SDL_GL_SwapWindow(window); //VERY IMPORTANT!!!! Used to swap the back and front buffer.
}



//This function updates the state of the game

void update()
{
	old_time = current_time;
	current_time = SDL_GetTicks();
	deltatime = (float)(current_time - old_time) / 1000.0f;
}

void createShader()
{
	GLuint vertexShaderProgram = 0;
	std::string vsPath = ASSET_PATH + SHADER_PATH + "simpleVS.glsl";
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);

	GLuint fragmentShaderProgram = 0;
	std::string fsPath = ASSET_PATH + SHADER_PATH + "/simpleFS.glsl";
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
}

//The main method. This is the entry point for the project.
int main(int argc, char* arg[]){

	
	// the following if statement initialises the SDL library. If a value other than 0 is returned, an error has occured and we will be shown what that error is.
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR IN SDL_Init" << SDL_GetError() << std::endl;

		return -1;
	}

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);

	initOpenGL(); //The call for the InitOpenGL Function
	initGeometry();
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);// Sets the viewport.

	SDL_Event event; //This holds the event data generated by the program. Most window based applications are event driven, which means that different events will be generated by the user's interaction during the program's lifecycle.

	while (running) //the game loop
	{
		

		while (SDL_PollEvent(&event)){ //checks to see if there are any events in the queue. If there is, a positive result is returned. If not, 0 is returned.
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) // In the event of the application closing or quiting.
			{
				running = false; //close the game loop.
			}

			/*switch (event.type){
			case SDL_KEYDOWN:

				switch (event.key.keysym.sym){
				case SDLK_LEFT:
					bottomLeftTriangleOneX = (bottomLeftTriangleOneX - (100.0f*deltatime));
					bottomRightTriangleOneX = (bottomRightTriangleOneX - (100.0f*deltatime));
					topLeftTriangleOneX = (topLeftTriangleOneX - (100.0f*deltatime));
					break;
				case SDLK_RIGHT:
					bottomLeftTriangleOneX = (bottomLeftTriangleOneX + 0.1f);
					bottomRightTriangleOneX = (bottomRightTriangleOneX + 0.1f);
					topLeftTriangleOneX = (topLeftTriangleOneX + 0.1f);
					break;
				case SDLK_UP:
					bottomLeftTriangleOneY = (bottomLeftTriangleOneY + 0.1f);
					bottomRightTriangleOneY = (bottomRightTriangleOneY + 0.1f);
					topLeftTriangleOneY = (topLeftTriangleOneY + 0.1f);
					break;
				case SDLK_DOWN:
					bottomLeftTriangleOneY = (bottomLeftTriangleOneY - 0.1f);
					bottomRightTriangleOneY = (bottomRightTriangleOneY - 0.1f);
					topLeftTriangleOneY = (topLeftTriangleOneY - 0.1f);
					break;
					
				}
			}*/


		}

		update(); //Calls the update function
		render(); // Calls the render function


	}

	

	CleanUp();
	return 0;
}