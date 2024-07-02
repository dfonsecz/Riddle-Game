#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include "submenu.h"

typedef struct Menu {
    int start_x;
    const char *text;
    char shortcut;
} Menu;

typedef struct MenuBar {
    WINDOW *win;
    Menu *menus;
    int num_menus;
} MenuBar;

WINDOW *menuWin();

#endif