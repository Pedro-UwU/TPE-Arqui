#ifndef KEYBOARD_DRIVER
#define KEYBOARD_DRIVER
#include <keyboard_asm.h>
#include <keyboard_driver.h>
#include <naiveConsole.h>
#include <regi.h>
#include <stdint.h>
#include <video_driver.h>
#define BUFFER_SIZE 32


static registerStruct regBackUp;
static uint8_t shiftL = 0, shiftR = 0;

static char pressCodes[][2] = {{0, 0}, {0, 0}, {'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'}, {'7', '&'},
{'8', '*'}, {'9', '('}, {'0', ')'}, {'-', '_'}, {'=', '+'}, {'\b', '\b'}, {'\t', '\t'}, {'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'},
{'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'}, {'\n', '\n'}, {0, 0}, {'a', 'A'},
{'s', 'S'}, {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, {'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'}, {'\'', '\"'}, {'`', '~'},
{0, 0}, {'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, {'.', '>'},
{'/', '?'}, {0, 0}, {0, 0}, {0, 0}, {' ', ' '}, {0, 0}};

static char BUFFER[BUFFER_SIZE] = {0}; //Buffer circular
static uint8_t startIndex = 0; //Indice del comienzo para el read
static uint8_t endIndex = 0; //Indice del final para el read

static void saveRegs(registerStruct * registers);

void keyboardHandler(registerStruct * registers) {
  uint8_t keyCode = getKeyCode();

  if (keyCode == SHIFT_L) {
    shiftL = 1;
  } else if (keyCode == SHIFT_R) {
    shiftR = 1;
  } else if (keyCode == (SHIFT_L + KEY_RELEASED)) {
    shiftL = 0;
  } else if (keyCode == (SHIFT_R + KEY_RELEASED)) {
    shiftR = 0;
  } else if (keyCode == F1) {
    saveRegs(registers);
  }


  else if (keyCode < KEYS) { //Si es una tecla presionada
    uint8_t mayus = (shiftL | shiftR);
    BUFFER[(endIndex++)%BUFFER_SIZE] = pressCodes[keyCode][mayus];
  }

}


uint8_t readKeyboard(char * buff, uint8_t size) {
  int i;
  for (i = 0; (startIndex + i) < endIndex && i < size; i++) {
    buff[i] = BUFFER[(startIndex + i)%BUFFER_SIZE];
    startIndex++;
  }
  return i;
}

static void saveRegs(registerStruct * registers) {
  regBackUp.r15 = registers->r15;
  regBackUp.r14 = registers->r14;
  regBackUp.r13 = registers->r13;
  regBackUp.r12 = registers->r12;
  regBackUp.r11 = registers->r11;
  regBackUp.r10 = registers->r10;
  regBackUp.r9 = registers->r9;
  regBackUp.r8 = registers->r8;
  regBackUp.rsi = registers->rsi;
  regBackUp.rdi = registers->rdi;
  regBackUp.rbp = registers->rbp;
  regBackUp.rdx = registers->rdx;
  regBackUp.rcx = registers->rcx;
  regBackUp.rbx = registers->rbx;
  regBackUp.rax = registers->rax;
  regBackUp.rsp = registers->rsp;
  regBackUp.rip = registers->rip;
}

registerStruct * getRegisters() {
  return &regBackUp;
}


#endif
