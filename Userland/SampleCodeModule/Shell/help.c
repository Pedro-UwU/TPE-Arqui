#include <help.h>
#include <stdGraphics.h>
void help(int argc, char * args[]){
    clearScreen(0x000000);
    drawString(0,0,
        "available commands: \n"
        "    help \n"
        "    inforeg \n"
        "    cpuid \n"
        "    printmem \n"
        "    divisionbyzero \n"
        "    invalidopcode \n"
        "    localtime \n"
        "for more information you can use google \n"
    ,100,0xff0000,0x000000,2,0);
}