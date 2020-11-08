#ifndef EXC_DISPATCHER
#define EXC_DISPATCHER

#include <regi.h>
#include <interrupts.h>
#include <video_driver.h>

void exc_0h(registerStruct * registers);
void exc_6h(registerStruct * registers);

void exceptionDispatcher(uint64_t exc, registerStruct * registers) {
  switch(exc) {
    case 0: exc_0h(registers);
    break;
    case 6: exc_6h(registers);
    break;
  }
}

void exc_0h(registerStruct * registers) {
  drawRectangle(100, 150, 100, 100, 0xF3D441);
}

void exc_6h(registerStruct * registers) {

}

#endif
