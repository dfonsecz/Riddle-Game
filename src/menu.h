#include <curses.h>
#include <string.h>

#ifndef _MENU_H_
#define _MENU_H_

typedef struct {
    int start_x;
    char *text;
    char trigger;
} Menu;

typedef struct {
    WINDOW *win;
    Menu *menus;
    int num_menus;
} MenuBar;

#endif