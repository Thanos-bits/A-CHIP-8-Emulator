#include <iostream>
#include "SDL.h"

/*
//Lesson 2 - Bitmaps
#define X_AXIS	1280
#define Y_AXIS	720

bool init();
void kill();
bool load();

SDL_Window *window;
SDL_Surface *winSurface;
SDL_Surface *image;

int main() {
    std::cout << "Press enter to continue" << std::endl;
	init();
	if(!load()) {
		return 1;
	}

	// Optimizes image with regard to winSurface
	SDL_Surface *conv = SDL_ConvertSurface( image, winSurface->format, 0);
	SDL_Rect dest;
	dest.x = X_AXIS / 2 - 100;
	dest.y = Y_AXIS / 2 - 100;
	// dest.w = X_AXIS;	//Only needed for SDL_BlitScaled
	// dest.h = Y_AXIS;	//Only needed for SDL_BlitScaled
	int result = SDL_BlitSurface(conv, NULL, winSurface, &dest);
	// int result = SDL_BlitScaled(conv, NULL, winSurface, &dest);

	if(result < 0) {
		std::cout << "Failed to blit image to surface " << SDL_GetError();
		return 1;
	}

	SDL_UpdateWindowSurface(window);
	std::cin.get();

	kill();

	return 0;
}

bool load() {
	image = SDL_LoadBMP( "bmp_24.bmp");
	if(!image) {
		std::cout << "Image could not be loaded" << std::endl;
		return false;
	}
	std::cout << "height = " << image->h << " and width = " << image->w << std::endl; 
	return true;
}

bool init() {
	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
		std:: cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return false;
	}
	
	window = SDL_CreateWindow("my window", 400, 400, X_AXIS,Y_AXIS, SDL_WINDOW_SHOWN );
    if(!window) {
        std::cout << "Failed to create a window! Error: " << SDL_GetError() << std::endl; 
		return false	;
	}

    winSurface = SDL_GetWindowSurface(window);
	if(!winSurface) {
		std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 255, 255, 255));
	return true;
}

void kill() {
	SDL_FreeSurface(image);

	SDL_DestroyWindow(window);
	SDL_Quit();
}
*/