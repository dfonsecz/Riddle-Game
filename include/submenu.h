#ifndef SUBMENU_H
#define SUBMENU_H

#include <ncurses.h>

typedef struct SubMenu {
    char **options;
    int num_options;
} SubMenu;

char *submenuWin(WINDOW *parent_win, SubMenu submenu);

#endif