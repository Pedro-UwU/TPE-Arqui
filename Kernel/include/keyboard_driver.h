#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#define CTRL_L 29
#define SHIFT_L 42
#define SHIFT_R 54
#define ALT_L 56
#define BLOCK_M 58

#define KEY_RELEASED 128

#include <regi.h>

void keyboardHandler(registerStruct *);

#endif
