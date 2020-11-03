#ifndef STD_GRAPHICS_H
#define STD_GRAPHICS_H
#include <stdint.h>

void drawString(int x, int y, char * buffer, int dim, int fontColor, int backgroundColor, int fontSize, int alphaBackground);
void clearScreen(uint64_t color);
#endif
