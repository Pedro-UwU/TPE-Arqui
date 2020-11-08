#ifndef STD_IO
#define STD_IO

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <syscallsASM.h>
#include <charLib.h>
#include <stdlib.h>

#include <stdGraphics.h>

void keyPressedStdIO(uint8_t keyCode);

char * std_in;
char * std_out;
static char std_io_initialized = 0;
void (*setKeyPressedPointer)(uint8_t);
uint8_t funcPointerInitialized = 0;

void (*updateConsolePointer)(char *, int);
uint8_t updateConsoleInitialized = 0;



static char lastCharReaded;

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

void scan(char * buff) {
  int ch = 0;
  int index = 0;
  while (ch != '\n') {
    if (ch)
      buff[index++] = ch;
      putChar(ch);
    ch = getChar();
  }
  putChar('\n');
}

void print(char * str, ...) {
  // for (int i = 0; buff[i] != 0; i++) {
  //   putChar(buff[i]);
  // }
  va_list vl;
  va_start(vl, str);
  char * auxPtr;
  char buffer[128] = {0};
  char tmp[20];
  int i = 0, j = 0;
  while (str && str[i]) {
    if (str[i] == '%') {
      i++;
      switch(str[i]) {
        case 'c':
        buffer[j++] = (char)va_arg( vl, int );
        break;
        case 'd':
        intToString(va_arg( vl, int ), tmp);
        strcpy(&buffer[j], tmp);
        j+=strlen(tmp);
        break;
        case 's':
        auxPtr = va_arg(vl, char*);
        strcpy(&buffer[j],auxPtr);
        j+=strlen(auxPtr);
        break;
        case 'x':
        intToBase(va_arg( vl, int ),16, tmp);
        strcpy(&buffer[j], tmp);
        j+=strlen(tmp);
      }
    } else {
      buffer[j++] = str[i];
    }
    i++;
  }
  updateConsolePointer(buffer, j);
}

void putChar(char ch) {
  updateConsolePointer(&ch, 1);
}

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
  uint64_t count = 0;
  if (aux) {
    readKeyboardSysCall(buffer, (uint8_t) size, &count);
    return 1;
  }
  return 0;
}

void setKeyPressedFunction(void (*f)(uint8_t)) {
  setKeyPressedPointer = f;
  funcPointerInitialized = 1;
}

void setConsoleUpdateFunction(void (*f)(char *, int)) {
  updateConsolePointer = f;
  updateConsoleInitialized = 1;
}




void keyPressedStdIO(uint8_t keyCode) {
  char c = getAsciiFromKeyCode(keyCode);
  if (c) {
    lastCharReaded = c;
  }
  if (funcPointerInitialized) {}
    setKeyPressedPointer(keyCode);
}

char getChar() {
  char ch = 0;
  uint64_t count;
  while(ch == 0 || count == 0) {
    readKeyboardSysCall(&ch, 1, &count);
  }
  return ch;
}


#endif
