#ifndef GLOB_H
#define GLOB_H

struct furl {
    char *url;
    char *filename;
};

void get_furl_input(struct furl *out);
void dl(const char *url, const char *filename);

#endif