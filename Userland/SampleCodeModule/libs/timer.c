#include <syscallsASM.h>
#include <timer.h>
#include <stdlib.h>

int readSeconds(){
  uint8_t ans;
  getTimeSyscall(0,&ans);
  return ans;
}

int readMinutes(){
  uint8_t ans;
  getTimeSyscall(1,&ans);
  return ans;
}

int readHours(){
  uint8_t ans;
  getTimeSyscall(2,&ans);
  return ans-3;
}

int readDays(){
  uint8_t ans;
  getTimeSyscall(3,&ans);
  return ans;
}

int readMonths(){
  uint8_t ans;
  getTimeSyscall(4,&ans);
  return ans;
}

int readYear(){
  uint8_t ans;
  getTimeSyscall(5,&ans);
  return ans;
}

void formatTime(int secondsT,char *buffer){
  int seconds = secondsT%60;
  char aux[2];
  intToBase(seconds,10,aux);
  if (seconds<10){
    buffer[4] = aux[0];
    buffer[3] = '0';
  }else  {
    buffer[3] = aux[0];
    buffer[4] = aux[1];
  }
  buffer[2] = ':';
  int minutes = secondsT/60;
  int len = intToBase(minutes,10,aux);
  if (len==0){
    buffer[0]=buffer[1]='0';
  }
  if (len==1)
  {
    buffer[0]='0';
  } else
  {
    buffer[0]=aux[0];
    buffer[1]=aux[1];
  }
}