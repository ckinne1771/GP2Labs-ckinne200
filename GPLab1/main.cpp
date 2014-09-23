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

}

//The main method. This is the entry point for the project.
int main(int argc, char* arg[]){
	return 0;
}