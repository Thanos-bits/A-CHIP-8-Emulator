#include <iostream>
#include "SDL.h"

//Lesson 1

// int main() {
//     std::cout << "Press enter to continue";
    
// 	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
// 		std:: cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
// 		// End the program
// 		return 1;
// 	}

//     SDL_Window *win = SDL_CreateWindow("my window", 400, 400, 1280, 720, SDL_WINDOW_SHOWN );
    
//     if(!win) {
//         std::cout << "Failed to create a window! Error: " << SDL_GetError() << std::endl; 
// 		return 1;
// 	}

//     SDL_Surface *winSurface = SDL_GetWindowSurface(win);
// 	if(!winSurface) {
// 		std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
// 		return 1;
// 	}
// 	//drawing ...

//     SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 255, 255, 255));
//     SDL_UpdateWindowSurface(win);		//shows the result

//     std::cin.get();
// 	SDL_DestroyWindow(win);
// 	SDL_Quit();

//     return 0;
// }

//Lesson 2

int main() {
    std::cout << "Press enter to continue";

	SDL_Surface *image = SDL_LoadBMP( "bmp_24.bmp");

	if(!image) {
		std::cout << "Image could not be loaded" << std::endl;
		return 1;
	}

	SDL_FreeSurface(image);
	
	return 0;
}