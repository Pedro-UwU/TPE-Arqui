#ifndef SYSCALLS
#define SYSCALLS
#include <stdint.h>
#include <regi.h>
#include <keyboard_driver.h>
#include <video_driver.h>
#include <timer_driver.h>
#include <date_driver.h>

void writeStr(registerStruct * registers);
void getTimeInfo(uint8_t mode, uint8_t * target);

void syscallHandler(registerStruct * registers) {
  uint64_t option = registers->rax;
  switch(option) {
    //READ KEYBOARD
    case 0:
    //rsi -> puntero a buffer
    //rdx -> uint8_t size
    readKeyboard((char *)registers->rsi, (uint8_t) registers->rdx);
    break;

    //WRITE STR
    case 1:
    //rsi -> puntero a buffer
    //rdx -> size
    //rbx -> x
    //rcx -> y
    //r8 -> fontColor
    //r9 -> backgroundColor
    //r10 -> fontSize
    writeStr(registers);
    break;



    //
    //case 1: writeSTR
    //case 2: getDate
    //case 3: DRAW
    //case 4: getMillis (?)


    case 8:
    //rdi -> mode
    //rsi -> puntero a entero
    getDateInfo((uint8_t) registers->rdi, (uint8_t *) registers->rsi);
    break
  }
}

void getTimeInfo(uint8_t mode, uint8_t * target) {
  switch(mode) {
    case 0: *target = getSeconds();
    break;
    case 1: *target = getMinutes();
    break;
    case 2: *target = getHours();
    break;
    case 3: *target = getDay();
    break;
    case 4: *target = getMonth();
    break;
    case 5: *target = getYear();
    break
  }
}

void writeStr(registerStruct * registers) {
  clear_display(0xFF0000 + (getTicks() %123));
  uint64_t xOffset = 0;
  char * buffer = (char *)registers->rsi;
  for (uint64_t i = 0; i < registers->rdx && buffer[i] != 0; i++) {
    char ch = ((char *)registers->rsi)[i];
    drawChar(registers->rbx + xOffset, registers->rcx, ch, registers->r10, registers->r8, registers->r9);
    xOffset += getCharWidth() * registers->r10;
  }
}

#endif
