#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>

void _cli();
void _sti();
void picSlaveMask(uint8_t mask);
void picMasterMask(uint8_t mask);


#endif
