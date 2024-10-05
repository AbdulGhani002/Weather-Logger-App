#ifndef GET_CONSOLE_H
#define GET_CONSOLE_H

#include <sys/ioctl.h>
#include <unistd.h>

struct winsize get_console_details(void);
int get_console_size(void);

#endif // GET_CONSOLE_H
