#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#include "glob.h"

#define BOX_HEIGHT 3
#define BOX_WIDTH  40

void draw_box(WINDOW *win) {
    box(win, 0, 0);
    wrefresh(win);
}

// This function fills a furl struct passed by pointer.
// It stores input strings dynamically so they live after function returns.
void get_furl_input(struct furl *out) {
    char url_buf[100] = {0};
    char filename_buf[100] = {0};

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    int starty = (LINES - (BOX_HEIGHT * 2 + 1)) / 2;
    int startx = (COLS - BOX_WIDTH) / 2;

    WINDOW *box1 = newwin(BOX_HEIGHT, BOX_WIDTH, starty, startx);
    WINDOW *box2 = newwin(BOX_HEIGHT, BOX_WIDTH, starty + BOX_HEIGHT + 1, startx);

    draw_box(box1);
    draw_box(box2);

    mvprintw(starty - 1, startx, "URL:");
    mvprintw(starty + BOX_HEIGHT, startx, "Filename:");

    refresh();

    echo();

    mvwgetnstr(box1, 1, 1, url_buf, sizeof(url_buf) - 1);
    mvwgetnstr(box2, 1, 1, filename_buf, sizeof(filename_buf) - 1);

    noecho();

    delwin(box1);
    delwin(box2);
    endwin();

    // Dynamically allocate so pointers stay valid after return
    out->url = strdup(url_buf);
    out->filename = strdup(filename_buf);
}