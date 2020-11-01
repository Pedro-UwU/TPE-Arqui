#ifndef KEYBOARD_DRIVER
#define KEYBOARD_DRIVER
#include <keyboard_asm.h>
#include <keyboard_driver.h>
#include <naiveConsole.h>
#include <regi.h>
#include <stdint.h>
#define BUFFER_SIZE 32


static void saveRegisters(registerStruct * registers);

static registerStruct registerSnapshot;
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
    saveRegisters(registers);
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

static void saveRegisters(registerStruct * registers) {
  registerSnapshot.r15 = registers->r15;
  registerSnapshot.r14 = registers->r14;
  registerSnapshot.r13 = registers->r13;
  registerSnapshot.r12 = registers->r12;
  registerSnapshot.r11 = registers->r11;
  registerSnapshot.r10 = registers->r10;
  registerSnapshot.r9 = registers->r9;
  registerSnapshot.r8 = registers->r8;
  registerSnapshot.rsi = registers->rsi;
  registerSnapshot.rdi = registers->rdi;
  registerSnapshot.rbp = registers->rbp;
  registerSnapshot.rdx = registers->rdx;
  registerSnapshot.rcx = registers->rcx;
  registerSnapshot.rbx = registers->rbx;
  registerSnapshot.rax = registers->rax;
  registerSnapshot.rsp = registers->rsp;
  registerSnapshot.rip = registers->rip;
}

registerStruct * getRegisters() {
  return &registerSnapshot;
}
#endif
