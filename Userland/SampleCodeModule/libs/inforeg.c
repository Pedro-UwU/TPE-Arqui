#include <inforeg.h>
#include <stdint.h>
#include <syscallsASM.h>

void inforegs(uint64_t * registers){
    getRegisters(registers);
}