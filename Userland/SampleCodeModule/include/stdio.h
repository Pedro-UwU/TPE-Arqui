#ifndef STD_IO_H
#define STD_IO_H value

#define STD_BUFFER_SIZE 256

#include <stdarg.h>
#include <stdint.h>

char * getSTD_INAddress();
char * getSTD_OUTAddress();
void writeInStream(char stream, char * str, int size);
int readKeyboard(char * buffer, int size);
void setConsoleUpdateFunction(void (*f)(char *, int));
char getChar();
void print(char *, ...);
void putChar(char ch);
uint64_t getError();
#endif
