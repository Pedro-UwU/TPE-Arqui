#ifndef IO_DRIVER_H
#define IO_DRIVER_H
#include <stdint.h>
#include <regi.h>

registerStruct * getRegisters();
void get32bytesFromAddress(uint64_t address, uint8_t * target, uint8_t totalBytes);
#endif
