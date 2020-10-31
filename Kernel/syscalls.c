#ifndef SYSCALLS
#define SYSCALLS
#include <stdint.h>
#include <regi.h>
#include <keyboard_driver.h>
#include <video_driver.h>

void syscallHandler(registerStruct * registers) {
  uint64_t option = registers->rax;
  switch(option) {
    //READ KEYBOARD
    case 0:
    //rsi -> puntero a buffer
    //rdx -> uint8_t size
    readKeyboard((char *)registers->rsi, (uint8_t) registers->rdx);
    drawString(0, 0, (char *)registers->rsi, 2, 0xFFFFFF, 0x000000);
    //drawString(0, 0, (char *)registers->rsi, 2, 0xFFFFFF, 0x000000);
    break;
    //case 1: writeChar
    //case 2: getDate
    //case 3: DRAW
    case 3:
      switch ((uint64_t) registers->rbx) {
      case 0:
      //rsi color
        clear_display((uint64_t) registers->rsi);
        break;
      case 1:
      // r9 xi , r8 yi, r10 xf, r11 yf, rsi color
        drawLine((int) registers->r9,(int) registers->r8,(int) registers->r10,(int) registers->r11,(uint64_t) registers->rsi);
        break;
      case 2:
      // r9 xi, r8 yi, rsi color
        drawPixel((uint64_t) registers->r9,(uint64_t) registers->r8,(uint64_t) registers->rsi);
        break;
      case 3:
      // r9 xi, r8 yi , r15 size, rsi color
        drawSquare((uint64_t) registers->r9,(uint64_t) registers->r8,(uint64_t) registers->r15,(uint64_t) registers->rsi);
        break;
      case 4:
      // r9 xi, r8 yi, rdx puntero a matriz, r10 height, r11 width , rsi color
        drawMatrix((uint64_t) registers->r9,(uint64_t) registers->r8,(uint64_t) registers->rdx,(uint64_t) registers->r10,(uint64_t) registers->r11,(uint64_t) registers->rsi);
        break;
      }
    //case 4: getMillis (?)
  }



}

#endif
