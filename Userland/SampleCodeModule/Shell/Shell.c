#ifndef SHELL
#define SHELL

#define TOTAL_LINES 63
#define MAX_LINE_LENGTH 129

#include <stdGraphics.h>
#include <stdio.h>
#include <stdint.h>
#include <colors.h>
#include <commands.h>
#include <Shell.h>
#include <stdlib.h>
#include <chess.h>
#include <timer.h>
#include <charLib.h>

static char finished = 0;
static char * stdIn;
static char * stdOut;


static char lines[TOTAL_LINES][MAX_LINE_LENGTH] = {{0}};// = {0};
static uint8_t lineCursor = 0;
static uint8_t currentLineNumber = 0;

static void readKey();
static void addLine();
static void drawShellLines();
static void clearShellLine(uint8_t line);
static void drawBottomLine();
static void clearScreenLine(uint8_t line);
static void exeCommand(int i);
static int isCommand();
void updateShell(char * buff, int dim);

char commandsNames[5][10]={"time","test","inforeg","chess"};
void  (* run[])(int,char * * ) = {time,test,inforeg,chess};

void init_shell() {
  stdIn = getSTD_INAddress();
  stdOut = getSTD_OUTAddress();
  //setKeyPressedFunction(keyPressedShell);
  setConsoleUpdateFunction(updateShell);
  //readKey();
  drawShellLines();
  //
  // while(!finished) {
  //
  // }
}

static void readKey() {
  uint8_t bufferLength = 5;
  char buffer[bufferLength];
  for (int i = 0; i < bufferLength; i++){
    buffer[i] = 0;
  }
  if (readKeyboard(buffer, bufferLength)) {
    writeToLines(buffer, bufferLength);
  }
}

void writeToLines(char * buff, int dim) {
  for (int i = 0; i < dim && buff[i] != 0 && i < MAX_LINE_LENGTH; i++) {
    if (buff[i] == '\n' || lineCursor == (MAX_LINE_LENGTH - 1)) { //El -1 es para que el ultimo elemento sea un 0
      addLine();

    } else if (buff[i] == '\b') {
      if (lineCursor > 0) {
        lines[currentLineNumber%(TOTAL_LINES-1)][lineCursor-1] = lines[currentLineNumber%(TOTAL_LINES-1)][lineCursor];
        lineCursor-=lineCursor==0?0:1; //TODO: checkear por que el lineCursor-- se va negativo aunque no deberia entrar al if
      }
    } else {
      lines[currentLineNumber%(TOTAL_LINES-1)][lineCursor] = buff[i];
      lineCursor++;
    }
  }
  drawBottomLine();
}

static void addLine() {
  currentLineNumber++;
  clearShellLine(currentLineNumber);
  lineCursor=0;
  drawShellLines();
}

static void drawShellLines() {
  clearScreen(BLACK);
  int y = SCREEN_HEIGHT;
  int x = 0;
  for (int i = 0; i >= -TOTAL_LINES && i >= -currentLineNumber; i--) {
    y-=BASE_CHAR_HEIGHT;
    if (lines[(i+currentLineNumber)%(TOTAL_LINES-1)][0] == '0') continue;
    if (i == 0) {
      drawString(0, y, "> ", 3, LIGHT_GRAY, BLACK, 1, 0);
      x += BASE_CHAR_WIDTH*2;
    } else {
      x = 0;
    }
    drawString(x, y, lines[(i+currentLineNumber)%(TOTAL_LINES-1)], MAX_LINE_LENGTH-1, LIGHT_GRAY, BLACK, 1, 0);
  }
}

static void clearShellLine(uint8_t line) {
  for (int i = 0; i < MAX_LINE_LENGTH; i++) {
    lines[line%(TOTAL_LINES-1)][i] = 0;
  }
}

static void drawBottomLine() {
  clearScreenLine(0);
  drawString(0, SCREEN_HEIGHT-BASE_CHAR_HEIGHT, "> ", 3, LIGHT_GRAY, BLACK, 1, 0);
  drawString(BASE_CHAR_WIDTH*2, SCREEN_HEIGHT-BASE_CHAR_HEIGHT, lines[(currentLineNumber)%(TOTAL_LINES-1)], MAX_LINE_LENGTH-1, LIGHT_GRAY, BLACK, 1, 0);
}

static void clearScreenLine(uint8_t line){
  drawRect(0,SCREEN_HEIGHT-BASE_CHAR_HEIGHT*(line+1),SCREEN_WIDTH,BASE_CHAR_HEIGHT, BLACK);
}

//ejecutaria los commands
static void exeCommand(int i){
  run[i](0,0);

}

//devuelve que comando es si no esta  devuelve -1
static int isCommand(){
  for (int i = 0; i < 5; i++) {
    if (!strcmp(commandsNames[i],lines[(currentLineNumber)%(TOTAL_LINES-1)]) && lines[(currentLineNumber)%(TOTAL_LINES-1)][0]){
      return i;
    }
  }
  return -1;
}

void keyPressedShell(char ch) {
  if (ch) {
    if (ch == '\n') {
      int i = isCommand();
      if (i>=0) {
        exeCommand(i);
        drawShellLines();
      }
      else{
        print(" - INVALID COMMAND");
      }
    }
    putChar(ch);
  }
}

void updateShell(char * buff, int dim) {
  writeToLines(buff, dim);
}

#endif
