#include <iostream>
#include "SDL.h"

/*
//Lesson 5 - Textures
//textures are the GPU rendering equivalent of surfaces, hence they are almost always created from surfaces
#define X_AXIS  640
#define Y_AXIS  480

bool init();
void kill();
bool loop();

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *image;
SDL_Texture *texture;

int main() {
    if(!init()) return 1;

    while(loop()) {
        SDL_Delay(10);
    }

    kill();
    return 0;
}

bool loop() {
    static const unsigned char* keys = SDL_GetKeyboardState(NULL);
    
    SDL_Event e;
    SDL_Rect dest;

    static int mx = -1, my = -1;
    static double rot = 0;
    static unsigned char alpha = 255;
    if(alpha > 0) alpha -+ 1;
    SDL_SetTextureAlphaMod(texture, alpha);

    //Clear the window to white
    SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    while(SDL_PollEvent(&e) != 0) {
        switch(e.type) {
            case SDL_QUIT:
                return false;
            case SDL_MOUSEMOTION:
                mx = e.motion.x;
                my = e.motion.y;
                break;
        }
    }

    if(mx != -1) {
        float wpercent = mx / 640.0f;
        float hpercent = my / 480.0f;

        unsigned char r = round(wpercent * 255);
        unsigned char g = round(hpercent / 480.0f);

        SDL_SetTextureColorMod(texture, r, g, 0);

        mx -= 320;
        my -= 240;
        rot = atan((float)my / (float)mx) * (180.0f / 3.14f);
        if(mx < 0) rot -= 180;
    }
    mx = my = -1;

    dest.x = 0;
    dest.y = 0;
    dest.w = X_AXIS;
    dest.h = Y_AXIS;
    //Equivelant of SDL_BlitScaled
    SDL_RenderCopyEx(renderer, texture, NULL, &dest, rot, NULL, keys[SDL_SCANCODE_F] ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);

    SDL_RenderPresent(renderer);
    return true;
}

bool init() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
        std::cout << "Error initializing SDL " << SDL_GetError() << std::endl;
        return false;
    }
    window = SDL_CreateWindow("mywindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, X_AXIS, Y_AXIS, SDL_WINDOW_SHOWN);
    if(!window) {
        std::cout << "Failed to create window " << SDL_GetError() << std::endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {
        std::cout << "Failed to create window " << SDL_GetError() << std::endl;
        return false;
    }
    image = SDL_LoadBMP("bmp_24.bmp");
    if(!image) {
        std::cout << "Failed to create surface " << SDL_GetError() << std::endl;
        return false;
    }
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = NULL;
    if(!texture) {
        std::cout << "Failed to create texture " << SDL_GetError() << std::endl;
        return false;
    }
    
    return true;
}

void kill() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    texture = NULL;
    renderer = NULL;
    window = NULL;
    SDL_Quit();
}
*/