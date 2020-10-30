#ifndef IRQ_DISPATCHER
#define IRQ_DISPATCHER

#include <naiveConsole.h>
#include <keyboard_driver.h>
#include <video_driver.h>
#include <timer_driver.h>
#include <regi.h>

static void int_21h(registerStruct *);

void irqDispatcher(uint64_t irq, uint64_t * registers) {
  // if (irq == 1) {
  //   for (int i = 0; i < 15; i++) {
  //     //ncPrintHex(registers[i]);
  //     ncPrintChar('-');
  //   }
  switch (irq) {
    case 0: timeHandler();
    break;
    case 1: int_21h((registerStruct *)registers);
    break;
  }
}

static void int_21h(registerStruct * registers) {
  keyboardHandler(registers);
  char buffer[1] = {0};
  uint8_t readed = readKeyboard(buffer, 1);
  if (readed) {
    clear_display(0x000000);
    drawChar(0, 0, buffer[0], 2, 0xFFFFFF, 0x515151);
  }
};


#endif
