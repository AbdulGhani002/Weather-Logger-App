#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LENGTH 256

char *get_API_key() {
    char *api_key = (char *)malloc(MAX_KEY_LENGTH);
    if (api_key == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    memset(api_key, 0, MAX_KEY_LENGTH);

    FILE *file = fopen("config.txt", "r");
    if (file == NULL) {
        printf("Could not open config file.\n");
        free(api_key);
        return NULL;
    }

    char line[MAX_KEY_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "API_KEY=", 8) == 0) {
            strncpy(api_key, line + 8, MAX_KEY_LENGTH - 1);
            api_key[strcspn(api_key, "\n")] = 0;
            break;
        }
    }
    fclose(file);

    return api_key;
}



