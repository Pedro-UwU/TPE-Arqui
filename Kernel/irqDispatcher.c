#ifndef IRQ_DISPATCHER
#define IRQ_DISPATCHER

#include <naiveConsole.h>
#include <keyboard_driver.h>
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
};


#endif
