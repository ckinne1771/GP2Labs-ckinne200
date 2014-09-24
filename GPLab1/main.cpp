//Header Files. Here are the includes for the Input/Output streams and SDL
#include <iostream>
#include <SDL.h>
//Put Global variables here

//Pointer to the SDL Windows
SDL_Window* window;

//constants to control the window's variables

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

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
	SDL_DestroyWindow(window); //clears up the memory allocated to call and create the window.
	SDL_Quit(); //clears up the memory allocated to initialise the SDL library.
}

//The main method. This is the entry point for the project.
int main(int argc, char* arg[]){

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR IN SDL_Init" << SDL_GetError() << std::endl;

		return -1;
	}

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);

	CleanUp();
	return 0;
}