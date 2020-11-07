#ifndef STD_IO
#define STD_IO

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <syscallsASM.h>
#include <charLib.h>


#include <stdGraphics.h>

void keyPressedStdIO(uint8_t keyCode);

char * std_in;
char * std_out;
static char std_io_initialized = 0;
void (*setKeyPressedPointer)(uint8_t);
uint8_t funcPointerInitialized = 0;

char lastCharReaded = 0;

void stdio_init() {
  if (!std_io_initialized) { //para no inicializarlo 2 veces
    char buffer1[STD_BUFFER_SIZE] = {0};
    char buffer2[STD_BUFFER_SIZE] = {0};
    std_in = buffer1;
    std_out = buffer2;
    std_io_initialized = 1;
  }
  setKeyPressedFunctionSyscall(keyPressedStdIO);
}

char * getSTD_INAddress() {
  return std_in;
}

char * getSTD_OUTAddress() {
  return std_out;
}

int scanf(char * fmt, ...);

int printf(char * fmt, ...);

void writeInStream(char stream, char * str, int size) {
  char * buffer;
  if (stream == 0) buffer = std_in;
  else if (stream == 1) buffer = std_out;
  else return;

  int i;
  for (i = 0; i < size && i < (STD_BUFFER_SIZE-1) && str[i] != 0; i++) {
    buffer[i] = str[i];
  }
  buffer[i] = 0;
}

int readKeyboard(char * buffer, int size) {
  if (size == 0) return 0;
  uint64_t aux;
  isKeyboardEmptySyscall(&aux);
  if (aux) {
    readKeyboardSysCall(buffer, (uint8_t) size);
    return 1;
  }
  return 0;
}

void setKeyPressedFunction(void (*f)(uint8_t)) {
  setKeyPressedPointer = f;
  funcPointerInitialized = 1;
}

void keyPressedStdIO(uint8_t keyCode) {
  char c = getAsciiFromKeyCode(keyCode);
  if (c != 0) {
    lastCharReaded = c;
  }
  if (funcPointerInitialized)
    setKeyPressedPointer(keyCode);
}

char getChar() {
  lastCharReaded = 0; //Borro lo que tenia antes
  while(lastCharReaded == 0) {};
  return lastCharReaded;
}


#endif
