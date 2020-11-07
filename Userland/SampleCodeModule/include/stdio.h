#ifndef STD_IO_H
#define STD_IO_H value

#define STD_BUFFER_SIZE 256

#include <stdarg.h>
#include <stdint.h>

void stdio_init();
char * getSTD_INAddress();
char * getSTD_OUTAddress();
void scan(char *);
int scanf(char * fmt, ...);
int printf(char * fmt, ...);
void writeInStream(char stream, char * str, int size);
int readKeyboard(char * buffer, int size);
void setKeyPressedFunction(void (*)(uint8_t));
char getChar();
#endif
