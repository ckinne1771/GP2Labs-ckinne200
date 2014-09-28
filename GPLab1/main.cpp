//Header Files. Here are the includes for the Input/Output streams and SDL
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h> //includes the openGL header
#include<gl/GLU.h> //Allows GLU to be used.
//Put Global variables here

//Pointer to the SDL Windows
SDL_Window* window;

//the context for SDL GL
SDL_GLContext glcontext = NULL;

//Gobal variables for the triangles
float bottomLeftTriangleOneX = -1.0f;
float bottomLeftTriangleOneY = -1.0f;
float bottomLeftTriangleOneZ = 0.0f;

float topLeftTriangleOneX = -1.0f;
float topLeftTriangleOneY = 1.0f;
float topLeftTriangleOneZ = 0.0f;

float bottomRightTriangleOneX = 1.0f;
float bottomRightTriangleOneY = -1.0f;
float bottomRightTriangleOneZ = 0.0f;

float topLeftTriangleTwoX = 1.5f;
float topLeftTriangleTwoY = 1.0f;
float topLeftTriangleTwoZ = 0.0f;

float topRightTriangleTwoX = 2.0f;
float topRightTriangleTwoY = 1.0f;
float topRightTriangleTwoZ = 0.0f;

float bottomRightTriangleTwoX = 2.0f;
float bottomRightTriangleTwoY = 0.0f;
float bottomRightTriangleTwoZ = 0.0f;


//constants to control the window's variables

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

//the boolean value which will determine the running of the game loop. In essence, the boolean value determines if the program is running or not.

bool running = true;

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
void CleanUp(){
	SDL_GL_DeleteContext(glcontext); //Clears up the memory allocated to handle the OpenGL functionality.
	SDL_DestroyWindow(window); //clears up the memory allocated to call and create the window.
	SDL_Quit(); //clears up the memory allocated to initialise the SDL library.
}

void initOpenGL() //This function initialises OpenGL
{
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

	glMatrixMode(GL_PROJECTION); //This changes the Matrix Mode to project the matrix
	glLoadIdentity();

	gluPerspective(45.0f, ratio, 0.1f, 100.0f); //Calculates the perspective matrix using the functions provided by the glu library.
	//the values used in the calculations represent the FOV, screen ratio, the nearest specified point on the z axis and the furthest specified point on the z axis.
	
	
	glMatrixMode(GL_MODELVIEW); //Switches the Matrix mode to ModelView

	glLoadIdentity(); //This resets using the Identity Matrix

}

//This function draws objects to be rendered.
void render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // This sets the clear colour AKA the background.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Empties the colour and depth buffer

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(topLeftTriangleOneX, topLeftTriangleOneY, topLeftTriangleOneZ);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(bottomLeftTriangleOneX, bottomLeftTriangleOneY, bottomLeftTriangleOneZ);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(bottomRightTriangleOneX, bottomRightTriangleOneY, bottomRightTriangleOneZ);

	glBegin(GL_TRIANGLES);
	glColor3f(4.0f, 0.0f, 0.0f);
	glVertex3f(topLeftTriangleTwoX, topLeftTriangleTwoY, topLeftTriangleTwoZ);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(topRightTriangleTwoX, topRightTriangleTwoY, topRightTriangleTwoZ);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(bottomRightTriangleTwoX, bottomRightTriangleTwoY, bottomRightTriangleTwoZ);
	glEnd();
	

	SDL_GL_SwapWindow(window); //VERY IMPORTANT!!!! Used to swap the back and front buffer.
}

//This function updates the state of the game

void update()
{

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
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);// Sets the viewport.

	SDL_Event event; //This holds the event data generated by the program. Most window based applications are event driven, which means that different events will be generated by the user's interaction during the program's lifecycle.

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

