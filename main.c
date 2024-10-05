#include <stdio.h>
#include "get_console.h"


void repeat_char(char,int);
int main(void) {
  int console_size = get_console_size();
  printf("Your console is %d spaces wide.\n" , console_size);
  repeat_char('=' , console_size);
  return 0;
}


void repeat_char(char to_print,int size){
  for(int i=0;i<size;i++){
    printf("%c" , to_print);
  }
  printf("\n");
}
