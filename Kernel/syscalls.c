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
  }



}

#endif
