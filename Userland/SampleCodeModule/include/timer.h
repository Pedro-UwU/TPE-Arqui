#ifndef  TIMER_H
#define TIMER_H

#include <stdint.h>

int readSeconds();
int readMinutes();
int readHours();
int readDays();
int readMonths();
int readYear();
void formatTime(int secondsT,char *buffer);
int secondsTic();

#endif