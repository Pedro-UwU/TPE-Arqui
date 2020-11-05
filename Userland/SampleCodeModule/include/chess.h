#ifndef CHESS_H
#define CHESS_H

#include <stdGraphics.h>
#include <stdint.h>
#include <syscallsASM.h>
#include <stdlib.h>
#include <stdio.h>

void drawBoard();

#define SQUAREDIM 64
#define SQUARES 8 
#define BOARDDIM SQUAREDIM * SQUARES

#define KING 0
#define QUEEN 1
#define BISHOP 2
#define KNIGHT 3
#define ROOK 4
#define PAWN 5
#define EMPTY 6

#define PIECES_SIZE 8
#define PIECES_AMOUNT 6

#define BACKGROUND 0xC0C0C0

#define CONSOLE_LIMIT_X SCREEN_WIDTH/2+BOARDDIM/2+SQUAREDIM/2
#define CONSOLE_LIMIT_Y SQUAREDIM
#define CONSOLE_SIZE_Y BOARDDIM
#define CONSOLE_SIZE_X SQUAREDIM*3
#define TOTAL_LINES_CHESS 30
#define MAX_LENGTH 16


#endif