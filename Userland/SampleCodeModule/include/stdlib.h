#ifndef STDLIB_H
#define STDLIB_H

int atoi(char * str);
double strToDouble(char * str);
int intToStr(char *str, int num);
int strlen(char *str);
int strcmp(char * str1, char * str2);
int intToBase(unsigned long long num, int base, char*buffer);

#endif