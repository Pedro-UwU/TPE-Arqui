#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#define CTRL_L 29
#define SHIFT_L 42
#define SHIFT_R 54
#define ALT_L 56
#define BLOCK_M 58

#define KEY_RELEASED 128
#define KEYS 59

#include <regi.h>

void keyboardHandler(registerStruct *);
uint8_t readKeyboard(char * buff, uint8_t size);

#endif
