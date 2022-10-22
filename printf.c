#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void print(char character) { write(1, &character, 1); }
int print_string(char *literal) {
  int counter = 0;
  while (literal[counter] != '\0') {
    print(literal[counter]);
    counter++;
  }
  return counter;
}

char *convert(int num, int base) {

  if(num<0){
    num=num*-1;
  }
  int size = 0;
  int duplicate = num;
  while (duplicate > 0) {
    duplicate =duplicate/ base;
    size++;
  }

  char *converted = (char *)malloc(size * sizeof(char));
  char representation[] = "0123456789ABCDEF";

  size--;
  while (num > 0) {
    converted[size] = representation[num % base];
    num /= base;
    size--;
  }
  return converted;
}

char *pointer_address(unsigned long pointed) {
  unsigned long duplicate = pointed;
  int count = 0;
  while (duplicate > 0) {
    duplicate /= 16;
    count++;
  }

  char *return_address = (char *)malloc(16 * sizeof(char));
  char representation[] = "0123456789ABCDEF";
  count--;
  while (pointed > 0) {
    return_address[count] = representation[pointed % 16];
    pointed /= 16;
    count--;
  }
  return return_address;
}

int my_printf(char * restrict format, ...) {
  va_list format_print;
  va_start (format_print, format);
  int counted = 0,counter = 0, hold_int=0;
  char hold_char;
  char *hold_string;
  unsigned long hold_point;
  for (counter = 0; format[counter] != '\0'; counter++) {
    if (format[counter] == '%') {
      counter++;
      switch (format[counter]) {
      case 'd':
        hold_int = va_arg (format_print, int);
        if (hold_int == 0) {
          print('0');
          counted++;
        }else if(hold_int<0) {
          print('-');
          counted++;
          counted += print_string(convert(hold_int,10)); }
        else{counted += print_string(convert(hold_int,10));}  
         break;
      case 'u':
        hold_int = va_arg (format_print, int);
        counted +=print_string(convert(hold_int,10));
        break;
      case 'o':
        hold_int = va_arg (format_print, int);
        if(hold_int>0){
        counted +=print_string(convert(hold_int,8));}
        break;
      case 'x':
        hold_int = va_arg (format_print, int);
        if(hold_int>0){  
        counted +=print_string(convert(hold_int,16));}
        break;
      case 'c':
        hold_char = (char)va_arg (format_print, int);
        print(hold_char);
        counted++;
        break;
      case 's':
        hold_string = va_arg (format_print, char *);
        if (hold_string == (char *)NULL) {
          hold_string = "(null)";}
        counted += print_string(hold_string);
        break;
      case 'p':
        hold_point= (unsigned long)va_arg (format_print, void *);
        counted += print_string("0x");
        counted += print_string(pointer_address(hold_point));
        break;  } }  
 else {
    print(format[counter]);
    counted++;}}
va_end(format_print);

return counted;}



//   int main(){
//       int a=-10;
//       my_printf("%d",a);
//       return 0;
//   }
