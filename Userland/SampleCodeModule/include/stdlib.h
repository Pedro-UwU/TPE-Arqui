#ifndef STDLIB_H
#define STDLIB_H

int atoi(char * str);
// double strToDouble(char * str);
int intToString(unsigned long long num, char * buffer);
int strlen(char *str);
int strcmp(char * str1, char * str2);
int intToBase(unsigned long long num, int base, char*buffer);

#endif