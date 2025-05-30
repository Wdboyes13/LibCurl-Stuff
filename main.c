#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "glob.h"

void* key_checker(void* arg) {
    int c;
    while (1) {
        c = getchar();
        if (c == 7) {
            gnumode();
        }
    }
}

int main(){
    // pthread_t key_thread;
    // pthread_create(&key_thread, NULL, key_checker, NULL);
    struct furl input;
    get_furl_input(&input);

    printf("URL: %s\n", input.url);
    printf("Filename: %s\n", input.filename);

    if (strlen(input.url) == 0 || strcmp(input.url, " ") == 0) {
        strcpy(input.url, "default-downloaded");
    }

    dl(input.url, input.filename);

    free((void*)input.url);
    free((void*)input.filename);
    return 0;
}