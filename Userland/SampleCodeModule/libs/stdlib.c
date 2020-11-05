#ifndef STD_LIB_C
#define STD_LIB_C value
#include <stdlib.h>

int atoi(char * str);
// double strToDouble(char * str);
int intToString(unsigned long long num, char * buffer);
int strlen(char *str);
int strcmp(char * str1, char * str2);
int intToBase(unsigned long long num, int base, char*buffer);

int atoi(char * str){
  int aux = 0;
  while (*str!=0){
    aux = aux*10 + (*str)+'0';
    str++;
  }
  return aux;
}

// char* itoa(int num, char* str, int base){ 
//     int i = 0; 
//     int isNegative = 0; 
  
//     /* Handle 0 explicitely, otherwise empty string is printed for 0 */
//     if (num == 0) 
//     { 
//         str[i++] = '0'; 
//         str[i] = '\0'; 
//         return str; 
//     } 
  
//     // In standard itoa(), negative numbers are handled only with  
//     // base 10. Otherwise numbers are considered unsigned. 
//     if (num < 0 && base == 10) 
//     { 
//         isNegative = 1; 
//         num = -num; 
//     } 
  
//     // Process individual digits 
//     while (num != 0) 
//     { 
//         int rem = num % base; 
//         str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
//         num = num/base; 
//     } 
  
//     // If number is negative, append '-' 
//     if (isNegative) 
//         str[i++] = '-'; 
  
//     str[i] = '\0'; // Append string terminator 
  
//     // Reverse the string 
//     for (int j = 0; j < i/2; j++){
//         int aux = str[j];
//         str[j] = str[i-j-1];
//         str[i-j-1]=aux;
//     }  
//     return str; 
// }
int intToBase(unsigned long long num, int base, char*buffer){
    char stack[11];
    int c = 0;
    int i=0;
    int remainder = 0;
    if(num==0) stack[i++]='0';
    while(num!=0){
        remainder = num % base;
        stack[i]=remainder>=10? remainder+'A'-10:remainder+'0';
        num = num/base;
        i++;
    }
    c=i;
    i--;
    while(i>=0){
        *buffer=stack[i];
        buffer++;
        i--;
    }
    *buffer=0;
    return c;
}
/*
double strToDouble(char * str){
  double aux = 0;
  while (*str!=','){
    aux = aux*10 + (*str)+'0';
  }
  int i =0;
  while (*str!=0){
    aux = aux*10+(*str)+'0';
    i++;
    str++;
  }
  aux/=(double) 10 * i;
  return aux;
}
*/

int intToString(unsigned long long num, char * buffer){
  return intToBase(num,10,buffer);
}

int strlen(char *str){
  int i =0;
  for ( i = 0; *(str+i); i++)
  {
    
  }
  return i;
}

int strcmp(char * str1, char * str2){
    int i =0;
    while(str1[i] != 0 && str2[i] != 0 ){
        if(str1[i] != str2[i]){
            return str1[i]-str2[i];
        }
        i++;
    }
    return str1[i]-str2[i];
}

#endif
