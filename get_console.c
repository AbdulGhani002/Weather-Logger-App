#include "get_console.h"
#include <stdio.h>

struct winsize get_console_details(void) {
  struct winsize console_details;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &console_details) == -1) {
    perror("Unable to know the console screen details");
    console_details.ws_col = 0;
    console_details.ws_row = 0;
  }
  return console_details;
}

int get_console_size(void) {
  struct winsize console_details = get_console_details();
  if (console_details.ws_col == 0) {
    return -1;
  }
  return console_details.ws_col;
}
