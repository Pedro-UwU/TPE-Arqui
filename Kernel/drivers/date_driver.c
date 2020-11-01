#ifndef DATE_DRIVER
#define DATE_DRIVER
#include <date_asm.h>
#include <date_driver.h>
#include <stdint.h>

int getSeconds() {
  return getTimeInfo(0);
}

int getMinutes() {
  return getTimeInfo(2);
}

int getHours() {
  return getTimeInfo(4);
}

int getDay() {
  return getTimeInfo(7);
}

int getMonth() {
  return getTimeInfo(8);
}

int getYear() {
  return getTimeInfo(9);
}



#endif
