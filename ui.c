#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "glob.h"

void get_furl_input(struct furl *out) {
    char url_buf[100] = {0};
    char filename_buf[100] = {0};

    printf("URL To download: ");
    scanf("%s", url_buf);
    printf("Filename: ");
    scanf("%s", filename_buf);

    if (strlen(url_buf) == 100) {
        printf("URL To long: Max 100");
        exit(1);
    }
    if (strlen(filename_buf) == 100) {
        printf("Filename To long: Max 100");
        exit(1);
    }
    // Dynamically allocate so pointers stay valid after return
    out->url = strdup(url_buf);
    out->filename = strdup(filename_buf);
}