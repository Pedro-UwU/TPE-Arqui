#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H
#include <stdint.h>

void clear_display(uint64_t color);
void drawSquare(uint64_t x, uint64_t y, uint64_t size, uint64_t color);
void drawLine(int xi,int yi,int xf,int yf,uint64_t color);
void drawMatrix(uint64_t x, uint64_t y, uint64_t *mat, uint64_t height, uint64_t width,uint64_t size);
void drawChar(uint64_t x, uint64_t y, uint8_t character, uint64_t fontSize, uint64_t fontColor, uint64_t backgroundColor);
void drawString(int x,int  y, char *string ,int fontSize,int fontColor, int backgroundColor);
void drawPixel(uint64_t x, uint64_t y, uint64_t color );
uint64_t getCharWidth();
uint64_t getCharHeight();

#endif
