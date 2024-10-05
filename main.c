#include <stdio.h>
#include <stdlib.h>
#include "get_console.h"
#include "main.h"
#include "data_handler.h"

void repeat_char(char to_print, int size);
void main_menu(int user_choice);

int main(void) {
    int console_size = get_console_size();
    printf("Your console is %d spaces wide.\n", console_size);
    repeat_char('=', console_size);
    main_menu(1);
    return 0;
}

void repeat_char(char to_print, int size) {
    for (int i = 0; i < size; i++) {
        printf("%c", to_print);
    }
    printf("\n");
}

void main_menu(int user_choice) {
    switch (user_choice) {
        case 1:
            show_whole_data();
            break;
        default:
            exit(1);
    }
}

