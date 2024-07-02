#include <ncurses.h>
#include <string.h>
#include "../include/submenu.h"

char *submenuWin(WINDOW *parent_win, SubMenu submenu) {
    int num_options = submenu.num_options;

    // Obtener parámetros de la terminal para centrar la ventana
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // Crear una nueva ventana para el submenú
    WINDOW *submenu_win = newwin(yMax / 2, xMax / 2, yMax / 4, xMax / 4);
    box(submenu_win, 0, 0);
    wrefresh(submenu_win);

    // Imprimir las opciones del submenú
    for (int i = 0; i < num_options; i++) {
        mvwprintw(submenu_win, i + 1, 1, "%s", submenu.options[i]);
    }
    wrefresh(submenu_win);

    // Activar teclado para el submenú
    keypad(submenu_win, true);

    int highlight = 0;
    int choice;
    char *selected_option = NULL;

    while (1) {
        // Resaltar la opción seleccionada
        for (int i = 0; i < num_options; i++) {
            if (i == highlight)
                wattron(submenu_win, A_STANDOUT);
            mvwprintw(submenu_win, i + 1, 1, "%s", submenu.options[i]);
            wattroff(submenu_win, A_STANDOUT);
        }
        wrefresh(submenu_win);

        choice = wgetch(submenu_win);
        switch (choice) {
            case KEY_UP:
                highlight = (highlight == 0) ? num_options - 1 : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight == num_options - 1) ? 0 : highlight + 1;
                break;
            case 10:  // Enter key
                // Guardar la opción seleccionada
                selected_option = submenu.options[highlight];
                // Limpiar y cerrar la ventana del submenú
                werase(submenu_win);
                wrefresh(submenu_win);
                delwin(submenu_win);
                return selected_option;
            default:
                break;
        }
    }
}