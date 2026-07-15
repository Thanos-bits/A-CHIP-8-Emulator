#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#define X_AXIS  640
#define Y_AXIS  480

using namespace std;

bool init();
void kill();
bool loop();

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture, *text;
TTF_Font* font;
string input;

int main() {
    if(!init()) return 1;
    while(loop()) {
        SDL_Delay(10);
    }
    kill();
    return 0;
}

bool loop() {

	static const unsigned char* keys = SDL_GetKeyboardState( NULL );

	SDL_Event e;
	SDL_Rect dest;

	// Clear the window to white
	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	SDL_RenderClear( renderer );

	// Event loop
	while ( SDL_PollEvent( &e ) != 0 ) {
		switch (e.type) {
			case SDL_QUIT:
				return false;
			case SDL_TEXTINPUT:
				input += e.text.text;
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_BACKSPACE && input.size()) {
					input.pop_back();
				}
				break;
		}
	}

	// Render texture
	SDL_RenderCopy(renderer, texture, NULL, NULL);

	SDL_Color foreground = { 0, 0, 0 };

	if ( input.size() ) {
		SDL_Surface* text_surf = TTF_RenderText_Solid(font, input.c_str(), foreground);
		text = SDL_CreateTextureFromSurface(renderer, text_surf);

		dest.x = 320 - (text_surf->w / 2.0f);
		dest.y = 240;
		dest.w = text_surf->w;
		dest.h = text_surf->h;
		SDL_RenderCopy(renderer, text, NULL, &dest);

		SDL_DestroyTexture(text);
		SDL_FreeSurface(text_surf);
	}

	// Update window
	SDL_RenderPresent( renderer );

	return true;
}

bool init() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0 ) { 
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    if(IMG_Init(IMG_INIT_PNG) < 0 ) {
        std::cout << "Error initializing SDL_image: " << IMG_GetError() << std::endl;
        return false;
    }
    if(TTF_Init() < 0 ) {
        std::cout << "Error intializing SDL_ttf: " << TTF_GetError() << std::endl;
        return false;
    }
    window = SDL_CreateWindow("my window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, X_AXIS, Y_AXIS, SDL_WINDOW_SHOWN);
    if(!window) {
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {
        std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_Surface* buffer = IMG_Load("test.png");
    if(!buffer) {
        std::cout << "Error loading image test.png: " << SDL_GetError() << std::endl;
        return false;
    }
    texture = SDL_CreateTextureFromSurface(renderer, buffer);
    SDL_FreeSurface(buffer);
    buffer = NULL;

    if(!texture) {
        std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
        return false;
    }
    font = TTF_OpenFont("CookieCrisp-L36ly.ttf", 72);
    if(!font) {
        std::cout << "Error loading font: " << TTF_GetError() << std::endl;
        return false;
    }
    SDL_StartTextInput();
    return true;
}

void kill() {
    SDL_StopTextInput();

    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyTexture(texture);
    texture = NULL;
    SDL_DestroyTexture(text);
    text = NULL;

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}