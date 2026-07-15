#ifndef CHIP8_H
#define CHIP8_H

#include <iostream>
#include <cstdint>
/* Header files affect every file they are included in, namespace std should be avoided, ptential collisions awaiting*/

class chip8{
public:
    chip8() { std::cout << "Constructor build\n";}
    ~chip8() {}
    void init();
    void emulateCycle();
    void debugRender();
    bool loadApp(const char *filename);
protected:
    bool drawFlag;
    uint16_t opcode;          //each opcode = 2 bytes
    uint8_t memory[4096];     //each memory location = 1 byte
    uint8_t V[16];            //15 - 8-bits GP regs, V0-VE, VE: carry flag

    uint16_t I;               //12-bits   0x000-0xFFF
    uint16_t pc;              //12-bits

    /*
    0x000-0x1FF - Chip8 Interpreter (first 512 bytes) - 0x1FF = 2^8 + 2^7 + ... + 2^0 = 512
    0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
    0x200-0xFFF - Program ROM and work RAM
    */

    uint8_t gfx[64 * 32];     //64 * 32 = 2048 pixels
    uint8_t delay_timer;      //Both count at 60Hz
    uint8_t sound_timer;      //buzzer sounds whenever sound timer reaches zero

    uint8_t stack[16];
    uint8_t sp;

    uint8_t key[16];          //HEX based keypad
};

#endif