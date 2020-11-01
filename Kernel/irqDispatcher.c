#ifndef IRQ_DISPATCHER
#define IRQ_DISPATCHER

#include <naiveConsole.h>
#include <keyboard_driver.h>
#include <video_driver.h>
#include <timer_driver.h>
#include <regi.h>
#include <syscalls.h>
#include <test.h>

static void int_21h(registerStruct *);
static void int_80h(registerStruct *);
static void int_20h();

void irqDispatcher(uint64_t irq, uint64_t * registers) {
  switch (irq) {
    case 0: int_20h();
    break;
    case 1: int_21h((registerStruct *)registers);
    break;
    case 80: int_80h((registerStruct *)registers);
    break;
  }
}

static void int_20h() {
  timeHandler();
}

static void intToStr(uint64_t num, uint64_t strDim, char * str) {
  if (num == 0) {
    str[0] = '0';
    str[1] = 0;
    return;
  }
  int index = 0;
  while (num > 0) {
    int rem = num % 10;
    for (int i = index; i > 0; i--) {
      str[i] = str[i-1];
    }
    str[0] = rem + '0';
    num/=10;
    index++;
  }
  str[index] = 0;
}

//Funcion temporal para ver los registros;
static void printRegisters(registerStruct * registers) {
  uint64_t x = 0;
  uint64_t y = 0;

  char buffer[128] = {0};

  drawString(x, y, "RAX ", 1, 0xFFFFFF, 0);
  intToStr(registers->rax, 128, buffer);
  drawString(x + getCharWidth() * 4, y, buffer, 1, 0xFFFFFF, 0);
  y += getCharHeight();

  drawString(x, y, "RBX ", 1, 0xFFFFFF, 0);
  intToStr(registers->rbx, 128, buffer);
  drawString(x + getCharWidth() * 4, y, buffer, 1, 0xFFFFFF, 0);
  y += getCharHeight();

  drawString(x, y, "RCX ", 1, 0xFFFFFF, 0);
  intToStr(registers->rcx, 128, buffer);
  drawString(x + getCharWidth() * 4, y, buffer, 1, 0xFFFFFF, 0);
  y += getCharHeight();

  drawString(x, y, "RDX ", 1, 0xFFFFFF, 0);
  intToStr(registers->rdx, 128, buffer);
  drawString(x + getCharWidth() * 4, y, buffer, 1, 0xFFFFFF, 0);
  y += getCharHeight();

  drawString(x, y, "RBP ", 1, 0xFFFFFF, 0);
  intToStr(registers->rbp, 128, buffer);
  drawString(x + getCharWidth() * 4, y, buffer, 1, 0xFFFFFF, 0);
  y += getCharHeight();

  drawString(x, y, "RSP ", 1, 0xFFFFFF, 0);
  intToStr(registers->rsp, 128, buffer);
  drawString(x + getCharWidth() * 4, y, buffer, 1, 0xFFFFFF, 0);
  y += getCharHeight();

  drawString(x, y, "RDI ", 1, 0xFFFFFF, 0);
  intToStr(registers->rdi, 128, buffer);
  drawString(x + getCharWidth() * 4, y, buffer, 1, 0xFFFFFF, 0);
  y += getCharHeight();

  drawString(x, y, "RIP ", 1, 0xFFFFFF, 0);
  intToStr(registers->rip, 128, buffer);
  drawString(x + getCharWidth() * 4, y, buffer, 1, 0xFFFFFF, 0);
  y += getCharHeight();

  drawString(x, y, "R15 ", 1, 0xFFFFFF, 0);
  intToStr(registers->r15, 128, buffer);
  drawString(x + getCharWidth() * 4, y, buffer, 1, 0xFFFFFF, 0);
  y += getCharHeight();

  drawString(x, y, "RSI ", 1, 0xFFFFFF, 0);
  intToStr(registers->rsi, 128, buffer);
  drawString(x + getCharWidth() * 4, y, buffer, 1, 0xFFFFFF, 0);
  y += getCharHeight();
}


static void int_21h(registerStruct * registers) {
  keyboardHandler(registers);
  uint8_t keyCode = getKeyCode();

  if (keyCode == 30) {
    registerStruct * reg = getRegisters();
    printRegisters(reg);
  }
  // uint8_t keyCode = getKeyCode();
  // char buffer[5];
  // intToStr(keyCode, 5, buffer);
  // drawString(0, 0, buffer, 3, 0xFFFFFF, 0);

};

static void int_80h(registerStruct * registers) {
  syscallHandler(registers);
}



#endif
