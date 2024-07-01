#ifndef _MENU_H_
#define _MENU_H_

#include <ncurses.h>

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

typedef struct {
    char **options;
    int num_options;
} SubMenu;

// Declaración de submenuWin
char *submenuWin(WINDOW *parent_win, SubMenu submenu);

#endif
