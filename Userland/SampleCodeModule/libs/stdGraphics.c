#ifndef STD_GRAPHICS
#define STD_GRAPHICS
#include <syscallsASM.h>
#include <stdint.h>

//NOTA: Hay un bug en el case en el que x = 0, no se porque no lo dibuja
//TODO: Arreglar eso

void drawString(int x, int y, char * buffer, int dim, int fontColor, int backgroundColor, int fontSize, int alphaBackground) {
    drawStringSysCall(buffer, (uint64_t)dim, (uint64_t)x, (uint64_t)y, (uint64_t)fontColor, (uint64_t)backgroundColor, (uint64_t)fontSize, (uint64_t)alphaBackground);
    //drawStringSysCall("ASD", 4, 0, 0, 0xFFFFFF, 0xFF0000, 2, 0);
}

void clearScreen(uint64_t color) {
  clearDisplaySyscall(color);
}
#endif
