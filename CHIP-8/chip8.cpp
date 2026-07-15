#include <iostream>
#include <cstdint>
#include "chip8.h"

#define X ((opcode & 0x0F00) >> 8)
#define Y ((opcode & 0x00F0) >> 4)

uint8_t chip8_fontset[80] =
{ 
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};


void chip8::init() {
    // Initialize registers and memory once
    pc = 0x200;
    opcode = 0;
    I = 0;
    sp = 0;
    
    //Clear display
    for(int i = 0; i < 2048; ++i) {
        gfx[i] = 0;
    }

    //Clear stack 
    for(int i = 0; i < 16; ++i) {
        stack[i] = 0;
    }

    //Clear registers
    for(int i = 0; i < 16; ++i) {
        V[i] = 0;
    }

    //Clear memory
    for(int i = 0; i < 4096; ++i) {
        memory[i] = 0;
    }

    //Load fontset
    for(int i = 0; i < 80; i++) {
        memory[i] = chip8_fontset[i];
    }

    //Reset timers
    delay_timer = 0;
    sound_timer = 0;
}

void chip8::emulateCycle() {
    // Fetch Opcode
    opcode = memory[pc] << 8 | memory[pc+1];

    // Decode Opcode
    switch (opcode & 0xF000)
    {
    case 0x0000:
        switch (opcode & 0x000F)
        {
        case 0x0000:
            for(int i; i < 2048; ++i) {
                gfx[i] = 0x0;
                drawFlag = true;
            }
        break;
        case 0x000E:
            sp--;
            pc = stack[sp];
        break;
        default:
            std::cout << "Unkown opcode: " << opcode << std::endl;
        break;
        }
        pc += 2;
    break;
    case 0x1000:    //Go to 0x0NNN
        pc = opcode & 0x0FFF;
    break;
    
    case 0x2000:    //Calls subroutine(jump)
        stack[sp] = pc;
        ++sp;
        pc = opcode & 0x0FFF;
    break;

    case 0x3000:    //Skips the next instruction(usually a jump)
        if (V[X] == (opcode & 0x00FF) ) pc += 4;
        else pc += 2;
    break;
    
    case 0x4000:    //Skips the next instruction(usually a jump)
        if (V[X] != (opcode & 0x00FF) ) pc += 4; 
        else pc += 2;
    break;

    case 0x5000:    //0x5XY0
        if (V[X] == V[opcode & 0x00F0] ) pc += 4;
        else pc += 2;
    break;
    
    case 0x6000:     //V[X] = 0x00NN
        V[X] = opcode & 0x00FF;
        pc += 2;
    break;

    case 0x7000:
        V[X] = opcode & 0x00FF;
        pc += 2;
    break;

    case 0x8000:    
        switch (opcode & 0x000F)
        {
            case 0x0000:
                V[X] = V[Y];
            break;

            case 0x0001:
                V[X] |= V[Y]; 
            break;

            case 0x0002:
                V[X] &= V[Y];
            break;
            
            case 0x0003:
                V[X] ^= V[Y];
            break;
            
            case 0x0004:
                V[X] += V[Y];
                if(V[X] + V[Y] > 255) { V[16] = 1;} //overflow
                else V[16] = 0;
            break;

            case 0x0005:
                V[X] -= V[Y];
                if( V[X] < V[Y]) { V[16] = 0;}      //underflow
                else V[16] = 1;
            break;

            case 0x0006:
                V[16] = V[X] & 0x0001;
                V[X] >>= 1;
            break;

            case 0x0007:
                V[X] = V[Y] - V[X];
                if(V[X] > V[Y]) {V[16] = 0;}        //underflow
                else V[16] = 1; 
            break;

            case 0x000E:
                V[X] <<= 1;
                if((V[X] & 0x4000) == 0x4000) {V[16] = 1;}
                else V[16] = 0;            
            break;

            default:
                std::cout << "Unkown opcode: " << opcode << std::endl;
            break;
        }
        pc +=2;
    break;
    
    case 0x9000:
        if( V[X] != V[Y]) { pc += 4;}
        else pc += 2;
    break;

    case 0xA000:    //ANNN: Sets I to the address 0x0NNN
        I = opcode & 0x0FFF;
        pc += 2;
    break;
    
    case 0xB000:    //Jumps to NNN + V0
        pc = V[0] + (opcode & 0x0FFF);
    break;
    
    case 0xC000:    
        V[X] = rand() & (opcode & 0x00FF);
        pc += 2;
    break;

    case 0xD000:
        //draw(V[X], V[Y], (opcode & 0x000F));
        for(int i = X; i < (X + 8); ++i) {
            for(int j = Y; j < ((opcode & 0x000F) + Y); ++j) {
                gfx[X * Y] = memory[I*j + i];
            }
        }
        pc += 2;
        drawFlag = true;
    break;

    case 0xE000:
        if((opcode & 0x00A1) == 0x0A1) {
            if(key[X] != V[X]) pc += 4;
            else pc += 2;
        }
        else if((opcode & 0x009E) == 0x09E) {
            if(key[X] == V[X]) pc += 4;
            else pc += 2;
        }
        else pc += 2;
    break;

    case 0xF000:
        switch (opcode & 0x00FF)
        {
            case 0x0007:
                V[X] = delay_timer;
            break;
            
            case 0x000A:
            {
                bool keyPressed = false;
                for(int i = 0; i < 16; ++i) {
                    if(key[i] != 0) {
                        V[X] = i;
                        keyPressed = true;
                    }
                }
                if(!keyPressed) return;
            }
            break;

            case 0x0015:
                delay_timer = V[X];
            break;

            case 0x0018:
                sound_timer = V[X];
            break;
            
            case 0x001E:
                I += V[X];
            break;

            case 0x0029:    //Sets I to the location of the sprite for the char in VX
                I = V[X] * 0x5;     //X after shift contains 4 bits, * 5 -> 4x5 font
            break;

            case 0x0033:    //VX is a byte -> a number from 0-255, we want to store in different locations the hundreds, tens and ones
                memory[I] = V[X] / 100;
                memory[I + 1] = ( V[X] / 10 ) % 10;
                memory [I + 2] = (V[X] % 10) % 10;
            break;

            case 0x0055:    //Starting from address I in memory, we store the values from V0-VX
                for(int i = 0; i <= X; ++i) {
                    memory[i + I] = V[i];
                }
                I += X + 1; //Moves I to the last address stored 
            break;

            case 0X0065:    //Loads in the same way it stores
                for(int i = 0; i <= X; ++i) {
                    V[i] = memory[I + i];
                }
                I += X + 1; //Moves I to the last address loaded
            break;

            default:
                std::cout << "Unkown opcode: " << opcode << std::endl;
            break;
        }
        pc += 2;
    break;

    default:
        std::cout << "Unkown opcode: " << opcode << std::endl;
    break;
    }
    
    // Execute Opcode
    // Update timers
    if(delay_timer > 0) {
        delay_timer--;
    }

    if(sound_timer > 0) {
        if(sound_timer == 1) { std::cout << "BEEP!\n";}
        sound_timer--;
    }
}

void chip8::debugRender() {

}

bool chip8::loadApp(const char *filename) {
    init();
    FILE *file = fopen(filename, "rb");
    if(!file) {
        std::cout << "Error opening file: " << stderr <<std::endl;
        return false;
    }

    
    return true;
}