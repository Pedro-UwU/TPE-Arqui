#include <stdio.h>
#include <commands.h>
#include <stdlib.h>
#include <stdGraphics.h>
#include <timer.h>
#include <inforeg.h>
#include <Shell.h>
#include <stdint.h>

void test(){
  print("TEST\n");
}

void inforeg(){
  clearScreen(0);
  uint64_t registers[17];
  inforegs(registers);
  int movey=0;
  for (int i = 0; i < 17; i++){
    char num[10];
    int len = intToString(registers[i],num);
    drawString(0,movey,num, len, 0xffffff,0,1,0);
    movey+=BASE_CHAR_HEIGHT;
  }

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
