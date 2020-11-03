#include <stdio.h>
#include <commands.h>
#include <stdlib.h>

int test(){
    char num[3];
    int len = intToStr(num,11);
    drawString(0,0,num,len,0x00ffff,0x000000,1,0);
}