#include <iostream>
#include "chip8.h"
#include "SDL.h"

#define X_AXIS  640
#define Y_AXIS  320

chip8 myChip8;

bool init_sdl();
void kill();
bool loop();
void handleKeyEvent(const SDL_Event& e, bool isDown);

SDL_Window* window;
SDL_Renderer *renderer;
SDL_Texture *texture;

const SDL_Scancode keymap[16] = {
    SDL_SCANCODE_X, // 0
    SDL_SCANCODE_1, // 1
    SDL_SCANCODE_2, // 2
    SDL_SCANCODE_3, // 3
    SDL_SCANCODE_Q, // 4
    SDL_SCANCODE_W, // 5
    SDL_SCANCODE_E, // 6
    SDL_SCANCODE_A, // 7
    SDL_SCANCODE_S, // 8
    SDL_SCANCODE_D, // 9
    SDL_SCANCODE_Z, // A
    SDL_SCANCODE_C, // B
    SDL_SCANCODE_4, // C
    SDL_SCANCODE_R, // D
    SDL_SCANCODE_F, // E
    SDL_SCANCODE_V  // F
};

int main() {
    //myChip8.loadApp("~/Documents/A-CHIP-8-Emulator/Games/invaders.c8");
    if(!myChip8.loadApp("tetris.c8")) {
        std::cerr << "Failed to load ROM" << std::endl;
        return 1;
    }

    if(!init_sdl()) {
        std::cerr << "Failed to initialize sdl lib " << SDL_GetError() << std::endl;
        return 1;
    }

    const int cyclesPerFrame = 10;

    while(loop()) {
        for(int i = 0; i < cyclesPerFrame; i++) {
            myChip8.emulateCycle();
        }
        if(myChip8.drawFlag) {
            uint32_t pixels[64*32];
            for(int i = 0; i < 64*32; i++) {
                pixels[i] = myChip8.gfx[i] ? 0x00FFFFFF : 0x00000000;
            }
            SDL_UpdateTexture(texture, NULL, pixels, 64 * sizeof(uint32_t));
            
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            
            myChip8.drawFlag = false;
        }
        if(myChip8.delay_timer > 0) myChip8.delay_timer--;
        if (myChip8.sound_timer > 0) {
            if (myChip8.sound_timer == 1) {
                std::cout << "BEEP!" << std::endl;
            }
            myChip8.sound_timer--;
        }
    }

    kill();
    return 0;
}

bool loop() {
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0) {
        switch(e.type) {
            case SDL_QUIT:
                return false;
            case SDL_KEYDOWN:
                if(e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    return false;
                }
                handleKeyEvent(e, true);
            break;
            case SDL_KEYUP:
                handleKeyEvent(e, false);
            break;
        }
    }    
    return true;
}

void handleKeyEvent(const SDL_Event& e, bool isDown) {
    for (int i = 0; i < 16; i++) {
        if (e.key.keysym.scancode == keymap[i]) {
            myChip8.key[i] = isDown ? 1 : 0;
            break;
        }
    }
}

bool init_sdl() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, X_AXIS, Y_AXIS, SDL_WINDOW_SHOWN);
    if(!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, 64, 32);
    if(!texture) {
        std::cerr << "Error while creating texture" << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void kill() {
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyTexture(texture);
    texture = NULL;

    SDL_Quit();
}