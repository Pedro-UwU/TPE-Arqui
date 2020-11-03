#ifndef  SHELL_H
#define SHELL_H
#include <stdint.h>

void init_shell();
static void readKey();
static void writeToLines(char * buff, int dim);
static void addLine();
static void drawShellLines();
static void clearShellLine(uint8_t line);
static void drawBottomLine();
static void clearScreenLine(uint8_t line);
static void exeCommand(int i);
static int isCommand();

#endif