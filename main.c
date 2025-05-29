#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "glob.h"

int main(){
    struct furl input;
    get_furl_input(&input);

    printf("URL: %s\n", input.url);
    printf("Filename: %s\n", input.filename);

    if (input.url == NULL || strcmp(input.url, "") || strcmp(input.url, " ")) {
        snprintf(input.url, sizeof(input.url), "%s-downloaded", input.url);
    }

    dl(input.url, input.filename);

    free((void*)input.url);
    free((void*)input.filename);
    return 0;
}