#include <stdio.h>
#include <commands.h>
#include <stdlib.h>
#include <stdGraphics.h>
#include <timer.h>
#include <inforeg.h>
#include <Shell.h>
#include <stdint.h>

void test(char ** args){
  putChar('\n');
  print("Hola %x", 15);
}


void inforeg(char ** args){
  clearScreen(0);
  uint64_t registers[19];
  getRegisters(registers);
  putChar('\n');
  print("R15: %X - R14: %X\n", registers[18], registers[17]);
  print("R13: %X - R12: %X\n", registers[16], registers[15]);
  print("R11: %X - R10: %X\n", registers[14], registers[13]);
  print("R9: %X - R8: %X\n", registers[12], registers[11]);
  print("RSI: %X - RDI: %X\n", registers[10], registers[9]);
  print("RBP: %X - RDX: %X\n", registers[8], registers[7]);
  print("RCX: %X - RBX: %X\n", registers[6], registers[5]);
  print("RAX: %X - RIP: %X\n", registers[4], registers[3]);
  print("CS: %X - FLAGS: %X\n", registers[2], registers[1]);
  print("RSP: %X\n", registers[0]);

// void printmem(char ** args) {
//
// }




  int movey=0;
  for (int i = 0; i < 17; i++){
    char num[10];
    int len = intToString(registers[i],num);
    drawString(0,movey,num, len, 0xffffff,0,1,0);
    movey+=BASE_CHAR_HEIGHT;
  }

}

void time(char ** args) {
  putChar('\n');
  print("%d:%d:%d %d/%d/%d", readHours(), readMinutes(), readSeconds(), readDays(), readMonths(), readYear());
}

void timer(){
    char num[10]={0};
    int movex=SCREEN_WIDTH-BASE_CHAR_WIDTH*18;
    int len = intToString(readDays(),num);
    drawString(movex,0,num,len,0xffff00,0,1,0);
    movex+=BASE_CHAR_WIDTH*2;
    drawString(movex,0,"/",1,0xffff00,0,1,0);
    movex+=BASE_CHAR_WIDTH;
    len = intToString(readMonths(),num);
    drawString(movex,0,num,len,0xffff00,0,1,0);
    movex+=BASE_CHAR_WIDTH*2;
    drawString(movex,0,"/",1,0xffff00,0,1,0);
    movex+=BASE_CHAR_WIDTH;
    len = intToString(readYear(),num);
    drawString(movex,0,num,len,0xffff00,0,1,0);
    movex+=BASE_CHAR_WIDTH*3;
    drawString(movex,0," ",1,0xffff00,0,1,0);
    len = intToString(readHours(),num);
    drawString(movex,0,num,len,0xffff00,0,1,0);
    movex+=BASE_CHAR_WIDTH*2;
    drawString(movex,0,":",1,0xffff00,0,1,0);
    len = intToString(readMinutes(),num);
    movex+=BASE_CHAR_WIDTH;
    drawString(movex,0,num,len,0xffff00,0,1,0);
    movex+=BASE_CHAR_WIDTH*2;
    drawString(movex,0,":",1,0xffff00,0,1,0);
    int seconds = readSeconds();
    len = intToString(seconds,num);
    movex+=BASE_CHAR_WIDTH;
    if (seconds<10){
      drawString(movex,0,"0",len,0xffff00,0,1,0);
      movex+=BASE_CHAR_WIDTH;
    }
    drawString(movex,0,num,len,0xffff00,0,1,0);
}
