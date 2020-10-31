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
  // if (irq == 1) {
  //   for (int i = 0; i < 15; i++) {
  //     //ncPrintHex(registers[i]);
  //     ncPrintChar('-');
  //   }
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
  uint64_t ticks = getTicks();
  if (ticks % 20 == 0) {
    testeo();
  }
}

static void int_21h(registerStruct * registers) {
  keyboardHandler(registers);
  //char buffer[1] = {0};
  //uint8_t readed = readKeyboard(buffer, 1);
  // if (readed) {
  //   //clear_display(0x000000);
  //   drawChar(0, 0, buffer[0], 2, 0xFFFFFF, 0x515151);
  // }
};

static void int_80h(registerStruct * registers) {
  syscallHandler(registers);
}


#endif
