#include <iostream>
#include "SDL.h"
/*
//Lesson 3 - Events
#define X_AXIS	640
#define Y_AXIS	480

bool init();
void kill();
bool load();
bool loop();

SDL_Window *window;
SDL_Surface *winSurface;
SDL_Surface *image1;
SDL_Surface *image2;

bool running = true;

int main() {

	if(!init()) return 1;

	if(!load()) return 1;
    while (loop())	{
		SDL_Delay(10);
	}

	kill();

    return 0;
}

bool loop() {
	static bool renderImage2;
	SDL_Event e;

	// Blit image to entire window
	SDL_BlitSurface( image1, NULL, winSurface, NULL );

	while( SDL_PollEvent( &e ) != 0 ) {
		switch (e.type) {
			case SDL_QUIT:
				return false;
			case SDL_KEYDOWN:
				renderImage2 = true;
				break;
			case SDL_KEYUP:
				renderImage2 = false;
				// can also test individual keys, modifier flags, etc, etc.
				break;
			case SDL_MOUSEMOTION:
				// etc.
				break;
		}
	}

	if (renderImage2) {
		// Blit image to scaled portion of window
		SDL_Rect dest;
		dest.x = 200;
		dest.y = 0;
		dest.w = 320;
		dest.h = 240;
		SDL_BlitScaled(image2, NULL, winSurface, &dest);
	}

	// Update window
	SDL_UpdateWindowSurface( window );

	return true;

}

bool load() {
	SDL_Surface *temp1, *temp2;

	// Load images
	temp1 = SDL_LoadBMP("bmp_24.bmp");
	temp2 = SDL_LoadBMP("snail.bmp");

	// Make sure loads succeeded
	if ( !temp1 || !temp2 ) {
		std::cout << "Error loading image: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}

	// Format surfaces
	image1 = SDL_ConvertSurface( temp1, winSurface->format, 0 );
	image2 = SDL_ConvertSurface( temp2, winSurface->format, 0 );

	// Free temporary surfaces
	SDL_FreeSurface( temp1 );
	SDL_FreeSurface( temp2 );

	// Make sure format succeeded
	if ( !image1 || !image2 ) {
		std::cout << "Error converting surface: " << SDL_GetError() << std::endl;
		system("pause");
		return false;
	}
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
	SDL_FreeSurface(image1);
	SDL_FreeSurface(image2);

	SDL_DestroyWindow(window);
	SDL_Quit();
}
*/